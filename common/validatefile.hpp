#ifndef VALIDATEFILE_HPP
#define VALIDATEFILE_HPP

#include <cstddef>
#include <string>

namespace common {

class validateFile {
public:
  static void validate_magic_number(const std::string &string);
  static int validate_width(const std::string &string);
  static int validate_height(const std::string &string);
  static int validate_maxlevel(const std::string &string);
  static void validate_pixels(const std::string &string,
                              const size_t number_of_bytes);
};
} // namespace common

#endif