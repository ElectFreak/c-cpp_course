#include <cmath>
#include <iostream>

#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int w, int h) :
  Figure(id, x, y),
  width{ w },
  height{ h }
{};

bool Rectangle::is_inside(int x, int y) const {
  return (2 * std::abs(x - this->x) <= (width) && 2 * std::abs(y - this->y) <= height);
}

void Rectangle::zoom(int factor) {
  width *= factor;
  height *= factor;
}

void Rectangle::print() const {
  std::cout << "Rectangle: " << id << " x = " << x << " y = " << y << " width = " << width << " height = " << height << std::endl;
}