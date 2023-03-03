#include "s21_graph_algorithms.h"
#include <printf.h>

int main() {

    unsigned** matrix = new unsigned*[2]{new unsigned[2]{0, 2}, new unsigned[2]{2, 0}}; // leak
	s21::Graph graph(matrix, 2);

	std::vector<int> a = s21::GraphAlgorithms::depthFirstSearch(graph, 1);
	std::cout << "\033[1;32mdepthFirstSearch\033[0m" << std::endl;
	for (int i = 0; i < a.size(); i++)
		std::cout << a[i] << std::endl;

	std::vector<int> b = s21::GraphAlgorithms::breadthFirstSearch(graph, 1);
	std::cout << "\033[1;33m\nbreadthFirstSearch\033[0m" << std::endl;
	for (int i = 0; i < b.size(); i++)
		std::cout << b[i] << std::endl;

	try {
		std::size_t c = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 2);
        std::cout << "\033[1;34m\ngetShortestPathBetweenVertices\033[0m" << std::endl;
		std::cout << c << std::endl;
	} catch (s21::GraphAlgorithms::GraphAlgorithmsError &e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		std::vector<int> d = s21::GraphAlgorithms::getShortestPathBetweenVertices_improved(graph, 1, 2);
        std::cout << "\033[1;35m\ngetShortestPathBetweenVertices_improved\033[0m" << std::endl;
		for (auto i = d.begin(); i != d.end(); ++i)
			std::cout << *i << " ";
		std::cout << std::endl;
	} catch (s21::GraphAlgorithms::GraphAlgorithmsError &e) {
		std::cerr << e.what() << std::endl;
	}

	std::vector<std::vector<float>> shortest_path = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
    std::cout << "\033[1;36m\ngetShortestPathsBetweenAllVertices\033[0m" << std::endl;
	for (int i = 0; i < graph.size(); ++i) {
		for (int j = 0; j < graph.size(); ++j)
			std::printf("%10.2f ", shortest_path[i][j]);
		std::cout << std::endl;
	}

	std::vector<std::vector<int>> tree = s21::GraphAlgorithms::getLeastSpanningTree(graph);
    std::cout << "\033[1;32m\ngetLeastSpanningTree\033[0m" << std::endl;
	for (int i = 0; i < graph.size(); ++i) {
		for (int j = 0; j < graph.size(); ++j)
			std::printf("%4d ", tree[i][j]);
		std::cout << std::endl;
	}

	try {
        s21::GraphAlgorithms::TsmResult tsm = s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph);
        std::cout << tsm.distance << std::endl;
    } catch (s21::GraphAlgorithms::GraphAlgorithmsError &e) {
		std::cerr << e.what() << std::endl;
	}

}

//c++ -std=c++17 graph_algorithms_test.cpp GraphAlgorithms_utils.cpp GraphAlgorithms_search.cpp GraphAlgorithms_shortest_path.cpp GraphAlgorithms_additional.cpp GraphAlgorithms_salesman_problem.cpp ../s21_graph/Graph.cpp

