#include "ConsoleEngine.h"
#include "../DotFormatHandler/DotFormatHandler.h"

namespace s21 {
void ConsoleEngine::start() {
    DotFormatHandler handle_shoulders;
    std::string path = "/Users/violette/Desktop/GraphAlgorithms/src/DotFiles/example.dot";
    S21Matrix kek = std::move(handle_shoulders.GetMatrixFromFile(path));
    for (int i = 0; i < kek.get_cols(); i++) {
        for (int j = 0; j < kek.get_rows(); j++) {
            std::cout << kek(i, j) << ' ';
        }
        std::cout << "\n";
    }
}
} // namespace s21
