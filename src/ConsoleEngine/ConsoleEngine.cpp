#include "ConsoleEngine.h"

namespace s21 {

  void ConsoleEngine::start() {
      int answer = -1;
      read_path_ = "/Users/violette/Desktop/GraphAlgorithmsCpp/src/DotFiles/example.dot";
      write_path_ = "/Users/violette/Desktop/GraphAlgorithmsCpp/src/DotFiles/test.dot";

      while (true) {
          cout << menu_options_;
          std::string input;
          cin >> input;
          if (input.size() == 1 && input.at(0) >= '0' && input.at(0) <= '7') {
              answer = stoi(input);
          }

          if (answer == 1) {
              matrix_ = dot_format_handler_.GetMatrixFromFile(read_path_);
          } else if (answer == 2) {
              dot_format_handler_.WriteMatrixToFile(matrix_, write_path_);
          } else if (answer == 3) {
              cout << "Not implemented\n";
          } else if (answer == 4) {
              cout << "Not implemented\n";
          } else if (answer == 5) {
              cout << "Not implemented\n";
          } else if (answer == 6) {
              cout << "Not implemented\n";
          } else if (answer == 7) {
              cout << "Not implemented\n";
          } else if (answer == 0) {
              break;
          } else {
              cout << "Invalid menu option\n";
          }
          answer = -1;
      }
  }


} // namespace s21
