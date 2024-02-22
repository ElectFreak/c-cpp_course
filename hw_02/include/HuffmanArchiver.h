#pragma once

#include "HuffCodes.h"
#include "Exception.h"

#include <cstddef>
#include <string_view>

struct stats_t {
  uint64_t input_size;
  uint64_t output_size;
  uint16_t metadata_size = 264;
};

class HuffmanArchiver {
public:
  stats_t zip(std::string_view file_in, std::string_view file_out);
  stats_t unzip(std::string_view file_in, std::string_view file_out);

private: 
  stats_t stats;
};
