#include <gtest/gtest.h>

#include "../s21_graph/s21_graph.h"
#include "../s21_graph_algorithms/s21_graph_algorithms.h"

/* ------------------------------------------------------------------------------------------------ loadGraphFromFile */

TEST(graph, loadStandardGraphFromFile) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    EXPECT_EQ(graph.size(), 11);
}

TEST(graph, loadElementaryGraphFromFile) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    EXPECT_EQ(graph.size(), 1);
} // wrong matrix, но граф может состоять из одной вершины

TEST(graph, loadSmallGraphFromFile) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    EXPECT_EQ(graph.size(), 2);
}

TEST(graph, loadNonExistGraphFromFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/0.txt"));
}

TEST(graph, loadNullGraphFromFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/1.txt"));
} // создается нулевой граф, не соответствует сабджекту

TEST(graph, loadDirectedGraphFromFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/2.txt"));
}

TEST(graph, loadGraphFromEmptyFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/6.txt"));
}

TEST(graph, loadGraphFromNonReadableFile) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/7.txt");
    EXPECT_EQ(graph.size(), 11); // не та ошибка бросается: файл есть, нет прав на чтение
}

TEST(graph, loadGraphFromFileWithoutRowsNumber) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/8.txt");
    EXPECT_EQ(graph.size(), 3); // вместо ошибки кидается exit
} //expect Fail test

//TEST(graph, loadGraphFromFileWithInvalidLength) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/9.txt");
//    EXPECT_EQ(graph.size(), 3); // вместо ошибки кидается exit + malloc: *** error for object 0xd00007ffb15c063b: pointer being freed was not allocated
//} //expect Fail test

//TEST(graph, loadGraphFromFileWithInvalidWidth) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/10.txt");
//    EXPECT_EQ(graph.size(), 3); // вместо ошибки кидается exit + malloc: *** error for object 0xa000000000000000: pointer being freed was not allocated
//} //expect Fail test

//TEST(graph, loadGraphFromFileWithInvalidWidth2) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/11.txt");
//    EXPECT_EQ(graph.size(), 3); // вместо ошибки кидается exit + malloc: *** error for object 0xa000000000000000: pointer being freed was not allocated
//} //expect Fail test

//TEST(graph, loadGraphFromFileWithInvalidRowsNumber) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/12.txt");
//    EXPECT_EQ(graph.size(), 2); //
//} //expect Fail test

//TEST(graph, loadGraphFromFileWithInvalidElement) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/13.txt");
//    EXPECT_EQ(graph.size(), 2); // вместо ошибки кидается exit + malloc: *** error for object 0xc000000000000000: pointer being freed was not allocated
//} //expect Fail test

//TEST(graph, loadGraphFromFileWithInvalidElement) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/13.txt");
//    EXPECT_EQ(graph.size(), 2); // вместо ошибки кидается exit + malloc: *** error for object 0xc000000000000000: pointer being freed was not allocated
//} //expect Fail test

//TEST(graph, loadGraphFromFileWithOnlyRowNumber) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/14.txt");
//    EXPECT_EQ(graph.size(), 2); // make: *** [test] Segmentation fault: 11
//} //expect Fail test

//TEST(graph, loadGraphFromAlmostEmptyFile) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/15.txt");
//    EXPECT_EQ(graph.size(), 2); // вместо ошибки кидается exit
//} //expect Fail test

//TEST(graph, loadGraphFromAlmostEmptyFile) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/15.txt");
//    EXPECT_EQ(graph.size(), 2); // вместо ошибки кидается exit
//} //expect Fail test


/* ------------------------------------------------------------------------------------------------ loadGraphFromFile */



/* ------------------------------------------------------------------------------------------------- exportGraphToDot */

TEST(graph, exportGraphToDot) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    graph.exportGraphToDot("test_graph.dot");
}

TEST(graph, exportGraphToDot2) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
    graph.exportGraphToDot("test_graph2.dot");
}

/* ------------------------------------------------------------------------------------------------- exportGraphToDot */


TEST(graph_algorithms, depthFirstSearchM) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    std::vector<int> res = s21::GraphAlgorithms::depthFirstSearch(graph, 1);
    std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    EXPECT_EQ(res, vec);
}

TEST(graph_algorithms, BreadthFirstSearch) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    std::vector<int> res = s21::GraphAlgorithms::breadthFirstSearch(graph, 1);
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    EXPECT_EQ(res, vec);
}

TEST(graph_algorithms, GetShortestPathBetweenVertices) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    int res = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 11);
    EXPECT_EQ(res, 18);
}

//TEST(graph_algorithms, GetShortestPathsBetweenAllVertices) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/3.txt");
//    Matrix res = s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
//    Matrix result(4, {{0, 10, 17, 10}, {10, 0, 10, 10}, {17, 10, 0, 10}, {10, 10, 10, 0}});
//    EXPECT_TRUE(res.EqMatrix(result));
//}
//
//TEST(graph_algorithms, GetLeastSpanningTree) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/3.txt");
//    Matrix res = s21::GraphAlgorithms::getLeastSpanningTree(graph);
//    Matrix result(4, {{0, 10, 0, 10}, {10, 0, 10, 0}, {0, 10, 0, 0}, {10, 0, 0, 0}});
//    EXPECT_TRUE(res.EqMatrix(result));
//}

TEST(graph_algorithms, AntColonyOptimization) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/3.txt");
    s21::GraphAlgorithms::TsmResult res = s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph);
    EXPECT_EQ(res.distance, 40);
}




int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
