#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H

#include "../s21_graph/s21_graph.h"
#include <system_error>

namespace s21 {

	class GraphAlgorithms {
	private:
		GraphAlgorithms(GraphAlgorithms& other);
		GraphAlgorithms(GraphAlgorithms&& other);
		GraphAlgorithms& operator=(GraphAlgorithms& other);
		GraphAlgorithms& operator=(GraphAlgorithms&& other);
		~GraphAlgorithms();

	public:
		static std::vector<int> depthFirstSearch(Graph &graph, int startVertex);
		static std::vector<int> breadthFirstSearch(Graph &graph, int startVertex);
		static std::vector<int> getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);

		struct GraphAlgorithmsError : std::runtime_error {
			explicit GraphAlgorithmsError(const std::string& arg);
		};
	};

};

#endif //GRAPHALGORITHMS_H
