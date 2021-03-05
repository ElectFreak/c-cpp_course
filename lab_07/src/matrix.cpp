#include <cstddef> 
#include <algorithm> 
#include "matrix.h"

void Matrix::_init_data(std::size_t rows, std::size_t cols) {
  _rows = rows;
  _cols = cols;

  _data = new int* [rows];
  for (std::size_t i = 0; i < rows; i++)
    _data[i] = new int[cols]();
}

void Matrix::_free_data() {
  if (_data == nullptr)
    return;

  for (std::size_t i = 0; i < _rows; i++)
    delete[] _data[i];

  delete[] _data;
}

Matrix::Matrix(const std::size_t rows, const std::size_t cols) {
  _init_data(rows, cols);
}

Matrix::Matrix(const Matrix& matrix) {
  _init_data(matrix._rows, matrix._cols);

  for (std::size_t i = 0; i < _rows; i++)
    for (std::size_t j = 0; j < _cols; j++)
      _data[i][j] = matrix._data[i][j];
}

Matrix::~Matrix() {
  _free_data();
}

std::size_t Matrix::get_rows() const {
  return _rows;
}

std::size_t Matrix::get_cols() const {
  return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
  _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}

void Matrix::print(FILE* f) const {
  for (std::size_t i = 0; i < _rows; i++) {
    for (std::size_t j = 0; j < _cols; j++)
      fprintf(f, "%d ", _data[i][j]);
    fprintf(f, "\n");
  }
}

Matrix& Matrix::operator=(const Matrix& matrix) {
  if (this == &matrix)
    return *this;

  if (_rows != matrix._rows || _cols != matrix._cols)
    _free_data(),
    _init_data(matrix._rows, matrix._cols);

  for (std::size_t i = 0; i < _rows; i++)
    for (std::size_t j = 0; j < _cols; j++)
      _data[i][j] = matrix._data[i][j];

  return *this;
}

Matrix Matrix::operator+(const Matrix& matrix) const {
  Matrix matrix_result(_rows, _cols);
  for (std::size_t i = 0; i < _rows; i++)
    for (std::size_t j = 0; j < _cols; j++)
      matrix_result.set(i, j, _data[i][j] + matrix._data[i][j]);
  return matrix_result;
}

Matrix Matrix::operator-(const Matrix& matrix) const {
  Matrix matrix_result(_rows, _cols);
  for (std::size_t i = 0; i < _rows; i++)
    for (std::size_t j = 0; j < _cols; j++)
      matrix_result.set(i, j, _data[i][j] - matrix._data[i][j]);

  return matrix_result;
}

Matrix Matrix::operator*(const Matrix& matrix) const {
  // contract: _rows == matrix._cols, _cols = matrix._rows
  Matrix matrix_result(_rows, matrix._cols);

  for (std::size_t i = 0; i < matrix_result._rows; i++)
    for (std::size_t j = 0; j < matrix_result._cols; j++)
      for (std::size_t k = 0; k < _cols; k++)
        matrix_result._data[i][j] += _data[i][k] * matrix._data[k][j];

  return matrix_result;
}

Matrix& Matrix::operator+=(const Matrix& matrix) {
  *this = *this + matrix;
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix) {
  *this = *this - matrix;
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& matrix) {
  *this = *this * matrix;
  return *this;
}

bool Matrix::operator==(const Matrix& matrix) {
  if (_rows != matrix._rows || _cols != matrix._cols)
    return false;

  for (std::size_t i = 0; i < _rows; i++)
    for (std::size_t j = 0; j < _cols; j++)
      if (_data[i][j] != matrix._data[i][j])
        return false;

  return true;
}

bool Matrix::operator!=(const Matrix& matrix) {
  return !(*this == matrix);
}