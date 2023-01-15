#include "Graph.h"

Graph::Graph():
{
}

Graph::Graph(const std::string &name): _name(name), _grade(150)
{
}

Graph::~Graph()
{
}

Graph::Graph(const Graph &other):
{
	*this = other;
}

Graph &Graph::operator=(const Graph &other)
{
	if (&other != this)
		setGrade(other.getGrade());
	return *this;
}

const std::string &Graph::getName() const
{
	return _name;
}

int Graph::getGrade() const
{
	return _grade;
}


void Graph::incrementGrade()
{
	setGrade(getGrade() - 1);
}

//std::ostream	&operator<<(std::ostream &os, Graph *b)
//{
//	os << "Bureaucrat's \"" << b->getName() << "\" grade: " << b->getGrade() << std::endl;
//	return (os);
//}

//const char *Graph::GradeTooHighException::what() const throw()
//{
//	return "Grade too high";
//}
//
//const char *Graph::GradeTooLowException::what() const throw()
//{
//	return "Grade too low";
//}
