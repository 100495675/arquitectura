#include "validatefile.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>

namespace common {
constexpr int MAX_MAXLEVEL = 65536;

void validateFile::validate_magic_number(const std::string &string) {
  if (string != "P6") {
    throw std::invalid_argument("Invalid magic number");
  }
}

int validateFile::validate_width(const std::string &string) {
  try {
    const int width = std::stoi(string);
    if (width <= 0) {
      throw std::invalid_argument("Invalid width");
    }
    return width;
  } catch (const std::invalid_argument &ia) {
    throw std::invalid_argument("Invalid width");
  }
}

int validateFile::validate_height(const std::string &string) {
  try {
    const int height = std::stoi(string);
    if (height <= 0) {
      throw std::invalid_argument("Invalid height");
    }
    return height;
  } catch (const std::invalid_argument &ia) {
    throw std::invalid_argument("Invalid height");
  }
}

int validateFile::validate_maxlevel(const std::string &string) {
  try {
    const int maxlevel = std::stoi(string);
    if (maxlevel <= 0 || maxlevel >= MAX_MAXLEVEL) {
      throw std::invalid_argument("Invalid maxlevel");
    }
    return maxlevel;
  } catch (const std::invalid_argument &ia) {
    throw std::invalid_argument("Invalid maxlevel");
  }
}

void validateFile::validate_pixels(const std::string &string,
                                   size_t number_of_bytes) {
  if (string.size() != number_of_bytes) {
    throw std::invalid_argument("Invalid number of pixels");
  }
}
} // namespace common