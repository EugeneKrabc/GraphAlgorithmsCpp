#include <gtest/gtest.h>

#include "../Graph/Graph.h"
#include "../GraphAlgorithms/GraphAlgorithms.h"

using namespace s21;

TEST(PartOneTests, DFS) {
    Graph graph;
    GraphAlgorithms graph_algorithms;
    graph.GetMatrixFromFile("DotFiles/DFS1.txt");
    std::vector<int> result = graph_algorithms.DepthFirstSearch(graph, 1);
    int expected_values[] = {1, 2, 3, 5, 4};
    EXPECT_EQ(result.size(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(result[i], expected_values[i]);
    }

    result = graph_algorithms.DepthFirstSearch(graph, 999);
    EXPECT_EQ(result.at(0), -1);

    Graph empty_graph;
    result = graph_algorithms.DepthFirstSearch(empty_graph, 2);
    EXPECT_EQ(result.at(0), -2);

    graph.GetMatrixFromFile("DotFiles/DFS2.txt");
    result = graph_algorithms.DepthFirstSearch(graph, 3);
    int expected_values2[] = {3, 1, 2, 4};
    EXPECT_EQ(result.size(), 4);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(result[i], expected_values2[i]);
    }
}

TEST(PartOneTests, exportGraphToDot) {
    Graph graph;
    graph.GetMatrixFromFile("DotFiles/example.txt");
    graph.ExportGraphToDot("DotFiles/aboba.dot");
    std::ifstream file("DotFiles/aboba.dot");
    char c;
    if (!file.is_open() || !(file >> c)) {
        file.close();
        FAIL();
    }
    file.close();
}

TEST(PartTwoTests, GetShortestPathBetweenVertices) {
    Graph graph;
    GraphAlgorithms graph_algorithms;
    graph.GetMatrixFromFile("DotFiles/example.txt");
    EXPECT_EQ(graph_algorithms.GetShortestPathBetweenVertices(graph, 1, 4), 20);
    EXPECT_EQ(graph_algorithms.GetShortestPathBetweenVertices(graph, 3, 8), 9);
    EXPECT_EQ(graph_algorithms.GetShortestPathBetweenVertices(graph, 11, 2), 12);
    EXPECT_EQ(graph_algorithms.GetShortestPathBetweenVertices(graph, 4, 10), 13);
}

TEST(PartTwoTests, GetShortestPathsBetweenAllVertices) {
    Graph graph, graph2;
    GraphAlgorithms graph_algorithms;
    graph.GetMatrixFromFile("DotFiles/example2.dot");
    s21::S21Matrix tmp_matrix = graph_algorithms.GetShortestPathsBetweenAllVertices(graph);
    graph2.GetMatrixFromFile("DotFiles/example3.dot");
    s21::S21Matrix expected_matrix = graph2.GetMatrix();
    EXPECT_TRUE(tmp_matrix == expected_matrix);
}

TEST(PartThreeTests, GetLeastSpanningTree) {
    Graph graph, graph2;
    GraphAlgorithms graph_algorithms;
    graph.GetMatrixFromFile("DotFiles/example4.dot");
    S21Matrix tmp_matrix(graph_algorithms.GetLeastSpanningTree(graph));
    graph2.GetMatrixFromFile("DotFiles/example5.dot");
    s21::S21Matrix expected_matrix = graph2.GetMatrix();
    EXPECT_TRUE(tmp_matrix == expected_matrix);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
