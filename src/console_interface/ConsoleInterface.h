#ifndef SRC_VIEW_CONSOLE_INTERFACE_H_
#define SRC_VIEW_CONSOLE_INTERFACE_H_

#include <iostream>
#include <string>
#include <cstdlib>

#include "../s21_graph/s21_graph.h"
#include "../s21_graph_algorithms/s21_graph_algorithms.h"

#define BLUE "\033[1;36m"
#define GREY "\033[1;37m"
#define NONE "\033[0m"

#define GRAPHS_DST "tests/graphs/"

namespace s21 {

    class ConsoleInterface {

    private:
        class ConsoleInterfaceInstance {
            friend ConsoleInterface;
            Graph graph_;
            std::string filename_;
            ConsoleInterfaceInstance(const std::string &filename);
            ConsoleInterfaceInstance(ConsoleInterfaceInstance &other) = default;
            ConsoleInterfaceInstance(ConsoleInterfaceInstance &&other) = default;
            ConsoleInterfaceInstance &operator=(ConsoleInterfaceInstance &other) = default;
            ConsoleInterfaceInstance &operator=(ConsoleInterfaceInstance &&other) = default;
            ~ConsoleInterfaceInstance();

            void bfs(int);
            void dfs();
            void dijkstra(int, int);
            void floydwar();
            void aco();
            void save();
        };

    private:
        static ConsoleInterfaceInstance *instance_;
        ConsoleInterface(const std::string &filename) noexcept;
        ConsoleInterface(ConsoleInterface &other) noexcept;
        ConsoleInterface(ConsoleInterface &&other) noexcept;
        ConsoleInterface &operator=(ConsoleInterface &other) noexcept;
        ConsoleInterface &operator=(ConsoleInterface &&other) noexcept;
        ~ConsoleInterface() noexcept;

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
