#ifndef PIXEL_HPP
#define PIXEL_HPP
#include "colors.hpp"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace common {

  template <typename T>
  struct pixel {
    public:
      pixel(Red<T> red, Green<T> green, Blue<T> blue);
      void write_to_binary(std::vector<uint8_t> & binary) const;
      bool operator==(pixel<T> const & other) const;
      [[nodiscard]] T getR() const;
      [[nodiscard]] T getG() const;
      [[nodiscard]] T getB() const;

    private:
      T red   = 0;
      T green = 0;
      T blue  = 0;
  };

  template <typename T>
  struct PixelHash {
      size_t operator()(pixel<T> const & pixel) const;
  };

  // Implementation
  template <typename T>
  pixel<T>::pixel(Red<T> red, Green<T> green, Blue<T> blue)
    : red(red.getValue()), green(green.getValue()), blue(blue.getValue()) { }

  template <typename T>
  void pixel<T>::write_to_binary(std::vector<uint8_t> & binary) const {
    if constexpr (std::is_same_v<T, uint8_t>) {
      binary.push_back(red);
      binary.push_back(green);
      binary.push_back(blue);
    }

    else if constexpr (std::is_same_v<T, uint16_t>) {
      binary.push_back(static_cast<uint8_t>(red >> UINT8_WIDTH));
      binary.push_back(static_cast<uint8_t>(red & UINT8_MAX));
      binary.push_back(static_cast<uint8_t>(green >> UINT8_WIDTH));
      binary.push_back(static_cast<uint8_t>(green & UINT8_MAX));
      binary.push_back(static_cast<uint8_t>(blue >> UINT8_WIDTH));
      binary.push_back(static_cast<uint8_t>(blue & UINT8_MAX));
    }
  }

  template <typename T>
  bool pixel<T>::operator==(pixel<T> const & other) const = default;

  template <typename T>
  [[nodiscard]] T pixel<T>::getR() const {
    return red;
  }

  template <typename T>
  [[nodiscard]] T pixel<T>::getG() const {
    return green;
  }

  template <typename T>
  [[nodiscard]] T pixel<T>::getB() const {
    return blue;
  }

  template <typename T>
  size_t PixelHash<T>::operator()(pixel<T> const & pixel) const {
    return std::hash<size_t>()(static_cast<size_t>(pixel.getR()) *
                               static_cast<size_t>(pixel.getG()) *
                               static_cast<size_t>(pixel.getB()));
  }

}  // namespace common
#endif