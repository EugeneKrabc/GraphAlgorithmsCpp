#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_CONSOLEENGINE_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_CONSOLEENGINE_H

#include <iostream>

#include "../DotFormatHandler/DotFormatHandler.h"
#include "../Graph/Graph.h"
#include "../GraphAlgorithms/GraphAlgorithms.h"

namespace s21 {

using std::cout;
using std::cin;

class ConsoleEngine {
 public:
    void start();

private:
    DotFormatHandler dot_format_handler_;
    std::string read_path_, write_path_;
    S21Matrix matrix_;
};

}

#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_CONSOLEENGINE_H