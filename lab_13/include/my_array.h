#pragma once

#include <cassert>
#include <array>
#include <cstddef>

#include <iostream>

namespace lab_13 {
  template<typename T, std::size_t N>
  class my_array {
  public:
    my_array() {};
    ~my_array() {};

    T& operator[](std::size_t index) {
      return data[index];
    }

    const T& operator[](std::size_t index) const {
      return data[index];
    }

    T& at(std::size_t index) {
      assert(index < N);

      return (*this)[index];
    }

    const T& at(std::size_t index) const {
      assert(index < N);

      return (*this)[index];
    }

    bool empty() const {
      return false;
    }

    std::size_t size() const {
      return N;
    }

    void fill(T val) {
      for (std::size_t i = 0; i < N; i++)
        data[i] = val;
    }

  private:
    T data[N];
  };

  template <std::size_t N>
  class my_array<bool, N> {
  public:
    my_array() {};
    ~my_array() {};

    class bool_reference {
    public:
      bool_reference(std::uint8_t& byte, std::size_t msk) : byte(byte), msk(msk) {};
      ~bool_reference() {};

      bool_reference& operator=(bool val) {
        byte &= ~msk;

        if (val)
          byte |= msk;

        return *this;
      }

      bool_reference& operator=(bool_reference& val) {
        return *this = (bool)val;
      }

      operator bool() const {
        return !((byte & msk) == 0);
      }

    private:
      std::uint8_t& byte;
      std::size_t msk;
    };

    static std::size_t msk(std::size_t index) {
      return 1 << (index % 8);
    }

    bool operator[](std::size_t index) const {
      return !((data[index >> 3] & msk(index)) == 0);
    }

    bool_reference operator[](std::size_t index) {
      return bool_reference(data[index >> 3], msk(index));
    }

    bool_reference at(std::size_t index) {
      assert(index < N);

      return (*this)[index];
    }

    bool at(std::size_t index) const {
      assert(index < N);

      return (*this)[index];
    }

    bool empty() const {
      return false;
    }

    std::size_t size() const {
      return N;
    }

    void fill(bool val) {
      for (std::size_t i = 0; i < N; i++)
        (*this)[i] = val;
    }

  private:
    std::uint8_t data[(N % 8) ? N / 8 + 1 : N / 8];
  };

}
