#include <gtest/gtest.h>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

#include "../s21_graph/s21_graph.h"
#include "../s21_graph_algorithms/s21_graph_algorithms.h"

/* ------------------------------------------------------------------------------------------- GraphMatrixConstructor */

TEST(GraphMatrixConstructor, NullZeroThrowsException) {
    EXPECT_ANY_THROW(s21::Graph graph(NULL, 0));
}

//TEST(GraphMatrixConstructor, NullNonZeroThrowsException) {
//    EXPECT_ANY_THROW(s21::Graph graph(NULL, 3));
//} segmentation

TEST(GraphMatrixConstructor, NonNullZeroThrowException) {
    unsigned **matrix = new unsigned *[0];
    EXPECT_ANY_THROW(s21::Graph graph(matrix, 0));
    delete [] matrix;
}

TEST(GraphMatrixConstructor, NonNullElementaryMatrixConstructorThrowsException) {
    unsigned **matrix = new unsigned *[1]{new unsigned[1]{0}};
    EXPECT_ANY_THROW(s21::Graph graph(matrix, 1));
    delete matrix[0];
    delete [] matrix;
}

//TEST(GraphMatrixConstructor, NullElementaryThrowsException) {
//    EXPECT_ANY_THROW(s21::Graph graph(NULL, 1));
//} segmentation

/* ------------------------------------------------------------------------------------------- GraphMatrixConstructor */


/* --------------------------------------------------------------------------------------------- GraphCopyConstructor */

TEST(GraphCopyConstructor, CopyConstructorDoesRightCopy) {
    unsigned **matrix = new unsigned *[2]{new unsigned[2]{0, 1}, new unsigned[2]{1, 0}};
    s21::Graph graph(matrix, 2);
    EXPECT_EQ(graph.size(), 2);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(matrix[i][j], graph[i][j]);
        delete matrix[i];
    }
    delete [] matrix;
}

TEST(GraphCopyConstructor, ReallocatesMemory) {
    unsigned **matrix = new unsigned *[2]{new unsigned[2]{0, 1}, new unsigned[2]{1, 0}};
    s21::Graph graph(matrix, 2);
    s21::Graph graph2(graph);
    EXPECT_NE(&graph, &graph2);
    EXPECT_NE(graph[0], graph2[0]);
    for (int i = 0; i < 2; ++i)
        delete matrix[i];
    delete [] matrix;
}

/* --------------------------------------------------------------------------------------------- GraphCopyConstructor */


/* ---------------------------------------------------------------------------------------------- GraphCopyAssignment */

TEST(GraphCopyAssignment, DoesRightCopy) {
    unsigned **matrix = new unsigned *[2]{new unsigned[2]{0, 1}, new unsigned[2]{1, 0}};
    s21::Graph graph(matrix, 2);
    s21::Graph graph2(graph);
    EXPECT_EQ(graph.size(), graph2.size());
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(graph2[i][j], graph[i][j]);
        delete matrix[i];
    }
    delete [] matrix;
}

TEST(GraphCopyAssignment, ReallocatesMemory) {
    unsigned **matrix = new unsigned *[2]{new unsigned[2]{0, 1}, new unsigned[2]{1, 0}};
    s21::Graph graph(matrix, 2);
    s21::Graph graph2(graph);
    EXPECT_NE(&graph, &graph2);
    EXPECT_NE(graph[0], graph2[0]);
    for (int i = 0; i < 2; ++i)
        delete matrix[i];
    delete [] matrix;
}

TEST(GraphCopyAssignment, SelfAssignmentDoesNotReallocateMemory) {
    unsigned **matrix = new unsigned *[2]{new unsigned[2]{0, 1}, new unsigned[2]{1, 0}};
    s21::Graph graph(matrix, 2);
    s21::Graph *old_ptr_graph = &graph;
    graph = graph;
    s21::Graph *new_ptr_graph = &graph;
    for (int i = 0; i < 2; ++i)
        delete matrix[i];
    delete [] matrix;
    EXPECT_EQ(old_ptr_graph, new_ptr_graph);
    EXPECT_EQ((*old_ptr_graph)[0], (*new_ptr_graph)[0]);
}

