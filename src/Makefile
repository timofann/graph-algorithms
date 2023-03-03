all: s21_graph.a s21_graph_algorithms.a
	c++ -std=c++17 main_test.cpp s21_graph/s21_graph.a s21_graph_algorithms/s21_graph_algorithms.a
	./a.out

s21_graph.a:
	cd s21_graph; make

s21_graph_algorithms.a:
	cd s21_graph_algorithms; make

fclean:
	cd s21_graph; make fclean
	cd s21_graph_algorithms; make fclean
	rm -f a.out

test:
	c++ s21_graph/s21_graph.a s21_graph_algorithms/s21_graph_algorithms.a tests/tests.cc -o test -lgtest -std=c++17
