#include "../include/Graph.h"
#include <climits>
#include <filesystem>

using namespace s21;

Graph::Graph(unsigned **matrix, std::size_t size)
    : a_matrix_(nullptr), a_matrix_size_(0), weighted_(false) {
  setMatrix(matrix, size);
}

Graph::~Graph() { Graph::clearMatrix(a_matrix_, a_matrix_size_); }

void Graph::clearMatrix(unsigned **matrix, std::size_t rows) noexcept {
  if (matrix != nullptr) {
    for (std::size_t i = 0; i < rows; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
}

Graph::Graph(const Graph &other)
    : a_matrix_(nullptr), a_matrix_size_(0), weighted_(false) {
  *this = other;
}

Graph::Graph(Graph &&other)
    : a_matrix_(nullptr), a_matrix_size_(0), weighted_(false) {
  *this = std::move(other);
}

Graph &Graph::operator=(Graph &&other) {
  if (other.a_matrix_ == nullptr || other.a_matrix_size_ == 0) {
    throw Graph::WrongMatrixException(
        "You are trying to move Graph that has already moved.");
  }
  if (this != &other) {
    Graph::clearMatrix(a_matrix_, a_matrix_size_);
    a_matrix_ = other.a_matrix_;
    a_matrix_size_ = other.a_matrix_size_;
    other.a_matrix_ = nullptr;
    other.a_matrix_size_ = 0;
  }
  return *this;
}

Graph &Graph::operator=(const Graph &other) {
  if (other.a_matrix_ == nullptr || other.a_matrix_size_ == 0) {
    throw Graph::WrongMatrixException(
        "You are trying to copy Graph that has been moved.");
  }
  if (&other != this)
    setMatrix(other.a_matrix_, other.a_matrix_size_);
  return *this;
}

std::size_t Graph::size() const noexcept { return this->a_matrix_size_; }

void Graph::setMatrix(unsigned **matrix, std::size_t size) {
  checkMatrix(matrix, size);

  for (unsigned i = 0; i < a_matrix_size_; ++i)
    delete[] a_matrix_[i];
  delete[] this->a_matrix_;
  a_matrix_size_ = size;
  a_matrix_ = new unsigned *[size];
  for (unsigned i = 0; i < size; ++i) {
    a_matrix_[i] = new unsigned[size];
    for (unsigned j = 0; j < size; ++j) {
      a_matrix_[i][j] = matrix[i][j];
      if (!weighted_ && a_matrix_[i][j] > 1) {
        weighted_ = true;
      }
    }
  }
}

void dfs(unsigned start, unsigned *const *matrix, std::vector<bool> *used,
         std::size_t size) {

  std::stack<unsigned> stack;

  stack.push(start);
  while (!stack.empty()) {
    auto current = stack.top();
    stack.pop();
    (*used)[current] = true;
    for (unsigned i = 0; i < size; ++i) {
      if (matrix[current][i] != 0 && !(*used)[i]) {
        stack.push(i);
      }
    }
  }
}

std::string *generateNodeNames(unsigned count) noexcept {
  auto names = new std::string[count];
  int base_len = -2;
  char char_idx = 'a';
  std::string s;
  for (unsigned i = 0; i < count; ++i) {
    if (i % 26 == 0) {
      char_idx = 'a';
      base_len++;
    }
    char c = char_idx++;
    if (i > 25) {
      s = {c, char(base_len + 48)};
    } else {
      s = {c};
    }

    names[i] = s;
  }
  return names;
}

void Graph::checkMatrix(unsigned *const *matrix, std::size_t size) {
  if (matrix == nullptr) {
    throw Graph::WrongMatrixException(
        "Can't set matrix with NULL matrix pointer.");
  }
  if (size < 2) {
    throw Graph::WrongMatrixException("Can't set matrix with no edges.");
  }
  if (size >= INT32_MAX) {
    throw Graph::TooLargeGraph();
  }

  std::vector<bool> used;

  int res = 0;
  used.push_back(false);

  for (unsigned i = 0; i < size; ++i) {
    unsigned cons = 0;

    for (unsigned j = 0; j < size; ++j) {
      if (matrix[i][j] != matrix[j][i])
        throw WrongMatrixException("Directed graphs are not supported.");
      cons += matrix[i][j];
    }
    if (cons == 0) {
      throw WrongMatrixException();
    }
    if (!used[i]) {
      dfs(i, matrix, &used, size);
      res++;
    }
    if (res > 1) {
      throw WrongMatrixException("Graph is not connected.");
    }
  }
}

void Graph::exportGraphToDot(const std::string &filename) const {
  std::ofstream ofs;

  std::filesystem::path filepath = filename;
  if (filepath.extension() != ".gv" && filepath.extension() != ".dot") {
    throw std::invalid_argument("Wrong extension of file");
  }

  ofs.open(filename);
  if (!ofs.is_open()) {
    throw Graph::CantOpenFile(filename);
  } else {
    ofs << *this;
    ofs.close();
  }
}

std::string Graph::generateDotString() const noexcept {
  std::stringstream res;
  std::string pp_ident = "    ";
  auto nn = generateNodeNames(this->a_matrix_size_);
  unsigned current_iter = 0;

  res << "graph {\n";
  for (unsigned i = 0; i < this->a_matrix_size_; ++i) {
    for (unsigned j = i; j < this->a_matrix_size_; ++j) {
      if (this->a_matrix_[i][j] == 0) {
        continue;
      }
      res << pp_ident << nn[i] << " -- " << nn[j];
      if (weighted_) {
        res << " [weight=" << a_matrix_[i][j] << "]";
      }
      res << "\n";
      current_iter++;
    }
  }
  res << "}\n";
  delete[] nn;
  return res.str();
}

std::ostream &operator<<(std::ostream &os, const Graph &b) {
  os << b.generateDotString();
  return (os);
}

const unsigned *Graph::operator[](std::size_t row) const {
  return this->a_matrix_[row];
}

Graph::GraphException::GraphException(const std::string &arg)
    : std::runtime_error(arg) {}
Graph::WrongMatrixException::WrongMatrixException(const std::string &arg)
    : Graph::GraphException(arg) {}
Graph::TooLargeGraph::TooLargeGraph()
    : Graph::GraphException(
          "Number of vertices should be less. Can't set large graph.") {}
Graph::CantOpenFile::CantOpenFile(const std::string &filename)
    : Graph::GraphException("Can't open file " + filename) {}