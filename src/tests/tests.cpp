#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <gtest/gtest.h>

#include "../s21_graph/s21_graph.h"
#include "../s21_graph_algorithms/s21_graph_algorithms.h"

/* --------------------------------------------------- GraphMatrixConstructor */

TEST(GraphMatrixConstructor, NullZeroThrowsException) {
  EXPECT_THROW(s21::Graph graph(NULL, 0), s21::Graph::WrongMatrixException);
}

TEST(GraphMatrixConstructor, NullNonZeroThrowsException) {
  EXPECT_THROW(s21::Graph graph(NULL, 3), s21::Graph::WrongMatrixException);
}

TEST(GraphMatrixConstructor, NonNullZeroThrowException) {
  unsigned **matrix = new unsigned *[0];
  EXPECT_THROW(s21::Graph graph(matrix, 0), s21::Graph::WrongMatrixException);
  delete[] matrix;
}

TEST(GraphMatrixConstructor,
     NonNullElementaryMatrixConstructorThrowsException) {
  unsigned **matrix = new unsigned *[1] {
    new unsigned[1] { 0 }
  };
  EXPECT_THROW(s21::Graph graph(matrix, 1), s21::Graph::WrongMatrixException);
  delete matrix[0];
  delete[] matrix;
}

TEST(GraphMatrixConstructor, NullElementaryThrowsException) {
  EXPECT_THROW(s21::Graph graph(NULL, 1), s21::Graph::WrongMatrixException);
}

TEST(GraphMatrixConstructor, LargeSize) {
  unsigned **matrix = new unsigned *[0];
  EXPECT_THROW(s21::Graph graph(matrix, INT_MAX), s21::Graph::TooLargeGraph);
  EXPECT_THROW(s21::Graph graph(matrix, (unsigned)INT_MAX + 1u),
               s21::Graph::TooLargeGraph);
  EXPECT_THROW(s21::Graph graph(matrix, (unsigned)INT_MAX + 10u),
               s21::Graph::TooLargeGraph);
  delete[] matrix;
}

/* --------------------------------------------------- GraphMatrixConstructor */

/* ----------------------------------------------------- GraphCopyConstructor */

TEST(GraphCopyConstructor, DoesRightCopy) {
  unsigned **matrix = new unsigned *[2] {
    new unsigned[2]{0, 1}, new unsigned[2] { 1, 0 }
  };
  s21::Graph graph(matrix, 2);
  s21::Graph graph2(graph);
  EXPECT_EQ(graph2.size(), 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j)
      EXPECT_EQ(matrix[i][j], graph2[i][j]);
    delete matrix[i];
  }
  delete[] matrix;
  EXPECT_EQ(graph.size(), 2);
}

TEST(GraphCopyConstructor, ReallocatesMemory) {
  unsigned **matrix = new unsigned *[2] {
    new unsigned[2]{0, 1}, new unsigned[2] { 1, 0 }
  };
  s21::Graph graph(matrix, 2);
  s21::Graph graph2(graph);
  EXPECT_NE(&graph, &graph2);
  EXPECT_NE(graph[0], graph2[0]);
  for (int i = 0; i < 2; ++i)
    delete matrix[i];
  delete[] matrix;
}

/* ------------------------------------------------------GraphCopyConstructor */

/* ----------------------------------------------------- GraphMoveConstructor */

TEST(GraphMoveConstructor, DoesRightMove) {
  unsigned **matrix = new unsigned *[2] {
    new unsigned[2]{0, 1}, new unsigned[2] { 1, 0 }
  };
  s21::Graph graph(matrix, 2);
  s21::Graph graph2(std::move(graph));
  EXPECT_EQ(graph2.size(), 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j)
      EXPECT_EQ(matrix[i][j], graph2[i][j]);
    delete matrix[i];
  }
  delete[] matrix;
  EXPECT_EQ(graph.size(), 0);
}

