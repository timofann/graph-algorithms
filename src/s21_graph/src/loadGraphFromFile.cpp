#include "../include/Graph.h"

using namespace s21;

Graph Graph::loadGraphFromFile(const std::string &filename) {
  std::ifstream inf;
  std::size_t size = 0;
  std::vector<unsigned> tmp;

  inf.open(filename, std::ifstream::in);
  if (!inf.is_open()) {
    throw Graph::CantOpenFile(filename);
  }
  if (inf.eof() == true) {
    throw std::runtime_error{"Empty file"};
  }
  inf >> size;
  if (inf.fail() == true) {
    throw std::runtime_error{"Bad data on file"};
  }
  unsigned **array_num = new unsigned *[size];
  for (std::size_t i = 0; i < size; ++i) {
    tmp.clear();
    for (std::size_t j = 0; j < size; ++j) {
      if (inf.peek() == std::ifstream::traits_type::eof()) {
        Graph::clearMatrix(array_num, i);
        throw s21::Graph::WrongMatrixException("Incorrect row length in file.");
      }
      unsigned tmp_arr;
      inf >> tmp_arr;
      tmp.push_back(tmp_arr);
    }
    array_num[i] = new unsigned[tmp.size()];
    std::copy(tmp.begin(), tmp.end(), array_num[i]);
  }
  inf.close();
  Graph date(array_num, size);
  Graph::clearMatrix(array_num, size);
  return date;
}