#include "GraphAlgorithms.h"
#include <vector>
#include <queue>
#include <iostream>


using namespace s21;

static void //дублирование кода search.cpp
init_is_traversed_array(Graph& graph, bool* is_traversed_array) {
	for (int i = 0; i < graph.vertices_cnt_; i++)
		is_traversed_array[i] = false;
}

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

std::vector<int> &GraphAlgorithms::
getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {

	bool is_traversed_array[graph.vertices_cnt_];
	int shortest_distance[graph.vertices_cnt_](INT_MAX);
	int last_vertex_on_shortest_path[graph.vertices_cnt_];
	std::vector<int>& shortest_path = *(new std::vector<int>);
	std::queue<int> next_vertex_queue;
	std::vector<int> vertices_to_add_in_queue;
	int next_vertex;
	int tmp;

	validate_vertex(graph, vertex1);
	validate_vertex(graph, vertex2);
	init_is_traversed_array(graph, is_traversed_array);
	next_vertex_queue.push(vertex1);
	shortest_distance[vertex1] = 0;

	while (next_vertex_queue.size()) {
		next_vertex = next_vertex_queue.front();
		if (!is_traversed_array[next_vertex]) {
			is_traversed_array[next_vertex] = true;

			for (int v = 0; v < graph.vertices_cnt_; v++) {
				if (!is_traversed_array[v] && graph.matrix_[next_vertex][v]
					&& graph.matrix_[next_vertex][v] + shortest_distance[next_vertex] < shortest_distance[v]) {
					last_vertex_on_shortest_path[v] = next_vertex;
					shortest_distance[v] = graph.matrix_[next_vertex][v] + shortest_distance[next_vertex];
				}
			}

			vertices_to_add_in_queue.clear();
			for (int v = 0; v < graph.vertices_cnt_; v++) {
				if (!is_traversed_array[v] && graph.matrix_[next_vertex][v])
					vertices_to_add_in_queue.push_back(v);
			}
			if (vertices_to_add_in_queue.size() > 1) {
				for (int i = vertices_to_add_in_queue.size() - 1; i > 0; i--) {
					for (int j = 0; j < i; j++) {
						if (graph.matrix_[next_vertex][vertices_to_add_in_queue[j]] < graph.matrix_[next_vertex][vertices_to_add_in_queue[j + 1]]) {
							tmp = vertices_to_add_in_queue[j];
							vertices_to_add_in_queue[j] = vertices_to_add_in_queue[j + 1];
							vertices_to_add_in_queue[j + 1] = tmp;
						}
					}
					next_vertex_queue.push(vertices_to_add_in_queue[i]);
				}
			}
			if (vertices_to_add_in_queue.size() > 0)
				next_vertex_queue.push(vertices_to_add_in_queue[0]);
		}
		next_vertex_queue.pop();
	}

	shortest_path.push_back(vertex2);
	next_vertex = last_vertex_on_shortest_path[vertex2];
	while (next_vertex != 0) {
		shortest_path.push_back(last_vertex_on_shortest_path[next_vertex]);
		next_vertex = last_vertex_on_shortest_path[next_vertex];
	}
	for (int i = 0; i < (shortest_path.size() - 1) / 2; i++) {
		tmp = shortest_path[i];
		shortest_path[i] = shortest_path[shortest_path.size() - 1 - i];
		shortest_path[shortest_path.size() - 1 - i] = shortest_path[i];
	}

	for (int i = 0; i < shortest_path.size() - 1; i++) //debug
		std::cout << shortest_path[i] << " ";
	std::cout << std::endl;

	return shortest_path;
}