TEST(GraphMoveConstructor, DoesNotReallocateMemory) {
  unsigned **matrix = new unsigned *[2] {
    new unsigned[2]{0, 1}, new unsigned[2] { 1, 0 }
  };
  s21::Graph graph(matrix, 2);
  const unsigned *old_ptr_matrix = graph[0];
  s21::Graph graph2(std::move(graph));
  const unsigned *new_ptr_matrix = graph2[0];
  EXPECT_EQ(old_ptr_matrix, new_ptr_matrix);
  for (int i = 0; i < 2; ++i)
    delete matrix[i];
  delete[] matrix;
}

/* ------------------------------------------------------GraphMoveConstructor */

/* ------------------------------------------------------ GraphCopyAssignment */

TEST(GraphCopyAssignment, DoesRightCopy) {
  unsigned **matrix = new unsigned *[2] {
    new unsigned[2]{0, 1}, new unsigned[2] { 1, 0 }
  };
  unsigned **matrix2 = new unsigned *[3] {
    new unsigned[3]{0, 2, 0}, new unsigned[3]{2, 0, 1}, new unsigned[3] {
      0, 1, 0
    }
  };
  s21::Graph graph(matrix, 2);
  s21::Graph graph2(matrix2, 3);
  graph = graph2;
  EXPECT_EQ(graph.size(), graph2.size());
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j)
      EXPECT_EQ(graph2[i][j], graph[i][j]);
    delete matrix2[i];
  }
  delete[] matrix2;
  for (int i = 0; i < 2; ++i)
    delete matrix[i];
  delete[] matrix;
}

TEST(GraphCopyAssignment, ReallocatesMemory) {
  unsigned **matrix = new unsigned *[2] {
    new unsigned[2]{0, 1}, new unsigned[2] { 1, 0 }
  };
  unsigned **matrix2 = new unsigned *[3] {
    new unsigned[3]{0, 2, 0}, new unsigned[3]{2, 0, 1}, new unsigned[3] {
      0, 1, 0
    }
  };
  s21::Graph graph(matrix, 2);
  s21::Graph graph2(matrix2, 3);
  graph = graph2;
  EXPECT_NE(&graph, &graph2);
  EXPECT_NE(graph[0], graph2[0]);
  for (int i = 0; i < 3; ++i)
    delete matrix2[i];
  delete[] matrix2;
  for (int i = 0; i < 2; ++i)
    delete matrix[i];
  delete[] matrix;
}

TEST(GraphCopyAssignment, SelfAssignmentDoesNotReallocateMemory) {
  unsigned **matrix = new unsigned *[2] {
    new unsigned[2]{0, 1}, new unsigned[2] { 1, 0 }
  };
  s21::Graph graph(matrix, 2);
  s21::Graph *old_ptr_graph = &graph;
  graph = graph;
  s21::Graph *new_ptr_graph = &graph;
  for (int i = 0; i < 2; ++i)
    delete matrix[i];
  delete[] matrix;
  EXPECT_EQ(old_ptr_graph, new_ptr_graph);
  EXPECT_EQ((*old_ptr_graph)[0], (*new_ptr_graph)[0]);
}

/* ------------------------------------------------------ GraphCopyAssignment */

/* ------------------------------------------------------ GraphMoveAssignment */

TEST(GraphMoveAssignment, DoesRightMove) {
  unsigned **matrix = new unsigned *[2] {
    new unsigned[2]{0, 1}, new unsigned[2] { 1, 0 }
  };
  unsigned **matrix2 = new unsigned *[3] {
    new unsigned[3]{0, 2, 0}, new unsigned[3]{2, 0, 1}, new unsigned[3] {
      0, 1, 0
    }
  };
  s21::Graph graph(matrix, 2);
  s21::Graph graph2(matrix2, 3);
  graph = std::move(graph2);
  EXPECT_EQ(graph.size(), 3);
  EXPECT_EQ(graph2.size(), 0);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j)
      EXPECT_EQ(graph[i][j], matrix2[i][j]);
    delete matrix2[i];
  }
  delete[] matrix2;
  for (int i = 0; i < 2; ++i)
    delete matrix[i];
  delete[] matrix;
}

