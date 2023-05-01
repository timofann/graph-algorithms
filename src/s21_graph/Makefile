CC			= g++
CCFLAGS		= -g -Wall -Wextra -Werror -std=c++17
NAME		= s21_graph.a
SRC_DIR		= src/
OBJ_DIR		= obj/
INCLUDE_DIR	= include/
INCLUDE_F	= Graph.h
SRC_FILES	= Graph.cpp loadGraphFromFile.cpp
OBJ_FILES	= $(SRC_FILES:.cpp=.o)
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
HEADER      = s21_graph.h
INC			= $(addprefix $(INCLUDE_DIR), $(INCLUDE_F)) $(HEADER)
AR			= ar rcs
RM			= rm -rf

.PHONY: all clean fclean re test

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -I. -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	${AR} ${NAME} $?

clean:
	$(RM) $(OBJ_DIR) a.out

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)