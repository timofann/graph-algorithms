#include "../include/GraphAlgorithms.h"
#define NO_EXIST_VERTEX -1

using namespace s21;

struct vertex{
	// номер вершины из которой пришли минимально по расстоянию
	int vertex_nbr;
	// минимальная дистанция от стартовой точки до рассматриваемой вершины
	double distance_to_vertex;
};

static int
cmp(const void *x, const void *y) {
	const double arg1 = static_cast<const vertex*>(x)->distance_to_vertex;
	const double arg2 = static_cast<const vertex*>(y)->distance_to_vertex;
	if (arg1 < arg2) return -1;
	return 1;
}

static void
sort_vertex_vector(std::vector<vertex>& vec) {
	std::qsort(vec.data(), vec.size(), sizeof(vertex), cmp);
}

static void
update_shortest_info(Graph &graph,
					 int next_vertex,
					 std::vector<vertex>& shortest_distance,
					 const std::vector<bool>& is_traversed_array) {

	for (int v = 0; v < (int)graph.size(); v++) {
		if (!is_traversed_array[v] && graph[next_vertex][v]
			&& (double)graph[next_vertex][v] + shortest_distance[next_vertex].distance_to_vertex <= shortest_distance[v].distance_to_vertex) {
			shortest_distance[v] = {next_vertex, (double)graph[next_vertex][v] + shortest_distance[next_vertex].distance_to_vertex};
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
			vertices_to_add_in_queue.push_back(vertex{v, (double)graph[next_vertex][v]});
	}
	sort_vertex_vector(vertices_to_add_in_queue);
	for (int v = 0; v < (int)vertices_to_add_in_queue.size(); v++) {
		next_vertex_queue.push(vertices_to_add_in_queue[v].vertex_nbr);
	}
}

static std::vector<vertex>
getShortestPathBetweenVerticesInner(Graph &graph, int vertex1) {

    std::vector<bool> is_traversed_array(graph.size(), false);
    // сначала минимальные расстояния от предыдущих посещенных вершин максимальны, наша задача найти минимумы
    // номера вершин откуда пришли заполнить можно чем угодно, они должны быть перезаписаны в соответствии с минимальным расстоянием (для стартовой точки останется дефолтным)
    std::vector<vertex> shortest_distance(graph.size(), vertex{NO_EXIST_VERTEX, 1.0 / 0.0});
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
    return shortest_distance;
}

static std::vector<int>
collect_path(int vertex2, const std::vector<vertex>& shortest_distance) {

	std::vector<int> shortest_path;
	int next_vertex;

	next_vertex = vertex2; // использовать одну переменную?
	while (next_vertex != NO_EXIST_VERTEX) {
		shortest_path.push_back(next_vertex + 1);
		next_vertex = shortest_distance[next_vertex].vertex_nbr;
	}
	std::reverse(shortest_path.begin(), shortest_path.end());
	return shortest_path;
}

double GraphAlgorithms::
getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {

	vertex1 = GraphAlgorithms::validate_vertex(graph, vertex1);
	vertex2 = GraphAlgorithms::validate_vertex(graph, vertex2);
    std::vector<vertex> shortest_distance = getShortestPathBetweenVerticesInner(graph, vertex1);
	return shortest_distance[vertex2].distance_to_vertex;
}

std::vector<int> GraphAlgorithms::
getShortestPathBetweenVerticesImproved(Graph &graph, int vertex1, int vertex2) {

	vertex1 = GraphAlgorithms::validate_vertex(graph, vertex1);
	vertex2 = GraphAlgorithms::validate_vertex(graph, vertex2);
    std::vector<vertex> shortest_distance = getShortestPathBetweenVerticesInner(graph, vertex1);
	return collect_path(vertex2, shortest_distance);
}


static void
get_start_state(Graph& graph, std::vector<std::vector<double>>& shortest_path) {

	for (int i = 0; i < (int)graph.size(); ++i)
		for (int j = 0; j < (int)graph.size(); ++j)
			if (i == j)
				shortest_path[i][j] = 0.0;
			else
				if (graph[i][j]) {
					shortest_path[i][j] = (double)graph[i][j];
					shortest_path[j][i] = (double)graph[i][j]; }
}



std::vector<std::vector<double>> GraphAlgorithms::
getShortestPathsBetweenAllVertices(Graph &graph) {

	std::vector<std::vector<double>> shortest_path = std::vector<std::vector<double>>(
			graph.size(), std::vector<double>(graph.size(), 1.0 / 0.0));
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
