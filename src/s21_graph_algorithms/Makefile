CC			= g++
CCFLAGS		= -Wall -Wextra -Werror -std=c++17
NAME		= s21_graph_algorithms.a
SRC_DIR		= src/
OBJ_DIR		= obj/
SRC_FILES   = GraphAlgorithms_search.cpp			GraphAlgorithms_utils.cpp \
              GraphAlgorithms_shortest_path.cpp		GraphAlgorithms_spanning_tree.cpp \
              GraphAlgorithms_salesman_problem.cpp
OBJ_FILES   = $(SRC_FILES:.cpp=.o)
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
HEADER      = s21_graph_algorithms.h
INC         = include/GraphAlgorithms.h $(HEADER)

.PHONY: all clean fclean re test

all : $(NAME)

$(NAME): $(OBJ)
	ar rcs s21_graph_algorithms.a $(OBJ)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -I. -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) a.out

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)