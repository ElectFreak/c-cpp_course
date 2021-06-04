#pragma once

#include "HuffCodes.h"
#include "Exception.h"

#include <string_view>
#include <vector>
#include <fstream>
#include <bitset>

struct stats_t {
  uint64_t input_size;
  uint64_t output_size;
  uint16_t metadata_size = 264;
};

class HuffmanArchiver {
public:
  void zip(std::string_view file_in, std::string_view file_out) {
    std::ifstream fin(file_in, std::ios::binary | std::ios::in);
    std::ofstream fout(file_out, std::ios::binary | std::ios::out);

    if (!(fin.is_open()) || !(fout.is_open()))
      throw HuffException::OpenFileFailed();

    /* Input size */
    fin.seekg(0, std::ios::end);
    stats.input_size = fin.tellg();

    if (!stats.input_size) {
      stats.output_size = 0;
      stats.metadata_size = 0;
      fin.close();
      fout.close();
      return;
    }

    fout.write((char*)&stats.input_size, 8);

    /* First reading, count frequency */
    uint64_t bytes_freq[256]{0};

    uint8_t byte;
    fin.seekg(0);
    while (fin.read((char*)&byte, 1)) {
      ++bytes_freq[byte];
    }

    HuffCodes codes;
    codes.make_codes_from_file(bytes_freq);

    /* Write lengths of codes */
    for (uint16_t i = 0; i < 256; ++i) {
      code_t code = codes.get_code(i);
      fout.write((char*)&code.len, 1);
    }

    /* Write data */
    uint64_t acc = 0;
    uint8_t fill = 0;
    code_t code;
    fin.close();
    fin.open(file_in);
    if (!fin)
      throw HuffException::OpenFileFailed();

    while (fin.read((char*)&byte, 1)) {
      code = codes.get_code(byte);
      while (fill != 64 && code.len != 0) {
        acc |= ((code.bits >> --code.len) & 1) << fill;
        ++fill;
      }

      if (fill == 64) {
        fout.write((char*)&acc, 8);
        fill = 0;
        acc = 0;
      }

      while (code.len) {
        acc |= ((code.bits >> --code.len) & 1) << fill;
        ++fill;
      }
    }

    while (fill > 8) {
      uint8_t byte = static_cast<uint8_t>(acc & 0xFF);
      fout.write((char*)&byte, 1);
      acc >>= 8;
      fill -= 8;
    }

    if (fill)
      fout.write((char*)&acc, 1);

    stats.output_size = fout.tellp();

    fin.close();
    fout.close();
  }

  void unzip(std::string_view file_in, std::string_view file_out) {
    std::ifstream fin(file_in, std::ios::binary);
    std::ofstream fout(file_out, std::ios::binary);

    if (!fin.is_open() || !fout.is_open())
      throw HuffException::OpenFileFailed();

    fin.seekg(0, std::ios::end);
    stats.input_size = fin.tellg();

    if (!stats.input_size) {
      stats.output_size = 0;
      stats.metadata_size = 0;
      fin.close();
      fout.close();
      return;
    }

    fin.seekg(0);
    fin.read((char*)&stats.output_size, 8);
    uint8_t lengths[256];
    fin.read((char*)&lengths, 256);
    HuffCodes codes;
    codes.make_codes_from_archive(lengths);
    TreeNode* prefix_tree_root = codes.get_prefix_tree();
    TreeNode* current_node = prefix_tree_root;
    uint64_t progress = 0;
    
    while (true) {
      uint8_t byte;
      fin.read((char*)&byte, 1);

      for (uint8_t j = 0; j < 8; ++j) {
        uint8_t bit = 1 & (byte >> j);

        if (bit && !current_node->left || !bit && !current_node->right)
          throw HuffException::CorruptedArchive();

        if (bit) 
          current_node = current_node->left;
        else
          current_node = current_node->right;

        if (current_node->left == nullptr && current_node->right == nullptr) {
          fout.write((char*)&(current_node->byte), 1);

          if (++progress == stats.output_size) {
            fout.close();
            fin.close();
            return;
          }

          current_node = prefix_tree_root;
        }
      }
    }
  }

  stats_t stats;
};
