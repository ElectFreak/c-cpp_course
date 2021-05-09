#include <iostream>

#include "HuffmanArchiver.h"

int main(int arc, char** argv) {  
  HuffmanArchiver archiver("file", "out");
  // std::cout << "smth" << std::endl;
  archiver.zip();

  HuffmanArchiver unpack("out", "unpack");
  unpack.unzip();

  return 0;
}