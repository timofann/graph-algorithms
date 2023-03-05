#include "s21_graph/s21_graph.h"
#include "s21_graph_algorithms/s21_graph_algorithms.h"
#include <iostream>
#include <vector>

int main() {

    unsigned** matrix = new unsigned*[11]{ new unsigned[11]{0, 0, 20, 21, 16, 31, 100, 12, 4, 31, 18}, //[1]: 29
                                           new unsigned[11]{0, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12}, //[0]: 29
                                           new unsigned[11]{20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13},
                                           new unsigned[11]{21, 29, 15, 0, 4, 12, 92, 12, 25, 13, 25},
                                           new unsigned[11]{16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22},
                                           new unsigned[11]{31, 40, 25, 12, 16, 0, 95, 24, 36, 3, 37},
                                           new unsigned[11]{100, 72, 81, 92, 94, 95, 0, 90, 101, 99, 84},
                                           new unsigned[11]{12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13},
                                           new unsigned[11]{4, 29, 23, 25, 20, 36, 101, 15, 0, 35, 18},
                                           new unsigned[11]{31, 41, 27, 13, 16, 3, 99, 25, 35, 0, 38},
                                           new unsigned[11]{18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0} };

    s21::Graph graph2(matrix, 11);
	std::cout << "\033[1;32mGraph is created\033[0m" << std::endl;
	for (int i = 0; i < graph2.size(); i++) {
		for (int j = 0; j < graph2.size(); j++)
			printf("%4u ", graph2[i][j]);
		std::cout << std::endl;
	}

    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    std::cout << "\033[1;32m\nGraph is created2\033[0m" << std::endl;
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.size(); j++)
            printf("%4u ", graph[i][j]);
        std::cout << std::endl;
    }


	try {

		std::cout << "\033[1;32m\ndepthFirstSearch\033[0m" << std::endl;
		std::vector<int> a = s21::GraphAlgorithms::depthFirstSearch(graph, 1);
		for (int i = 0; i < a.size(); i++)
			printf("%d ", a[i]);
		std::cout << std::endl;

		std::cout << "\033[1;32m\ndepthFirstSearch\033[0m" << std::endl;
		std::vector<int> b = s21::GraphAlgorithms::depthFirstSearch(graph, 0);
		for (int i = 0; i < b.size(); i++)
			printf("%d ", b[i]);
		std::cout << std::endl;

	} catch (s21::GraphAlgorithms::GraphAlgorithmsError &e) {
		std::cerr << e.what() << std::endl;
	}

	try {

		std::cout << "\033[1;33m\nbreadthFirstSearch\033[0m" << std::endl;
		std::vector<int> c = s21::GraphAlgorithms::breadthFirstSearch(graph, 1);
		for (int i = 0; i < c.size(); i++)
			printf("%d ", c[i]);
		std::cout << std::endl;

		std::cout << "\033[1;33m\nbreadthFirstSearch\033[0m" << std::endl;
		std::vector<int> d = s21::GraphAlgorithms::breadthFirstSearch(graph, 0);
		for (int i = 0; i < d.size(); i++)
			printf("%d ", d[i]);
		std::cout << std::endl;

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
	for (int i = 0; i < graph.size(); ++i) {
		for (int j = 0; j < graph.size(); ++j)
			std::printf("%10.2f ", g[i][j]);
		std::cout << std::endl;
	}

	std::cout << "\033[1;32m\ngetLeastSpanningTree\033[0m" << std::endl;
	std::vector<std::vector<int>> h = s21::GraphAlgorithms::getLeastSpanningTree(graph);
	for (int i = 0; i < graph.size(); ++i) {
		for (int j = 0; j < graph.size(); ++j)
			std::printf("%4d ", h[i][j]);
		std::cout << std::endl;
	}

    std::cout << "\033[1;33m\nsolveTravelingSalesmanProblem\033[0m" << std::endl;
    s21::GraphAlgorithms::TsmResult tsmr = s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph);
    for (auto city = tsmr.vertices.begin(); city < tsmr.vertices.end(); city++)
        std::printf("%4d ", *city);
    std::cout << " - distance: " << tsmr.distance << std::endl;
}