/* ---------------------------------------------------------------------------------------------- GraphCopyAssignment */


/* ------------------------------------------------------------------------------------------------ loadGraphFromFile */

TEST(LoadGraphFromFile, LoadsFile) {
    EXPECT_EQ(s21::Graph::loadGraphFromFile("tests/graphs/1.txt").size(), 11);
    EXPECT_EQ(s21::Graph::loadGraphFromFile("tests/graphs/2.txt").size(), 2);
    EXPECT_EQ(s21::Graph::loadGraphFromFile("tests/graphs/3.txt").size(), 4);
    EXPECT_EQ(s21::Graph::loadGraphFromFile("tests/graphs/4.txt").size(), 5);
    EXPECT_EQ(s21::Graph::loadGraphFromFile("tests/graphs/5.txt").size(), 5);
}

TEST(LoadGraphFromFile, ElementaryGraph) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/3.txt"));
} // эта ошибка должна обрабатываться в конструкторе


TEST(LoadGraphFromFile, NonExistFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/0.txt"));
}

TEST(LoadGraphFromFile, loadNullGraphFromFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/1.txt"));
} // эта ошибка должна обрабатываться в конструкторе

TEST(LoadGraphFromFile, DirectedGraph) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/2.txt"));
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/4.txt"));
}

TEST(LoadGraphFromFile, EmptyFile) {
    EXPECT_ANY_THROW(s21::Graph graph = s21::Graph::loadGraphFromFile("tests/bad_graphs/6.txt"));
}

TEST(LoadGraphFromFile, NonReadableFile) {
    std::system("chmod 000 tests/bad_graphs/7.txt");
    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/7.txt"));
    std::system("chmod 777 tests/bad_graphs/7.txt");
} // не та ошибка бросается: файл есть, нет прав на чтение

//TEST(LoadGraphFromFile, WithoutRowsNumber) {
//    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/8.txt")); // вместо ошибки кидается exit
//}

//TEST(LoadGraphFromFile, InvalidLength) {
//    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/9.txt")); // вместо ошибки кидается exit + malloc: *** error for object 0xd00007ffb15c063b: pointer being freed was not allocated
//}

//TEST(LoadGraphFromFile, InvalidWidth) {
//    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/10.txt")); // вместо ошибки кидается exit + malloc: *** error for object 0xa000000000000000: pointer being freed was not allocated
//    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/11.txt")); // вместо ошибки кидается exit + malloc: *** error for object 0xa000000000000000: pointer being freed was not allocated
//}

//TEST(LoadGraphFromFile, InvalidRowsNumber) {
//    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/12.txt"));
//}

//TEST(LoadGraphFromFile, InvalidElement) {
//    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/13.txt")); // вместо ошибки кидается exit + malloc: *** error for object 0xc000000000000000: pointer being freed was not allocated
//}

//TEST(LoadGraphFromFile, OnlyRowNumber) {
//    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/14.txt")); // make: *** [test] Segmentation fault: 11
//}

//TEST(LoadGraphFromFile, AlmostEmptyFile) {
//    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/15.txt")); // вместо ошибки кидается exit
//}

/* ------------------------------------------------------------------------------------------------ loadGraphFromFile */


/* ------------------------------------------------------------------------------------------------- exportGraphToDot */

TEST(ExportGraphToDot, StandardGraph) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    graph.exportGraphToDot("tests/test_graph.dot");
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    gvc = gvContext();
    fp = fopen("tests/test_graph.dot", "r");
    g = agread(fp, 0);
    int agraph_size = agnnodes(g);
    gvFreeLayout(gvc, g);
    agclose(g);
    fclose(fp);
    gvFreeContext(gvc);
    EXPECT_EQ(graph.size(), agraph_size);
}

