#ifndef IMGAOS_HPP
#define IMGAOS_HPP
#include "../common/pixel.hpp"
#include "../common/sizes.hpp"

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
      std::variant<std::vector<common::pixel<uint8_t>>, std::vector<common::pixel<uint16_t>>> data;

      void process_uint8_pixels(std::string const & pixel_data, size_t total_pixels);
      void process_uint16_pixels(std::string const & pixel_data, size_t total_pixels);
      void write_pixels(std::vector<uint8_t> & binary) const;

      template <typename T, typename U>
      void max_level_generic(int level);
      template <typename T>
      void resize_generic(common::Width new_width, common::Height new_height);

      template <typename T>
      common::pixel<T> calculate_pixel(std::vector<common::pixel<T>> const & old_vector_data,
                                       common::Size old_size, int new_x, int new_y);
      template <typename T>
      common::pixel<T> interpolate_pixel(std::tuple<float, float> const & positions, float pos,
                                         common::pixel<T> const & pixel_1,
                                         common::pixel<T> const & pixel_2);
      template <typename T>
      void cut_freq_generic(int number);
      template <typename T>
      void sort_first_n(std::vector<std::pair<common::pixel<T>, std::vector<size_t>>> & freq_vector,
                        int number);
      template <typename T>
      void addPixelToTable(common::pixel<T> const & pixel, std::vector<uint8_t> & binary,
                           size_t & index) const;
      [[nodiscard]] static size_t calculatePixelByteSize(size_t freq_vector_size);
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
  void AOS::addPixelToTable(common::pixel<T> const & pixel, std::vector<uint8_t> & binary,
                            size_t & index) const {
    if (std::is_same_v<T, uint8_t>) {
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
