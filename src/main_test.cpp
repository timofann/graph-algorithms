#include "s21_graph/s21_graph.h"
#include "s21_graph_algorithms/s21_graph_algorithms.h"
#include <iostream>
#include <vector>

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

	try {

		std::cout << "\033[1;32m\ndepthFirstSearch\033[0m" << std::endl;
		std::vector<int> a = s21::GraphAlgorithms::depthFirstSearch(graph, 1);
		for (int i = 0; i < a.size(); i++)
			std::cout << a[i] << std::endl;

		std::cout << "\033[1;32m\ndepthFirstSearch\033[0m" << std::endl;
		std::vector<int> b = s21::GraphAlgorithms::depthFirstSearch(graph, 0);
		for (int i = 0; i < b.size(); i++)
			std::cout << b[i] << std::endl;

	} catch (s21::GraphAlgorithms::GraphAlgorithmsError &e) {
		std::cerr << e.what() << std::endl;
	}

	try {

		std::cout << "\033[1;33m\nbreadthFirstSearch\033[0m" << std::endl;
		std::vector<int> c = s21::GraphAlgorithms::breadthFirstSearch(graph, 1);
		for (int i = 0; i < c.size(); i++)
			std::cout << c[i] << std::endl;

		std::cout << "\033[1;33m\nbreadthFirstSearch\033[0m" << std::endl;
		std::vector<int> d = s21::GraphAlgorithms::breadthFirstSearch(graph, 0);
		for (int i = 0; i < d.size(); i++)
			std::cout << d[i] << std::endl;

	} catch (s21::GraphAlgorithms::GraphAlgorithmsError &e) {
		std::cerr << e.what() << std::endl;
	}

	try {

		std::cout << "\033[1;34m\ngetShortestPathBetweenVertices_improved\033[0m" << std::endl;
		std::vector<int> vec1 = s21::GraphAlgorithms::getShortestPathBetweenVertices_improved(graph, 1, 2);
		for (int i = 0; i < vec1.size(); i++)
			std::cout << vec1[i] << " ";
		std::cout << std::endl;

		std::cout << "\033[1;34m\ngetShortestPathBetweenVertices_improved\033[0m" << std::endl;
		std::vector<int> vec2 = s21::GraphAlgorithms::getShortestPathBetweenVertices_improved(graph, 0, 2);
		for (int i = 0; i < vec2.size(); i++)
			std::cout << vec2[i] << " ";
		std::cout << std::endl;

	} catch (s21::GraphAlgorithms::GraphAlgorithmsError &e) {
		std::cerr << e.what() << std::endl;
	}

	try {

		std::cout << "\033[1;35m\ngetShortestPathBetweenVertices\033[0m" << std::endl;
		std::size_t e = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 2);
		std::cout << e << std::endl;

		std::cout << "\033[1;35m\ngetShortestPathBetweenVertices\033[0m" << std::endl;
		std::size_t f = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 0, 2);
		std::cout << f << std::endl;

	} catch (s21::GraphAlgorithms::GraphAlgorithmsError &e) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << "\033[1;36m\ngetShortestPathBetweenAllVertices\033[0m" << std::endl;
	std::vector<std::vector<float>> g = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
	for (int i = 0; i < graph.vertices_cnt_; ++i) {
		for (int j = 0; j < graph.vertices_cnt_; ++j)
			std::printf("%10.2f ", g[i][j]);
		std::cout << std::endl;
	}
}
