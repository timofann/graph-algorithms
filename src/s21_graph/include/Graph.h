#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <charconv>
#include <sstream>
#include <fstream>

class Graph
{
public:
	Graph(unsigned **matrix, size_t size);

	Graph(const Graph &other);

	~Graph();

	Graph &operator=(const Graph &other);

	void loadGraphFromFile(const std::string &filename);

	void exportGraphToDot(const std::string &filename);

	[[nodiscard]] size_t size() const;
	std::string generateDotString();

	class WrongMatrixException : public std::exception
	{
	public:
		[[nodiscard]] const char *what() const noexcept override;
	};

private:
	Graph();

	unsigned **a_matrix;
	size_t a_matrix_size;
	bool weighted;

	void set_a_matrix(unsigned **matrix, size_t size);

	static void check_matrix(unsigned int *const *matrix, size_t size);

};

std::ostream &operator<<(std::ostream &o, Graph *a);

#endif
