#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H

#include "../s21_graph/s21_graph.h"
#include <system_error>
#include <vector>

namespace s21 {



	class GraphAlgorithms {

	public:
		struct TsmResult {
			std::vector<int> vertices;
			double distance;
		};

	private:
		GraphAlgorithms(GraphAlgorithms& other);
		GraphAlgorithms(GraphAlgorithms&& other);
		GraphAlgorithms& operator=(GraphAlgorithms& other);
		GraphAlgorithms& operator=(GraphAlgorithms&& other);
		~GraphAlgorithms();

	public:
		static std::vector<int> depthFirstSearch(Graph &graph, int startVertex);
		static std::vector<int> breadthFirstSearch(Graph &graph, int startVertex);
		static std::vector<int> getShortestPathBetweenVertices_improved(Graph &graph, int vertex1, int vertex2);
		static std::size_t getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
		static std::vector<std::vector<float>> getShortestPathsBetweenAllVertices(Graph &graph);
		static std::vector<std::vector<int>> getLeastSpanningTree(Graph &graph);
		static TsmResult solveTravelingSalesmanProblem(Graph &graph);

		struct GraphAlgorithmsError : std::runtime_error {
			explicit GraphAlgorithmsError(const std::string& arg);
		};
	};

};

#endif //GRAPHALGORITHMS_H