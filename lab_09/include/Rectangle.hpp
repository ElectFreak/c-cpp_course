#pragma once

#include "Figure.hpp"

class Rectangle : public Figure {
public:
  Rectangle(int id, int x, int y, int w, int h);
  ~Rectangle() override = default;

  int width, height;
  void print() const override;
  bool is_inside(int x, int y) const override;

  void zoom(int factor) override;
};