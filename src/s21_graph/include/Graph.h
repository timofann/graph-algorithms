#ifndef GRAPH_H
#define GRAPH_H

#include <charconv>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace s21 {

class Graph {
public:
  explicit Graph(unsigned **matrix, std::size_t size);

  Graph(const Graph &other);
  Graph(Graph &&other);

  ~Graph(); // правило пяти

  Graph &operator=(const Graph &other);
  Graph &operator=(Graph &&other);

  static Graph loadGraphFromFile(const std::string &filename);

  void exportGraphToDot(const std::string &filename) const;

  [[nodiscard]] std::size_t size() const noexcept;
  std::string generateDotString() const noexcept;

  //        class WrongMatrixException : public std::exception
  //        {
  //        public:
  //            [[nodiscard]] const char *what() const noexcept override;
  //        };

  struct GraphException : std::runtime_error {
    explicit GraphException(const std::string &arg);
  };

  struct WrongMatrixException : GraphException {
    explicit WrongMatrixException(const std::string &arg = "Wrong matrix.");
  };

  struct TooLargeGraph : GraphException {
    explicit TooLargeGraph();
  };

  struct CantOpenFile : GraphException {
    explicit CantOpenFile(const std::string &arg);
  };

  const unsigned *operator[](std::size_t) const;

private:
  Graph();

  unsigned **a_matrix_; // google style названия приватных переменных должны
                        // заканчиваться знаком подчеркивания _
  std::size_t a_matrix_size_;
  bool weighted_;

  void setMatrix(unsigned **matrix, std::size_t size);

  /*loadGraphFromFile*/
  static void clearMatrix(unsigned **matrix, std::size_t rows) noexcept;
  /*loadGraphFromFile*/

  static void checkMatrix(unsigned int *const *matrix, std::size_t size);

  static void throwCantOpenFile(const std::string &filename);
};

} // namespace s21

std::ostream &operator<<(std::ostream &o, const s21::Graph &a);

#endif
