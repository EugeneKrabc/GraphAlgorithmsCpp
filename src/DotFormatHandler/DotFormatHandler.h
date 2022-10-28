#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_DOTFORMATHANDLER_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_DOTFORMATHANDLER_H

#include "../DataStructures/Matrix/Matrix.h"
#include <string>
#include <iostream>
#include <fstream>

namespace s21 {

class DotFormatHandler {
 public:
    void WriteMatrixToFile(S21Matrix &matrix, std::string filename);
    S21Matrix GetMatrixFromFile(std::string filename);

private:
    S21Matrix matrix;
};

}  // namespace s21


#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_DOTFORMATHANDLER_H
