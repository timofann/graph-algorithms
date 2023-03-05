#include "ConsoleInterface.h"

using namespace s21;

ConsoleInterface::ConsoleInterfaceInstance::ConsoleInterfaceInstance(const std::string &filename) :
        filename_(filename),
        graph_(Graph::loadGraphFromFile(GRAPHS_DST + filename)) {}

ConsoleInterface::ConsoleInterfaceInstance::~ConsoleInterfaceInstance() {}

void ConsoleInterface::ConsoleInterfaceInstance::bfs(int v) {
    std::cout << GREY << "Inner run bfs" << NONE << std::endl;
    std::vector<int> a = s21::GraphAlgorithms::breadthFirstSearch(graph_, v);
    std::cout << "> > > > RESULT" << std::endl;
    for (int i = 0; i < a.size(); i++)
        printf("%d ", a[i]);
    std::cout << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::dfs() {
    std::cout << GREY << "Inner run dfs" << NONE << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::dijkstra(int v1, int v2) {
    std::cout << GREY << "Inner run dijkstra" << NONE << std::endl;
    std::vector<int> a = GraphAlgorithms::getShortestPathBetweenVertices_improved(graph_, v1, v2);
    std::size_t b = GraphAlgorithms::getShortestPathBetweenVertices(graph_, v1, v2);
    std::cout << "> > > > RESULT" << std::endl;
    for (int i = 0; i < a.size(); i++)
        printf("%d ", a[i]);
    std::cout << "- distance " << b << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::floydwar() {
    std::cout << GREY << "Inner run floydwar" << NONE << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::aco() {
    std::cout << GREY << "Inner run aco" << NONE << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::save() {
    std::cout << GREY << "Inner run save" << NONE << std::endl;
}
