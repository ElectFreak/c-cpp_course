#include <iostream> 
#include <string>
#include <stdint.h>
#include <fstream>

#include "employees.hpp"

int main() {
  std::string arg;
  EmployeesArray arr;
  while (true) {
    if (!(std::cin >> arg))
      break;

    if (arg == "exit")
      break;

    if (arg == "add") {
      int32_t type;
      std::cin >> type;
      Employee* employee;
      create_employee_of_type(type, employee);
      std::cin >> *employee;
      arr.add(employee);
    }

    if (arg == "list") {
      std::cout << arr;
    }

    if (arg == "save") {
      std::string path;
      std::cin >> path;
      std::ofstream fout{ path };
      fout << arr;
    }

    if (arg == "load") {
      std::string path;
      std::cin >> path;
      std::ifstream fin{ path };
      fin >> arr;
    }
  }

  return 0;
}