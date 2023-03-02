CC			= c++
CCFLAGS		= -g -Wall -Wextra -Werror -std=c++17
NAME		= s21_graph_algorithms.a
SRC_DIR		= src/
OBJ_DIR		= obj/
SRC_FILES   = GraphAlgorithms_search.cpp			GraphAlgorithms_utils.cpp \
              GraphAlgorithms_shortest_path.cpp		GraphAlgorithms_additional.cpp \
              GraphAlgorithms_spanning_tree.cpp		GraphAlgorithms_salesman_problem.cpp
OBJ_FILES   = $(SRC_FILES:.cpp=.o)
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
HEADER      = s21_graph_algorithms.h
INC         = include/GraphAlgorithms.h $(HEADER)

.PHONY: all clean fclean re test

all : s21_graph.a $(NAME)

$(NAME): $(OBJ)
	ar rcs s21_graph_algorithms.a $(OBJ)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -I$(HEADER) -c $< -o $@

s21_graph.a:
	cd ../s21_graph; make

clean:
	rm -rf $(OBJ_DIR) a.out

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

test: all
	c++ -std=c++17 graph_algorithms_test.cpp ../s21_graph/s21_graph.a s21_graph_algorithms.a
	./a.out