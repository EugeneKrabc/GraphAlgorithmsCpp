#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_S21_MATRIX_OOP_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_S21_MATRIX_OOP_H

#include <cmath>
#include <cstdio>

namespace s21 {

#define EPSILON 1e-15

class S21Matrix {
 private:
    int _rows, _cols;
    int **_matrix;

    void destroy_matrix();
    void allocate_matrix(int rows, int cols);
    void copy_matrix_elements(const S21Matrix &other);

 public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix &other);
    S21Matrix(S21Matrix &&other);
    ~S21Matrix();

    int get_rows();
    int get_cols();

    void set_rows(int new_rows);
    void set_columns(int new_cols);

    bool eq_matrix(const S21Matrix &other) const;
    void sum_matrix(const S21Matrix &other);
    void sub_matrix(const S21Matrix &other);
    void mul_number(const int num);
    void mul_matrix(const S21Matrix &other);

    S21Matrix transpose();

    S21Matrix operator+(const S21Matrix &other);
    S21Matrix operator-(const S21Matrix &other);
    S21Matrix operator*(const S21Matrix &other);
    bool operator==(const S21Matrix &other) const;
    S21Matrix &operator=(const S21Matrix &other);
    void operator+=(const S21Matrix &other);
    void operator-=(const S21Matrix &other);
    void operator*=(const S21Matrix &other);
    int &operator()(const int i, const int j);
};

}

#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_S21_MATRIX_OOP_H
