#pragma once

#include <cstddef>
// #include <new>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace containers {

  template<typename T>
  class my_vector {
  public:
    my_vector() : _capacity{ 0 }, _size{ 0 }, _array{ nullptr } {}

    explicit my_vector(std::size_t n) : _capacity{ 0 }, _size{ 0 } { // contract: T is DefaultConstructable
      reserve(n);

      for (std::size_t i = 0; i < n; i++)
        new(_array + i)T();

      _size = n;
    }

    my_vector(const my_vector<T>& other) : _capacity{ 0 }, _size{ 0 } {
      _copy(other);
    }

    ~my_vector() {
      _run_destructors();
      delete[](char*)_array;
    }

    T& operator[](std::size_t i) {
      return _array[i];
    }

    const T& operator[](std::size_t i) const {
      return _array[i];
    }

    my_vector& operator=(const my_vector<T>& other) {
      _copy(other);
      return *this;
    }

    std::size_t size() const {
      return _size;
    }

    std::size_t capacity() const {
      return _capacity;
    }

    bool empty() const {
      return _size == 0;
    }

    void resize(std::size_t n) { // contract: T is DefaultConstructable
      if (n > _size)
        _resize_up(n);
      if (n < _size)
        _resize_down(n);
    }

    void push_back(const T& t) {
      if (_size + 1 > _capacity)
        reserve(std::max(_size << 1, (std::size_t)2));

      new(_array + _size)T(t);
      _size++;
    }

    void pop_back() {
      _array[_size - 1].~T();
      _size--;
    }

    void clear() {
      _resize_down(0);
    }

    void reserve(std::size_t new_capacity) {
      if (new_capacity <= _capacity)
        return;

      std::size_t complete_capacity = 1;
      while (complete_capacity < new_capacity)
        complete_capacity <<= 1;

      T* new_array = _alloc_mem(complete_capacity);
      for (std::size_t i = 0; i < _size; i++)
        new(new_array + i)T(_array[i]);

      _run_destructors();
      delete[](char*)_array;
      _array = new_array;
      _capacity = complete_capacity;
    }

    template<typename T1>
    friend std::ostream& operator<<(std::ostream&, const my_vector<T1>&);

  private:
    std::size_t _capacity;
    std::size_t _size;
    T* _array;

    static T* _alloc_mem(size_t n) {
      return (T*)new char[sizeof(T) * n];
    }

    void _run_destructors() {
      for (std::size_t i = 0; i < _size; i++)
        _array[i].~T();
    }

    void _copy(const my_vector<T>& other) {
      reserve(other._size);
      _run_destructors();
      for (std::size_t i = 0; i < other._size; i++)
        new(_array + i)T(other._array[i]);
    }

    void _resize_up(std::size_t n) { // contract: T is DefaultConstructable
      if (n <= _size)
        return;

      reserve(n);
      for (std::size_t i = _size; i < n; i++)
        new(_array + i)T();

      _size = n;
    }

    void _resize_down(std::size_t n) { // contract: T is Destrutable (always)
      if (n >= _size)
        return;

      for (std::size_t i = n; i < _size; i++)
        _array[i].~T();

      _size = n;
    }

  };

  template<typename T>
  inline std::ostream& operator<<(std::ostream& out, const my_vector<T>& v) {
    for (std::size_t i = 0; i < v.size() - 1; i++)
      out << v[i] << " ";
    out << v[v.size() - 1];
    return out;
  }
}
