#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <cstddef>

class Matrix {
public:
  Matrix(const std::size_t rows, const std::size_t cols);
  Matrix(const Matrix& matrix);
  ~Matrix();

  std::size_t get_rows() const;
  std::size_t get_cols() const;
  void set(std::size_t i, std::size_t j, int val);
  int get(std::size_t i, std::size_t j) const;
  void print(FILE* f) const;

  Matrix& operator=(const Matrix& matrix);

  Matrix operator+(const Matrix& matrix);
  Matrix operator-(const Matrix& matrix);
  Matrix operator*(const Matrix& matrix);

  Matrix& operator+=(const Matrix& matrix);
  Matrix& operator-=(const Matrix& matrix);
  Matrix& operator*=(const Matrix& matrix);

  bool operator==(const Matrix& matrix);
  bool operator!=(const Matrix& matrix);
private:
  void _init_data(std::size_t rows, std::size_t cols);
  void _free_data();
  std::size_t _rows;
  std::size_t _cols;
  int** _data;
};

#endif