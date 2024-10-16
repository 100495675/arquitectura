#include "parsebinary.hpp"
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace common {

void ParseBinary::skip_spaces(const std::vector<uint8_t> &data, size_t &i) {
  skip_one_space(data, i);
  while (std::isspace(data.at(i))) {
    if (i < data.size() - 1) {
      i++;
    } else {
      throw std::runtime_error("Error en los espacios");
    }
  }
}
void ParseBinary::skip_one_space(const std::vector<uint8_t> &data, size_t &i) {
  if (std::isspace(data.at(i)) && i < data.size() - 1) {
    i++;
  } else {
    throw std::runtime_error("Error en los espacios");
  }
}

std::string ParseBinary::read_string(const std::vector<uint8_t> &data,
                                     size_t &i) {
  std::string s;
  while (i < data.size() && !std::isspace(data.at(i))) {
    s += static_cast<char>(data.at(i));
    i++;
  }
  if (i >= data.size()) {
    throw std::runtime_error("Error en la lectura de la cadena");
  }
  return s;
}

std::string ParseBinary::read_string_to_end(const std::vector<uint8_t> &data,
                                            size_t &i) {
  std::string s;
  while (i < data.size()) {
    s += static_cast<char>(data.at(i));
    i++;
  }
  return s;
}
std::vector<std::string> ParseBinary::parse(const std::vector<uint8_t> &data) {
  if (data.size() == 0) {
    throw std::runtime_error("Error archivo vacio");
  }
  std::vector<std::string> result;
  size_t i = 0;

  if (std::isspace(data.at(i))) {
    throw std::runtime_error("Error en los espacios al inicio");
  }

  result.push_back(read_string(data, i));

  skip_spaces(data, i);

  result.push_back(read_string(data, i));

  skip_spaces(data, i);

  result.push_back(read_string(data, i));

  skip_spaces(data, i);

  result.push_back(read_string(data, i));

  skip_one_space(data, i);

  result.push_back(read_string_to_end(data, i));

  return result;
}

} // namespace common