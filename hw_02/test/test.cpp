#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "HuffmanArchiver.h"
#include "HuffCodes.h"

#include <fstream>
#include <filesystem>
#include <iostream>

bool test_pack_unpack(std::string_view path) {
  HuffmanArchiver archiver;
  archiver.zip(path, "out");
  archiver.unzip("out", "unpack");

  std::ifstream first(path);
  std::ifstream second("unpack");

  first.seekg(0, std::ios::end);
  uint64_t size = first.tellg();
  second.seekg(0, std::ios::end);
  if (size != second.tellg())
    return false;
  first.seekg(0);
  second.seekg(0);

  uint8_t byte1, byte2;
  while (size--) {
    second.read((char*)&byte2, 1);
    first.read((char*)&byte1, 1);

    if (byte1 != byte2)
      return false;
  }

  return true;
}

TEST_CASE("Generally") {
  for (const auto& entry : std::filesystem::directory_iterator("./bin"))
    CHECK(test_pack_unpack(entry.path().c_str()));
}

TEST_CASE("Make codes from file") {
  uint64_t freq[256]{0};
  for (uint16_t i = 0; i < 256; i += 2)
    freq[i] = 1;

  HuffCodes codes;
  codes.make_codes_from_file(freq);

  for (uint16_t i = 0; i < 256; ++i) {
    code_t code = codes.get_code(i);
  
    if (i % 2)
      CHECK(code.len == 0);
    else 
      CHECK(code.len != 0);
  }

}

TEST_CASE("Make codes from archive") {
  uint8_t lengths[256]{0};
  lengths[0] = 1;
  lengths[1] = 1;
  HuffCodes codes;
  codes.make_codes_from_archive(lengths);
  code_t code;
  code = codes.get_code(0);
  CHECK(code.len);
  code = codes.get_code(1);
  CHECK(code.len);
  for (uint16_t i = 2; i < 256; ++i)
    CHECK(!codes.get_code(i).len);
}