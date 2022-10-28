#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_DOTFORMATHANDLER_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_DOTFORMATHANDLER_H

#include "../DataStructures/Matrix/Matrix.h"
#include <string>
#include <iostream>
#include <fstream>

namespace s21 {

class Graph {
 public:
    void WriteMatrixToFile(std::string filename);
    void GetMatrixFromFile(std::string filename);

private:
    S21Matrix matrix_;
};

}  // namespace s21


#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_DOTFORMATHANDLER_H