TEST(ExportGraphToDot, IncompleteGraph) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
    graph.exportGraphToDot("tests/test_graph2.gv");
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    gvc = gvContext();
    fp = fopen("tests/test_graph2.gv", "r");
    g = agread(fp, 0);
    int agraph_size = agnnodes(g);
    gvFreeLayout(gvc, g);
    agclose(g);
    fclose(fp);
    gvFreeContext(gvc);
    EXPECT_EQ(graph.size(), agraph_size);
}

TEST(ExportGraphToDot, FilenameWithoutExtension) {
    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/graphs/5.txt").exportGraphToDot("test_graph"));
}

TEST(ExportGraphToDot, FilenameWithWrongExtension) {
    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/graphs/5.txt").exportGraphToDot("test_graph.hello"));
}

TEST(ExportGraphToDot, NonWritableFile) {
    std::system("chmod 000 tests/dot_files/test_graph.dot");
    EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/graphs/5.txt").exportGraphToDot("tests/dot_files/test_graph.dot"));
    std::system("chmod 777 tests/dot_files/test_graph.dot");
}

TEST(ExportGraphToDot, ExistingFile) {
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


/* -------------------------------------------------------------------------------------------- GraphAlgorithmsSearch */

TEST(DepthFirstSearch, LargeVertex) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    EXPECT_THROW(s21::GraphAlgorithms::breadthFirstSearch(graph, 3), s21::GraphAlgorithms::GraphAlgorithmsError);
}

TEST(DepthFirstSearch, ZeroVertex) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    EXPECT_THROW(s21::GraphAlgorithms::breadthFirstSearch(graph, 0), s21::GraphAlgorithms::GraphAlgorithmsError);
}

TEST(DepthFirstSearch, RightAnswer) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    std::vector<int> res = s21::GraphAlgorithms::depthFirstSearch(graph, 1);
    std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    EXPECT_EQ(res, vec);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
    res = s21::GraphAlgorithms::depthFirstSearch(graph, 5);
    vec = std::vector<int>{ 5, 4, 2, 1, 3 };
    EXPECT_EQ(res, vec);
}

TEST(DepthFirstSearch, IncompleteGraph) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    std::vector<int> res = s21::GraphAlgorithms::depthFirstSearch(graph, 2);
    std::vector<int> vec{ 2, 1, 3, 4, 5 };
    EXPECT_EQ(res, vec);
}

TEST(BreadthFirstSearch, LargeVertex) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    EXPECT_THROW(s21::GraphAlgorithms::breadthFirstSearch(graph, 3), s21::GraphAlgorithms::GraphAlgorithmsError);
}

TEST(BreadthFirstSearch, ZeroVertex) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    EXPECT_THROW(s21::GraphAlgorithms::breadthFirstSearch(graph, 0), s21::GraphAlgorithms::GraphAlgorithmsError);
}

TEST(BreadthFirstSearch, RightAnswer) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
    std::vector<int> res = s21::GraphAlgorithms::breadthFirstSearch(graph, 5);
    std::vector<int> vec{ 5, 4, 2, 3, 1 };
    EXPECT_EQ(res, vec);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    res = s21::GraphAlgorithms::breadthFirstSearch(graph, 2);
    vec = std::vector<int>{ 2, 1 };
    EXPECT_EQ(res, vec);
}

TEST(BreadthFirstSearch, IncompleteGraph) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    std::vector<int> res = s21::GraphAlgorithms::breadthFirstSearch(graph, 2);
    std::vector<int> vec{ 2, 1, 3, 4, 5 };
    EXPECT_EQ(res, vec);
}

/* -------------------------------------------------------------------------------------------- GraphAlgorithmsSearch */


/* -------------------------------------------------------------------------------------- GraphAlgorithmsShortestPath */

