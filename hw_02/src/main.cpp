#include <iostream>
#include <string_view>

#include "HuffmanArchiver.h"
#include "Exception.h"

enum action_t {
  PACK,
  UNPACK
} action;

std::string_view file_in, file_out;

void process_args(int argc, char** argv) {
  if (argc != 6) {
    throw HuffException::BadArguments();
  }

  int i = 1, j = 0;
  while (i != argc && ++j != 5) {
    std::string_view arg(argv[i]);

    if (arg == "-c") {
      action = PACK;
      ++i;
    }

    if (arg == "-u") {
      action = UNPACK;
      ++i;
    }

    if (arg == "-f" || arg == "--file") {
      file_in = std::string_view(argv[i + 1]);
      i += 2;
    }

    if (arg == "-o" || arg == "--output") {
      file_out = std::string_view(argv[i + 1]);
      i += 2;
    }
  }

  if (i != argc)
    throw HuffException::BadArguments();
}

int main(int argc, char** argv) {

  HuffmanArchiver archiver;
  stats_t stats;
  try {
    process_args(argc, argv);
    switch (action) {
    case (PACK):
      stats = archiver.zip(file_in, file_out);
      break;
    case (UNPACK):
      stats = archiver.unzip(file_in, file_out);
      break;
    }
  }
  catch (HuffException::Exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  std::cout << std::dec << stats.input_size << '\n'
    << stats.output_size << '\n'
    << stats.metadata_size << std::endl;

  return 0;
}