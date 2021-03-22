#pragma once

#include "Figure.hpp"

class Scheme {
public:
  Scheme(int capacity);
  ~Scheme();

  void push_back_figure(Figure* figure);
  void remove_figure(int id);

  void print_all_figures() const;
  void zoom_figure(int id, int factor);
  Figure* is_inside_figure(int x, int y) const;
  void move(int id, int new_x, int new_y);
  
private:  
  Figure** _data;
  int _sz, _cp;
};