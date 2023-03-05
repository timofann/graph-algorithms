#include "ConsoleInterface.h"

#define NOT_INITIALISED_MESSAGE "You have not load graph yet. Come later."

using namespace s21;

ConsoleInterface::ConsoleInterfaceInstance* ConsoleInterface::instance_ = NULL;

ConsoleInterface::ConsoleInterface(const std::string &filename) noexcept {
    try {
        if (!ConsoleInterface::instance_)
            ConsoleInterface::instance_ = new ConsoleInterfaceInstance(filename);
        else
            if (ConsoleInterface::instance_->filename_ != filename)
//                ;
                *(ConsoleInterface::instance_) = ConsoleInterfaceInstance(filename);
    }
    catch (std::exception &e) {
        std::cout << GREY << "Can't set a new graph: " << e.what() << GREY << std::endl;
    }
}

ConsoleInterface::~ConsoleInterface() noexcept {}

void ConsoleInterface::load() noexcept {
    std::cout << GREY << "Run load command" << NONE << std::endl;
    std::cout << GREY << "Choose a file to load the graph from: " << NONE;
    std::string filename;
    std::cin >> filename;
    ConsoleInterface interface = ConsoleInterface(filename);
}

void ConsoleInterface::list() noexcept {
    std::cout << GREY << "Run list command" << NONE << std::endl;
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
        try { ConsoleInterface::instance_->bfs(std::stoi(input)); } catch (...) {
            std::cout << GREY << "Invalid value." << NONE << std::endl;
        }
    }
}

void ConsoleInterface::dfs() noexcept {
    if (!ConsoleInterface::instance_)
        std::cout << GREY << NOT_INITIALISED_MESSAGE << NONE << std::endl;
    else {
        std::cout << GREY << "Run dfs command" << NONE << std::endl;
        ConsoleInterface::instance_->dfs();
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
        try { ConsoleInterface::instance_->dijkstra(std::stoi(input1), std::stoi(input2)); } catch (...) {
            std::cout << GREY << "Invalid value." << NONE << std::endl;
        }
    }
}

void ConsoleInterface::floydwar() noexcept {
    if (!ConsoleInterface::instance_)
        std::cout << GREY << NOT_INITIALISED_MESSAGE << NONE << std::endl;
    else {
        std::cout << GREY << "Run floydwar command" << NONE << std::endl;
        ConsoleInterface::instance_->floydwar();
    }
}

void ConsoleInterface::aco() noexcept {
    if (!ConsoleInterface::instance_)
        std::cout << GREY << NOT_INITIALISED_MESSAGE << NONE << std::endl;
    else {
        std::cout << GREY << "Run aco command" << NONE << std::endl;
        ConsoleInterface::instance_->aco();
    }
}

void ConsoleInterface::save() noexcept {
    if (!ConsoleInterface::instance_)
        std::cout << GREY << NOT_INITIALISED_MESSAGE << NONE << std::endl;
    else {
        std::cout << GREY << "Run save command" << NONE << std::endl;
        ConsoleInterface::instance_->save();
    }
}









