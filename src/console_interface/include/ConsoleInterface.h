#ifndef SRC_VIEW_CONSOLE_INTERFACE_H_
#define SRC_VIEW_CONSOLE_INTERFACE_H_

#include <iostream>
#include <string>
#include <cstdlib>

#include "../../s21_graph/s21_graph.h"
#include "../../s21_graph_algorithms/s21_graph_algorithms.h"

#define BLUE "\033[1;36m"
#define GREY "\033[1;37m"
#define NONE "\033[0m"
#define RED "\033[1;31m"

#define GRAPHS_DST "tests/graphs/"

namespace s21 {

    class ConsoleInterface {

    private:
        class ConsoleInterfaceInstance {
            friend ConsoleInterface;
            Graph graph_;
            std::string filename_;
            explicit ConsoleInterfaceInstance(const std::string &filename);
            ConsoleInterfaceInstance(ConsoleInterfaceInstance &other) = default;
            ConsoleInterfaceInstance(ConsoleInterfaceInstance &&other) = default;
            ConsoleInterfaceInstance &operator=(ConsoleInterfaceInstance &other) = default;
            ConsoleInterfaceInstance &operator=(ConsoleInterfaceInstance &&other) = default;
            ~ConsoleInterfaceInstance() = default;

            void bfs(int);
            void dfs(int);
            void dijkstra(int, int);
            void floydwar();
            void aco();
            void save(const std::string& filename);
        };

    private:
        static ConsoleInterfaceInstance *instance_;
        ConsoleInterface(ConsoleInterface &other) = delete;
        ConsoleInterface(ConsoleInterface &&other) = delete;
        ConsoleInterface &operator=(ConsoleInterface &other) = delete;
        ConsoleInterface &operator=(ConsoleInterface &&other) = delete;
        ~ConsoleInterface() = delete;

    public:
        static void start() noexcept;
        static void start_menu() noexcept;
        static void menu() noexcept;
        static void load() noexcept;
        static void list() noexcept;
        static void exit() noexcept;
        static void bfs() noexcept;
        static void dfs() noexcept;
        static void dijkstra() noexcept;
        static void floydwar() noexcept;
        static void aco() noexcept;
        static void save() noexcept;
    };

} // namespace s21

#endif  // SRC_VIEW_CONSOLE_INTERFACE_H_