TEST(GetShortestPathBetweenVertices, ZeroVertex) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    EXPECT_THROW(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 0, 4), s21::GraphAlgorithms::GraphAlgorithmsError);
    EXPECT_THROW(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 0), s21::GraphAlgorithms::GraphAlgorithmsError);
}

TEST(GetShortestPathBetweenVertices, LargeVertex) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    EXPECT_THROW(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 12, 1), s21::GraphAlgorithms::GraphAlgorithmsError);
    EXPECT_THROW(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 3, 14), s21::GraphAlgorithms::GraphAlgorithmsError);
}

TEST(GetShortestPathBetweenVertices, RightAnswer) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    EXPECT_EQ(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 4), 20u);
    EXPECT_EQ(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 11), 18u);
    graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    EXPECT_EQ(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 5), 6u);
}

TEST(GetShortestPathBetweenVertices, OneVertex) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    std::size_t res = s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 1);
    EXPECT_EQ(res, 0);
}

TEST(GetShortestPathBetweenVerticesImproved, ZeroVertex) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    EXPECT_THROW(s21::GraphAlgorithms::getShortestPathBetweenVertices_improved(graph, 0, 4), s21::GraphAlgorithms::GraphAlgorithmsError);
    EXPECT_THROW(s21::GraphAlgorithms::getShortestPathBetweenVertices_improved(graph, 1, 0), s21::GraphAlgorithms::GraphAlgorithmsError);
}

TEST(GetShortestPathBetweenVerticesImproved, LargeVertex) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    EXPECT_THROW(s21::GraphAlgorithms::getShortestPathBetweenVertices_improved(graph, 12, 1), s21::GraphAlgorithms::GraphAlgorithmsError);
    EXPECT_THROW(s21::GraphAlgorithms::getShortestPathBetweenVertices_improved(graph, 3, 14), s21::GraphAlgorithms::GraphAlgorithmsError);
}

TEST(GetShortestPathBetweenVerticesImproved, RightAnswer) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    std::vector<int> res = s21::GraphAlgorithms::getShortestPathBetweenVertices_improved(graph, 1, 4);
    std::vector<int> vec{ 1, 5, 4 };
    EXPECT_EQ(res, vec);
}

TEST(GetShortestPathBetweenVerticesImproved, OneVertex) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    std::vector<int> res = s21::GraphAlgorithms::getShortestPathBetweenVertices_improved(graph, 1, 1);
    std::vector<int> vec{ 1 };
    EXPECT_EQ(res, vec);
}

TEST(GetShortestPathBetweenAllVertices, RightSizedMatrix) {

    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    std::vector<std::vector<float>> res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
    EXPECT_EQ(res.size(), 11);
    for (int i = 0; i < 11; ++i)
        EXPECT_EQ(res[i].size(), 11);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
    EXPECT_EQ(res.size(), 2);
    for (int i = 0; i < 2; ++i)
        EXPECT_EQ(res[i].size(), 2);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/3.txt");
    res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
    EXPECT_EQ(res.size(), 4);
    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(res[i].size(), 4);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
    EXPECT_EQ(res.size(), 5);
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(res[i].size(), 5);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
    res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
    EXPECT_EQ(res.size(), 5);
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(res[i].size(), 5);
}

