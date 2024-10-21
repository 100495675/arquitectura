#ifndef IMGAOS_HPP
#define IMGAOS_HPP

#include <cstdint>
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
          pixel(T r_, T g_, T b_) : r(r_), g(g_), b(b_) { }

          bool operator==(pixel<T> const & other) const = default;

          [[nodiscard]] T getR() const { return r; }

          [[nodiscard]] T getG() const { return g; }

          [[nodiscard]] T getB() const { return b; }

        private:
          T r = 0;
          T g = 0;
          T b = 0;
      };

      template <typename T>
      struct PixelHash {
          size_t operator()(const AOS::pixel<T> & p) const {
            return std::hash<T>()(p.getR()) ^ (std::hash<T>()(p.getG()) << 1) ^
                   (std::hash<T>()(p.getB()) << 2);
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
      void resize_generic(int new_width, int new_height);
      template <typename T>
      void cut_freq_generic(int new_freq);

    public:
      void max_level(int level);
      void resize(int width, int height);
      void cut_freq(int freq);
      AOS(std::vector<uint8_t> const & binary);
      [[nodiscard]] std::vector<uint8_t> toBinary() const;

      [[nodiscard]] int getWidth() const;
      [[nodiscard]] int getHeight() const;
      [[nodiscard]] int getMaxLevel() const;
  };
}  // namespace imgaos

#endif
