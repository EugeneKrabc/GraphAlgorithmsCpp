#include "DotFormatHandler.h"

namespace s21 {

    S21Matrix DotFormatHandler::GetMatrixFromFile(std::string filename) {
        std::fstream file(filename);
        if (!file) {
            file.close();
            throw std::invalid_argument("Wrong path to the file!");
        }
        int rows, cols;
        char separator;
        file >> rows >> separator >> cols;
        S21Matrix dot_format(rows, cols);
        rows = cols = 0;
        while (!file.eof()) {
            file >> dot_format(rows, cols++) >> separator;
            if (separator == '\n') {
                cols = 0;
                rows++;
            }
        }
        file.close();
        return dot_format;
    }

    void DotFormatHandler::WriteMatrixToFile(const S21Matrix &matrix, std::string filename) {
    }
}
