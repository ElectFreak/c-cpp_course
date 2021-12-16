#include <cstddef>
#include <algorithm>
#include <fstream>
#include "matrix.hpp"
#include "MatrixException.hpp"

void Matrix::_free_data() {
    if (_data == nullptr)
        return;

    delete[] _data[0];
    delete[] _data;

    _data = nullptr;
    _rows = _cols = 0;
}

Matrix::Matrix() : _rows{0}, _cols{0}, _data{nullptr} {}

Matrix::Matrix(const std::size_t rows, const std::size_t cols) : _rows{rows}, _cols{cols}, _data{nullptr} {
    int **data = new int *[rows];
    try {
        data[0] = new int[rows * cols]{};
    } catch (std::bad_alloc const &e) {
        delete[] data;
        throw;
    }

    for (std::size_t i = 1; i < rows; i++)
        data[i] = data[0] + i * cols;

    _data = data;
}

Matrix::Matrix(const Matrix &matrix) : Matrix(matrix._rows, matrix._cols) {
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
    if (i >= _rows || j >= _cols)
        throw MatrixGetException("ACCESS: bad index.");

    return _data[i][j];
}

Matrix &Matrix::operator=(Matrix copy) {
    std::swap(_data, copy._data);
    std::swap(_cols, copy._cols);
    std::swap(_rows, copy._rows);

    return *this;
}

Matrix Matrix::operator+(const Matrix &matrix) const {
    Matrix matrix_result(_rows, _cols);
    matrix_result += matrix;

    return matrix_result;
}

Matrix Matrix::operator-(const Matrix &matrix) const {
    Matrix matrix_result(_rows, _cols);
    matrix_result += matrix;

    return matrix_result;
}

Matrix Matrix::operator*(const Matrix &matrix) const {
    if (_cols != matrix._rows)
        throw MatrixMulException("MUL: #arg1.columns != #arg2.rows.");

    Matrix matrix_result(_rows, matrix._cols);

    for (std::size_t i = 0; i < matrix_result._rows; i++)
        for (std::size_t j = 0; j < matrix_result._cols; j++)
            for (std::size_t k = 0; k < _cols; k++)
                matrix_result._data[i][j] += _data[i][k] * matrix._data[k][j];

    return matrix_result;
}

Matrix &Matrix::operator+=(const Matrix &matrix) {
    if (_rows != matrix._rows || _cols != matrix._cols)
        throw MatrixAddException("ADD: dimensions do not match.");

    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t j = 0; j < _cols; j++)
            _data[i][j] += matrix._data[i][j];

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &matrix) {
    if (_rows != matrix._rows || _cols != matrix._cols)
        throw MatrixException("");

    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t j = 0; j < _cols; j++)
            _data[i][j] -= matrix._data[i][j];

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &matrix) {
    *this = *this * matrix;
    return *this;
}

bool Matrix::operator==(const Matrix &matrix) {
    if (_rows != matrix._rows || _cols != matrix._cols)
        return false;

    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t j = 0; j < _cols; j++)
            if (_data[i][j] != matrix._data[i][j])
                return false;

    return true;
}

bool Matrix::operator!=(const Matrix &matrix) {
    return !(*this == matrix);
}

std::ostream &operator<<(std::ostream &out, const Matrix &matrix) {
    for (std::size_t i = 0; i < matrix._rows; i++) {
        if (i)
            out << '\n';
        for (std::size_t j = 0; j < matrix._cols; j++) {
            if (j)
                out << ' ';
            out << matrix._data[i][j];
        }
    }

    return out;
}

Matrix Matrix::from_file(std::string file_path) {
    std::ifstream in(file_path);
    if (!in.is_open())
        throw MatrixFreadException("LOAD: unable to open file.");

    std::size_t rows, cols;
    if (!(in >> rows >> cols))
        throw MatrixFreadException("LOAD: invalid file format");

    Matrix result(rows, cols);

    for (std::size_t i = 0; i < result._rows; i++)
        for (std::size_t j = 0; j < result._cols; j++) {
            if (!(in >> result._data[i][j]))
                throw MatrixFreadException("LOAD: invalid file format");
        }

    return result;
}