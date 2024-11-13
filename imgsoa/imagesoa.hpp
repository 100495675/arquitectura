#ifndef IMGSOA_HPP
#define IMGSOA_HPP
#include "../common/colors.hpp"
#include "../common/pixel.hpp"
#include "../common/sizes.hpp"

#include <cstdint>
#include <cstring>
#include <forward_list>
#include <gtest/gtest_prod.h>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace imgsoa {

  class SOA {
      FRIEND_TEST(imgsoa, normal_uint8);
      FRIEND_TEST(imgsoa, normal_uint16);

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
      template <typename T, typename U>
      void max_level_generic(int level);
      template <typename T>
      void resize_generic(common::Width new_width, common::Height new_height);

      template <typename Color>
      Color calculate_color(std::vector<Color> const & old_vector_data, common::Size old_size,
                            int new_x, int new_y);

      template <typename T, typename U>
      U interpolate_color(std::tuple<float, float> const & positions, float pos, T const & value_1,
                          T const & value_2);
      template <typename T>
      void cut_freq_generic(int number);
      template <typename T>
      void sort_first_n(std::vector<std::pair<common::pixel<T>, std::vector<size_t>>> & freq_vector,
                        int number);
      template <typename T>
      std::vector<std::pair<common::pixel<T>, std::vector<size_t>>> compress_sort(
          std::unordered_map<common::pixel<T>, std::vector<size_t>, common::PixelHash<T>> & freq)
          const;
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

      SOA(std::vector<uint8_t> const & binary);
      [[nodiscard]] std::vector<uint8_t> toBinary() const;

      [[nodiscard]] int getWidth() const;
      [[nodiscard]] int getHeight() const;
      [[nodiscard]] int getMaxLevel() const;
  };

  // Implementation
  template <typename T>
  void SOA::addPixelToTable(common::pixel<T> const & pixel, std::vector<uint8_t> & binary,
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
}  // namespace imgsoa

#endif