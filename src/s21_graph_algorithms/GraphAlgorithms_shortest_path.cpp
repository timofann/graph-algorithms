#include "GraphAlgorithms.h"
#include <vector>
#include <queue>
#include <iostream>


using namespace s21;

//static void //дублирование кода search.cpp
//init_is_traversed_array(Graph& graph, bool* is_traversed_array) {
//	for (int i = 0; i < graph.vertices_cnt_; i++)
//		is_traversed_array[i] = false;
//}

static void //дублирование кода search.cpp
validate_vertex(Graph &graph, int startVertex) { // todo: изменить индексацию с нуля на индексацию с единицы
	if (startVertex < 0 || startVertex >= graph.vertices_cnt_)
		throw GraphAlgorithms::GraphAlgorithmsError("Start vertex for DFS should be in range of graph size");
}

//static int
//closest_untraversed_vertex(const Graph& graph, int vertex, bool* is_traversed_array) {
//	int min = INT_MAX;
//	int min_vertex =
//	for (int i = 0; i < graph.vertices_cnt_; i++) {
//		if (!is_traversed_array[i] && graph.matrix_[vertex][i] && graph.matrix_[vertex][i] < min)
//			min = graph.matrix_[vertex][i];
//	}
//	return min;
//}

struct vertex{
	// номер вершины
	int vertex_nbr;
	// минимальная дистанция от стартовой точки до этой вершины
	int distance_to_vertex;
};

int cmp(const void *x, const void *y) {
	const int arg1 = static_cast<const vertex*>(x)->distance_to_vertex;
	const int arg2 = static_cast<const vertex*>(y)->distance_to_vertex;
	if (arg1 < arg2) return -1;
	return 1;
}

std::vector<int> &GraphAlgorithms::
getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {

	std::vector<bool> is_traversed_array(graph.vertices_cnt_, false);
	// сначала минимальные расстояния от предыдущих посещенных вершин максимальны, наша задача найти минимумы
	// номера вершин откуда пришли заполнить можно чем угодно, они должны быть перезаписаны в соответствии с минимальным расстоянием
	std::vector<vertex> shortest_distance(graph.vertices_cnt_, vertex{INT_MAX, INT_MAX});
	std::vector<int>& shortest_path = *(new std::vector<int>);
	std::queue<int> next_vertex_queue;
	std::vector<vertex> vertices_to_add_in_queue;
	int next_vertex;

	validate_vertex(graph, vertex1);
	validate_vertex(graph, vertex2);
	next_vertex_queue.push(vertex1);
	shortest_distance[vertex1] = vertex{0, 0}; // задаем номер вершины откуда пришли и дистанцию от нее для стартовой вершины

	while (next_vertex_queue.size()) {
		next_vertex = next_vertex_queue.front();
		if (!is_traversed_array[next_vertex]) {
			is_traversed_array[next_vertex] = true;

			for (int v = 0; v < graph.vertices_cnt_; v++) {
				if (!is_traversed_array[v] && graph.matrix_[next_vertex][v]
					&& graph.matrix_[next_vertex][v] + shortest_distance[next_vertex].distance_to_vertex < shortest_distance[v].distance_to_vertex) {
					shortest_distance[v] = {next_vertex, graph.matrix_[next_vertex][v] + shortest_distance[next_vertex].distance_to_vertex};
				}
			}

			vertices_to_add_in_queue.clear();
			for (int v = 0; v < graph.vertices_cnt_; v++) {
				if (!is_traversed_array[v] && graph.matrix_[next_vertex][v])
					vertices_to_add_in_queue.push_back(vertex{v, graph.matrix_[next_vertex][v]});
			}
			std::qsort(vertices_to_add_in_queue.data(),
					   vertices_to_add_in_queue.size(),
					   sizeof(vertex), cmp);
			for (int v = 0; v < graph.vertices_cnt_; v++)
				next_vertex_queue.push(vertices_to_add_in_queue[v].vertex_nbr);
		}
		next_vertex_queue.pop();
	}

	shortest_path.push_back(vertex2);
	next_vertex = shortest_distance[vertex2].vertex_nbr;
	while (next_vertex != 0) {
		shortest_path.push_back(shortest_distance[next_vertex].vertex_nbr);
		next_vertex = shortest_distance[next_vertex].vertex_nbr;;
	}
	std::reverse(shortest_path.begin(), shortest_path.end());

	for (int i = 0; i < shortest_path.size(); i++) //debug
		std::cout << shortest_path[i] << " ";
	std::cout << std::endl;

	return shortest_path;
}


