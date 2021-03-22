#include <cassert>

#include "Scheme.hpp"
#include "Figure.hpp"

Scheme::Scheme(int capacity) : _data(new Figure*[capacity]), _sz{0}, _cp{capacity} {}

Scheme::~Scheme() {
  for (int i = 0; i < _sz; i++)
    delete _data[i];
  delete [] _data;
}

void Scheme::push_back_figure(Figure* figure) {
  assert(_sz < _cp);
  _data[_sz++] = figure;
}

void Scheme::remove_figure(int id) {
  for (int i = 0; i < _sz; i++)
    if (_data[i]->get_id() == id) {
      delete _data[i];
      for (int j = i; j < _sz - 1; j++) 
        _data[j] = _data[j+1];
      
      _data[--_sz] = nullptr;
    }
}

void Scheme::print_all_figures() const {
  for (int i = 0; i < _sz; i++)
    _data[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
  for (int i = 0; i < _sz; i++)
    if (_data[i]->get_id() == id) {
      _data[i]->zoom(factor);
      return;
    }
}

Figure* Scheme::is_inside_figure(int x, int y) const {
  for (int i = 0; i < _sz; i++)
    if (_data[i]->is_inside(x, y))
      return _data[i];
  return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
  for (int i = 0; i < _sz; i++)
    if (_data[i]->get_id() == id) {
      _data[i]->move(new_x, new_y);
      return;
    }
}