#ifndef S21_GRAPH_H
#define S21_GRAPH_H
// если библиотека будет содержать какие-либо функции помимо методов класса Graph,
// вынести класс в отдельный заголовочный Graph.h
// или вообще все переделать как угодно)))

#include <string>

namespace s21 {

	class Graph {
	public://private
		size_t vertices_cnt_;
		size_t** matrix_; //  поменять тип данных? использовать шаблонные типы? s21_matrix?

	public:
		Graph();
//		Graph(std::string &filename);
//		Graph(Graph &other);
//		Graph(Graph &&other);
//		~Graph();
//
//		Graph &operator=(Graph &other);
//		Graph &operator=(Graph &&other);

 		Graph& loadGraphFromFile(std::string filename);
		void exportGraphToDot(std::string filename);
	};

};

#endif //S21_GRAPH_H
