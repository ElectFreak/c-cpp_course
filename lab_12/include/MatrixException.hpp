#pragma once

#include <exception>
#include <cstring>

class MatrixException : public std::exception {
public:
  MatrixException(const char* message) : _message{
    std::strcpy(new char[std::strlen(message) + 1], message)
  } {}

  ~MatrixException() {
    delete[] _message;
  } 

  virtual const char* what() const noexcept override {
    return _message;
  }

private:
  const char* _message;
};

class MatrixAddException : public MatrixException {
public:
  MatrixAddException(const char* message) : MatrixException(message) {}
};

class MatrixMulException : public MatrixException {
public:
  MatrixMulException(const char* message) : MatrixException(message) {}
};

class MatrixGetException : public MatrixException {
public:
  MatrixGetException(const char* message) : MatrixException(message) {}
};

class MatrixFreadException : public MatrixException {
public:
  MatrixFreadException(const char* message) : MatrixException(message) {}
};