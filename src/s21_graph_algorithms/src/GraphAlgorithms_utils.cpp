#include "../include/GraphAlgorithms.h"

namespace s21 {
	GraphAlgorithms::GraphAlgorithmsError::GraphAlgorithmsError(const std::string& arg) : std::runtime_error(arg) {}
}