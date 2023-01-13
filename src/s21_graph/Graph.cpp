#include "s21_graph.h"

using namespace s21;

Graph::Graph() : vertices_cnt_(11) {
	this->matrix_ = (size_t**)malloc(11 * sizeof(size_t *));
//	for(size_t i; i != 11; i++) {
//		this->matrix_[i] = (size_t*)malloc(11 * sizeof(size_t));
//		for(size_t j; j!=11; j++) {
//			this->matrix_[i][j] = 0;
//		}
//	}
	// тут я реализую заполнение по примеру из materials пока что, а сама буду работать над алгоритмом
}


Graph& Graph::loadGraphFromFile(std::string filename) {
	Graph *g = new Graph();
	return *g;  //  это временно, надо все переделать
}

void Graph::exportGraphToDot(std::string filename) {}

