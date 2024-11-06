#ifndef IMGSOA_HPP
#define IMGSOA_HPP
#include "../common/aux.hpp"

#include <cstdint>
#include <cstring>
#include <forward_list>
#include <gtest/gtest_prod.h>
#include <string>
#include <variant>
#include <vector>

namespace imgsoa {

  class SOA {
    private:
      int width    = 0;
      int height   = 0;
      int maxlevel = 0;
      enum class Type : uint8_t { UINT8 = 1, UINT16 = 2 };
      Type type;

      std::variant<std::vector<common::Red<uint8_t>>, std::vector<common::Red<uint16_t>>> red;
      std::variant<std::vector<common::Green<uint8_t>>, std::vector<common::Green<uint16_t>>> green;
      std::variant<std::vector<common::Blue<uint8_t>>, std::vector<common::Blue<uint16_t>>> blue;

      void process_uint8_pixels(std::string const & pixel_data, size_t total_pixels);
      void process_uint16_pixels(std::string const & pixel_data, size_t total_pixels);
      void write_pixels(std::vector<uint8_t> & binary) const;

    public:
      // void max_level(int level);
      // void resize(int width, int height);
      // void cut_freq(int freq);
      //[[nodiscard]] std::vector<uint8_t> compress() const;
      SOA(std::vector<uint8_t> const & binary);
      [[nodiscard]] std::vector<uint8_t> toBinary() const;

      [[nodiscard]] int getWidth() const;
      [[nodiscard]] int getHeight() const;
      [[nodiscard]] int getMaxLevel() const;
  };

}  // namespace imgsoa

#endif