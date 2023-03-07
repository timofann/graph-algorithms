#include <gtest/gtest.h>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

#include "../s21_graph/s21_graph.h"
#include "../s21_graph_algorithms/s21_graph_algorithms.h"

// g++ s21_graph/s21_graph.a s21_graph_algorithms/s21_graph_algorithms.a tests/tests.cc -o test -lgtest -std=c++17 -lgvc -lcgraph


/* ------------------------------------------------------------------------------------------------------------ Graph */

TEST(graph, NullZeroConstruction) {
    EXPECT_ANY_THROW(s21::Graph graph(NULL, 0));
}

TEST(graph, NonNullZeroConstruction) {
    unsigned **matrix = new unsigned *[0];
    EXPECT_ANY_THROW(s21::Graph graph(matrix, 0));
    delete [] matrix;
}

TEST(graph, ElementaryConstruction) {
    unsigned **matrix = new unsigned *[1]{new unsigned[1]{0}};
    EXPECT_ANY_THROW(s21::Graph graph(matrix, 1));
    delete matrix[0];
    delete [] matrix;
}

TEST(graph, NullZeroConstruction) {
    unsigned **matrix = new unsigned *[2]{new unsigned[2]{0, 1}, new unsigned[2]{1, 0}};
    s21::Graph graph(matrix, 2);
    EXPECT_EQ(graph.size(), 2);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ([)matrix[i][j], graph[i][j]);
        }
        delete matrix[i];
    }
    delete [] matrix;

}

/* ------------------------------------------------------------------------------------------------------------ Graph */


/* ------------------------------------------------------------------------------------------------ loadGraphFromFile */

TEST(graph, loadStandardGraphFromFile) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    EXPECT_EQ(graph.size(), 11);
}

TEST(graph, loadElementaryGraphFromFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/3.txt"));
} // wrong matrix, но граф может состоять из одной вершины ! ошиблась, по сабджу не может (эту проверку лучше делать в конструкторе, а не в парсере)

TEST(graph, loadSmallGraphFromFile) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    EXPECT_EQ(graph.size(), 2);
}

TEST(graph, loadNonExistGraphFromFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/0.txt"));
}

TEST(graph, loadNullGraphFromFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/1.txt"));
} // создается нулевой граф, не соответствует сабджекту (ошибка должна обрабатываться в конструкторе)

TEST(graph, loadDirectedGraphFromFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/2.txt"));
}

TEST(graph, loadIncompleteGraphFromFile) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    EXPECT_EQ(graph.size(), 5);
}

TEST(graph, loadOneSideDirectedGraphFromFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/4.txt"));
}

TEST(graph, loadGraphFromEmptyFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/6.txt"));
}

TEST(graph, loadGraphFromNonReadableFile) {
    std::system("chmod 000 tests/bad_graphs/7.txt");
    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/7.txt"));
    std::system("chmod 777 tests/bad_graphs/7.txt");
} // не та ошибка бросается: файл есть, нет прав на чтение

//TEST(graph, loadGraphFromFileWithoutRowsNumber) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/8.txt");
//    EXPECT_EQ(graph.size(), 3); // вместо ошибки кидается exit
//} //expect Fail test

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

TEST(graph, exportStandardGraphToDot) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    graph.exportGraphToDot("test_graph.dot");
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    gvc = gvContext();
    fp = fopen("test_graph.dot", "r");
    g = agread(fp, 0);
    int agraph_size = agnnodes(g);
    gvFreeLayout(gvc, g);
    agclose(g);
    fclose(fp);
    gvFreeContext(gvc);
    EXPECT_EQ(graph.size(), agraph_size);
}

TEST(graph, exportIncompleteGraphToDot) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
    graph.exportGraphToDot("test_graph2.gv");
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    gvc = gvContext();
    fp = fopen("test_graph2.gv", "r");
    g = agread(fp, 0);
    int agraph_size = agnnodes(g);
    gvFreeLayout(gvc, g);
    agclose(g);
    fclose(fp);
    gvFreeContext(gvc);
    EXPECT_EQ(graph.size(), agraph_size);
}

TEST(graph, exportGraphToDotWithoutExtension) {
    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/graphs/5.txt").exportGraphToDot("test_graph"));
}

TEST(graph, exportGraphToDotWrongExtension) {
    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/graphs/5.txt").exportGraphToDot("test_graph.hello"));
}

TEST(graph, exportGraphToNonWritableDot) {
    std::system("chmod 000 tests/dot_files/test_graph.dot");
    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/graphs/5.txt").exportGraphToDot("tests/dot_files/test_graph.dot"));
    std::system("chmod 777 tests/dot_files/test_graph.dot");
}

TEST(graph, exportGraphToExistingDot) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    graph.exportGraphToDot("tests/dot_files/test_graph2.dot");
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    gvc = gvContext();
    fp = fopen("tests/dot_files/test_graph2.dot", "r");
    g = agread(fp, 0);
    int agraph_size = agnnodes(g);
    gvFreeLayout(gvc, g);
    agclose(g);
    fclose(fp);
    gvFreeContext(gvc);
    EXPECT_EQ(graph.size(), agraph_size);
    s21::Graph::loadGraphFromFile("tests/graphs/5.txt").exportGraphToDot("tests/dot_files/test_graph2.dot");
}

/* ------------------------------------------------------------------------------------------------- exportGraphToDot */


/* ----------------------------------------------------------------------------------------------------------- search */

TEST(graph_algorithms, depthFirstSearchStandard) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    std::vector<int> res = s21::GraphAlgorithms::depthFirstSearch(graph, 1);
    std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    EXPECT_EQ(res, vec);
}

TEST(graph_algorithms, depthFirstSearchSmall) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    std::vector<int> res = s21::GraphAlgorithms::depthFirstSearch(graph, 2);
    std::vector<int> vec{ 2, 1 };
    EXPECT_EQ(res, vec);
}

TEST(graph_algorithms, breadthFirstSearchStandard) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    std::vector<int> res = s21::GraphAlgorithms::breadthFirstSearch(graph, 1);
    std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    EXPECT_EQ(res, vec);
}

TEST(graph_algorithms, breadthFirstSearchSmall) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    std::vector<int> res = s21::GraphAlgorithms::breadthFirstSearch(graph, 2);
    std::vector<int> vec{ 2, 1 };
    EXPECT_EQ(res, vec);
}

TEST(graph_algorithms, breadthFirstSearchErrorLargeVertex) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    EXPECT_THROW(s21::GraphAlgorithms::breadthFirstSearch(graph, 3), s21::GraphAlgorithms::GraphAlgorithmsError);
}

TEST(graph_algorithms, breadthFirstSearchErrorZeroVertex) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    EXPECT_THROW(s21::GraphAlgorithms::breadthFirstSearch(graph, 0), s21::GraphAlgorithms::GraphAlgorithmsError);
}

TEST(graph_algorithms, depthFirstSearchIncomplete) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    std::vector<int> res = s21::GraphAlgorithms::depthFirstSearch(graph, 2);
    std::vector<int> vec{ 2, 1, 3, 4, 5 };
    EXPECT_EQ(res, vec);
}

/* ----------------------------------------------------------------------------------------------------------- search */



//TEST(graph_algorithms, GetShortestPathBetweenVertices) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
//    int res = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 11);
//    EXPECT_EQ(res, 18);
//}

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

//TEST(graph_algorithms, AntColonyOptimization) {
//    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/3.txt");
//    s21::GraphAlgorithms::TsmResult res = s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph);
//    EXPECT_EQ(res.distance, 40);
//}




int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
