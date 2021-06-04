#pragma once

#include <exception>

namespace HuffException {
  class Exception : public std::exception {};

  class OpenFileFailed : public Exception {
  public:
    const char* what() const noexcept override {
      return "Failed to open file";
    }
  };

  class CorruptedArchive : public Exception {
  public:
    const char* what() const noexcept override {
      return "Archive is corrupted. Please execute with correct arhive";
    }
  };

  class BadArguments : public Exception {
  public:
    const char* what() const noexcept override {
      return "Bad command line arguments. Pleace execute with correct arguments";
    }
  };
}
