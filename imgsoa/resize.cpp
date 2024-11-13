#include "../common/colors.hpp"
#include "imagesoa.hpp"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace imgsoa {

  void SOA::resize(int new_width, int new_height) {
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
  void SOA::resize_generic(common::Width new_width, common::Height new_height) {
    if (new_width.getValue() <= 0) { throw std::invalid_argument("Invalid width"); }
    if (new_height.getValue() <= 0) { throw std::invalid_argument("Invalid height"); }

    common::Size const old_size = common::Size(common::Height(height), common::Width(width));
    width                       = new_width.getValue();
    height                      = new_height.getValue();
    auto & old_red_vector       = std::get<std::vector<common::Red<T>>>(red);
    auto & old_green_vector     = std::get<std::vector<common::Green<T>>>(green);
    auto & old_blue_vector      = std::get<std::vector<common::Blue<T>>>(blue);
    std::vector<common::Red<T>> new_red_vector;
    std::vector<common::Green<T>> new_green_vector;
    std::vector<common::Blue<T>> new_blue_vector;
    new_red_vector.reserve(static_cast<size_t>(width) * static_cast<size_t>(height));
    new_green_vector.reserve(static_cast<size_t>(width) * static_cast<size_t>(height));
    new_blue_vector.reserve(static_cast<size_t>(width) * static_cast<size_t>(height));
    for (int new_y = 0; new_y < height; new_y++) {
      for (int new_x = 0; new_x < width; new_x++) {
        common::Red<T> const new_red = calculate_color(old_red_vector, old_size, new_x, new_y);
        new_red_vector.push_back(new_red);
      }
    }
    for (int new_y = 0; new_y < height; new_y++) {
      for (int new_x = 0; new_x < width; new_x++) {
        common::Green<T> const new_green =
            calculate_color(old_green_vector, old_size, new_x, new_y);
        new_green_vector.push_back(new_green);
      }
    }
    for (int new_y = 0; new_y < height; new_y++) {
      for (int new_x = 0; new_x < width; new_x++) {
        common::Blue<T> const new_blue = calculate_color(old_blue_vector, old_size, new_x, new_y);
        new_blue_vector.push_back(new_blue);
      }
    }
    red   = std::move(new_red_vector);
    green = std::move(new_green_vector);
    blue  = std::move(new_blue_vector);
  }

  template <typename Color>
  Color SOA::calculate_color(std::vector<Color> const & old_vector_data, common::Size old_size,
                             int new_x, int new_y) {
    float const old_x = static_cast<float>(new_x * (old_size.getWidth().getValue() - 1)) /
                        static_cast<float>(width - 1);
    float const old_y = static_cast<float>(new_y * (old_size.getHeight().getValue() - 1)) /
                        static_cast<float>(height - 1);
    float const x_1    = std::floor(old_x);
    float const x_2    = std::ceil(old_x);
    float const y_1    = std::floor(old_y);
    float const y_2    = std::ceil(old_y);
    size_t const width = static_cast<size_t>(old_size.getWidth().getValue());
    Color const color_11 =
        old_vector_data[(static_cast<size_t>(y_1) * width) + static_cast<size_t>(x_1)];
    Color const color_21 =
        old_vector_data[(static_cast<size_t>(y_1) * width) + static_cast<size_t>(x_2)];
    Color const color_12 =
        old_vector_data[(static_cast<size_t>(y_2) * width) + static_cast<size_t>(x_1)];
    Color const color_22 =
        old_vector_data[(static_cast<size_t>(y_2) * width) + static_cast<size_t>(x_2)];

    auto const color_1 = interpolate_color<typename Color::value_type, float>(
        std::make_tuple(x_1, x_2), old_x, color_11.getValue(), color_21.getValue());
    auto const color_2 = interpolate_color<typename Color::value_type, float>(
        std::make_tuple(x_1, x_2), old_x, color_12.getValue(), color_22.getValue());
    return Color(interpolate_color<float, typename Color::value_type>(std::make_tuple(y_1, y_2),
                                                                      old_y, color_1, color_2));
  }

  template <typename T, typename U>
  U SOA::interpolate_color(std::tuple<float, float> const & positions, float pos, T const & value_1,
                           T const & value_2) {
    auto const [pos1, pos2] = positions;
    auto const delta        = pos2 - pos1;
    if (delta == 0) { return static_cast<U>(value_1); }
    return static_cast<U>(((pos2 - pos) * value_1 + (pos - pos1) * value_2) / delta);
  }
}  // namespace imgsoa