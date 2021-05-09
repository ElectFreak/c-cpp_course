#pragma once

#include "HuffTree.h"

#include <string>
#include <vector>
#include <fstream>
#include <bitset>

class HuffmanArchiver {
public:
  HuffmanArchiver(std::string file_in, std::string file_out) : file_in{ file_in }, file_out{ file_out } {};

  bool zip() {
    std::ifstream fin(file_in, std::ios::binary | std::ios::in);
    std::ofstream fout(file_out, std::ios::binary | std::ios::out);

    if (!(fin.is_open()) || !(fout.is_open()))
      return false;

    /* Build tree */
    HuffTree tree;
    tree.make_codes_from_file(fin);

    /* Write lengths of codes */
    for (uint16_t i = 0; i < 256; ++i) {
      code_t code = tree.get_code(i);
      fout << code.len;
    }

    /* Write data */
    uint64_t acc = 0;
    uint8_t fill = 0;
    uint8_t byte;
    code_t code;
    fin.close();
    fin.open(file_in);
    if (!fin)
      std::cout << "open failed" << std::endl;

    while (fin.read((char*)&byte, 1)) {
      code = tree.get_code(byte);
      // std::cout << "byte is " << byte << " code is " << std::bitset<3>(code.bits) << std::endl;
      while (fill != 64 && code.len != 0) {
        acc |= ((code.bits >> --code.len) & 1) << fill;
        ++fill;
      }

      if (fill == 64) {
        fout.write((char*)&acc, 8);
        // std::cout << "filled, acc: " << std::bitset<64>(acc) << std::endl;
        fill = 0;
        acc = 0;
      }

      while (code.len) {
        acc |= ((code.bits >> --code.len) & 1) << fill;
        ++fill;
      }

    }

    while (fill > 8) {
      fout << (uint8_t)(acc & 0xFF);
      acc >>= 8;
      fill -= 8;
    }

    fout.write((char*)&acc, 1);
    fout.write((char*)&fill, 1);
    // std::cout << "last fill: " << (int)fill << std::endl;

    fin.close();
    fout.close();
    return true;
  }

  bool unzip() {
    std::ifstream fin(file_in, std::ios::binary);
    std::ofstream fout(file_out, std::ios::binary);

    if (!fin.is_open() || !fout.is_open())
      return false;

    HuffTree tree;
    tree.make_codes_from_archive(fin);
    TreeNode* prefix_tree_root = tree.get_prefix_tree();

    fin.seekg(-1, std::ios_base::end);
    uint64_t data_size = (uint64_t)fin.tellg() - 256;
    // std::cout << "data_size: " << data_size << std::endl;
    uint8_t last_fill;
    fin.read((char*)&last_fill, 1);
    // std::cout << "last fill: " << (int)last_fill << std::endl;

    fin.clear();
    fin.seekg(256, std::ios_base::beg);
    uint8_t byte;
    TreeNode* current_node = prefix_tree_root;

    // std::cout << "will be " << data_size - 1 << " iterations" << std::endl;
    for (uint64_t i = 0; i < data_size - 1; ++i) {
      // std::cout << "i = " << i << std::endl;
      if (fin.tellg() != 256 + i)
        std::cout << "попался!" << std::endl;

      fin.read((char*)&byte, 1);
      // if (!(fin >> byte)) {
      //   std::cout << "failed to read data, i = " << i << std::endl;
      //   std::cout << fin.eof() << std::endl;
      // }

      // std::cout << "byte is " << (int)byte << std::endl;
      for (uint8_t j = 0; j < 8; ++j) {
        uint8_t bit = 1 & (byte >> j);
        // std::cout << "bit is " << (int)bit << std::endl;

        if (bit)
          current_node = current_node->left;
        else
          current_node = current_node->right;

        if (current_node->left == nullptr && current_node->right == nullptr) {
          // std::cout << "write byte: " << current_node->byte << std::endl;
          fout << current_node->byte << std::flush;
          current_node = prefix_tree_root;
        }
      }
    }

    // std::cout << "tellg: " << fin.tellg() << std::endl;

    fin.read((char*)&byte, 1);

    // std::cout << "last byte is " << (int)byte << std::endl;

    for (uint8_t i = 0; i < last_fill; i++) {
      uint8_t bit = 1 & (byte >> i);
      // std::cout << "bit is " << (int)bit << std::endl;

      if (bit)
        current_node = current_node->left;
      else
        current_node = current_node->right;

      if (current_node->left == nullptr && current_node->right == nullptr) {
        // std::cout << "write byte: " << current_node->byte << std::endl;
        fout << current_node->byte << std::flush;
        current_node = prefix_tree_root;
      }
    }

    fout.close();
    fin.close();
    return true;
  }

private:
  std::string file_in, file_out;
};
