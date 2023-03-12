#include "../include/ConsoleInterface.h"
#include <stdlib.h>
#include <unistd.h>

#define WELCOME_MESSAGE                                                        \
  "\
Hello! You're lucky, because it is THE BEST CONSOLE INTERFACE EVER!\n\
-------------------------------------------------------------------"
#define START_MENU_MESSAGE                                                     \
  "\n\
Now you have the next opportunities:\n\
    1. Show the list of available files with adjacency matrices.\n\
    2. Load Graph with adjacency matrix from file.\n\
    3. Exit program.\n\n\
You need to choose one and enter the number: "
#define CURRENT_GRAPH "\nYou're working on graph from the file "
#define MENU_MESSAGE                                                           \
  "\
and you have the next opportunities:\n\
    1. Show the list of available files with adjacency matrices.\n\
    2. Load Graph with adjacency matrix from file.\n\
    3. Breadth-first search.\n\
    4. Depth-first search.\n\
    5. Dijkstra's algorithm.\n\
    6. Floyd-Warshall algorithm.\n\
    7. Ant colony algorithm.\n\
    8. Save to .dot.\n\
    9. Exit program.\n\n\
You need to choose one and enter the number: "

#define input()                                                                \
  {                                                                            \
    std::cout << BLUE                                                          \
              << "Your request does not satisfy the list. Try another one: "   \
              << NONE;                                                         \
    std::cin >> choice;                                                        \
  };

using namespace s21;

static void runArrows();
static int validateAndRunStartChoice(std::string &);
static int validateAndRunChoice(std::string &);

void ConsoleInterface::start() noexcept {
  system("clear");
  std::cout << BLUE << WELCOME_MESSAGE << NONE << std::endl;
  runArrows();
  while (!ConsoleInterface::instance_)
    startMenu();
  while (true)
    menu();
}

void ConsoleInterface::startMenu() noexcept {
  std::cout << BLUE << START_MENU_MESSAGE << NONE;
  std::string choice;
  std::cin >> choice;
  while (validateAndRunStartChoice(choice))
    input();
}

void ConsoleInterface::menu() noexcept {
  std::cout << BLUE << CURRENT_GRAPH << ConsoleInterface::instance_->filename_
            << NONE << std::endl;
  std::cout << BLUE << MENU_MESSAGE << NONE;
  std::string choice;
  std::cin >> choice;
  while (validateAndRunChoice(choice))
    input();
}

static int validateAndRunStartChoice(std::string &choice) {
  runArrows();
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

static int validateAndRunChoice(std::string &choice) {
  runArrows();
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

static void runArrows() {
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
