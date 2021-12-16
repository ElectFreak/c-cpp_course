#pragma once

#include "TreeNode.h"
#include "Exception.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstddef>

struct code_t {
  uint64_t bits;
  uint8_t len;
};

class HuffCodes {

public:
  void make_codes_from_file(const uint64_t* bytes_freq) {

    std::vector<TreeNode*> nodes;
    for (uint16_t i = 0; i < 256; i++)
      if (bytes_freq[i])
        nodes.push_back(new TreeNode(i, bytes_freq[i]));

    /* Sorting leafs by frequency */
    std::sort(nodes.begin(), nodes.end(), [](TreeNode* first, TreeNode* second) {
      return first->freq > second->freq;
      });

    /* Build tree */
    if (nodes.size() == 1) {
      codes_table.resize(256);
      codes_table[nodes.back()->byte] = code_t{ 0, 1 };
      return;
    }

    while (nodes.size() > 1) {
      TreeNode* new_node = new TreeNode(*(nodes.end() - 1), *(nodes.end() - 2));
      nodes.pop_back(), nodes.pop_back();

      for (auto node_it = nodes.begin(); node_it <= nodes.end(); node_it++)
        if (node_it == nodes.end() || (*node_it)->freq < new_node->freq) {
          nodes.insert(node_it, new_node);
          break;
        }
    }

    average_codes_tree_root = nodes.back();

    /* Fill average codes lengths */
    current_code_len = 0;
    _fill_codes_lengths(average_codes_tree_root);

    /* Make cannonical codes */
    _make_cannonical_codes();
  }

  void make_codes_from_archive(const uint8_t* lengths) {
    for (uint16_t i = 0; i < 256; i++) {
      if (lengths[i])
        length_byte_pairs.emplace_back(lengths[i], i);
    }

    _make_cannonical_codes();
    _make_prefix_tree();
  }

  code_t get_code(const uint8_t byte) {
    return codes_table[byte];
  }

  TreeNode* get_prefix_tree() {
    return prefix_tree_root;
  }

  ~HuffCodes() {
    if (average_codes_tree_root)
      _free_node(average_codes_tree_root);

    if (prefix_tree_root)
      _free_node(prefix_tree_root);
  }

private:
  TreeNode* average_codes_tree_root = nullptr;
  TreeNode* prefix_tree_root = nullptr;
  std::vector<std::pair<uint8_t, uint8_t>> length_byte_pairs;
  std::vector<code_t> codes_table;
  uint8_t current_code_len;

  void _make_prefix_tree() {
    TreeNode* root = new TreeNode();
    for (uint16_t i = 0; i < 256; i++) {
      code_t code = get_code((uint8_t)i);
      if (!code.len)
        continue;

      TreeNode* current_node = root;

      while (code.len--) {
        uint8_t bit = 1 & (code.bits >> code.len);
        if (bit) {
          if (current_node->left == nullptr)
            current_node->left = new TreeNode;

          current_node = current_node->left;
        }
        else {
          if (current_node->right == nullptr)
            current_node->right = new TreeNode;

          current_node = current_node->right;
        }
      }

      current_node->byte = (uint8_t)i;
    }

    prefix_tree_root = root;
  }

  void _free_node(TreeNode* node) {
    if (node->left && node->right) {
      _free_node(node->left);
      _free_node(node->right);
    }

    delete node;
  }

  void  _make_cannonical_codes() {
    std::sort(length_byte_pairs.begin(), length_byte_pairs.end());
    code_t current_code = { 0, 0 };
    codes_table.resize(256, code_t{ 0, 0 });
    for (auto [len, byte] : length_byte_pairs) {
      current_code.bits <<= (len - current_code.len);
      current_code.len = len;
      codes_table[byte] = current_code;

      ++current_code.bits;
    }
  }

  void _fill_codes_lengths(TreeNode* node) {
    if (node->left == nullptr && node->right == nullptr) {
      length_byte_pairs.emplace_back(current_code_len, node->byte);
    }
    else {
      ++current_code_len;
      _fill_codes_lengths(node->left);
      _fill_codes_lengths(node->right);
      --current_code_len;
    }
  }
};