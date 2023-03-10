.PHONY: test all s21_graph.a s21_graph_algorithms.a fclean re interface

all: s21_graph.a s21_graph_algorithms.a
	g++ main.cpp console_interface/ConsoleInterface.cpp -std=c++17 s21_graph/s21_graph.a s21_graph_algorithms/s21_graph_algorithms.a console_interface/ConsoleInterface_menu.cpp console_interface/ConsoleInterfaceInstance.cpp -o run
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

test:
	g++ tests/tests.cpp s21_graph/s21_graph.a s21_graph_algorithms/s21_graph_algorithms.a -o tests/test -lgtest -std=c++17 -lgvc -lcgraph
	./tests/test
	rm -f tests/test tests/test_graph.dot tests/test_graph2.gv
