#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include "matrix.hpp"
#include "MatrixException.hpp"

static inline int get_reg_id(std::string reg) {
  int reg_id = std::stoi(reg.substr(1));
  return reg_id;
}

int main() {
  std::vector<Matrix> registers(10);

  while (true) {
    std::string arg;
    if (!(std::cin >> arg) || arg == "exit")
      break;

    try {
      if (arg == "load") {
        std::string reg;
        std::cin >> reg;
        int reg_id = std::stoi(reg.substr(1));
        std::string file_path;
        std::cin >> file_path;
        Matrix matrix = Matrix::from_file(file_path);
        registers[reg_id] = matrix;
      }

      if (arg == "print") {
        std::string reg;
        std::cin >> reg;
        int reg_id = get_reg_id(reg);
        std::cout << registers[reg_id] << std::endl;
      }

      if (arg == "add") {
        std::string reg1, reg2;
        std::cin >> reg1 >> reg2;
        int reg1_id = get_reg_id(reg1);
        int reg2_id = get_reg_id(reg2);
        registers[reg1_id] += registers[reg2_id];
      }

      if (arg == "mul") {
        std::string reg1, reg2;
        std::cin >> reg1 >> reg2;
        int reg1_id = get_reg_id(reg1);
        int reg2_id = get_reg_id(reg2);
        registers[reg1_id] *= registers[reg2_id];
      }

      if (arg == "elem") {
        std::string reg;
        std::size_t row, col;
        std::cin >> reg;
        std::cin >> row >> col;
        int reg_id = get_reg_id(reg);
        std::cout << registers[reg_id].get(row, col) << std::endl;
      }

    }
    catch (std::bad_alloc& e) {
      std::cout << "Unable to allocate memory." << std::endl;
      continue;
    }
    catch (MatrixException& e) {
      std::cout << e.what() << std::endl;
    }

  }

  return 0;
}