TEST(GraphMoveAssignment, DoesNotReallocateMemory) {
  unsigned **matrix = new unsigned *[2] {
    new unsigned[2]{0, 1}, new unsigned[2] { 1, 0 }
  };
  unsigned **matrix2 = new unsigned *[3] {
    new unsigned[3]{0, 2, 0}, new unsigned[3]{2, 0, 1}, new unsigned[3] {
      0, 1, 0
    }
  };
  s21::Graph graph(matrix, 2);
  s21::Graph graph2(matrix2, 3);
  const unsigned *old_ptr_matrix = graph2[0];
  graph = std::move(graph2);
  const unsigned *new_ptr_matrix = graph[0];
  EXPECT_EQ(old_ptr_matrix, new_ptr_matrix);
  for (int i = 0; i < 3; ++i)
    delete matrix2[i];
  delete[] matrix2;
  for (int i = 0; i < 2; ++i)
    delete matrix[i];
  delete[] matrix;
}

TEST(GraphMoveAssignment, SelfAssignmentDoesNotReallocateMemory) {
  unsigned **matrix = new unsigned *[2] {
    new unsigned[2]{0, 1}, new unsigned[2] { 1, 0 }
  };
  s21::Graph graph(matrix, 2);
  s21::Graph *old_ptr_graph = &graph;
  graph = std::move(graph);
  s21::Graph *new_ptr_graph = &graph;
  for (int i = 0; i < 2; ++i)
    delete matrix[i];
  delete[] matrix;
  EXPECT_EQ(old_ptr_graph, new_ptr_graph);
  EXPECT_EQ((*old_ptr_graph)[0], (*new_ptr_graph)[0]);
}

/* ------------------------------------------------------ GraphMoveAssignment */

/* -------------------------------------------------------- loadGraphFromFile */

TEST(LoadGraphFromFile, LoadsFile) {
  EXPECT_EQ(s21::Graph::loadGraphFromFile("tests/graphs/1.txt").size(), 11);
  EXPECT_EQ(s21::Graph::loadGraphFromFile("tests/graphs/2.txt").size(), 2);
  EXPECT_EQ(s21::Graph::loadGraphFromFile("tests/graphs/3.txt").size(), 4);
  EXPECT_EQ(s21::Graph::loadGraphFromFile("tests/graphs/4.txt").size(), 5);
  EXPECT_EQ(s21::Graph::loadGraphFromFile("tests/graphs/5.txt").size(), 5);
}

TEST(LoadGraphFromFile, ElementaryGraph) {
  EXPECT_THROW(s21::Graph graph =
                   s21::Graph::loadGraphFromFile("tests/bad_graphs/3.txt"),
               s21::Graph::WrongMatrixException);
}

TEST(LoadGraphFromFile, NonExistFile) {
  EXPECT_THROW(s21::Graph graph =
                   s21::Graph::loadGraphFromFile("tests/bad_graphs/0.txt"),
               s21::Graph::CantOpenFile);
}

TEST(LoadGraphFromFile, loadNullGraphFromFile) {
  EXPECT_THROW(s21::Graph graph =
                   s21::Graph::loadGraphFromFile("tests/bad_graphs/1.txt"),
               s21::Graph::WrongMatrixException);
}

TEST(LoadGraphFromFile, DirectedGraph) {
  EXPECT_THROW(s21::Graph graph =
                   s21::Graph::loadGraphFromFile("tests/bad_graphs/2.txt"),
               s21::Graph::WrongMatrixException);
  EXPECT_THROW(s21::Graph graph =
                   s21::Graph::loadGraphFromFile("tests/bad_graphs/4.txt"),
               s21::Graph::WrongMatrixException);
}

TEST(LoadGraphFromFile, EmptyFile) {
  EXPECT_ANY_THROW(s21::Graph graph =
                       s21::Graph::loadGraphFromFile("tests/bad_graphs/6.txt"));
}

TEST(LoadGraphFromFile, NonReadableFile) {
  std::system("chmod 000 tests/bad_graphs/7.txt");
  EXPECT_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/7.txt"),
               s21::Graph::CantOpenFile);
  std::system("chmod 777 tests/bad_graphs/7.txt");
}

TEST(LoadGraphFromFile, WithoutRowsNumber) {
  EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/8.txt"));
}

