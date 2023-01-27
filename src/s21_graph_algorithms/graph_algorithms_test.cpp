#include "../s21_graph/s21_graph.h"
#include "s21_graph_algorithms.h"
#include <iostream>
#include <vector>

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

	std::vector<int> vec = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 2);
	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << " ";
	std::cout << std::endl;

}

//c++ -std=c++17 graph_algorithms_test.cpp GraphAlgorithms_utils.cpp GraphAlgorithms_search.cpp GraphAlgorithms_shortest_path.cpp ../s21_graph/Graph.cpp

