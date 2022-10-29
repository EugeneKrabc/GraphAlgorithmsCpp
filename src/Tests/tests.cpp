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
}


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
