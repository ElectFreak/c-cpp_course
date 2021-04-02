#pragma once

#include "my_vector.hpp"

namespace containers {
  template <typename T>
  void my_vector<T>::push_back(const T& t) {
    if (_size + 1 > _capacity)
      reserve(std::max(_size << 1, (std::size_t)2));

    new(_array + _size)T(t);
    _size++;
  }

}



