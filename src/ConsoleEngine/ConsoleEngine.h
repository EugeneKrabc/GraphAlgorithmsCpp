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
    DotFormatHandler handle_shoulders_;

    void ReadDotFile();
    void WriteToFile();
};

}

#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_CONSOLEENGINE_H