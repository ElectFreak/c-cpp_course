#pragma once

#include <cstddef>

class MyVector {
public:
  MyVector() {
    _size = _capacity = 0;
    _data = nullptr;
    reserve(2);
  }

  MyVector(std::size_t init_capacity) {
    _data = new int[init_capacity];
    _size = 0;
  }

  MyVector(MyVector const &vector) {
    _data = new int[vector._capacity];
    _capacity = vector._capacity;
    _size = vector._size;
    for (std::size_t i = 0; i < _size; i++)
      _data[i] = vector._data[i];
  }

  ~MyVector() {
    delete[] _data;
  }

  void set(std::size_t index, int value) {
    _data[index] = value;
  }

  int get(std::size_t index) {
    return _data[index];
  }

  std::size_t size() {
    return _size;
  }

  std::size_t capacity() {
    return _capacity;
  }

  void reserve(std::size_t new_capacity) {
    if (new_capacity <= _capacity)
      return;

    int* new_data = new int[new_capacity];
    for (int i = 0; i < _size; i++)
      new_data[i] = _data[i];
    if (_data != nullptr)
      delete[] _data;
    _data = new_data;
    _capacity = new_capacity;
  }

  void resize(std::size_t new_size) {
    reserve(new_size); 
    for (int i = _size; i < new_size; i++)
      _data[i] = 0;
    _size = new_size;
  }

  void push_back(int value) {
    reserve_twice_cp();
    _data[_size] = value;
    _size++;
  }

  void insert(std::size_t index, int value) {
    reserve_twice_cp();
    for (int i = _size; i > index; i--)
      _data[i] = _data[i - 1];
    _data[index] = value; 
    _size++;
  }

  void erase(std::size_t index) {
    for (int i = index; i < _size - 1; i++)
      _data[i] = _data[i + 1];
    _size--;
  }

private:
  int* _data;
  std::size_t _capacity, _size;

  void reserve_twice_cp() {
    if (_size + 1 > _capacity)
      reserve(_size << 1);
  }
};