#include "imageaos.hpp"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace imgaos {

void AOS::resize(int new_width, int new_height) {
  switch (type) {
  case Type::UINT8:
    resize_generic<uint8_t>(new_width, new_height);
    break;
  case Type::UINT16:
    resize_generic<uint16_t>(new_width, new_height);
    break;
  }
}

template <typename T> void AOS::resize_generic(int new_width, int new_height) {
  if (new_width <= 0 || new_height <= 0) {
    if (new_width <= 0) {
      throw std::invalid_argument("Invalid width");
    } else {
      throw std::invalid_argument("Invalid height");
    }
  }
  const int old_width = width;
  const int old_height = height;
  width = new_width;
  height = new_height;
  auto &old_vector_data = std::get<std::vector<pixel<T>>>(data);

  std::vector<pixel<T>> new_vector_data;
  new_vector_data.reserve(static_cast<size_t>(width) *
                          static_cast<size_t>(height));

  for (int new_y = 0; new_y < height; new_y++) {
    for (int new_x = 0; new_x < width; new_x++) {
      const float old_x = static_cast<float>(new_x * (old_width - 1)) /
                          static_cast<float>(width - 1);
      const float old_y = static_cast<float>(new_y * (old_height - 1)) /
                          static_cast<float>(height - 1);
      const int x_l = static_cast<int>(std::floor(old_x));
      const int x_h = static_cast<int>(std::ceil(old_x));
      const int y_l = static_cast<int>(std::floor(old_y));
      const int y_h = static_cast<int>(std::ceil(old_y));

      const pixel<T> pixel_ll =
          old_vector_data[static_cast<size_t>(y_l) *
                              static_cast<size_t>(old_width) +
                          static_cast<size_t>(x_l)];
      const pixel<T> pixel_hl =
          old_vector_data[static_cast<size_t>(y_l) *
                              static_cast<size_t>(old_width) +
                          static_cast<size_t>(x_h)];
      const pixel<T> pixel_lh =
          old_vector_data[static_cast<size_t>(y_h) *
                              static_cast<size_t>(old_width) +
                          static_cast<size_t>(x_l)];
      const pixel<T> pixel_hh =
          old_vector_data[static_cast<size_t>(y_h) *
                              static_cast<size_t>(old_width) +
                          static_cast<size_t>(x_h)];

      const auto r = static_cast<T>((pixel_ll.getR() + pixel_hl.getR() +
                                     pixel_lh.getR() + pixel_hh.getR()) /
                                    4);
      const auto g = static_cast<T>((pixel_ll.getG() + pixel_hl.getG() +
                                     pixel_lh.getG() + pixel_hh.getG()) /
                                    4);
      const auto b = static_cast<T>((pixel_ll.getB() + pixel_hl.getB() +
                                     pixel_lh.getB() + pixel_hh.getB()) /
                                    4);

      const pixel<T> new_pixel(r, g, b);

      new_vector_data.push_back(new_pixel);
    }
  }
  data = std::move(new_vector_data);
}
} // namespace imgaos