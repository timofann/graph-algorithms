SRCS = Graph.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(OBJS)
	ar rcs s21_graph.a $(OBJS)

%.o : %.cpp
	c++ -std=c++17 $< -c -o $@

clean:
	rm -f $(OBJS) a.out

fclean: clean
	rm -f s21_graph.a

test: all
	c++ -std=c++17 graph_test.cpp s21_graph.a
	./a.out
