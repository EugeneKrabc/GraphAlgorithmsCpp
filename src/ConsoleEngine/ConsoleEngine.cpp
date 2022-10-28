#include "ConsoleEngine.h"
#include "../DotFormatHandler/DotFormatHandler.h"

namespace s21 {

void ConsoleEngine::start() {
  int answer = 0;
  path_ = "/Users/violette/Desktop/GraphAlgorithmsCPP/src/DotFiles/example.dot";
  while (true) {
    cout << "Choice:\n";
    cin >> answer;
    if (answer == 1)
        matrix_ = dot_format_handler_.GetMatrixFromFile(path_);
    else if (answer == 2)
        dot_format_handler_.WriteMatrixToFile(matrix_, path_);
    else
      break;
  }
}

} // namespace s21
