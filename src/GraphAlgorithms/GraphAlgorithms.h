#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_GRAPHALGORITHMS_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_GRAPHALGORITHMS_H

#include <vector>
#include "../Graph/Graph.h"
#include "../DataStructures/Stack/Stack.h"
#include "../DataStructures/Queue/Queue.h"

namespace s21 {

struct TsmResult {
    std::vector<int> vertices;
    double distance;
};

enum Status {
    WRONG_VERTEX_NUMBER = -1,
    EMPTY_GRAPH_ERROR = -2
};

class GraphAlgorithms {
 public:
    std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
    std::vector<int> BreadthFirstSearch(Graph &graph, int startVertex);

    int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
    S21Matrix GetShortestPathsBetweenAllVertices(Graph &graph);

    S21Matrix GetLeastSpanningTree(Graph &graph);

    TsmResult SolveTravelingSalesmanProblem(Graph &graph);

 private:
    void debug_print_vector(std::vector<int> vector);
    void debug_print_stack(Stack stack);

};
}  // namespace s21

#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_GRAPHALGORITHMS_H