TEST(GetShortestPathBetweenAllVertices, RightAnswer) {

    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    std::vector<std::vector<float>> res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
    unsigned **expected_res = new unsigned *[11]{new unsigned[11]{  0u,  29u,  20u,  20u,  16u,  31u, 100u,  12u,   4u,  31u,  18u},
                                                 new unsigned[11]{ 29u,   0u,  15u,  29u,  28u,  40u,  72u,  21u,  29u,  41u,  12u},
                                                 new unsigned[11]{ 20u,  15u,   0u,  15u,  14u,  25u,  81u,   9u,  23u,  27u,  13u},
                                                 new unsigned[11]{ 20u,  29u,  15u,   0u,   4u,  12u,  92u,  12u,  24u,  13u,  25u},
                                                 new unsigned[11]{ 16u,  28u,  14u,   4u,   0u,  16u,  94u,   9u,  20u,  16u,  22u},
                                                 new unsigned[11]{ 31u,  40u,  25u,  12u,  16u,   0u,  95u,  24u,  35u,   3u,  37u},
                                                 new unsigned[11]{100u,  72u,  81u,  92u,  94u,  95u,   0u,  90u, 101u,  98u,  84u},
                                                 new unsigned[11]{ 12u,  21u,   9u,  12u,   9u,  24u,  90u,   0u,  15u,  25u,  13u},
                                                 new unsigned[11]{  4u,  29u,  23u,  24u,  20u,  35u, 101u,  15u,   0u,  35u,  18u},
                                                 new unsigned[11]{ 31u,  41u,  27u,  13u,  16u,   3u,  98u,  25u,  35u,   0u,  38u},
                                                 new unsigned[11]{ 18u,  12u,  13u,  25u,  22u,  37u,  84u,  13u,  18u,  38u,   0u}};
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j)
            EXPECT_EQ(res[i][j], expected_res[i][j]);
        delete expected_res[i];
    }
    delete [] expected_res;

    graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
    expected_res = new unsigned *[2]{new unsigned[2]{0u, 1u},
                                     new unsigned[2]{1u, 0u}};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(res[i][j], expected_res[i][j]);
        delete expected_res[i];
    }
    delete [] expected_res;

    graph = s21::Graph::loadGraphFromFile("tests/graphs/3.txt");
    res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
    expected_res = new unsigned *[4]{new unsigned[4]{ 0u, 10u, 17u, 10u},
                                     new unsigned[4]{10u,  0u, 10u, 10u},
                                     new unsigned[4]{17u, 10u,  0u, 10u},
                                     new unsigned[4]{10u, 10u, 10u,  0u}};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j)
            EXPECT_EQ(res[i][j], expected_res[i][j]);
        delete expected_res[i];
    }
    delete [] expected_res;

    graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
    expected_res = new unsigned *[5]{new unsigned[5]{0u, 2u, 5u, 5u, 6u},
                                     new unsigned[5]{2u, 0u, 3u, 3u, 4u},
                                     new unsigned[5]{5u, 3u, 0u, 4u, 5u},
                                     new unsigned[5]{5u, 3u, 4u, 0u, 1u},
                                     new unsigned[5]{6u, 4u, 5u, 1u, 0u}};
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
            EXPECT_EQ(res[i][j], expected_res[i][j]);
        delete expected_res[i];
    }
    delete [] expected_res;

    graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
    res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
    expected_res = new unsigned *[5]{new unsigned[5]{0u, 1u, 1u, 1u, 2u},
                                     new unsigned[5]{1u, 0u, 2u, 2u, 3u},
                                     new unsigned[5]{1u, 2u, 0u, 2u, 1u},
                                     new unsigned[5]{1u, 2u, 2u, 0u, 1u},
                                     new unsigned[5]{2u, 3u, 1u, 1u, 0u}};
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
            EXPECT_EQ(res[i][j], expected_res[i][j]);
        delete expected_res[i];
    }
    delete [] expected_res;
}

/* -------------------------------------------------------------------------------------- GraphAlgorithmsShortestPath */


/* -------------------------------------------------------------------------------------- GraphAlgorithmsSpanningTree */

