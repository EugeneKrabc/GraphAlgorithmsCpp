//
// Created by Curran Carr on 10/28/22.
//

#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_DOTFORMATHANDLER_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_DOTFORMATHANDLER_H

#include "../DataStructures/Matrix/Matrix.h"
#include <string>

namespace s21 {

class DotFormatHandler {
 public:
    void WriteMatrixToFile(const S21Matrix &matrix, std::string filename);
    S21Matrix GetMatrixFromFile(std::string filename);
};

}  // namespace s21


#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_DOTFORMATHANDLER_H
