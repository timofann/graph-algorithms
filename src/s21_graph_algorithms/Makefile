SRCS = GraphAlgorithms_search.cpp			GraphAlgorithms_utils.cpp \
       GraphAlgorithms_shortest_path.cpp	GraphAlgorithms_additional.cpp

OBJS = $(SRCS:.cpp=.o)

all: s21_graph.a $(OBJS)
	ar rcs s21_graph_algorithms.a $(OBJS)

%.o : %.cpp
	c++ -std=c++17 ../s21_graph/s21_graph.a $< -c -o $@

s21_graph.a:
	cd ../s21_graph; make

clean:
	cd ../s21_graph; make clean
	rm -f $(OBJS) a.out

fclean: clean
	cd ../s21_graph; make fclean
	rm -f s21_graph_algorithms.a

test: all
	c++ -std=c++17 graph_algorithms_test.cpp ../s21_graph/s21_graph.a s21_graph_algorithms.a
	./a.out