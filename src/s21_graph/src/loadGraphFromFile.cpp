#include "../include/Graph.h"

using namespace s21;

Graph Graph::loadGraphFromFile(const std::string &filename) {
  std::ifstream inf;
  std::size_t size = 0;
  std::vector<unsigned> tmp;

  inf.open(filename, std::ifstream::in);
  if (!inf.is_open()) {
    throw std::runtime_error{"Incorrect file path"};
  }
  if (inf.eof() == true) {
    throw std::runtime_error{"Empty file"};
  }
  inf >> size;
  if (inf.fail() == true || size < 2) {
    throw std::runtime_error{"Bad data on file"};
  }
  unsigned **array_num = new unsigned *[size];
  for (size_t i = 0; i < size; ++i) {
    tmp.clear();
    for (size_t j = 0; j < size; ++j) {
      if (inf.peek() == std::ifstream::traits_type::eof()) {
        throw std::runtime_error{"Incorrect file"};
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
  Graph clearMatrix(array_num, size);
  return date;
}