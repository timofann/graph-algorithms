#include "GraphAlgorithms.h"
#include <stack>
#include <queue>
#include <iostream>

using namespace s21;

static int
validate_vertex(Graph &graph, int startVertex) {
	if (startVertex < 1 || startVertex > graph.vertices_cnt_) {
		throw GraphAlgorithms::GraphAlgorithmsError("\033[1;31mGraphAlgorithmsError:\033[0m Start vertex for search algorithm should be in range [1; vertices count]");
	}
	return startVertex - 1;
}

static void
process_next_vertex_bfs(std::queue<int>& next_vertexes_to_process, Graph& graph,
						const std::vector<bool>& is_traversed_array) {
	int current_vertex = next_vertexes_to_process.front();
//	std::cout << "add_all_connected_start" << current_vertex << std::endl; //debug
	for (int v = 0; v < graph.vertices_cnt_; v++) {
		if (graph.matrix_[current_vertex][v] && !is_traversed_array[v]) {
			next_vertexes_to_process.push(v);
//			is_traversed_array[v] = 1;
//			std::cout << v << std::endl; //debug
		}
	}
}

static void
process_next_vertex_dfs(std::stack<int>& next_vertexes_stack, Graph& graph, // todo:заменить дублирующиеся функции на шаблонные
						const std::vector<bool>& is_traversed_array) {
	int current_vertex = next_vertexes_stack.top();
//	std::cout << "process_next_vertex_dfs" << current_vertex << std::endl; //debug
	for (int v = graph.vertices_cnt_ -1; v >= 0; v--)
		if (graph.matrix_[current_vertex][v] && !is_traversed_array[v])
			next_vertexes_stack.push(v);
}

std::vector<int> GraphAlgorithms::
breadthFirstSearch(Graph &graph, int startVertex) {

	std::vector<bool> is_traversed_array(graph.vertices_cnt_, false);
	std::queue<int> next_vertex_queue;
	std::vector<int> traversed_vertices;
	int next_vertex;

	startVertex = validate_vertex(graph, startVertex);
	next_vertex_queue.push(startVertex);

	while (next_vertex_queue.size()) {
		next_vertex = next_vertex_queue.front();
//		std::cout << next_vertex << std::endl; //debug
		if (!is_traversed_array[next_vertex]) {
			is_traversed_array[next_vertex] = true;
			traversed_vertices.push_back(next_vertex + 1);
			process_next_vertex_bfs(next_vertex_queue, graph, is_traversed_array); }
		else
			next_vertex_queue.pop();
	}

//	for (int i=0; i<traversed_vertices.size(); i++)
//		std::cout << traversed_vertices[i] << std::endl; //debug
	return traversed_vertices;
}

std::vector<int> GraphAlgorithms::
depthFirstSearch(Graph &graph, int startVertex) {

	std::vector<bool> is_traversed_array(graph.vertices_cnt_, false);
	std::stack<int> next_vertex_stack;
	std::vector<int> traversed_vertices;
	int next_vertex;

	startVertex = validate_vertex(graph, startVertex);
	next_vertex_stack.push(startVertex);

	while (next_vertex_stack.size()) {
		next_vertex = next_vertex_stack.top();
//		std::cout << next_vertex << std::endl; //debug
		if (!is_traversed_array[next_vertex]) {
			is_traversed_array[next_vertex] = true;
			traversed_vertices.push_back(next_vertex + 1);
			process_next_vertex_dfs(next_vertex_stack, graph, is_traversed_array); }
		else
			next_vertex_stack.pop();
	}

//	for (int i=0; i<traversed_vertices.size(); i++)
//		std::cout << traversed_vertices[i] << std::endl; //debug
	return traversed_vertices;
}