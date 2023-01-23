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
	check_matrix(matrix, size);

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

void dfs(unsigned start, unsigned *const *matrix, std::vector<bool> *used, size_t size) {

	std::stack<unsigned> stack;

	stack.push(start);
	while (! stack.empty()) {
		auto current = stack.top();
		stack.pop();
		(*used)[current] = true;
		for (unsigned i = 0; i < size; ++i) {
			if (matrix[current][i] == 1 && ! (*used)[i]) {
				stack.push(i);
			}
		}
	}
}

void Graph::check_matrix(unsigned *const *matrix, size_t size)
{
	std::vector<bool> used;

	int res = 0;
	used.push_back(false);

	for (unsigned i = 0; i < size; ++i)
	{
		unsigned cons = 0;

		for (unsigned j = 0; j < size; ++j)
		{
			if (matrix[i][j] != matrix[j][i])
				throw WrongMatrixException();
			cons += matrix[i][j];
		}
		if (cons == 0) {
			throw WrongMatrixException();
		}
		if (! used[i]) {
			dfs(i, matrix, &used, size);
			res++;
		}
		if (res > 1) {
			throw WrongMatrixException();
		}

	}
}

void Graph::loadGraphFromFile(const std::string& filename)
{
	std::cout << filename;
}

void Graph::exportGraphToDot(const std::string& filename)
{
	std::cout << filename;
}

std::ostream	&operator<<(std::ostream &os, Graph *b)
{
	// todo Print values of matrix in dot format
	os << b->size();
	return (os);
}

const char *Graph::WrongMatrixException::what() const noexcept
{
	return "wrong matrix";
}
