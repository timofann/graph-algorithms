#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H
#include "../../s21_containers/queue.h"
#include "../../s21_containers/stack.h"
#include "../../s21_graph/s21_graph.h"
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <math.h>
#include <system_error>
#include <vector>

namespace s21 {

class GraphAlgorithms {

public:
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };

private:
  GraphAlgorithms(GraphAlgorithms &other) = delete;
  GraphAlgorithms(GraphAlgorithms &&other) = delete;
  GraphAlgorithms &operator=(GraphAlgorithms &other) = delete;
  GraphAlgorithms &operator=(GraphAlgorithms &&other) = delete;
  ~GraphAlgorithms() = delete;

public:
  static std::vector<int> depthFirstSearch(const Graph &graph, int startVertex);
  static std::vector<int> breadthFirstSearch(const Graph &graph,
                                             int startVertex);
  static std::vector<int>
  getShortestPathBetweenVerticesImproved(const Graph &graph, int vertex1,
                                         int vertex2);
  static double getShortestPathBetweenVertices(const Graph &graph, int vertex1,
                                               int vertex2);
  static std::vector<std::vector<double>>
  getShortestPathsBetweenAllVertices(const Graph &graph);
  static std::vector<std::vector<int>> getLeastSpanningTree(const Graph &graph);
  static TsmResult solveTravelingSalesmanProblem(const Graph &graph);

private:
  static int validateVertex(const Graph &graph, int startVertex);

  template <typename T>
  static std::vector<int> search(const Graph &graph, int startVertex);

public:
  struct GraphAlgorithmsError : std::runtime_error {
    explicit GraphAlgorithmsError(const std::string &arg);
  };

  struct VertexIsOutOfRange : GraphAlgorithmsError {
    explicit VertexIsOutOfRange(const std::string &arg);
  };

  struct NoSolution : GraphAlgorithmsError {
    explicit NoSolution(const std::string &arg);
  };
};

} // namespace s21

#endif // GRAPHALGORITHMS_H
