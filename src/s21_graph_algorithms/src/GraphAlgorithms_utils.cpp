#include "../include/GraphAlgorithms.h"

namespace s21 {

	GraphAlgorithms::GraphAlgorithmsError::GraphAlgorithmsError(const std::string& arg) : std::runtime_error(arg) {}
    GraphAlgorithms::VertexIsOutOfRange::VertexIsOutOfRange(const std::string &arg) : GraphAlgorithms::GraphAlgorithmsError(arg) {}
    GraphAlgorithms::NoSolution::NoSolution(const std::string &arg) : GraphAlgorithms::GraphAlgorithmsError(arg) {}

}