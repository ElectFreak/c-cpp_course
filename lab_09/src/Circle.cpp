#include <iostream>
#include <cstring>

#include "Circle.hpp"
#include "Figure.hpp"

Circle::Circle(int id, int x, int y, int radius, const char* s) : Figure(id, x, y), radius{radius} {
  label = new char[std::strlen(s) + 1]();
  std::strcpy(label, s);
};

Circle::~Circle() {
  delete label;
}

void Circle::print() const {
  std::cout << "Circle " << id << " x = " << x << " y = " << y << " radius = " << radius << " label = " << label << std::endl;
}

void Circle::zoom(int factor) {
  radius *= factor;
}

static inline int sqr(int x) {
  return x * x;
}

bool Circle::is_inside(int x, int y) const {
  return sqr(this->x - x) + sqr(this->y - y) <= sqr(this->radius);
}