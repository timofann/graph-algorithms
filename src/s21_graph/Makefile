SRCS = Graph.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(OBJS)
	ar rsc s21_graph.a $(OBJS)

%.o: %.c
	g++ $< -c -o $@