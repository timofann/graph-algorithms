#include "../include/ConsoleInterface.h"

#define NOT_INITIALISED_MESSAGE "You have not load graph yet. Come later."

using namespace s21;

ConsoleInterface::ConsoleInterfaceInstance* ConsoleInterface::instance_ = NULL;

void ConsoleInterface::load() noexcept {
    std::cout << GREY << "Run load command" << NONE << std::endl;
    std::cout << GREY << "Choose a file to load the graph from: " << NONE;
    std::string filename;
    std::cin >> filename;
    try {
        if (!ConsoleInterface::instance_)
            ConsoleInterface::instance_ = new ConsoleInterfaceInstance(filename);
        else
            if (ConsoleInterface::instance_->filename_ != filename)
                *(ConsoleInterface::instance_) = ConsoleInterfaceInstance(filename);
    } catch (std::exception &e) {
        std::cout << GREY << "Can't set a new graph: " << e.what() << GREY << std::endl; }
}

void ConsoleInterface::list() noexcept {
    std::cout << GREY << "Next files are available:" << NONE << std::endl;
    std::system("ls tests/graphs");
}

void ConsoleInterface::exit() noexcept {
    std::cout << GREY << "Run exit command" << NONE << std::endl;
    std::cout << GREY << "Goodbye!" << NONE << std::endl;
    delete ConsoleInterface::instance_;
    ConsoleInterface::instance_ = NULL;
    std::exit(0);
}

void ConsoleInterface::bfs() noexcept {
    if (!ConsoleInterface::instance_)
        std::cout << GREY << NOT_INITIALISED_MESSAGE << NONE << std::endl;
    else {
        std::cout << GREY << "Run bfs command" << NONE << std::endl;
        std::cout << GREY << "This algorithm goes throw all the vertices." << NONE << std::endl;
        std::string input;
        std::cout << GREY << "Enter the start vertex number [1 - " << ConsoleInterface::instance_->graph_.size() << "]: " << NONE;
        std::cin >> input;
        try { ConsoleInterface::instance_->bfs(std::stoi(input)); } catch (std::exception &e) {
            std::cout << std::endl << GREY << "Stop: " << e.what() << NONE << std::endl;
        }
    }
}

void ConsoleInterface::dfs() noexcept {
    if (!ConsoleInterface::instance_)
        std::cout << GREY << NOT_INITIALISED_MESSAGE << NONE << std::endl;
    else {
        std::cout << GREY << "Run dfs command" << NONE << std::endl;
        std::cout << GREY << "This algorithm goes throw all the vertices." << NONE << std::endl;
        std::string input;
        std::cout << GREY << "Enter the start vertex number [1 - " << ConsoleInterface::instance_->graph_.size() << "]: " << NONE;
        std::cin >> input;
        try { ConsoleInterface::instance_->dfs(std::stoi(input)); } catch (std::exception &e) {
            std::cout << std::endl << GREY << "Stop: " << e.what() << NONE << std::endl;
        }
    }
}

void ConsoleInterface::dijkstra() noexcept {
    if (!ConsoleInterface::instance_)
        std::cout << GREY << NOT_INITIALISED_MESSAGE << NONE << std::endl;
    else {
        std::cout << GREY << "Run dijkstra command" << NONE << std::endl;
        std::cout << GREY << "This algorithm finds the path between two vertices." << NONE << std::endl;
        std::string input1;
        std::string input2;
        std::cout << GREY << "Enter the first vertex number [1 - " << ConsoleInterface::instance_->graph_.size() << "]: " << NONE;
        std::cin >> input1;
        std::cout << GREY << "Enter the second vertex number [1 - " << ConsoleInterface::instance_->graph_.size() << "]: " << NONE;
        std::cin >> input2;
        try { ConsoleInterface::instance_->dijkstra(std::stoi(input1), std::stoi(input2)); } catch (std::exception &e) {
            std::cout << std::endl << GREY << "Stop: " << e.what() << NONE << std::endl;
        }
    }
}

void ConsoleInterface::floydwar() noexcept {
    if (!ConsoleInterface::instance_)
        std::cout << GREY << NOT_INITIALISED_MESSAGE << NONE << std::endl;
    else {
        std::cout << GREY << "Run floydwar command" << NONE << std::endl;
        std::cout << GREY << "This algorithm finds paths between all vertices." << NONE << std::endl;
        ConsoleInterface::instance_->floydwar();
    }
}

void ConsoleInterface::aco() noexcept {
    if (!ConsoleInterface::instance_)
        std::cout << GREY << NOT_INITIALISED_MESSAGE << NONE << std::endl;
    else {
        std::cout << GREY << "Run aco command" << NONE << std::endl;
        std::cout << GREY << "This algorithm solves travelling salesman problem." << NONE << std::endl;
        try { ConsoleInterface::instance_->aco(); } catch (std::exception &e) {
            std::cout << std::endl << GREY << "Stop: " << e.what() << NONE << std::endl;
        }
    }
}

void ConsoleInterface::save() noexcept {
    if (!ConsoleInterface::instance_)
        std::cout << GREY << NOT_INITIALISED_MESSAGE << NONE << std::endl;
    else {
        std::cout << GREY << "Run save command" << NONE << std::endl;
        std::cout << GREY << "Choose a file to save the graph to (it should have extention .gv or .dot): " << NONE;
        std::string filename;
        std::cin >> filename;
        try { ConsoleInterface::instance_->save(filename); } catch (std::exception &e) {
            std::cout << std::endl << GREY << "Can't save graph: " << e.what() << NONE << std::endl;
        }
    }
}