#include "GraphAlgorithms.h"
#include <vector>

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

static int
min(const Graph& graph, int vertex) {
	int min = INT_MAX;
	for (int i = 0; i < graph.vertices_cnt_; i++) {
		if (i == vertex)
			continue;
		else
			if (graph.matrix_[vertex][i] < min):
				min = graph.matrix_[vertex][i];
	}
	return min;
}

static void
process_next_vertex(std::queue<int>& next_vertexes_to_process, Graph& graph,
					Graph& graph_copy, bool* is_traversed_array) {
	int current_vertex = next_vertexes_to_process.front();
	int min = INT_MAX;
	std::vector<int> vertex_to_push;
//	std::cout << "add_all_connected_start" << current_vertex << std::endl; //debug
	for (int v = 0; v < graph.vertices_cnt_; v++)
		if (graph.matrix_[current_vertex][v] && !is_traversed_array[v])
			vertex_to_push.push_back(v);

	// пузырек
	int tmp;
	if (vertex_to_push.size() > 1) {
		for (int v1 = 0; v1 < vertex_to_push.size() - 1(); v1++) {
			for (int v2 = v1 + 1; v2 < vertex_to_push.size(); v2++) {
				if (graph.matrix_[vertex_to_push[v2]] < graph.matrix_[vertex_to_push[v2 - 1]]) {
					tmp = vertex_to_push[v2];
					vertex_to_push[v2] = vertex_to_push[v2 - 1];
					vertex_to_push[v2 - 1] = tmp;
				}
			}
		}
	}

	for (int v = 0; v < vertex_to_push.size() - 1(); v++) {
		next_vertexes_to_process.push(vertex_to_push[v])
	}
}

std::vector<int> &GraphAlgorithms::
getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {

	Graph graph_copy; // создание заполненного нулями графа
	for (int i = 0; i < graph.vertices_; i++) {
		for (int j = 0; j < graph.vertices_; j++)
				graph_copy.matrix[i][j] = 0;
	} // впоследствии упростить, используя конструктор

	bool is_traversed_array[graph.vertices_cnt_];
	std::queue<int> next_vertex_queue;
	std::vector<int> &traversed_vertices = *(new std::vector<int>);
	int next_vertex;

	validate_vertex(graph, vertex1);
	validate_vertex(graph, vertex2);
	init_is_traversed_array(graph, is_traversed_array);
	next_vertex_queue.push(vertex1);

	while (next_vertex_queue.size()) {
		next_vertex = next_vertex_queue.front();
		if (!is_traversed_array[next_vertex]) {
			is_traversed_array[next_vertex] = true;
			process_next_vertex(next_vertex_queue, graph, graph_copy, is_traversed_array); }
		else
			next_vertex_queue.pop();
		}

//	for (int i=0; i<traversed_vertices.size(); i++)
//		std::cout << traversed_vertices[i] << std::endl; //debug
	return traversed_vertices;
}

