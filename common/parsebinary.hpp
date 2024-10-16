#ifndef PARSEBINARY_HPP
#define PARSEBINARY_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace common {
class ParseBinary {
private:
  static void skip_spaces(const std::vector<uint8_t> &data, size_t &i);
  static void skip_one_space(const std::vector<uint8_t> &data, size_t &i);
  static std::string read_string(const std::vector<uint8_t> &data, size_t &i);
  static std::string read_string_to_end(const std::vector<uint8_t> &data,
                                        size_t &i);

public:
  static std::vector<std::string> parse(const std::vector<uint8_t> &data);
};
} // namespace common

#endif