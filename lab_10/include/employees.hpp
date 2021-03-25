#pragma once

#include <stdint.h>
#include <vector>

class Employee {
public:
  Employee(const char* name, int32_t base_salary);

  virtual ~Employee();

  const static int32_t type = 0;

  virtual int salary() const = 0;

  friend std::istream& operator>>(std::istream&, Employee&);
  friend std::ostream& operator<<(std::ostream&, const Employee&);
  friend std::ifstream& operator>>(std::ifstream&, Employee&);
  friend std::ofstream& operator<<(std::ofstream&, const Employee&);
protected:
  virtual void print(std::ostream& out) const = 0;
  virtual void read(std::istream& in) = 0;
  virtual void printf(std::ofstream& out) const = 0;
  virtual void readf(std::ifstream& in) = 0;
  char* _name;
  int32_t _base_salary;
};

void create_employee_of_type(int32_t type, Employee*& employee);

class Developer : public Employee {
public:
  Developer(const char* name = "", int32_t base_salary = 0, bool has_bonus = false);

  const static int32_t type = 1;

  int salary() const;
  bool has_bonus() const;

  void print(std::ostream& out) const;
  void read(std::istream& in);
  void printf(std::ofstream& out) const;
  void readf(std::ifstream& in);

private:
  bool _has_bonus;
};

class SalesManager : public Employee {
public:
  SalesManager(const char* name = "", int32_t base_salary = 0, int32_t sold_nm = 0, int32_t price = 0);

  const static int32_t type = 2;

  int salary() const;
  int32_t sold_items() const;
  int32_t price() const;

  void print(std::ostream& out) const;
  void read(std::istream& in);
  void printf(std::ofstream& out) const;
  void readf(std::ifstream& in);

private:
  int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
  EmployeesArray() = default;
  ~EmployeesArray();
  void add(Employee* e);
  int total_salary() const;

  friend std::ostream& operator<<(std::ostream&, const EmployeesArray&);
  friend std::ofstream& operator<<(std::ofstream&, const EmployeesArray&);
  friend std::ifstream& operator>>(std::ifstream&, EmployeesArray&);

private:
  std::vector<Employee*> _employees;
};