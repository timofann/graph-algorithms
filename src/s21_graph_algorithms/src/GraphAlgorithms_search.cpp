#include "../include/GraphAlgorithms.h"

using namespace s21;

template <typename T>
static void processNextVertex(T &next_vertexes_container, const Graph &graph,
                              std::vector<bool> &is_already_added) {

  int current_vertex = next_vertexes_container.get_start_element();
  for (std::size_t v = 0; v < graph.size(); v++)
    if (graph[current_vertex][v] && !is_already_added[v]) {
      next_vertexes_container.push(v);
      is_already_added[v] = true;
    }
}

template <typename T>
std::vector<int> GraphAlgorithms::search(const Graph &graph, int startVertex) {

  std::vector<bool> is_traversed_array(graph.size(), false);
  std::vector<bool> is_already_added(graph.size(), false);
  T next_vertex_container;
  std::vector<int> traversed_vertices;
  int next_vertex;

  startVertex = GraphAlgorithms::validateVertex(graph, startVertex);
  next_vertex_container.push(startVertex);
  is_already_added[startVertex] = true;

  while (next_vertex_container.size()) {
    next_vertex = next_vertex_container.get_start_element();
    if (!is_traversed_array[next_vertex]) {
      is_traversed_array[next_vertex] = true;
      traversed_vertices.push_back(next_vertex + 1);
      processNextVertex(next_vertex_container, graph, is_already_added);
    } else
      next_vertex_container.pop();
  }
  return traversed_vertices;
}

std::vector<int> GraphAlgorithms::breadthFirstSearch(const Graph &graph,
                                                     int startVertex) {
  return search<queue<int>>(graph, startVertex);
}

std::vector<int> GraphAlgorithms::depthFirstSearch(const Graph &graph,
                                                   int startVertex) {
  return search<stack<int>>(graph, startVertex);
}
