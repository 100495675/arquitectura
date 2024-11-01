#ifndef IMGAOS_HPP
#define IMGAOS_HPP
#include "../common/aux.hpp"

#include <cstdint>
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
      template <typename T>
      struct pixel {
        public:
          pixel(Red<T> red, Green<T> green, Blue<T> blue)
            : red(red.getValue()), green(green.getValue()), blue(blue.getValue()) { }

          void write_to_binary(std::vector<uint8_t> & binary) const {
            if constexpr (std::is_same_v<T, uint8_t>) {
              binary.push_back(static_cast<uint8_t>(red));
              binary.push_back(static_cast<uint8_t>(green));
              binary.push_back(static_cast<uint8_t>(blue));
            }

            else if constexpr (std::is_same_v<T, uint16_t>) {
              binary.push_back(static_cast<uint8_t>(red >> (4 + 4)));
              binary.push_back(static_cast<uint8_t>(red & UINT8_MAX));
              binary.push_back(static_cast<uint8_t>(green >> (4 + 4)));
              binary.push_back(static_cast<uint8_t>(green & UINT8_MAX));
              binary.push_back(static_cast<uint8_t>(blue >> (4 + 4)));
              binary.push_back(static_cast<uint8_t>(blue & UINT8_MAX));
            }
          }

          bool operator==(pixel<T> const & other) const = default;

          [[nodiscard]] T getR() const { return red; }

          [[nodiscard]] T getG() const { return green; }

          [[nodiscard]] T getB() const { return blue; }

        private:
          T red   = 0;
          T green = 0;
          T blue  = 0;
      };

      template <typename T>
      struct PixelHash {
          size_t operator()(const AOS::pixel<T> & pixel) const {
            return std::hash<T>()(pixel.getR()) ^ (std::hash<T>()(pixel.getG()) << 1) ^
                   (std::hash<T>()(pixel.getB()) << 2);
          }
      };

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
      void resize_generic(Width new_width, Height new_height);

      template <typename T>
      pixel<T> interpolate_pixel(std::vector<pixel<T>> const & old_vector_data, Size old_size,
                                 int new_x, int new_y);
      template <typename T>
      void cut_freq_generic(int number);
      template <typename T>
      void sort_first_n(
          std::vector<std::pair<pixel<T>, std::pair<size_t, std::forward_list<size_t>>>> &
              freq_vector,
          int number);
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
}  // namespace imgaos

#endif
