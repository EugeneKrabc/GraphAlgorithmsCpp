//
// Created by Curran Carr on 10/27/22.
//

#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_GRAPHALGORITHMS_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_GRAPHALGORITHMS_H

#include <vector>
#include "../Graph/Graph.h"
#include "../DataStructures/Matrix/Matrix.h"
#include "../DataStructures/Stack/Stack.h"
#include "../DataStructures/Queue/Queue.h"

namespace s21 {

struct TsmResult {
    std::vector<int> vertices;
    double distance;
};

class GraphAlgorithms {
 public:
    std::vector<int> DepthFirstSearch(Graph &graph);
    std::vector<int> BreadthFirstSearch(Graph &graph, int startVertex);

    int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
    S21Matrix GetShortestPathsBetweenAllVertices(Graph &graph);

    S21Matrix GetLeastSpanningTree(Graph &graph);

    TsmResult SolveTravelingSalesmanProblem(Graph &graph);

 private:

};
}  // namespace s21

#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_GRAPHALGORITHMS_H
