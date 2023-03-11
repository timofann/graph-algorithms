.PHONY: test all s21_graph.a s21_graph_algorithms.a fclean re

CC = g++
CCFLAGS = -std=c++17 -Wall -Werror -Wextra
SRC_FILES = ConsoleInterface.cpp ConsoleInterface_menu.cpp ConsoleInterfaceInstance.cpp
SRC_DIR = console_interface/src/
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ_DIR = console_interface/obj/
OBJ_FILES = $(SRC_FILES:.cpp=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))


$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -Iconsole_interface/include -c $< -o $@

all: s21_graph.a s21_graph_algorithms.a $(OBJS) console_interface/include/ConsoleInterface.h
	g++ main.cpp $(OBJS) -std=c++17 -Iconsole_interface/include s21_graph/s21_graph.a s21_graph_algorithms/s21_graph_algorithms.a -o run
	./run

s21_graph.a:
	cd s21_graph; make

s21_graph_algorithms.a:
	cd s21_graph_algorithms; make

fclean:
	cd s21_graph; make fclean
	cd s21_graph_algorithms; make fclean
	rm -f a.out

re: fclean all

test: s21_graph.a s21_graph_algorithms.a
	g++ tests/tests.cpp s21_graph/s21_graph.a s21_graph_algorithms/s21_graph_algorithms.a -o tests/test -lgtest -std=c++17 -lgvc -lcgraph
	./tests/test
	cd tests; rm -f test test_graph.dot test_graph2.gv
