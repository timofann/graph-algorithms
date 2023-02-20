#include "../s21_graph/s21_graph.h"
#include "s21_graph_algorithms.h"
#include <iostream>
#include <vector>
#include <printf.h>

int main() {

	s21::Graph graph;

//	std::vector<int> a = s21::GraphAlgorithms::depthFirstSearch(graph, 0);
//	std::cout << "\033[1;32mdepthFirstSearch\033[0m" << std::endl;
//	for (int i = 0; i < a.size(); i++)
//		std::cout << a[i] << std::endl;
//
//	std::vector<int> b = s21::GraphAlgorithms::breadthFirstSearch(graph, 0);
//	std::cout << "\033[1;33m\nbreadthFirstSearch\033[0m" << std::endl;
//	for (int i = 0; i < b.size(); i++)
//		std::cout << b[i] << std::endl;

//	try {
//		std::size_t c = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 2);
//		std::cout << c << std::endl;
//	} catch (s21::GraphAlgorithms::GraphAlgorithmsError &e) {
//		std::cerr << e.what() << std::endl;
//	}

//	try {
//		std::vector<int> d = s21::GraphAlgorithms::getShortestPathBetweenVertices_improved(graph, 1, 2);
//		for (auto i = d.begin(); i != d.end(); ++i)
//			std::cout << *i << " ";
//		std::cout << std::endl;
//	} catch (s21::GraphAlgorithms::GraphAlgorithmsError &e) {
//		std::cerr << e.what() << std::endl;
//	}

//	std::vector<std::vector<float>> shortest_path = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
//	for (int i = 0; i < graph.vertices_cnt_; ++i) {
//		for (int j = 0; j < graph.vertices_cnt_; ++j)
//			std::printf("%10.2f ", shortest_path[i][j]);
//		std::cout << std::endl;
//	}

	std::vector<std::vector<int>> tree = s21::GraphAlgorithms::getLeastSpanningTree(graph);
	for (int i = 0; i < graph.vertices_cnt_; ++i) {
		for (int j = 0; j < graph.vertices_cnt_; ++j)
			std::printf("%4d ", tree[i][j]);
		std::cout << std::endl;
	}

}

//c++ -std=c++17 graph_algorithms_test.cpp GraphAlgorithms_utils.cpp GraphAlgorithms_search.cpp GraphAlgorithms_shortest_path.cpp GraphAlgorithms_additional.cpp ../s21_graph/Graph.cpp

