#include <gtest/gtest.h>
#include "../Graph/Graph.h"
#include "../GraphAlgorithms/GraphAlgorithms.h"

using namespace s21;

TEST(PartOneTests, DFS) {
    Graph graph;
    GraphAlgorithms graph_algorithms;
    graph.GetMatrixFromFile("DotFiles/DFS1.dot");
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

    graph.GetMatrixFromFile("DotFiles/DFS2.dot");
    result = graph_algorithms.DepthFirstSearch(graph, 3);
    int expected_values2[] = {3, 1, 2, 4};
    EXPECT_EQ(result.size(), 4);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(result[i], expected_values2[i]);
    }
}


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