TEST(LoadGraphFromFile, InvalidLength) {
  EXPECT_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/16.txt"),
               s21::Graph::WrongMatrixException);
  EXPECT_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/12.txt"),
               s21::Graph::WrongMatrixException);
}

TEST(LoadGraphFromFile, InvalidWidth) {
  EXPECT_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/9.txt"),
               s21::Graph::WrongMatrixException);
  EXPECT_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/10.txt"),
               s21::Graph::WrongMatrixException);
  EXPECT_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/11.txt"),
               s21::Graph::WrongMatrixException);
}

TEST(LoadGraphFromFile, InvalidElement) {
  EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/13.txt"));
}

TEST(LoadGraphFromFile, OnlyRowNumber) {
  EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/14.txt"));
}

TEST(LoadGraphFromFile, AlmostEmptyFile) {
  EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/bad_graphs/15.txt"));
}

/* -------------------------------------------------------- loadGraphFromFile */

/* --------------------------------------------------------- exportGraphToDot */

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
  EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/graphs/5.txt")
                       .exportGraphToDot("test_graph"));
}

TEST(ExportGraphToDot, FilenameWithWrongExtension) {
  EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/graphs/5.txt")
                       .exportGraphToDot("test_graph.hello"));
}

TEST(ExportGraphToDot, NonWritableFile) {
  std::system("chmod 000 tests/dot_files/test_graph.dot");
  EXPECT_ANY_THROW(s21::Graph::loadGraphFromFile("tests/graphs/5.txt")
                       .exportGraphToDot("tests/dot_files/test_graph.dot"));
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
  s21::Graph::loadGraphFromFile("tests/graphs/5.txt")
      .exportGraphToDot("tests/dot_files/test_graph2.dot");
}

/* --------------------------------------------------------- exportGraphToDot */

/* ---------------------------------------------------- GraphAlgorithmsSearch */

TEST(DepthFirstSearch, LargeVertex) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
  EXPECT_THROW(s21::GraphAlgorithms::breadthFirstSearch(graph, 3),
               s21::GraphAlgorithms::VertexIsOutOfRange);
}

TEST(DepthFirstSearch, ZeroVertex) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
  EXPECT_THROW(s21::GraphAlgorithms::breadthFirstSearch(graph, 0),
               s21::GraphAlgorithms::VertexIsOutOfRange);
}

TEST(DepthFirstSearch, RightAnswer) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
  std::vector<int> res = s21::GraphAlgorithms::depthFirstSearch(graph, 1);
  std::vector<int> vec{1, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
  EXPECT_EQ(res, vec);

  graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
  res = s21::GraphAlgorithms::depthFirstSearch(graph, 5);
  vec = std::vector<int>{5, 4, 1, 2, 3};
  EXPECT_EQ(res, vec);

  graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
  res = s21::GraphAlgorithms::depthFirstSearch(graph, 2);
  vec = std::vector<int>{2, 4, 5, 3, 1};
  EXPECT_EQ(res, vec);
}

TEST(BreadthFirstSearch, LargeVertex) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
  EXPECT_THROW(s21::GraphAlgorithms::breadthFirstSearch(graph, 3),
               s21::GraphAlgorithms::VertexIsOutOfRange);
}

TEST(BreadthFirstSearch, ZeroVertex) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
  EXPECT_THROW(s21::GraphAlgorithms::breadthFirstSearch(graph, 0),
               s21::GraphAlgorithms::VertexIsOutOfRange);
}

TEST(BreadthFirstSearch, RightAnswer) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
  std::vector<int> res = s21::GraphAlgorithms::breadthFirstSearch(graph, 5);
  std::vector<int> vec{5, 3, 4, 1, 2};
  EXPECT_EQ(res, vec);

  graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
  res = s21::GraphAlgorithms::breadthFirstSearch(graph, 2);
  vec = std::vector<int>{2, 1};
  EXPECT_EQ(res, vec);

  graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
  res = s21::GraphAlgorithms::breadthFirstSearch(graph, 2);
  vec = std::vector<int>{2, 1, 3, 4, 5};
  EXPECT_EQ(res, vec);
}