//std::vector<int> &GraphAlgorithms::
//getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {
//
//	std::vector<bool> is_traversed_array(graph.vertices_cnt_, false);
//	std::vector<int> shortest_distance(graph.vertices_cnt_, INT_MAX);
//	std::vector<int> last_vertex_on_shortest_path(graph.vertices_cnt_, INT_MAX);
//	std::vector<int>& shortest_path = *(new std::vector<int>);
//	std::queue<int> next_vertex_queue;
//	std::vector<int> vertices_to_add_in_queue;
//	int next_vertex;
//	int tmp;
//
//	validate_vertex(graph, vertex1);
//	validate_vertex(graph, vertex2);
////	init_is_traversed_array(graph, is_traversed_array);
//	next_vertex_queue.push(vertex1);
//	shortest_distance[vertex1] = 0;
//	last_vertex_on_shortest_path[vertex1] = 0;
//
//	while (next_vertex_queue.size()) {
//		next_vertex = next_vertex_queue.front();
//		if (!is_traversed_array[next_vertex]) {
//			is_traversed_array[next_vertex] = true;
//
//			for (int v = 0; v < graph.vertices_cnt_; v++) {
//				if (!is_traversed_array[v] && graph.matrix_[next_vertex][v]
//					&& graph.matrix_[next_vertex][v] + shortest_distance[next_vertex] < shortest_distance[v]) {
//					last_vertex_on_shortest_path[v] = next_vertex;
//					shortest_distance[v] = graph.matrix_[next_vertex][v] + shortest_distance[next_vertex];
//				}
//			}
//
//			vertices_to_add_in_queue.clear();
//			for (int v = 0; v < graph.vertices_cnt_; v++) {
//				if (!is_traversed_array[v] && graph.matrix_[next_vertex][v])
//					vertices_to_add_in_queue.push_back(v);
//			}
//			if (vertices_to_add_in_queue.size() > 1) {
//				for (int i = vertices_to_add_in_queue.size() - 1; i > 0; i--) {
//					for (int j = 0; j < i; j++) {
//						if (graph.matrix_[next_vertex][vertices_to_add_in_queue[j]] < graph.matrix_[next_vertex][vertices_to_add_in_queue[j + 1]]) {
//							tmp = vertices_to_add_in_queue[j];
//							vertices_to_add_in_queue[j] = vertices_to_add_in_queue[j + 1];
//							vertices_to_add_in_queue[j + 1] = tmp;
//						}
//					}
//					next_vertex_queue.push(vertices_to_add_in_queue[i]);
//				}
//			}
//			if (vertices_to_add_in_queue.size() > 0)
//				next_vertex_queue.push(vertices_to_add_in_queue[0]);
//		}
//		next_vertex_queue.pop();
//	}
//
//	shortest_path.push_back(vertex2);
//	next_vertex = last_vertex_on_shortest_path[vertex2];
//	while (next_vertex != 0) {
//		shortest_path.push_back(last_vertex_on_shortest_path[next_vertex]);
//		next_vertex = last_vertex_on_shortest_path[next_vertex];
//	}
//	std::reverse(shortest_path.begin(), shortest_path.end());
//
//	for (int i = 0; i < shortest_path.size() - 1; i++) //debug
//		std::cout << shortest_path[i] << " ";
//	std::cout << std::endl;
//
//	return shortest_path;
//}

