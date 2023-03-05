all: s21_graph.a s21_graph_algorithms.a
	g++ -std=c++17 main_test.cpp s21_graph/s21_graph.a s21_graph_algorithms/s21_graph_algorithms.a
	./a.out

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
	g++ s21_graph/s21_graph.a s21_graph_algorithms/s21_graph_algorithms.a tests/tests.cc -o test -lgtest -std=c++17
	./test
	rm -f test

interface: $(NAME)
	g++ main.cpp console_interface/ConsoleInterface.cpp -std=c++17 s21_graph/s21_graph.a  console_interface/ConsoleInterface_menu.cpp console_interface/ConsoleInterfaceInstance.cpp
	./a.out
