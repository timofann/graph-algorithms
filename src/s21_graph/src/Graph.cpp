#include "Graph.h"

Graph::Graph(): a_matrix(nullptr), a_matrix_size(0)
{
}

Graph::Graph(unsigned **matrix, size_t size): a_matrix(nullptr), a_matrix_size(0)
{
	set_a_matrix(matrix, size);
}

Graph::~Graph()
{
	for (unsigned i = 0; i < a_matrix_size; ++i)
		delete[] a_matrix[i];
	delete[] a_matrix;
}

Graph::Graph(const Graph &other): a_matrix(nullptr), a_matrix_size(0)
{
	set_a_matrix(other.a_matrix, other.a_matrix_size);
}

Graph &Graph::operator=(const Graph &other)
{
	if (&other != this)
		set_a_matrix(other.a_matrix, other.a_matrix_size);
	return *this;
}

size_t Graph::size() const
{
	return this->a_matrix_size;
}

void Graph::set_a_matrix(unsigned **matrix, size_t size)
{
	for (unsigned i = 0; i < a_matrix_size; ++i)
		delete[] a_matrix[i];
	delete[] this->a_matrix;
	a_matrix_size = size;
	a_matrix = new unsigned*[size];
	for (unsigned i = 0; i < size; ++i)
	{
		a_matrix[i] = new unsigned[size];
		for (unsigned j = 0; j < size; ++j)
		{
			a_matrix[i][j] = matrix[i][j];
		}
	}
}

void Graph::loadGraphFromFile(std::string filename)
{
	std::cout << filename;
}

void Graph::exportGraphToDot(std::string filename)
{
	std::cout << filename;
}

std::ostream	&operator<<(std::ostream &os, Graph *b)
{
	// todo Print values of matrix in dot format
	os << b->size();
	return (os);
}

//const char *Graph::GradeTooHighException::what() const throw()
//{
//	return "Grade too high";
//}
//
//const char *Graph::GradeTooLowException::what() const throw()
//{
//	return "Grade too low";
//}