TEST(GetLeastSpanningTree, RightSize) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    std::vector<std::vector<int>> res = s21::GraphAlgorithms::getLeastSpanningTree(graph);
    ASSERT_EQ(res.size(), 11);
    for (int i = 0; i < 11; ++i)
        EXPECT_EQ(res[i].size(), 11);


    graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    res = s21::GraphAlgorithms::getLeastSpanningTree(graph);
    ASSERT_EQ(res.size(), 2);
    for (int i = 0; i < 2; ++i)
        EXPECT_EQ(res[i].size(), 2);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/3.txt");
    res = s21::GraphAlgorithms::getLeastSpanningTree(graph);
    ASSERT_EQ(res.size(), 4);
    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(res[i].size(), 4);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    res = s21::GraphAlgorithms::getLeastSpanningTree(graph);
    ASSERT_EQ(res.size(), 5);
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(res[i].size(), 5);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
    res = s21::GraphAlgorithms::getLeastSpanningTree(graph);
    ASSERT_EQ(res.size(), 5);
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(res[i].size(), 5);
}

TEST(GetLeastSpanningTree, RightFullWeight) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    std::vector<std::vector<int>> res = s21::GraphAlgorithms::getLeastSpanningTree(graph);
    ASSERT_EQ(res.size(), 11);
    int sum = 0;
    for (int i = 0; i < 11; ++i) {
        ASSERT_EQ(res[i].size(), 11);
        for (int j = 0; j < 11; ++j)
            sum += res[i][j];
    }
    EXPECT_EQ(sum, 300);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    res = s21::GraphAlgorithms::getLeastSpanningTree(graph);
    ASSERT_EQ(res.size(), 2);
    sum = 0;
    for (int i = 0; i < 2; ++i) {
        ASSERT_EQ(res[i].size(), 2);
        for (int j = 0; j < 2; ++j)
            sum += res[i][j];
    }
    EXPECT_EQ(sum, 2);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/3.txt");
    res = s21::GraphAlgorithms::getLeastSpanningTree(graph);
    ASSERT_EQ(res.size(), 4);
    sum = 0;
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(res[i].size(), 4);
        for (int j = 0; j < 4; ++j)
            sum += res[i][j];
    }
    EXPECT_EQ(sum, 60);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    res = s21::GraphAlgorithms::getLeastSpanningTree(graph);
    ASSERT_EQ(res.size(), 5);
    sum = 0;
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(res[i].size(), 5);
        for (int j = 0; j < 5; ++j)
            sum += res[i][j];
    }
    EXPECT_EQ(sum, 18);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
    res = s21::GraphAlgorithms::getLeastSpanningTree(graph);
    ASSERT_EQ(res.size(), 5);
    sum = 0;
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(res[i].size(), 5);
        for (int j = 0; j < 5; ++j)
            sum += res[i][j];
    }
    EXPECT_EQ(sum, 8);
}

/* -------------------------------------------------------------------------------------- GraphAlgorithmsSpanningTree */


/* ----------------------------------------------------------------------------- GraphAlgorithmsAntColonyOptimization */

TEST(SolveTravelingSalesmanProblem, RightAnswer) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
    s21::GraphAlgorithms::TsmResult res = s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph);
    EXPECT_EQ(res.distance, 253);
    EXPECT_EQ(res.vertices.size(), 12);
    EXPECT_EQ(res.vertices.front(), res.vertices.back());

    graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
    res = s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph);
    EXPECT_EQ(res.distance, 2);
    EXPECT_EQ(res.vertices.size(), 3);
    EXPECT_EQ(res.vertices.front(), res.vertices.back());

    graph = s21::Graph::loadGraphFromFile("tests/graphs/3.txt");
    res = s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph);
    EXPECT_EQ(res.distance, 40);
    EXPECT_EQ(res.vertices.size(), 5);
    EXPECT_EQ(res.vertices.front(), res.vertices.back());
}

TEST(SolveTravelingSalesmanProblem, Error) {
    s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
    EXPECT_THROW(s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph), s21::GraphAlgorithms::GraphAlgorithmsError);

    graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
    EXPECT_THROW(s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph), s21::GraphAlgorithms::GraphAlgorithmsError);
}

/* ----------------------------------------------------------------------------- GraphAlgorithmsAntColonyOptimization */

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
