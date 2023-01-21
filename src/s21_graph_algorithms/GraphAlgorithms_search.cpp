#include "GraphAlgorithms.h"
#include <stack>
#include <queue>
#include <iostream>


using namespace s21;

static void
validate_vertex(Graph &graph, int startVertex) { // todo: изменить индексацию с нуля на индексацию с единицы
	if (startVertex < 0 || startVertex >= graph.vertices_cnt_)
		throw GraphAlgorithms::GraphAlgorithmsError("Start vertex for DFS should be in range of graph size");
}

static void
init_is_traversed_array(Graph& graph, bool* is_traversed_array) {
	for (int i = 0; i < graph.vertices_cnt_; i++)
		is_traversed_array[i] = false;
}

static void
process_next_vertex_bfs(std::queue<int>& next_vertexes_to_process, Graph& graph,
						bool* is_traversed_array) {
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
						bool* is_traversed_array) {
	int current_vertex = next_vertexes_stack.top();
//	std::cout << "process_next_vertex_dfs" << current_vertex << std::endl; //debug
	for (int v = graph.vertices_cnt_ -1; v >= 0; v--)
		if (graph.matrix_[current_vertex][v] && !is_traversed_array[v])
			next_vertexes_stack.push(v);
}

//static bool
//is_last_vertex_in_chain(Graph &graph, int vertex, bool is_traversed_array[graph.vertices_cnt_]) {
//	for (int v = 0; v < graph.vertices_cnt_; v++) {
//		if (graph.matrix_[vertex][v] && !is_traversed_array[v])
//			return false;
//	}
//	return true;
//}

std::vector<int> &GraphAlgorithms::
breadthFirstSearch(Graph &graph, int startVertex) {

	bool is_traversed_array[graph.vertices_cnt_];
	std::queue<int> next_vertex_queue;
	std::vector<int> &traversed_vertices = *(new std::vector<int>);
	int next_vertex;

	validate_vertex(graph, startVertex);
	init_is_traversed_array(graph, is_traversed_array);
	next_vertex_queue.push(startVertex);

	while (next_vertex_queue.size()) {
		next_vertex = next_vertex_queue.front();
//		std::cout << next_vertex << std::endl; //debug
		if (!is_traversed_array[next_vertex]) {
			is_traversed_array[next_vertex] = true;
			traversed_vertices.push_back(next_vertex);
			process_next_vertex_bfs(next_vertex_queue, graph, is_traversed_array); }
		else
			next_vertex_queue.pop();
	}

//	for (int i=0; i<traversed_vertices.size(); i++)
//		std::cout << traversed_vertices[i] << std::endl; //debug
	return traversed_vertices;
}

std::vector<int> &GraphAlgorithms::
depthFirstSearch(Graph &graph, int startVertex) {

	bool is_traversed_array[graph.vertices_cnt_];
	std::stack<int> next_vertex_stack;
	std::vector<int> &traversed_vertices = *(new std::vector<int>);
	int next_vertex;

	validate_vertex(graph, startVertex);
	init_is_traversed_array(graph, is_traversed_array);
	next_vertex_stack.push(startVertex);

	while (next_vertex_stack.size()) {
		next_vertex = next_vertex_stack.top();
//		std::cout << next_vertex << std::endl; //debug
		if (!is_traversed_array[next_vertex]) {
			is_traversed_array[next_vertex] = true;
			traversed_vertices.push_back(next_vertex);
			process_next_vertex_dfs(next_vertex_stack, graph, is_traversed_array); }
		else
			next_vertex_stack.pop();

//		if (is_last_vertex_in_chain(graph, next_vertex, is_traversed_array))
//			next_vertex_stack.pop();
	}

//	for (int i=0; i<traversed_vertices.size(); i++)
//		std::cout << traversed_vertices[i] << std::endl; //debug
	return traversed_vertices;
}