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
  file >> rows;
  S21Matrix dot_format(rows, rows);
  rows = cols = 0;
  while (!file.eof()) {
    file >> dot_format(rows, cols++);
    if (cols != dot_format.get_cols())
      file >> separator;
    if (cols == dot_format.get_cols()) {
      cols = 0;
      rows++;
    }
  }
  file.close();
  return dot_format;
}

void DotFormatHandler::WriteMatrixToFile(S21Matrix &matrix,
                                         std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        file.close();
        throw std::invalid_argument("Wrong path to the file!");
    }
    file << matrix.get_rows() << std::endl;
    for (int i = 0; i < matrix.get_cols(); i++) {
        for (int j = 0; j < matrix.get_rows(); j++) {
            file << matrix(i, j);
            if (j < matrix.get_rows() - 1)
                file << ',';
        }
        if (i < matrix.get_rows() - 1)
            file << std::endl;
    }
    file.close();
}
} // namespace s21
