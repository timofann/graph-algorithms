#include "../include/GraphAlgorithms.h"

namespace s21 {

	GraphAlgorithms::GraphAlgorithmsError::GraphAlgorithmsError(const std::string& arg) : std::runtime_error(arg) {}

    int GraphAlgorithms::
    validate_vertex(const Graph &graph, int startVertex) {
        if (startVertex < 1 || startVertex > (int)graph.size()) {
            throw GraphAlgorithms::GraphAlgorithmsError("\033[1;31mGraphAlgorithmsError:\033[0m Vertex for shortest path finding should be in range [1; vertices count]");
        }
        return startVertex - 1;
    }

}