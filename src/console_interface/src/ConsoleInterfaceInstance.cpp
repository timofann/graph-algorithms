#include "../include/ConsoleInterface.h"

using namespace s21;

ConsoleInterface::ConsoleInterfaceInstance::ConsoleInterfaceInstance(
    const std::string &filename)
    : graph_(Graph::loadGraphFromFile(GRAPHS_DST + filename)),
      filename_(filename) {}

void ConsoleInterface::ConsoleInterfaceInstance::bfs(int v) const {
  std::vector<int> a = s21::GraphAlgorithms::breadthFirstSearch(graph_, v);
  std::cout << std::endl << "> > > > RESULT" << std::endl;
  for (std::size_t i = 0; i < a.size() - 1; i++)
    printf("%d -> ", a[i]);
  std::cout << a.back() << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::dfs(int v) const {
  std::vector<int> a = s21::GraphAlgorithms::breadthFirstSearch(graph_, v);
  std::cout << std::endl << "> > > > RESULT" << std::endl;
  for (std::size_t i = 0; i < a.size() - 1; i++)
    printf("%d -> ", a[i]);
  std::cout << a.back() << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::dijkstra(int v1,
                                                          int v2) const {
  std::vector<int> a =
      GraphAlgorithms::getShortestPathBetweenVerticesImproved(graph_, v1, v2);
  std::size_t b =
      GraphAlgorithms::getShortestPathBetweenVertices(graph_, v1, v2);
  std::cout << std::endl << "> > > > RESULT" << std::endl;
  for (std::size_t i = 0; i < a.size() - 1; i++)
    printf("%d -> ", a[i]);
  std::cout << a.back() << " | distance: " << b << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::floydwar() const {
  std::vector<std::vector<double>> a =
      GraphAlgorithms::getShortestPathsBetweenAllVertices(graph_);
  std::cout << std::endl << "> > > > RESULT" << std::endl << std::endl;
  printf("       ");
  for (std::size_t i = 1; i < a.size() + 1; i++)
    printf("%4lu  ", i);
  std::cout << std::endl;
  printf("       ");
  for (std::size_t i = 0; i < a.size(); i++)
    printf("------");
  std::cout << std::endl;
  for (std::size_t i = 0; i < a.size(); i++) {
    printf("%4lu  |", i + 1);
    for (std::size_t j = 0; j < a[i].size(); j++)
      printf("%5.1f ", a[i][j]);
    std::cout << std::endl;
  }
}

void ConsoleInterface::ConsoleInterfaceInstance::aco() const {
  GraphAlgorithms::TsmResult a =
      GraphAlgorithms::solveTravelingSalesmanProblem(graph_);
  std::cout << std::endl << "> > > > RESULT" << std::endl;
  for (std::size_t i = 0; i < a.vertices.size() - 1; i++)
    printf("%d -> ", a.vertices[i]);
  std::cout << a.vertices.back() << " | distance: " << a.distance << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::save(
    const std::string &filename) const {
  graph_.exportGraphToDot(filename);
  std::cout << std::endl
            << GREY << "Graph saved to file " << NONE << filename << std::endl;
}
