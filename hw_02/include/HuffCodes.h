#pragma once

#include "TreeNode.h"
#include "Exception.h"

#include <algorithm>
#include <vector>
#include <cstddef>

struct code_t {
  uint64_t bits;
  uint8_t len;
};

class HuffCodes {

public:
  void make_codes_from_file(const uint64_t* bytes_freq);

  void make_codes_from_archive(const uint8_t* lengths);

  code_t get_code(const uint8_t byte);

  TreeNode* get_prefix_tree();

  HuffCodes() = default;
  HuffCodes(HuffCodes&) = delete;
  HuffCodes(HuffCodes&&) = delete;
  HuffCodes& operator=(HuffCodes&) = delete;
  HuffCodes& operator=(HuffCodes&&) = delete;

  ~HuffCodes();

private:
  TreeNode* average_codes_tree_root = nullptr;
  TreeNode* prefix_tree_root = nullptr;
  std::vector<std::pair<uint8_t, uint8_t>> length_byte_pairs;
  std::vector<code_t> codes_table;
  uint8_t current_code_len;

  void _make_prefix_tree();

  void _free_node(TreeNode* node);

  void  _make_cannonical_codes();

  void _fill_codes_lengths(TreeNode* node);
};