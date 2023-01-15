#ifndef GRAPH_H
#define GRAPH_H


#include <iostream>

class Graph
{
public:
	Graph();
	Graph(const Graph &other);
	~Graph();

	Graph &operator=(const Graph &other);

	void loadGraphFromFile(std::string filename);
	void exportGraphToDot(std::string filename);
//	const std::string &getName() const;
//	int getGrade() const;
//	void incrementGrade();
//	void decrementGrade();


//	class GradeTooHighException: public std::exception
//	{
//	public:
//		virtual const char *what() const throw();
//	};

private:
//	const std::string	_name;
//	int 				_grade;
//
//	void setGrade(int grade);
};

//std::ostream	&operator<<(std::ostream &o, Graph *a);

#endif
