#include "../include/GraphAlgorithms.h"

#define NO_EXIST_VERTEX -1

using namespace s21;

static int //todo: избавиться от дублирования кода
validate_vertex(const Graph &graph, int startVertex) {
	if (startVertex < 1 || startVertex > (int)graph.size()) {
		throw GraphAlgorithms::GraphAlgorithmsError("\033[1;31mGraphAlgorithmsError:\033[0m Vertex for shortest path finding should be in range [1; vertices count]");
	}
	return startVertex - 1;
}

struct vertex{
	// номер вершины из которой пришли минимально по расстоянию
	int vertex_nbr;
	// минимальная дистанция от стартовой точки до рассматриваемой вершины
	std::size_t distance_to_vertex;
};

static int cmp(const void *x, const void *y) {
	const int arg1 = static_cast<const vertex*>(x)->distance_to_vertex;
	const int arg2 = static_cast<const vertex*>(y)->distance_to_vertex;
	if (arg1 < arg2) return -1;
	return 1;
}

static void sort_vertex_vector(std::vector<vertex>& vec) {
	std::qsort(vec.data(), vec.size(), sizeof(vertex), cmp);
}

static void
update_shortest_info(Graph &graph,
					 int next_vertex,
					 std::vector<vertex>& shortest_distance,
					 const std::vector<bool>& is_traversed_array) {

	for (int v = 0; v < (int)graph.size(); v++) {
		if (!is_traversed_array[v] && graph[next_vertex][v]
			&& graph[next_vertex][v] + shortest_distance[next_vertex].distance_to_vertex <= shortest_distance[v].distance_to_vertex) {
			shortest_distance[v] = {next_vertex, graph[next_vertex][v] + shortest_distance[next_vertex].distance_to_vertex};
//					std::cout << "to vert:" << v << " shortest_distance:" << shortest_distance[v].distance_to_vertex << std::endl;
		}
	}
}

static void
add_children_in_queue(Graph &graph,
					  int next_vertex,
					  queue<int>& next_vertex_queue,
					  const std::vector<bool>& is_traversed_array) {

	std::vector<vertex> vertices_to_add_in_queue;

	for (int v = 0; v < (int)graph.size(); v++) {
		if (!is_traversed_array[v] && graph[next_vertex][v])
			vertices_to_add_in_queue.push_back(vertex{v, graph[next_vertex][v]});
	}
	sort_vertex_vector(vertices_to_add_in_queue);
	for (int v = 0; v < (int)vertices_to_add_in_queue.size(); v++) {
		next_vertex_queue.push(vertices_to_add_in_queue[v].vertex_nbr);
	}
}

std::size_t GraphAlgorithms::
getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {

	vertex1 = validate_vertex(graph, vertex1);
	vertex2 = validate_vertex(graph, vertex2);

	std::vector<bool> is_traversed_array(graph.size(), false);
	// сначала минимальные расстояния от предыдущих посещенных вершин максимальны, наша задача найти минимумы
	// номера вершин откуда пришли заполнить можно чем угодно, они должны быть перезаписаны в соответствии с минимальным расстоянием (для стартовой точки останется дефолтным)
	std::vector<vertex> shortest_distance(graph.size(), vertex{NO_EXIST_VERTEX, UINT_MAX});
	queue<int> next_vertex_queue;
	int next_vertex;

	next_vertex_queue.push(vertex1);
	shortest_distance[vertex1].distance_to_vertex = 0; // дистанцию до стартовой вершины

	while (next_vertex_queue.size()) {
		next_vertex = next_vertex_queue.front();
		if (!is_traversed_array[next_vertex]) {
			is_traversed_array[next_vertex] = true;
			update_shortest_info(graph, next_vertex, shortest_distance, is_traversed_array);
			add_children_in_queue(graph, next_vertex, next_vertex_queue, is_traversed_array);
		}
		next_vertex_queue.pop();
	}

//	for (int i = 0; i < shortest_path.size(); i++) //debug
//		std::cout << shortest_path[i] << " ";
//	std::cout << std::endl;

	return shortest_distance[vertex2].distance_to_vertex;
}

void
get_start_state(Graph& graph, std::vector<std::vector<float>>& shortest_path) {
	for (int i = 0; i < (int)graph.size(); ++i)
		for (int j = 0; j < (int)graph.size(); ++j)
			if (i == j)
				shortest_path[i][j] = 0;
			else
				if (graph[i][j]) {
					shortest_path[i][j] = graph[i][j];
					shortest_path[j][i] = graph[i][j]; }
}

std::vector<std::vector<float>> GraphAlgorithms::
getShortestPathsBetweenAllVertices(Graph &graph) {
	std::vector<std::vector<float>> shortest_path = std::vector<std::vector<float>>(
			graph.size(), std::vector<float>(graph.size(), 1.0f / 0.0f));
	get_start_state(graph, shortest_path);
	for (int i = 0; i < (int)graph.size(); ++i)
		for (int j = 0; j < (int)graph.size(); ++j)
			for (int k = 0; k < (int)graph.size(); ++k) {
				if (shortest_path[j][k] > shortest_path[j][i] + shortest_path[i][k]) {
					shortest_path[j][k] = shortest_path[j][i] + shortest_path[i][k];
				}
			}
	return shortest_path;
}
