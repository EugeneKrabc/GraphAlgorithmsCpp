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

void DotFormatHandler::WriteMatrixToFile(const S21Matrix &matrix,
                                         std::string filename) {}
} // namespace s21
