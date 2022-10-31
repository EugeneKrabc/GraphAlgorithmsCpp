//
// Created by Curran Carr on 10/30/22.
//

#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_TSMBRANCHANDBOUNDSOLVER_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_TSMBRANCHANDBOUNDSOLVER_H

#include <vector>
#include "../../DataStructures/Matrix/Matrix.h"

namespace s21 {

class TSMBranchAndBoundSolver {
 public:
    TSMBranchAndBoundSolver(int nmb_of_graph);
    void TSP(S21Matrix adj);
    int final_res_;
    std::vector<int> final_path_;
 private:
    int nmb_of_graph_;
    std::vector<bool> visited_;

    void CopyToFinal(std::vector<int> curr_path);
    int FirstMin(S21Matrix adj, int i);
    int SecondMin(S21Matrix adj, int i);
    void TSPRec(S21Matrix adj, int curr_bound, int curr_weight, int level, std::vector<int> curr_path);

};

}  // namespace s21
#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_TSMBRANCHANDBOUNDSOLVER_H
