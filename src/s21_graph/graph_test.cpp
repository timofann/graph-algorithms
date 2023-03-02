#include "s21_graph.h"
#include <iostream>

int main() {

    unsigned** matrix = new unsigned*[2]{new unsigned[2]{0, 2}, new unsigned[2]{2, 0}};
	s21::Graph graph(matrix, 2);
	std::cout << "\033[1;32mGraph is created\033[0m" << std::endl;
	for (std::size_t i = 0; i < graph.size(); i++) {
		for (std::size_t j = 0; j < graph.size(); j++) {
			std::cout << graph[i][j];
			if (j != graph.size())
				std::cout << ' ';
		}
		std::cout << std::endl;
	}

}
