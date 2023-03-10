#include "../include/Graph.h"
#include <filesystem>

using namespace s21;

Graph::Graph() : a_matrix(nullptr), a_matrix_size(0), weighted(false) // можно вообще не определять конструктор, если он не используется внутри класса и является приватным. Объявить нужно, чтобы не создался конструктор по умолчанию
{
}

Graph::Graph(unsigned **matrix, size_t size) :
		a_matrix(nullptr), a_matrix_size(0), weighted(false)
{
	set_a_matrix(matrix, size);
}

Graph::~Graph()
{
	for (unsigned i = 0; i < a_matrix_size; ++i)
		delete[] a_matrix[i];
	delete[] a_matrix;
}

Graph::Graph(const Graph &other) :
a_matrix(nullptr), a_matrix_size(0), weighted(false) // неконстантные и нессылочные поля не обязательно здесь определять, они автоматически заполнятся значениями по умолчанию
{
	set_a_matrix(other.a_matrix, other.a_matrix_size);
}

Graph &Graph::operator=(const Graph &other)
{
	if (&other != this)
		set_a_matrix(other.a_matrix, other.a_matrix_size);
	return *this;
} // по правилу 5 нужно ещё 2 конструктора

size_t Graph::size() const
{
	return this->a_matrix_size;
}

void Graph::set_a_matrix(unsigned **matrix, size_t size) // нет проверки на нулевую матрицу или я не нашла, также нужна проверка на то, что size не больше INT_MAX, это важно в алгоритмах
{
	check_matrix(matrix, size);

	for (unsigned i = 0; i < a_matrix_size; ++i)
		delete[] a_matrix[i];
	delete[] this->a_matrix;
	a_matrix_size = size;
	a_matrix = new unsigned *[size];
	for (unsigned i = 0; i < size; ++i)
	{
		a_matrix[i] = new unsigned[size];
		for (unsigned j = 0; j < size; ++j)
		{
			a_matrix[i][j] = matrix[i][j];
			if (!weighted && a_matrix[i][j] > 1)
			{
				weighted = true;
			}
		}
	}
}

void dfs(unsigned start, unsigned *const *matrix, std::vector<bool> *used,
		 size_t size)
{

	std::stack<unsigned> stack;

	stack.push(start);
	while (!stack.empty())
	{
		auto current = stack.top();
		stack.pop();
		(*used)[current] = true;
		for (unsigned i = 0; i < size; ++i)
		{
			if (matrix[current][i] != 0 && !(*used)[i])
			{
				stack.push(i);
			}
		}
	}
}

std::string *generate_node_names(unsigned count)
{
	auto names = new std::string[count];
	int base_len = -2;
	char char_idx = 'a';
	std::string s;
	for (unsigned i = 0; i < count; ++i)
	{
		if (i % 26 == 0)
		{
			char_idx = 'a';
			base_len++;
		}
		char c = char_idx++;
		if (i > 25)
		{
			s = {c, char(base_len + 48)};
		} else
		{
			s = {c};
		}

		names[i] = s;
	}
	return names;
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
		if (cons == 0)
		{
			throw WrongMatrixException();
		}
		if (!used[i])
		{
			dfs(i, matrix, &used, size);
			res++;
		}
		if (res > 1)
		{
			throw WrongMatrixException(); // можно в порядке низкого приоритета все ошибки оформить вот так
		}

	}
}

//void Graph::loadGraphFromFile(const std::string &filename)
//{
//	std::cout << filename;
//}

void Graph::exportGraphToDot(const std::string &filename)
{
	std::ofstream ofs;

	std::filesystem::path filepath = filename;
	if (filepath.extension() != ".gv" && filepath.extension() != ".dot")
	{
		throw std::invalid_argument("Wrong extension of file");
	}

	ofs.open(filename);
	if (! ofs.is_open()) // Разная обработка файлов в loadGraph и exportGraph, необходимо унифицировать
	{
		std::cerr << "Can't open file: " << filename << std::endl; // библиотека не должна печатать, только кидать ошибки
	}
	else
	{
		ofs << this;
		ofs.close();
	}
}

std::string Graph::generateDotString()
{
	std::stringstream res;
	std::string pp_ident = "    ";
	auto nn = generate_node_names(this->a_matrix_size);
	unsigned current_iter = 0;

	res << "graph {\n";
	for (unsigned i = 0; i < this->a_matrix_size; ++i)
	{
		for (unsigned j = i; j < this->a_matrix_size; ++j)
		{
			if (this->a_matrix[i][j] == 0)
			{
				continue;
			}
			res << pp_ident << nn[i] << " -- " << nn[j];
			if (weighted) {
				res << " [weight=" << a_matrix[i][j] << "]";
			}
			res << "\n";
			current_iter++;
		}
	}
	res << "}\n";
	delete []nn;
	return res.str();
}

std::ostream &operator<<(std::ostream &os, Graph *b) // почему работаем с указателем на граф, а не с объектом? А вдруг реально будет нужно указатель распечатать?
{
	os << b->generateDotString();
	return (os);
}

const char *Graph::WrongMatrixException::what() const noexcept // можно просто унаследоваться от runtime_error или другой ошибки, тогда переопределять what не нужно. Субъективно на мой взгляд элегантнее, просто как вариант
{
	return "wrong matrix";
}

const unsigned *Graph::operator[](size_t row) const { // нужно проверить за мной этот метод, потому что его я просто накидала, чтобы работало
    return this->a_matrix[row];
}