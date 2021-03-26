#include <iostream>
#include <cstring>
#include <vector>
#include <cstddef>
#include <fstream>
#include <stdint.h>

#include "employees.hpp"

const int32_t Employee::type;

Employee::Employee(const char* name, int32_t base_salary) :
  _name{ std::strcpy(new char[101], name) },
  _base_salary{ base_salary }
{}

Employee::~Employee() {
  delete[] _name;
}

void create_employee_of_type(int32_t type, Employee*& employee) {
  if (type == Developer::type)
    employee = new Developer;
  if (type == SalesManager::type)
    employee = new SalesManager;
}

std::ostream& operator<<(std::ostream& out, const Employee& employee) {
  employee.print(out);
  return out;
}

std::istream& operator>>(std::istream& in, Employee& employee) {
  employee.read(in);
  return in;
}

std::ofstream& operator<<(std::ofstream& out, const Employee& employee) {
  employee.printf(out);
  return out;
}

std::ifstream& operator>>(std::ifstream& in, Employee& employee) {
  employee.readf(in);
  return in;
}

const int32_t Developer::type;

Developer::Developer(const char* name, int32_t base_salary, bool has_bonus) :
  Employee(name, base_salary),
  _has_bonus{ has_bonus }
{}

int Developer::salary() const {
  int salary = _base_salary;
  if (_has_bonus) { salary += 1000; }
  return salary;
}

bool Developer::has_bonus() const {
  return _has_bonus;
}

void Developer::print(std::ostream& out) const {
  out << "Developer" << std::endl
    << "Name: " << _name << std::endl
    << "Base Salary: " << _base_salary << std::endl
    << "Has bonus: " << (_has_bonus ? "+" : "-") << std::endl;
}

void Developer::read(std::istream& in) {
  in >> _name
     >> _base_salary
     >> _has_bonus;
}

void Developer::printf(std::ofstream& out) const {
  out.write((char*)&(Developer::type), 4);
  out.write(_name, strlen(_name) + 1);
  out.write((char*)&(_base_salary), 4);
  out.write((char*)&(_has_bonus), 1);
}

void Developer::readf(std::ifstream& in) {
  in.getline(_name, 101, 0);
  in.read((char*)&(_base_salary), 4);
  in.read((char*)&(_has_bonus), 1);
}

const int32_t SalesManager::type;

SalesManager::SalesManager(const char* name, int32_t base_salary, int32_t sold_nm, int32_t price) :
  Employee(name, base_salary),
  _sold_nm{ sold_nm },
  _price{ price }
{}

int SalesManager::salary() const {
  return _base_salary + _sold_nm * _price * 0.01;
}

int32_t SalesManager::sold_items() const {
  return _sold_nm;
}

int32_t SalesManager::price() const {
  return _price;
}

void SalesManager::print(std::ostream& out) const {
  out << "Sales Manager" << std::endl
    << "Name: " << _name << std::endl
    << "Base Salary: " << _base_salary << std::endl
    << "Sold items: " << _sold_nm << std::endl
    << "Item price: " << _price << std::endl;
}

void SalesManager::read(std::istream& in) {
  in >> _name
    >> _base_salary
    >> _sold_nm
    >> _price;
}

void SalesManager::printf(std::ofstream& out) const {
  out.write((char*)&(SalesManager::type), 4);
  out.write(_name, std::strlen(_name) + 1);
  out.write((char*)&(_base_salary), 4);
  out.write((char*)&(_sold_nm), 4);
  out.write((char*)&(_price), 4);
}

void SalesManager::readf(std::ifstream& in) {
  in.getline(_name, 101, 0);
  in.read((char*)&(_base_salary), 4);
  in.read((char*)&(_sold_nm), 4);
  in.read((char*)&(_price), 4);
}

EmployeesArray::~EmployeesArray() {
  for (std::size_t i = 0; i < _employees.size(); i++)
    delete _employees[i];
}

void EmployeesArray::add(Employee* e) {
  _employees.push_back(e);
}

int EmployeesArray::total_salary() const {
  int sum = 0;
  for (std::size_t i = 0; i < _employees.size(); i++)
    sum += _employees[i]->salary();
  return sum;
}

std::ostream& operator<<(std::ostream& out, const EmployeesArray& arr) {
  for (std::size_t i = 0; i < arr._employees.size(); i++) {
    out << i + 1 << ". " << *(arr._employees[i]);
  }
  out << "== Total salary: " << arr.total_salary() << std::endl;
  out << std::endl;

  return out;
}

std::ofstream& operator<<(std::ofstream& out, const EmployeesArray& arr) {
  uint32_t size = (uint32_t)arr._employees.size();
  out.write((char*)&size, 4);

  for (size_t i = 0; i < arr._employees.size(); i++)
    out << *(arr._employees[i]);

  return out;
}

std::ifstream& operator>>(std::ifstream& in, EmployeesArray& arr) {
  uint32_t size;
  in.read((char*)&size, 4);

  for (size_t i = 0; i < size; i++) {
    int32_t type;
    in.read((char*)&type, 4);

    Employee* employee = nullptr;
    create_employee_of_type(type, employee);
    if (employee == nullptr) {
      std::cerr << "Bad type" << std::endl;
      in.setstate(std::ios::failbit);
      return in;
    }
      
    in >> *employee;
    if (in.fail()) {
      std::cerr << "Failed to read employee" << std::endl;
      return in;
    }
    arr.add(employee);
  }

  return in;
}