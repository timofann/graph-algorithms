#include "GraphAlgorithms.h"
#include <iostream>

namespace s21 {

	GraphAlgorithms::GraphAlgorithmsError::GraphAlgorithmsError(const std::string& arg) : std::runtime_error(arg) {}

}