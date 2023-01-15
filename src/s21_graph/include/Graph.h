#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

class Graph
{
public:
	Graph(unsigned **matrix, size_t size);
	Graph(const Graph &other);
	~Graph();

	Graph &operator=(const Graph &other);

	void loadGraphFromFile(std::string filename);
	void exportGraphToDot(std::string filename);
	[[nodiscard]] size_t size() const;



//	class GradeTooHighException: public std::exception
//	{
//	public:
//		virtual const char *what() const throw();
//	};

private:
	Graph();

	unsigned** a_matrix;
	size_t a_matrix_size;

	void set_a_matrix(unsigned ** matrix, size_t size);
};

//std::ostream	&operator<<(std::ostream &o, Graph *a);

#endif
