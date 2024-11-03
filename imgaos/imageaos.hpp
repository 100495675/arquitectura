#ifndef IMGAOS_HPP
#define IMGAOS_HPP
#include "../common/aux.hpp"
#include "pixel.hpp"

#include <cstdint>
#include <cstring>
#include <forward_list>
#include <gtest/gtest_prod.h>
#include <string>
#include <variant>
#include <vector>

namespace imgaos {

  class AOS {
      FRIEND_TEST(imgaos, normal_uint8);
      FRIEND_TEST(imgaos, normal_uint16);

    private:
      int width    = 0;
      int height   = 0;
      int maxlevel = 0;
      enum class Type : uint8_t { UINT8 = 1, UINT16 = 2 };
      Type type;
      std::variant<std::vector<pixel<uint8_t>>, std::vector<pixel<uint16_t>>> data;

      void process_uint8_pixels(std::string const & pixel_data, size_t total_pixels);
      void process_uint16_pixels(std::string const & pixel_data, size_t total_pixels);
      void write_pixels(std::vector<uint8_t> & binary) const;

      template <typename T, typename U>
      void max_level_generic(int level);
      template <typename T>
      void resize_generic(common::Width new_width, common::Height new_height);

      template <typename T>
      pixel<T> interpolate_pixel(std::vector<pixel<T>> const & old_vector_data,
                                 common::Size old_size, int new_x, int new_y);
      template <typename T>
      void cut_freq_generic(int number);
      template <typename T>
      void sort_first_n(
          std::vector<std::pair<pixel<T>, std::pair<size_t, std::forward_list<size_t>>>> &
              freq_vector,
          int number);
      template <typename T>
      void addPixelToTable(pixel<T> const & pixel, std::vector<uint8_t> & binary,
                           size_t & index) const;
      template <typename T>
      [[nodiscard]] std::vector<uint8_t> compress_generic() const;

    public:
      void max_level(int level);
      void resize(int width, int height);
      void cut_freq(int freq);
      [[nodiscard]] std::vector<uint8_t> compress() const;
      AOS(std::vector<uint8_t> const & binary);
      [[nodiscard]] std::vector<uint8_t> toBinary() const;

      [[nodiscard]] int getWidth() const;
      [[nodiscard]] int getHeight() const;
      [[nodiscard]] int getMaxLevel() const;
  };

  // Implementation
  template <typename T>
  void AOS::addPixelToTable(pixel<T> const & pixel, std::vector<uint8_t> & binary,
                            size_t & index) const {
    if (std::is_same<T, uint8_t>::value) {
      binary[index++] = static_cast<uint8_t>(pixel.getR());
      binary[index++] = static_cast<uint8_t>(pixel.getG());
      binary[index++] = static_cast<uint8_t>(pixel.getB());
    } else {
      uint16_t const red   = pixel.getR();
      uint16_t const green = pixel.getG();
      uint16_t const blue  = pixel.getB();
      binary[index++]      = static_cast<uint8_t>(red >> UINT8_WIDTH);
      binary[index++]      = static_cast<uint8_t>(red & UINT8_MAX);
      binary[index++]      = static_cast<uint8_t>(green >> UINT8_WIDTH);
      binary[index++]      = static_cast<uint8_t>(green & UINT8_MAX);
      binary[index++]      = static_cast<uint8_t>(blue >> UINT8_WIDTH);
      binary[index++]      = static_cast<uint8_t>(blue & UINT8_MAX);
    }
  }
}  // namespace imgaos

#endif
