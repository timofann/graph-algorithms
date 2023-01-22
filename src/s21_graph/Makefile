CC			= g++
CCFLAGS		= -Wall -Wextra -Werror -std=c++17
NAME		= s21_graph.a
SRC_DIR		= src/
OBJ_DIR		= obj/
INCLUDE_DIR	= include/
INCLUDE_F	= s21_graph.h Graph.h
SRC_FILES	= Graph.cpp
OBJ_FILES	= $(SRC_FILES:.cpp=.o)
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INC			= $(addprefix $(INCLUDE_DIR), $(INCLUDE_F))
AR			= ar rcs
RM			= rm -rf

.PHONY: all clean fclean re

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp $(INC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	${AR} ${NAME} $?

clean:
	$(RM) $(OBJ_DIR);

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

test: all
	$(CC) $(CCFLAGS) -g main_test.cpp -I$(INCLUDE_DIR) -lstdc++ s21_graph.a