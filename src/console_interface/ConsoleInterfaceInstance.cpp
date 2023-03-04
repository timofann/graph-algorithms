#include "ConsoleInterface.h"

#define GREY "\033[1;37m"
#define NONE "\033[0m"

using namespace s21;

ConsoleInterface::ConsoleInterfaceInstance::ConsoleInterfaceInstance(const std::string &filename) :
        filename_(filename),
        graph_(Graph::loadGraphFromFile(filename)) {}

ConsoleInterface::ConsoleInterfaceInstance::~ConsoleInterfaceInstance() {}


void ConsoleInterface::ConsoleInterfaceInstance::bfs() {
    std::cout << GREY << "Inner run bfs." << NONE << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::dfs() {
    std::cout << GREY << "Inner run dfs." << NONE << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::dijkstra() {
    std::cout << GREY << "Inner run dijkstra." << NONE << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::floydwar() {
    std::cout << GREY << "Inner run floydwar." << NONE << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::aco() {
    std::cout << GREY << "Inner run aco." << NONE << std::endl;
}

void ConsoleInterface::ConsoleInterfaceInstance::save() {
    std::cout << GREY << "Inner run save." << NONE << std::endl;
}
