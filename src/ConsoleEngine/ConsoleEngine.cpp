#include "ConsoleEngine.h"
#include "../DotFormatHandler/DotFormatHandler.h"

namespace s21 {

void ConsoleEngine::start() {
  int answer = 0;
  while (true) {
    cout << "Choice:\n";
    cin >> answer;
    if (answer == 1)
      ReadDotFile();
    else if (answer == 2)
      WriteToFile();
    else
      break;
  }
}

void ConsoleEngine::ReadDotFile() {
  std::string path =
      "/Users/violette/Desktop/GraphAlgorithmsCPP/src/DotFiles/example.dot";
  S21Matrix kek = std::move(handle_shoulders_.GetMatrixFromFile(path));
  for (int i = 0; i < kek.get_cols(); i++) {
    for (int j = 0; j < kek.get_rows(); j++) {
      std::cout << kek(i, j) << ' ';
    }
    std::cout << "\n";
  }
}

void ConsoleEngine::WriteToFile() {}

} // namespace s21
