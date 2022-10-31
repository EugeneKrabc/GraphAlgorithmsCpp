#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_GRAPHALGORITHMS_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_GRAPHALGORITHMS_H

#include <vector>
#include <set>
#include "../DataStructures/Queue/Queue.h"
#include "../DataStructures/Stack/Stack.h"
#include "../Graph/Graph.h"
#include "../DataStructures/AbstractList.h"
#include "BranchAndBoundAlgorithmForTSM/TSMBranchAndBoundSolver.h"

namespace s21 {
struct TsmResult {
    std::vector<int> vertices;
    double distance;

    TsmResult(std::vector<int> path, double distance) {
        this->distance = distance;
        vertices = path;
    }
};

enum Status {
    WRONG_VERTEX_NUMBER = -1,
    EMPTY_GRAPH_ERROR = -2,
    OUT_OF_RANGE = -3
};

enum SearchType { DepthFirstSearch = 1, BreadthFirstSearch = 2 };


class GraphAlgorithms {
 public:

    std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
    std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);

    int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
    S21Matrix GetShortestPathsBetweenAllVertices(Graph &graph);
    S21Matrix GetLeastSpanningTree(Graph &graph);
    TsmResult SolveTravelingSalesmanProblem(Graph &graph);
    TsmResult SolveTSMBranchAndBoundMethod(Graph &graph);

 private:
    AbstractList *list;
    void debug_print_vector(std::vector<int> vector);
    void debug_print_stack(Stack stack);
    std::vector<int> SearchAlgo(Graph &graph, int start_vertex, SearchType search_type);
    int big_number_ = 1000000;

    TSMBranchAndBoundSolver *branch_and_bound_solver;
    
    ////////////////////////////////////////////////////////////////
    // TSM-AntAlgorithm stuff
    S21Matrix pheromones_, pheromones_delta_, event_;
    double max_length_;

    TsmResult AntColonyAlgorithm(S21Matrix &matrix, const int length);
    TsmResult GetFullPath(S21Matrix &matrix);
    int GetNextNode(S21Matrix &matrix, int cur_pos, std::set<int> &visited);
    std::vector<int> GetStackWithShortestPathBetweenVertices(S21Matrix &matrix, int vertex1, int vertex2, int *length);
    double GetEventPossibility(S21Matrix &matrix, int rows, int cols, std::set<int> &nodes);
    void ApplyDeltaToPheromones(S21Matrix &matrix);
    void IncreaseDelta(S21Matrix &matrix, int path_of_cur, std::vector<int> &visited);
    double LastPositiveEvent(std::vector<double> &event_vec, int j);
    ////////////////////////////////////////////////////////////////

};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V1_0_0_MASTER_GRAPHALGORITHMS_H
