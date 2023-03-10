//#include "../include/Graph.h"
//#include "../s21_graph.h"

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <charconv>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>

//using namespace s21;


static void clear_matrix(unsigned **array_num, size_t matrix_size) 
{
    for (size_t s = 0; s < matrix_size; s++) 
        delete[] array_num[s];
    delete[] array_num;
}

static size_t count_rows(const std::string &filename)
{
    std::ifstream inf;
	inf.open(filename, std::ifstream::in);
	std::string str0;;
    size_t matrix_size = 0;
    std::getline(inf, str0);
	while (!inf.eof())
	{
		std::getline(inf, str0);
		if (!str0.empty())
			matrix_size++;
		while(str0.empty())
		{
			str0 = "";
			std::getline(inf, str0);
			if (inf.eof())
				break;
		}
	}
	inf.close();
	return matrix_size;
}

//Graph Graph::loadGraphFromFile(const std::string &filename) {
void loadGraphFromFile(const std::string &filename) {
    std::ifstream inf;
    size_t size = 0;
    size_t rows = 0;
    
	std::string str2;	
    std::size_t pos{};
    std::vector<unsigned> tmp;
	
    inf.open(filename, std::ifstream::in);
	if (!inf.is_open()){
		throw std::runtime_error{"Incorrect file path"};
	}
	if (inf.eof() == true){
		throw std::runtime_error{"Empty file"};
	}
    inf >> size;
   if (inf.fail() == true || size < 2) {
		throw std::runtime_error{"Bad data on file"};
   }
 rows = count_rows(filename);
 size_t count = 0;
  std::getline(inf, str2);
	unsigned **array_num = new unsigned*[size];//выделяем память под строки
    for (size_t i = 0; i < size; i++)
    {
		std::getline(inf, str2);
		if (str2.empty())
            throw std::runtime_error("wrong matrix");
        std::istringstream ss;
        ss.str(str2);
		for (std::string str3; std::getline(ss, str3, ' '); )
		{
            if (str3.find(' '))
                throw std::runtime_error("wrong matrix");            
			tmp.push_back(std::stoi(str3, &pos));
            str3 = "";
        }
        if (tmp.size() != size)
        {
            delete[] array_num;
            throw std::runtime_error("wrong matrix");
        }
        array_num[i] = new unsigned[tmp.size()];
        std::copy(tmp.begin(), tmp.end(), array_num[i]);
        
        //для проверки
        for (size_t col = 0; col < size; col++) 
        {
            std::cout << "arr " << i << "-" << array_num[i][col] << ' ';
        }
        std::cout << std::endl;
        //для проверки
        tmp.clear();
        count++;
	}
        std::cout << "tmp.size 1 " << tmp.size() << " count " << count <<std::endl;
    if (count != rows)
    {
        clear_matrix(array_num, size);
        throw std::runtime_error("wrong matrix");
    }
	inf.close();
	//Graph date(array_num, size);
	clear_matrix(array_num, size);
    //return date; //check leaks
}


int main() {
	// loadGraphFromFile("test.txt");
    // loadGraphFromFile("bad_graphs/1.txt");
    // loadGraphFromFile("bad_graphs/2.txt");
    // loadGraphFromFile("bad_graphs/3.txt");
    // loadGraphFromFile("bad_graphs/4.txt");
    // loadGraphFromFile("bad_graphs/6.txt");
    // loadGraphFromFile("bad_graphs/7.txt");
    // loadGraphFromFile("bad_graphs/8.txt");
    //  loadGraphFromFile("bad_graphs/9.txt");
    // loadGraphFromFile("bad_graphs/10.txt"); 
    //loadGraphFromFile("bad_graphs/11.txt"); 
    // loadGraphFromFile("bad_graphs/12.txt"); 
    // loadGraphFromFile("bad_graphs/13.txt");
    // loadGraphFromFile("bad_graphs/14.txt");
    // loadGraphFromFile("bad_graphs/15.txt");
}