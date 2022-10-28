//
// Created by Curran Carr on 10/27/22.
//

#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_GRAPH_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_GRAPH_H

#include <string>

namespace s21 {

class Graph {
 public:
    void LoadGraphFromFile(std::string filename);
    void exportGraphToDot(std::string filename);
 private:

};
}  // namespace s21

#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_GRAPH_H
