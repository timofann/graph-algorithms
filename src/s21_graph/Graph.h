#ifndef GRAPH_H
#define GRAPH_H

#include <string>

namespace s21 {


	class Graph {
	public:
		int vertices_cnt_;
		std::size_t** matrix_;
		Graph();
		~Graph();
	};


}; //namespace s21


#endif //GRAPH_H