/* ---------------------------------------------------- GraphAlgorithmsSearch */

/* ---------------------------------------------- GraphAlgorithmsShortestPath */

TEST(GetShortestPathBetweenVertices, ZeroVertex) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
  EXPECT_THROW(
      s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 0, 4),
      s21::GraphAlgorithms::VertexIsOutOfRange);
  EXPECT_THROW(
      s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 0),
      s21::GraphAlgorithms::VertexIsOutOfRange);
}

TEST(GetShortestPathBetweenVertices, LargeVertex) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
  EXPECT_THROW(
      s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 12, 1),
      s21::GraphAlgorithms::VertexIsOutOfRange);
  EXPECT_THROW(
      s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 3, 14),
      s21::GraphAlgorithms::VertexIsOutOfRange);
}

TEST(GetShortestPathBetweenVertices, RightAnswer) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
  EXPECT_EQ(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 4),
            20.0);
  EXPECT_EQ(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 11),
            18.0);
  graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
  EXPECT_EQ(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 5),
            6.0);
}

TEST(GetShortestPathBetweenVertices, OneVertex) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
  double res =
      s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 1);
  EXPECT_EQ(res, 0.0);
}

TEST(GetShortestPathBetweenVerticesImproved, ZeroVertex) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
  EXPECT_THROW(
      s21::GraphAlgorithms::getShortestPathBetweenVerticesImproved(graph, 0, 4),
      s21::GraphAlgorithms::VertexIsOutOfRange);
  EXPECT_THROW(
      s21::GraphAlgorithms::getShortestPathBetweenVerticesImproved(graph, 1, 0),
      s21::GraphAlgorithms::VertexIsOutOfRange);
}

TEST(GetShortestPathBetweenVerticesImproved, LargeVertex) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
  EXPECT_THROW(s21::GraphAlgorithms::getShortestPathBetweenVerticesImproved(
                   graph, 12, 1),
               s21::GraphAlgorithms::VertexIsOutOfRange);
  EXPECT_THROW(s21::GraphAlgorithms::getShortestPathBetweenVerticesImproved(
                   graph, 3, 14),
               s21::GraphAlgorithms::VertexIsOutOfRange);
}

TEST(GetShortestPathBetweenVerticesImproved, RightAnswer) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
  std::vector<int> res =
      s21::GraphAlgorithms::getShortestPathBetweenVerticesImproved(graph, 1, 4);
  std::vector<int> vec{1, 5, 4};
  EXPECT_EQ(res, vec);
}

TEST(GetShortestPathBetweenVerticesImproved, OneVertex) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
  std::vector<int> res =
      s21::GraphAlgorithms::getShortestPathBetweenVerticesImproved(graph, 1, 1);
  std::vector<int> vec{1};
  EXPECT_EQ(res, vec);
}

