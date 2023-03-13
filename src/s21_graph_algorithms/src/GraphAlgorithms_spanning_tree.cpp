#include "../include/GraphAlgorithms.h"

using namespace s21;

std::vector<std::vector<int>>
GraphAlgorithms::getLeastSpanningTree(const Graph &graph) {

  std::vector<std::vector<int>> tree = std::vector<std::vector<int>>(
      graph.size(), std::vector<int>(graph.size(), 0));
  std::vector<bool> is_traversed = std::vector<bool>(graph.size(), false);
  int from;
  int to;

  std::size_t min_distance = 1;
  int current_vertex = 0;
  is_traversed[current_vertex] = true;
  while (min_distance > 0) {
    min_distance = 0;
    for (int i = 0; i < (int)graph.size(); ++i)
      if (is_traversed[i]) {
        for (int j = 0; j < (int)graph.size(); ++j)
          if (!is_traversed[j] && graph[i][j] &&
              (min_distance == 0 || min_distance > graph[i][j])) {
            min_distance = graph[i][j];
            from = i;
            to = j;
          }
      }
    if (min_distance) {
      is_traversed[to] = true;
      tree[from][to] = min_distance;
      tree[to][from] = min_distance;
    }
  }
  return tree;
}