#ifndef GRAPHALGORITHMSCPP_ANTALGORITHMFORTSM_H
#define GRAPHALGORITHMSCPP_ANTALGORITHMFORTSM_H

#include <vector>
#include <set>
#include "../../DataStructures/Matrix/Matrix.h"

namespace s21 {

    class TSMAntAlgorithmSolver {
    public:
        using pair = std::pair<std::vector<int>, double>;

        TSMAntAlgorithmSolver(S21Matrix &matrix);
        void PerformAntAlgorithm();
        pair GetAnswer();

    private:
        S21Matrix matrix_, pheromones_, pheromones_delta_, event_;
        double count_of_nodes_, max_length_;
        pair shortest_path_;

        void ApplyDeltaToPheromones();
        pair AntColonyAlgorithm();
        double GetEventPossibility(int rows, int cols, std::set<int> &nodes);
        int GetNextNode(int cur_pos, std::set<int> &nodes);
        double LastPositiveEvent(std::vector<double> &event_vec, int j);
        void IncreaseDelta(int path_of_cur, std::vector<int> &visited);
        pair GetFullPath();
        pair GetShortestPath(int vertex1, int vertex2);
    };
}


#endif  // GRAPHALGORITHMSCPP_ANTALGORITHMFORTSM_H
