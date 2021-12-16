#pragma once

#include <cstdio>
#include <cstddef>
#include <iostream>
#include <fstream>

class Matrix {
public:
  Matrix();
  Matrix(const std::size_t rows, const std::size_t cols);
  Matrix(const Matrix& matrix);
  ~Matrix();

  static Matrix from_file(std::string file_path);

  std::size_t get_rows() const;
  std::size_t get_cols() const;
  void set(std::size_t i, std::size_t j, int val);
  int get(std::size_t i, std::size_t j) const;

  Matrix& operator=(Matrix source);

  Matrix operator+(const Matrix& matrix) const;
  Matrix operator-(const Matrix& matrix) const;
  Matrix operator*(const Matrix& matrix) const;

  Matrix& operator+=(const Matrix& matrix);
  Matrix& operator-=(const Matrix& matrix);
  Matrix& operator*=(const Matrix& matrix);

  bool operator==(const Matrix& matrix);
  bool operator!=(const Matrix& matrix);

  friend std::ostream& operator<<(std::ostream&, const Matrix&);

private:
  void _free_data();
  std::size_t _rows;
  std::size_t _cols;
  int** _data;
};