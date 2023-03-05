#include <gtest/gtest.h>

#include "../s21_graph_algorithms/s21_graph_algorithms.h"

TEST(graph, Load) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    EXPECT_EQ(graph.size(), 11);
}

TEST(graph, exportGraphToDot) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    graph.exportGraphToDot("test_graph.dot");
    SUCCEED();
}

TEST(graph, exportGraphToDot2) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
    graph.exportGraphToDot("test_graph2.dot");
    SUCCEED();
}

TEST(graph_algorithms, depthFirstSearch) {
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
