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
        explicit Graph(unsigned **matrix, size_t size);

        Graph(const Graph &other);
        Graph(Graph &&other);

        ~Graph(); // правило пяти

        Graph &operator=(const Graph &other);
        Graph &operator=(Graph &&other);

        static Graph loadGraphFromFile(const std::string &filename);

        void exportGraphToDot(const std::string &filename) const;

        [[nodiscard]] size_t size() const noexcept;
        std::string generateDotString() const noexcept;

//        class WrongMatrixException : public std::exception
//        {
//        public:
//            [[nodiscard]] const char *what() const noexcept override;
//        };

        struct GraphException : std::runtime_error {
            explicit GraphException(const std::string &arg);
        };

        struct WrongMatrixException : GraphException {
            explicit WrongMatrixException(const std::string &arg = "Wrong matrix.");
        };

        struct TooLargeGraph : GraphException {
            explicit TooLargeGraph();
        };

        struct CantOpenFile : GraphException {
            explicit CantOpenFile(const std::string &filename);
        };

        const unsigned *operator[](size_t) const;

    private:
        Graph();

        unsigned **a_matrix; // google style названия приватных переменных должны заканчиваться знаком подчеркивания _
        size_t a_matrix_size;
        bool weighted;

        void set_a_matrix(unsigned **matrix, size_t size);
        
        /*loadGraphFromFile*/
        void clearMatrix(unsigned **matrix, size_t rows) noexcept;
        /*loadGraphFromFile*/

        static void check_matrix(unsigned int *const *matrix, size_t size);

		static void throw_cant_open_file(const std::string &filename);
	};

} // namespace s21

std::ostream &operator<<(std::ostream &o, const s21::Graph &a);

#endif
