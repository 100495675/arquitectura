
#include "imagesoa.hpp"

#include "../common/aux.hpp"
#include "../common/parsebinary.hpp"
#include "../common/validatefile.hpp"

#include <string>
#include <variant>
#include <vector>

namespace imgsoa {

  int SOA::getWidth() const {
    return width;
  }

  int SOA::getHeight() const {
    return height;
  }

  int SOA::getMaxLevel() const {
    return maxlevel;
  }

  SOA::SOA(std::vector<uint8_t> const & binary) {
    std::vector<std::string> const tokens = common::ParseBinary::parse(binary);

    common::validateFile::validate_magic_number(tokens[0]);
    width    = common::validateFile::validate_width(tokens[1]);
    height   = common::validateFile::validate_height(tokens[2]);
    maxlevel = common::validateFile::validate_maxlevel(tokens[3]);

    if (maxlevel <= UINT8_MAX) {
      type = Type::UINT8;
    } else {
      type = Type::UINT16;
    }

    size_t const bytes_per_pixel = static_cast<size_t>(type) * 3;
    auto const total_pixels      = static_cast<size_t>(width) * static_cast<size_t>(height);
    size_t const total_bytes     = total_pixels * bytes_per_pixel;

    common::validateFile::validate_pixels(tokens[4], total_bytes);

    if (type == Type::UINT8) {
      process_uint8_pixels(tokens[4], total_pixels);
    } else {
      process_uint16_pixels(tokens[4], total_pixels);
    }
  }

  void SOA::process_uint8_pixels(std::string const & pixel_data, size_t total_pixels) {
    std::vector<common::Red<uint8_t>> vector_red;
    std::vector<common::Green<uint8_t>> vector_green;
    std::vector<common::Blue<uint8_t>> vector_blue;
    vector_red.reserve(total_pixels);
    vector_green.reserve(total_pixels);
    vector_blue.reserve(total_pixels);

    for (size_t i = 0; i < total_pixels; i++) {
      auto red_value   = common::Red<uint8_t>(static_cast<uint8_t>(pixel_data[i * 3]));
      auto green_value = common::Green<uint8_t>(static_cast<uint8_t>(pixel_data[i * 3 + 1]));
      auto blue_value  = common::Blue<uint8_t>(static_cast<uint8_t>(pixel_data[i * 3 + 2]));
      vector_red.push_back(red_value);
      vector_green.push_back(green_value);
      vector_blue.push_back(blue_value);
    }

    red   = std::move(vector_red);
    green = std::move(vector_green);
    blue  = std::move(vector_blue);
  }

  void SOA::process_uint16_pixels(std::string const & pixel_data, size_t total_pixels) {
    std::vector<common::Red<uint16_t>> vector_red;
    std::vector<common::Green<uint16_t>> vector_green;
    std::vector<common::Blue<uint16_t>> vector_blue;
    vector_red.reserve(total_pixels);
    vector_green.reserve(total_pixels);
    vector_blue.reserve(total_pixels);

    for (size_t i = 0; i < total_pixels; i++) {
      auto red_value = common::Red<uint16_t>(
          static_cast<uint16_t>((pixel_data[i * 3 * 2] << (4 + 4)) | pixel_data[i * 3 * 2 + 1]));
      auto green_value = common::Green<uint16_t>(static_cast<uint16_t>(
          (pixel_data[i * 3 * 2 + 2] << (4 + 4)) | pixel_data[i * 3 * 2 + 3]));
      auto blue_value  = common::Blue<uint16_t>(static_cast<uint16_t>(
          (pixel_data[i * 3 * 2 + 4] << (4 + 4)) | pixel_data[i * 3 * 2 + 4 + 1]));
      vector_red.push_back(red_value);
      vector_green.push_back(green_value);
      vector_blue.push_back(blue_value);
    }

    red   = std::move(vector_red);
    green = std::move(vector_green);
    blue  = std::move(vector_blue);
  }

  std::vector<uint8_t> SOA::toBinary() const {
    std::string const header = "P6\n" + std::to_string(width) + " " + std::to_string(height) +
                               "\n" + std::to_string(maxlevel) + "\n";
    std::vector<uint8_t> binary;

    size_t const pixel_size       = static_cast<size_t>(type) * 3;
    size_t const number_of_pixels = static_cast<size_t>(width) * static_cast<size_t>(height);
    binary.reserve(header.size() + number_of_pixels * pixel_size);

    binary.insert(binary.begin(), header.begin(), header.end());

    write_pixels(binary);

    return binary;
  }

  void SOA::write_pixels(std::vector<uint8_t> & binary) const {
    if (type == Type::UINT8) {
      for (size_t i = 0; i < static_cast<size_t>(width) * static_cast<size_t>(height); i++) {
        binary.push_back(std::get<std::vector<common::Red<uint8_t>>>(red)[i].getValue());
        binary.push_back(std::get<std::vector<common::Green<uint8_t>>>(green)[i].getValue());
        binary.push_back(std::get<std::vector<common::Blue<uint8_t>>>(blue)[i].getValue());
      }
    } else {
      for (size_t i = 0; i < static_cast<size_t>(width) * static_cast<size_t>(height); i++) {
        binary.push_back(static_cast<uint8_t>(
            std::get<std::vector<common::Red<uint16_t>>>(red)[i].getValue() >> UINT8_WIDTH));
        binary.push_back(static_cast<uint8_t>(
            std::get<std::vector<common::Red<uint16_t>>>(red)[i].getValue() & UINT8_MAX));
        binary.push_back(static_cast<uint8_t>(
            std::get<std::vector<common::Green<uint16_t>>>(green)[i].getValue() >> UINT8_WIDTH));
        binary.push_back(static_cast<uint8_t>(
            std::get<std::vector<common::Green<uint16_t>>>(green)[i].getValue() & UINT8_MAX));
        binary.push_back(static_cast<uint8_t>(
            std::get<std::vector<common::Blue<uint16_t>>>(blue)[i].getValue() >> UINT8_WIDTH));
        binary.push_back(static_cast<uint8_t>(
            std::get<std::vector<common::Blue<uint16_t>>>(blue)[i].getValue() & UINT8_MAX));
      }
    }
  }

}  // namespace imgsoa