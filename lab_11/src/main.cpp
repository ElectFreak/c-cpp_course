#include <iostream>
#include <cassert>
#include <cstring>
#include "my_vector.hpp"

namespace product {
  class Product {
  public:
    Product(const char* name, int quantity, double price) :
      _name{ std::strcpy(new char[std::strlen(name) + 1], name) },
      _quantity{ quantity },
      _price{ price }
    {}

    Product(const Product& p) :
      Product(p._name, p._quantity, p._price)
    {}

    ~Product() {
      delete[] _name;
    }

    friend std::ostream& operator<<(std::ostream&, const Product&);

  private:
    char* _name;  // Указатель владеет C-style строкой, на которую указывает.
    int _quantity;
    double _price;
  };

  void print(const containers::my_vector<Product>& v) {
    std::cout << v << std::endl;
  }

  std::ostream& operator<<(std::ostream& out, const Product& p) {
    return out << p._name << " " << p._quantity << " " << p._price;
  }

} // namespace product

template<typename T>
void test_my_vector(const T& a, const T& b) {
  containers::my_vector<T> v;

  v.push_back(a);
  v.push_back(b);

  assert(!v.empty());

  assert(v.size() == 2);
  std::cout << "both objects are added" << std::endl;

  v.pop_back();
  assert(v.size() == 1);
  std::cout << "second object is removed" << std::endl;

  v.push_back(b);
  assert(v.size() == 2);
  std::cout << "second object is added" << std::endl;

  v.reserve(1000);
  assert(v.capacity() == 1 << 10);

  std::cout << v << std::endl;
  std::cout << "OK" << std::endl;
}

template <typename T>
void test_my_vector_default_constructable(const T& a, const T& b) {
  containers::my_vector<T> v;
  v.push_back(a);
  v.push_back(b);
  v.resize(5);
  assert(v.size() == 5);
  std::cout << "resize to 5 is done, vector:" << std::endl;
  std::cout << v << std::endl;

  containers::my_vector<T> v_empty(2);
  assert(v_empty.size() == 2);
  std::cout << "empty 2x vector initialized, vector:" << std::endl;
  std::cout << v_empty << std::endl;
  v_empty.push_back(a);
  v_empty.push_back(b);
  assert(v_empty.size() == 4);
  std::cout << "both objects pushed, vector:" << std::endl;
  std::cout << v_empty << std::endl;

  std::cout << "OK" << std::endl;
}

int main() {
  test_my_vector<int>(5, 10);
  test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));

  test_my_vector_default_constructable(3, 5);
  return 0;
}