//
//void ConsoleInterface::BreadthDepthFirstSearch(int choice) {
//  try {
//    std::cout << font_ << "\n\tEnter starting vertex from 1 to "
//              << graph_.GetSize() << std::endl;
//    int num = CheckInput();
//    if (num != -1 && num < (graph_.GetSize() + 1) && num > 0) {
//      std::vector<int> path;
//      if (choice == 2) {
//        path = algorithm_.BreadthFirstSearch(graph_, num);
//      } else {
//        path = algorithm_.DepthFirstSearch(graph_, num);
//      }
//      std::cout << font_ << "\n\t";
//      PrintVector(path);
//      std::cout << color_off_;
//      WhatIsNext();
//    } else {
//      std::cout << font_ << "\n\tError: incorrect input, try again"
//                << color_off_ << std::endl;
//      BreadthDepthFirstSearch(choice);
//    }
//  } catch (std::exception &e) {
//    std::cerr << font_ << "\nError: " << e.what() << color_off_ << "\n";
//    WhatIsNext();
//  }
//}
//
//void ConsoleInterface::DijkstrasAlgorithm() {
//  try {
//    std::cout << font_ << "\n\tEnter starting vertex from 1 to "
//              << graph_.GetSize() << std::endl;
//    int start = CheckInput();
//    std::cout << font_ << "\n\tEnter finishing vertex from 1 to "
//              << graph_.GetSize() << std::endl;
//    int finish = CheckInput();
//    if (start != -1 && finish != -1 && start < (graph_.GetSize() + 1) &&
//        finish < (graph_.GetSize() + 1) && start > 0 && finish > 0) {
//      int distance =
//          algorithm_.GetShortestPathBetweenVertices(graph_, start, finish);
//      std::cout << font_ << "\n\tDistance: " << distance << color_off_
//                << std::endl;
//      WhatIsNext();
//    } else {
//      std::cout << font_ << "\n\tError: incorrect input, try again"
//                << color_off_ << std::endl;
//      DijkstrasAlgorithm();
//    }
//  } catch (std::exception &e) {
//    std::cerr << font_ << "\n\tError: " << e.what() << color_off_ << "\n";
//    WhatIsNext();
//  }
//}
//
//void ConsoleInterface::FloydWarshallPrimsAlgorithm(int choice) {
//  try {
//    Matrix res;
//    if (choice == 5) {
//      res = algorithm_.GetShortestPathsBetweenAllVertices(graph_);
//    } else {
//      res = algorithm_.GetLeastSpanningTree(graph_);
//    }
//    std::cout << font_ << "\n\t";
//    PrintMatrix(res);
//    std::cout << color_off_;
//    WhatIsNext();
//  } catch (std::exception &e) {
//    std::cerr << font_ << "\n\tError: " << e.what() << color_off_ << "\n";
//    WhatIsNext();
//  }
//}
//
//void ConsoleInterface::AntColonyAlgorithm() {
//  try {
//    TsmResult res;
//    res = algorithm_.TSPAntColonyOptimization(graph_);
//    if (!std::isinf(res.distance)) {
//      std::cout << font_ << "\n\tRoute length: " << res.distance;
//      std::cout << "\n\tSequence of traversing vertices: ";
//      PrintVector(res.vertices);
//      std::cout << color_off_;
//    } else {
//      std::cout << font_ << "\n\tNo path found!\n" << color_off_;
//    }
//    WhatIsNext();
//  } catch (std::exception &e) {
//    std::cerr << font_ << "\n\tError: " << e.what() << color_off_ << "\n";
//    WhatIsNext();
//  }
//}
//
//void ConsoleInterface::ComparisonTSP() {
//  try {
//    std::vector<std::tuple<std::string, double, std::vector<int>, double>> res;
//    std::cout << font_ << "\n\tEnter how many times to execute each algorithm"
//              << std::endl;
//
//    int num = CheckInput();
//    if (num != -1 && num < 1001 && num > 0) {
//      res = algorithm_.TSPComparison(graph_, num);
//      ComparisonOutput(res);
//    } else {
//      std::cout << font_ << "\n\tError: incorrect input, try again"
//                << color_off_ << std::endl;
//      ComparisonTSP();
//    }
//    WhatIsNext();
//  } catch (std::exception &e) {
//    std::cerr << font_ << "\n\tError: " << e.what() << color_off_ << "\n";
//    WhatIsNext();
//  }
//}
//
//void ConsoleInterface::Save() {
//  std::cout << font_ << "\n\tEnter file name to save graph with .dot extension"
//            << std::endl;
//  std::string filename;
//  std::cout << "\t";
//  std::cin >> filename;
//  graph_.ExportGraphToDot(filename);
//  std::cout << "\tFile is saved" << color_off_ << std::endl;
//  WhatIsNext();
//}
//
//void ConsoleInterface::ComparisonOutput(
//    const std::vector<std::tuple<std::string, double, std::vector<int>, double>>
//        &v) {
//  for (auto [A, B, C, D] : v) {
//    if (!std::isinf(B)) {
//      std::cout << font_ << "\n\tUsing algorithm: " << A;
//      std::cout << "\n\tRoute length: " << B;
//      std::cout << "\n\tSequence of traversing vertices: ";
//      auto &vec = C;
//      for (auto &it : vec) {
//        std::cout << it << " ";
//      }
//      std::cout << "\n\tExecution time: " << D << " sec" << std::endl;
//    } else {
//      std::cout << font_ << "\n\tUsing algorithm: " << A;
//      std::cout << "\n\tNo path found!\n" << color_off_;
//    }
//  }
//}
//
//int ConsoleInterface::CheckInput() {
//  std::string choice;
//  int num;
//  std::cout << "\t";
//  std::cin >> choice;
//  std::cout << color_off_;
//
//  return IsNumber(choice) == 1 ? num = std::stoi(choice) : -1;
//}
//
//template <typename T>
//void ConsoleInterface::PrintVector(std::vector<T> &v) {
//  for (auto &elem : v) {
//    std::cout << elem << " ";
//  }
//  std::cout << std::endl;
//}
//
//void ConsoleInterface::PrintMatrix(Matrix &m) {
//  for (unsigned int i = 0; i < m.GetSize(); i++) {
//    for (unsigned int j = 0; j < m.GetSize(); j++) {
//      std::cout << m(i, j) << ' ';
//    }
//    std::cout << "\n\t";
//  }
//}
