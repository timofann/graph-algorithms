#include "../include/GraphAlgorithms.h"

using namespace s21;

template <typename T>
static void
process_next_vertex(T& next_vertexes_container, Graph& graph,
                    const std::vector<bool>& is_traversed_array) {
    int current_vertex = next_vertexes_container.get_start_element();
    for (std::size_t v = 0; v < graph.size(); v++)
        if (graph[current_vertex][v] && !is_traversed_array[v])
            next_vertexes_container.push(v);
}

template <typename T>
std::vector<int> GraphAlgorithms::
search(Graph &graph, int startVertex) {

  std::vector<bool> is_traversed_array(graph.size(), false);
  T next_vertex_container;
  std::vector<int> traversed_vertices;
  int next_vertex;

  startVertex = GraphAlgorithms::validate_vertex(graph, startVertex);
  next_vertex_container.push(startVertex);

  while (next_vertex_container.size()) {
    next_vertex = next_vertex_container.get_start_element();
    //		std::cout << next_vertex << std::endl; //debug
    if (!is_traversed_array[next_vertex]) {
      is_traversed_array[next_vertex] = true;
      traversed_vertices.push_back(next_vertex + 1);
      process_next_vertex(next_vertex_container, graph, is_traversed_array); }
    else
      next_vertex_container.pop();
  }

  //	for (int i=0; i<traversed_vertices.size(); i++)
  //		std::cout << traversed_vertices[i] << std::endl; //debug
  return traversed_vertices;
}

std::vector<int> GraphAlgorithms::
breadthFirstSearch(Graph &graph, int startVertex) {
  return search<queue<int>>(graph, startVertex);
}

std::vector<int> GraphAlgorithms::
depthFirstSearch(Graph &graph, int startVertex) {
  return search<stack<int>>(graph, startVertex);
}
