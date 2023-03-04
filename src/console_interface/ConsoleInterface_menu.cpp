#include "ConsoleInterface.h"
#include <unistd.h>
#include <stdlib.h>

#define BLUE "\033[1;36m"
#define NONE "\033[0m"
#define WELCOME_MESSAGE "\
Hello! You're lucky, because it is THE BEST CONSOLE INTERFACE EVER!\n\
-------------------------------------------------------------------"
#define START_MENU_MESSAGE "\
Now you have the next opportunities:\n\
    1. Show the list of available files with adjacency matrices.\n\
    2. Load Graph with adjacency matrix from file.\n\
    3. Exit program.\n\n\
You need to choose one and enter the number: "
#define MENU_MESSAGE "\
Now you have the next opportunities:\n\
    1. Show the list of available files with adjacency matrices.\n\
    2. Load Graph with adjacency matrix from file.\n\
    3. Breadth-first search.\n\
    4. Depth-first search.\n\
    5. Dijkstra's algorithm\n\
    6. Floyd-Warshall algorithm\n\
    7. Ant colony algorithm\n\
    8. Save to .dot\n\
    9. Exit program.\n\n\
You need to choose one and enter the number: "

#define input() {\
    std::cout << BLUE << "Your request does not satisfy the list. Try another one: " << NONE; \
    std::cin >> choice;\
};

using namespace s21;

static void run_arrows();
static int validate_and_run_start_choice(std::string&);
static int validate_and_run_choice(std::string&);


void ConsoleInterface::start() {
    system("clear");
    std::cout << BLUE << WELCOME_MESSAGE << NONE << std::endl;
    run_arrows();
    std::cout << std::endl;
    while (!ConsoleInterface::instance_)
        start_menu();
    while (true)
        menu();
}


void ConsoleInterface::start_menu() {
    std::cout << BLUE << START_MENU_MESSAGE << NONE;
    std::string choice;
    std::cin >> choice;
    while (validate_and_run_start_choice(choice))
        input();
}


void ConsoleInterface::menu() {
    std::cout << BLUE << MENU_MESSAGE << NONE;
    std::string choice;
    std::cin >> choice;
    while (validate_and_run_choice(choice))
        input();
}


static int
validate_and_run_start_choice(std::string& choice) {
    run_arrows();
    if (!choice.compare("1")) {
        ConsoleInterface::list();
        return 0;
    }
    if (!choice.compare("2")) {
        ConsoleInterface::load();
        return 0;
    }
    if (!choice.compare("3")) {
        ConsoleInterface::exit();
        return 0;
    }
    return 1;
}


static int
validate_and_run_choice(std::string& choice) {
    run_arrows();
    if (!choice.compare("1")) {
        ConsoleInterface::list();
        return 0;
    }
    if (!choice.compare("2")) {
        ConsoleInterface::load();
        return 0;
    }
    if (!choice.compare("3")) {
        ConsoleInterface::bfs();
        return 0;
    }
    if (!choice.compare("4")) {
        ConsoleInterface::dfs();
        return 0;
    }
    if (!choice.compare("5")) {
        ConsoleInterface::dijkstra();
        return 0;
    }
    if (!choice.compare("6")) {
        ConsoleInterface::floydwar();
        return 0;
    }
    if (!choice.compare("7")) {
        ConsoleInterface::aco();
        return 0;
    }
    if (!choice.compare("8")) {
        ConsoleInterface::save();
        return 0;
    }
    if (!choice.compare("9")) {
        ConsoleInterface::exit();
        return 0;
    }
    return 1;
}


static void
run_arrows() {
    for (int i = 0; i < 60; ++i) {
        write(0, BLUE, 8);
        for (int j = 0; j < i; ++j)
            write(0, " ", 1);
        write(0, "> > > >", 7);
        for (int j = 0; j < 60 - i; ++j)
            write(0, " ", 1);
        usleep(10000);
        write(0, "\r", 1);
    }
    for (int j = 0; j < 67; ++j)
        write(0, " ", 1);
    write(0, "\r", 1);
    std::cout << NONE;
}