TEST(GetShortestPathBetweenAllVertices, RightSizedMatrix) {

  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
  std::vector<std::vector<double>> res =
      s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
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
  std::vector<std::vector<double>> res =
      s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
  unsigned **expected_res = new unsigned *[11] {
    new unsigned[11]{0u, 29u, 20u, 20u, 16u, 31u, 100u, 12u, 4u, 31u, 18u},
        new unsigned[11]{29u, 0u, 15u, 29u, 28u, 40u, 72u, 21u, 29u, 41u, 12u},
        new unsigned[11]{20u, 15u, 0u, 15u, 14u, 25u, 81u, 9u, 23u, 27u, 13u},
        new unsigned[11]{20u, 29u, 15u, 0u, 4u, 12u, 92u, 12u, 24u, 13u, 25u},
        new unsigned[11]{16u, 28u, 14u, 4u, 0u, 16u, 94u, 9u, 20u, 16u, 22u},
        new unsigned[11]{31u, 40u, 25u, 12u, 16u, 0u, 95u, 24u, 35u, 3u, 37u},
        new unsigned[11]{100u, 72u, 81u,  92u, 94u, 95u,
                         0u,   90u, 101u, 98u, 84u},
        new unsigned[11]{12u, 21u, 9u, 12u, 9u, 24u, 90u, 0u, 15u, 25u, 13u},
        new unsigned[11]{4u, 29u, 23u, 24u, 20u, 35u, 101u, 15u, 0u, 35u, 18u},
        new unsigned[11]{31u, 41u, 27u, 13u, 16u, 3u, 98u, 25u, 35u, 0u, 38u},
        new unsigned[11] {
      18u, 12u, 13u, 25u, 22u, 37u, 84u, 13u, 18u, 38u, 0u
    }
  };
  for (int i = 0; i < 11; ++i) {
    for (int j = 0; j < 11; ++j)
      EXPECT_EQ(res[i][j], expected_res[i][j]);
    delete expected_res[i];
  }
  delete[] expected_res;

  graph = s21::Graph::loadGraphFromFile("tests/graphs/2.txt");
  res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
  expected_res = new unsigned *[2] {
    new unsigned[2]{0u, 1u}, new unsigned[2] { 1u, 0u }
  };
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j)
      EXPECT_EQ(res[i][j], expected_res[i][j]);
    delete expected_res[i];
  }
  delete[] expected_res;

  graph = s21::Graph::loadGraphFromFile("tests/graphs/3.txt");
  res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
  expected_res = new unsigned *[4] {
    new unsigned[4]{0u, 10u, 17u, 10u}, new unsigned[4]{10u, 0u, 10u, 10u},
        new unsigned[4]{17u, 10u, 0u, 10u}, new unsigned[4] {
      10u, 10u, 10u, 0u
    }
  };
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j)
      EXPECT_EQ(res[i][j], expected_res[i][j]);
    delete expected_res[i];
  }
  delete[] expected_res;

  graph = s21::Graph::loadGraphFromFile("tests/graphs/4.txt");
  res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
  expected_res = new unsigned *[5] {
    new unsigned[5]{0u, 2u, 5u, 5u, 6u}, new unsigned[5]{2u, 0u, 3u, 3u, 4u},
        new unsigned[5]{5u, 3u, 0u, 4u, 5u},
        new unsigned[5]{5u, 3u, 4u, 0u, 1u}, new unsigned[5] {
      6u, 4u, 5u, 1u, 0u
    }
  };
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j)
      EXPECT_EQ(res[i][j], expected_res[i][j]);
    delete expected_res[i];
  }
  delete[] expected_res;

  graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
  res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
  expected_res = new unsigned *[5] {
    new unsigned[5]{0u, 1u, 1u, 1u, 2u}, new unsigned[5]{1u, 0u, 2u, 2u, 3u},
        new unsigned[5]{1u, 2u, 0u, 2u, 1u},
        new unsigned[5]{1u, 2u, 2u, 0u, 1u}, new unsigned[5] {
      2u, 3u, 1u, 1u, 0u
    }
  };
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j)
      EXPECT_EQ(res[i][j], expected_res[i][j]);
    delete expected_res[i];
  }
  delete[] expected_res;
}

/* ---------------------------------------------- GraphAlgorithmsShortestPath */

/* ---------------------------------------------- GraphAlgorithmsSpanningTree */

TEST(GetLeastSpanningTree, RightSize) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
  std::vector<std::vector<int>> res =
      s21::GraphAlgorithms::getLeastSpanningTree(graph);
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
  std::vector<std::vector<int>> res =
      s21::GraphAlgorithms::getLeastSpanningTree(graph);
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

/* ---------------------------------------------- GraphAlgorithmsSpanningTree */

/* ------------------------------------- GraphAlgorithmsAntColonyOptimization */

TEST(SolveTravelingSalesmanProblem, RightAnswer) {
  s21::Graph graph = s21::Graph::loadGraphFromFile("tests/graphs/1.txt");
  s21::GraphAlgorithms::TsmResult res =
      s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph);
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
  EXPECT_THROW(s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph),
               s21::GraphAlgorithms::NoSolution);

  graph = s21::Graph::loadGraphFromFile("tests/graphs/5.txt");
  EXPECT_THROW(s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph),
               s21::GraphAlgorithms::NoSolution);
}

/* -----------------------------------------------------------------------------
 * GraphAlgorithmsAntColonyOptimization */

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
