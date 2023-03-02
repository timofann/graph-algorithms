#include "Graph.h"
#include <filesystem>

Graph::Graph() : a_matrix(nullptr), a_matrix_size(0), weighted(false)
{
}

Graph::Graph(unsigned **matrix, size_t size) :
		a_matrix(nullptr), a_matrix_size(0), weighted(false)
{
	set_a_matrix(matrix, size);
}

Graph::~Graph()
{
	for (unsigned i = 0; i < a_matrix_size; ++i)
		delete[] a_matrix[i];
	delete[] a_matrix;
}

Graph::Graph(const Graph &other) :
a_matrix(nullptr), a_matrix_size(0), weighted(false)
{
	set_a_matrix(other.a_matrix, other.a_matrix_size);
}

Graph &Graph::operator=(const Graph &other)
{
	if (&other != this)
		set_a_matrix(other.a_matrix, other.a_matrix_size);
	return *this;
}

size_t Graph::size() const
{
	return this->a_matrix_size;
}

void Graph::set_a_matrix(unsigned **matrix, size_t size)
{
	check_matrix(matrix, size);

	for (unsigned i = 0; i < a_matrix_size; ++i)
		delete[] a_matrix[i];
	delete[] this->a_matrix;
	a_matrix_size = size;
	a_matrix = new unsigned *[size];
	for (unsigned i = 0; i < size; ++i)
	{
		a_matrix[i] = new unsigned[size];
		for (unsigned j = 0; j < size; ++j)
		{
			a_matrix[i][j] = matrix[i][j];
			if (!weighted && a_matrix[i][j] > 1)
			{
				weighted = true;
			}
		}
	}
}

void dfs(unsigned start, unsigned *const *matrix, std::vector<bool> *used,
		 size_t size)
{

	std::stack<unsigned> stack;

	stack.push(start);
	while (!stack.empty())
	{
		auto current = stack.top();
		stack.pop();
		(*used)[current] = true;
		for (unsigned i = 0; i < size; ++i)
		{
			if (matrix[current][i] != 0 && !(*used)[i])
			{
				stack.push(i);
			}
		}
	}
}

std::string *generate_node_names(unsigned count)
{
	auto names = new std::string[count];
	int base_len = -2;
	char char_idx = 'a';
	std::string s;
	for (unsigned i = 0; i < count; ++i)
	{
		if (i % 26 == 0)
		{
			char_idx = 'a';
			base_len++;
		}
		char c = char_idx++;
		if (i > 25)
		{
			s = {c, char(base_len + 48)};
		} else
		{
			s = {c};
		}

		names[i] = s;
	}
	return names;
}

void Graph::check_matrix(unsigned *const *matrix, size_t size)
{
	std::vector<bool> used;

	int res = 0;
	used.push_back(false);

	for (unsigned i = 0; i < size; ++i)
	{
		unsigned cons = 0;

		for (unsigned j = 0; j < size; ++j)
		{
			if (matrix[i][j] != matrix[j][i])
				throw WrongMatrixException();
			cons += matrix[i][j];
		}
		if (cons == 0)
		{
			throw WrongMatrixException();
		}
		if (!used[i])
		{
			dfs(i, matrix, &used, size);
			res++;
		}
		if (res > 1)
		{
			throw WrongMatrixException();
		}

	}
}

void Graph::loadGraphFromFile(const std::string &filename)
{
	std::cout << filename;
}

void Graph::exportGraphToDot(const std::string &filename)
{
	std::ofstream ofs;

	std::filesystem::path filepath = filename;
	if (filepath.extension() != ".gv" && filepath.extension() != ".dot")
	{
		throw std::invalid_argument("Wrong extension of file");
	}

	ofs.open(filename);
	if (! ofs.is_open())
	{
		std::cerr << "Can't open file: " << filename << std::endl;
	}
	else
	{
		ofs << this;
		ofs.close();
	}
}

std::string Graph::generateDotString()
{
	std::stringstream res;
	std::string pp_ident = "    ";
	auto nn = generate_node_names(this->a_matrix_size);
	unsigned current_iter = 0;

	res << "graph {\n";
	for (unsigned i = 0; i < this->a_matrix_size; ++i)
	{
		for (unsigned j = i; j < this->a_matrix_size; ++j)
		{
			if (this->a_matrix[i][j] == 0)
			{
				continue;
			}
			res << pp_ident << nn[i] << " -- " << nn[j];
			if (weighted) {
				res << " [weight=" << a_matrix[i][j] << "]";
			}
			res << "\n";
			current_iter++;
		}
	}
	res << "}\n";
	delete []nn;
	return res.str();
}

std::ostream &operator<<(std::ostream &os, Graph *b)
{
	os << b->generateDotString();
	return (os);
}

const char *Graph::WrongMatrixException::what() const noexcept
{
	return "wrong matrix";
}