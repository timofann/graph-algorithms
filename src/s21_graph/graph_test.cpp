#include "s21_graph.h"
#include <iostream>

int main() {

	s21::Graph graph;
	std::cout << "\033[1;32mGraph is created\033[0m" << std::endl;
	for (int i = 0; i < graph.vertices_cnt_; i++) {
		for (int j = 0; j < graph.vertices_cnt_; j++) {
			std::cout << graph.matrix_[i][j];
			if (j != graph.vertices_cnt_)
				std::cout << ' ';
		}
		std::cout << std::endl;
	}

}

// c++ -std=c++17 graph_test.cpp Graph.cpp
// or
// c++ -std=c++17 graph_test.cpp s21_graph.a