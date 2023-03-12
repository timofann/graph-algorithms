#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <charconv>
#include <sstream>
#include <fstream>

namespace s21 {

    class Graph
    {
    public:
        Graph(unsigned **matrix, size_t size); //explicit

        Graph(const Graph &other);

        ~Graph(); // правило пяти

        Graph &operator=(const Graph &other);

        static Graph loadGraphFromFile(const std::string &filename);

        void exportGraphToDot(const std::string &filename) const; // const

        [[nodiscard]] size_t size() const; //noexcept
        std::string generateDotString(); // const

        class WrongMatrixException : public std::exception
        {
        public:
            [[nodiscard]] const char *what() const noexcept override;
        };

        const unsigned *operator[](size_t) const;

    private:
        Graph();

        unsigned **a_matrix; // google style названия приватных переменных должны заканчиваться знаком подчеркивания _
        size_t a_matrix_size;
        bool weighted;

        void set_a_matrix(unsigned **matrix, size_t size);
        
        /*loadGraphFromFile*/
        void clearMatrix(unsigned **matrix, size_t rows);
        /*loadGraphFromFile*/

        static void check_matrix(unsigned int *const *matrix, size_t size); // const

    };

} // namespace s21

std::ostream &operator<<(std::ostream &o, s21::Graph *a);

#endif
