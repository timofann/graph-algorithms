#ifndef SRC_VIEW_CONSOLE_INTERFACE_H_
#define SRC_VIEW_CONSOLE_INTERFACE_H_

#include <iostream>
#include <string>

#include "../s21_graph_algorithms/s21_graph_algorithms.h"

namespace s21 {

    class ConsoleInterface {

    private:
        class ConsoleInterfaceInstance {
            friend ConsoleInterface;
            Graph graph_;
            std::string filename_;
            ConsoleInterfaceInstance(const std::string &filename);
            ConsoleInterfaceInstance(ConsoleInterfaceInstance &other);
            ConsoleInterfaceInstance(ConsoleInterfaceInstance &&other);
            ConsoleInterfaceInstance &operator=(ConsoleInterfaceInstance &other);
            ConsoleInterfaceInstance &operator=(ConsoleInterfaceInstance &&other);
            ~ConsoleInterfaceInstance();

            void bfs();
            void dfs();
            void dijkstra();
            void floydwar();
            void aco();
            void save();
        };

    private:
        static ConsoleInterfaceInstance *instance_;
        ConsoleInterface(const std::string &filename);
        ConsoleInterface(ConsoleInterface &other);
        ConsoleInterface(ConsoleInterface &&other);
        ConsoleInterface &operator=(ConsoleInterface &other);
        ConsoleInterface &operator=(ConsoleInterface &&other);
        ~ConsoleInterface();

    public:
        static void start();
        static void start_menu();
        static void menu();
        static void load();
        static void list();
        static void exit();
        static void bfs();
        static void dfs();
        static void dijkstra();
        static void floydwar();
        static void aco();
        static void save();
    };

} // namespace s21

#endif  // SRC_VIEW_CONSOLE_INTERFACE_H_
