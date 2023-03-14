.PHONY: test all s21_graph.a s21_graph_algorithms.a fclean re norminette run

NAME = run_console_interface
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

all: $(NAME)

$(NAME) : s21_graph.a s21_graph_algorithms.a $(OBJS) console_interface/include/ConsoleInterface.h
	$(CC) $(CCFLAGS) main.cpp $(OBJS) -Iconsole_interface/include s21_graph/s21_graph.a s21_graph_algorithms/s21_graph_algorithms.a -o run_console_interface

run : run_console_interface
	./run_console_interface

s21_graph.a:
	cd s21_graph; make

s21_graph_algorithms.a:
	cd s21_graph_algorithms; make

clean:
	rm -rf $(OBJ_DIR) rm -f tests/test_graph.dot tests/test_graph2.gv
	cd s21_graph; make clean
	cd s21_graph_algorithms; make clean

fclean: clean
	cd s21_graph; make fclean
	cd s21_graph_algorithms; make fclean
	rm -f run_console_interface tests/test

re: fclean all

test: s21_graph.a s21_graph_algorithms.a
	$(CC) $(CCFLAGS) tests/tests.cpp s21_graph/s21_graph.a s21_graph_algorithms/s21_graph_algorithms.a -o tests/test -lgtest -std=c++17 -lgvc -lcgraph
	./tests/test

norminette:
	cppcheck .
	clang-format -n s21_containers/*.h s21_graph/src/*.cpp s21_graph/include/*.h s21_graph_algorithms/src/*.cpp s21_graph_algorithms/include/*.h console_interface/include/*.h console_interface/src/*.cpp tests/tests.cpp main.cpp -Werror

