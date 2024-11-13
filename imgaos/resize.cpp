#include "../common/sizes.hpp"
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
        resize_generic<uint8_t>(common::Width(new_width), common::Height(new_height));
        break;
      case Type::UINT16:
        resize_generic<uint16_t>(common::Width(new_width), common::Height(new_height));
        break;
    }
  }

  template <typename T>
  void AOS::resize_generic(common::Width new_width, common::Height new_height) {
    if (new_width.getValue() <= 0) { throw std::invalid_argument("Invalid width"); }
    if (new_height.getValue() <= 0) { throw std::invalid_argument("Invalid height"); }

    common::Size const old_size = common::Size(common::Height(height), common::Width(width));
    width                       = new_width.getValue();
    height                      = new_height.getValue();
    auto & old_vector_data      = std::get<std::vector<common::pixel<T>>>(data);

    std::vector<common::pixel<T>> new_vector_data;
    new_vector_data.reserve(static_cast<size_t>(width) * static_cast<size_t>(height));

    for (int new_y = 0; new_y < height; new_y++) {
      for (int new_x = 0; new_x < width; new_x++) {
        common::pixel<T> const new_pixel =
            calculate_pixel<T>(old_vector_data, old_size, new_x, new_y);
        new_vector_data.push_back(new_pixel);
      }
    }
    data = std::move(new_vector_data);
  }

  template <typename T>
  common::pixel<T> AOS::calculate_pixel(std::vector<common::pixel<T>> const & old_vector_data,
                                        common::Size old_size, int new_x, int new_y) {
    float const old_x = static_cast<float>(new_x * (old_size.getWidth().getValue() - 1)) /
                        static_cast<float>(width - 1);
    float const old_y = static_cast<float>(new_y * (old_size.getHeight().getValue() - 1)) /
                        static_cast<float>(height - 1);
    float const x_1    = std::floor(old_x);
    float const x_2    = std::ceil(old_x);
    float const y_1    = std::floor(old_y);
    float const y_2    = std::ceil(old_y);
    size_t const width = static_cast<size_t>(old_size.getWidth().getValue());
    common::pixel<T> const pixel_11 =
        old_vector_data[(static_cast<size_t>(y_1) * width) + static_cast<size_t>(x_1)];
    common::pixel<T> const pixel_21 =
        old_vector_data[(static_cast<size_t>(y_1) * width) + static_cast<size_t>(x_2)];
    common::pixel<T> const pixel_12 =
        old_vector_data[(static_cast<size_t>(y_2) * width) + static_cast<size_t>(x_1)];
    common::pixel<T> const pixel_22 =
        old_vector_data[(static_cast<size_t>(y_2) * width) + static_cast<size_t>(x_2)];

    auto const pixel_1 =
        interpolate_pixel<T, float>(std::make_tuple(x_1, x_2), old_x, pixel_11, pixel_21);
    auto const pixel_2 =
        interpolate_pixel<T, float>(std::make_tuple(x_1, x_2), old_x, pixel_12, pixel_22);
    return interpolate_pixel<float, T>(std::make_tuple(y_1, y_2), old_y, pixel_1, pixel_2);
  }

  template <typename T, typename U>
  common::pixel<U> AOS::interpolate_pixel(std::tuple<float, float> const & positions, float pos,
                                          common::pixel<T> const & pixel_1,
                                          common::pixel<T> const & pixel_2) {
    auto const [pos1, pos2] = positions;
    auto const delta        = pos2 - pos1;
    if (delta == 0) {
      return common::pixel<U>(common::Red(static_cast<U>(pixel_1.getR())),
                              common::Green(static_cast<U>(pixel_1.getG())),
                              common::Blue(static_cast<U>(pixel_1.getB())));
    }

    auto const red   = common::Red(static_cast<U>(
        (((pos2 - pos) * pixel_1.getR()) + ((pos - pos1) * pixel_2.getR())) / delta));
    auto const green = common::Green(static_cast<U>(
        (((pos2 - pos) * pixel_1.getG()) + ((pos - pos1) * pixel_2.getG())) / delta));
    auto const blue  = common::Blue(static_cast<U>(
        (((pos2 - pos) * pixel_1.getB()) + ((pos - pos1) * pixel_2.getB())) / delta));
    return common::pixel<U>(red, green, blue);
  }
}  // namespace imgaos