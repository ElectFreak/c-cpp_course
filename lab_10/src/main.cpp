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
      if (std::cin.fail()) {
        std::cerr << "Failed to read type" << std::endl;
        break;
      }

      Employee* employee = nullptr;
      create_employee_of_type(type, employee);
      if (employee == nullptr) {
        std::cerr << "Bad type" << std::endl;
        break;
      }
      
      std::cin >> *employee;
      if (std::cin.fail()) {
        std::cerr << "Failed to read employee" << std::endl;
        break;
      }

      arr.add(employee);
    }

    if (arg == "list") {
      std::cout << arr;
    }

    if (arg == "save") {
      std::string path;
      std::cin >> path;
      if (std::cin.fail()) {
        std::cerr << "Failed to read path" << std::endl;
        break;
      }

      std::ofstream fout{ path };
      if (!fout.is_open()) {
        std::cerr << "Failed to open " << path << std::endl;
        break;
      }

      fout << arr;
      if (fout.fail()) {
        std::cerr << "Failed to write employees" << std::endl;
        break;
      }

    }

    if (arg == "load") {
      std::string path;
      std::cin >> path;
      std::ifstream fin{ path };

      if (!fin.is_open()) {
        std::cerr << "Failed to open " << path << std::endl;
        break;
      }

      fin >> arr;
      if (fin.fail()) {
        std::cerr << "Failed to read employees" << std::endl;
      }
    }
  }

  return 0;
}