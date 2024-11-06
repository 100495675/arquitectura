#include "imgsoa/imagesoa.hpp"

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace imgsoa {

  constexpr int MAX_MAXLEVEL = 65536;

  void SOA::max_level(int new_max_level) {
    if (new_max_level <= 0 || new_max_level >= MAX_MAXLEVEL) {
      throw std::invalid_argument("Invalid maxlevel");
    }
    if (new_max_level <= UINT8_MAX) {
      if (maxlevel <= UINT8_MAX) {
        max_level_generic<uint8_t, uint8_t>(new_max_level);
      } else {
        max_level_generic<uint16_t, uint8_t>(new_max_level);
      }
      type = Type::UINT8;
    } else {
      if (maxlevel <= UINT8_MAX) {
        max_level_generic<uint8_t, uint16_t>(new_max_level);
      } else {
        max_level_generic<uint16_t, uint16_t>(new_max_level);
      }
      type = Type::UINT16;
    }
  }

  template <typename T, typename U>
  void SOA::max_level_generic(int level) {
    if constexpr (std::is_same_v<T, U>) {
      for (size_t i = 0; i < static_cast<size_t>(width) * static_cast<size_t>(height); i++) {
        T new_r = std::get<std::vector<common::Red<T>>>(red)[i].getValue() * level / maxlevel;
        T new_g = std::get<std::vector<common::Green<T>>>(green)[i].getValue() * level / maxlevel;
        T new_b = std::get<std::vector<common::Green<T>>>(green)[i].getValue() * level / maxlevel;
        std::get<std::vector<common::Red<T>>>(red)[i]     = common::Red<T>(new_r);
        std::get<std::vector<common::Green<T>>>(green)[i] = common::Green<T>(new_g);
        std::get<std::vector<common::Blue<T>>>(blue)[i]   = common::Blue<T>(new_b);
      }
      maxlevel = level;
    } else {
      std::vector<common::Red<U>> new_red_vector;
      std::vector<common::Green<U>> new_green_vector;
      std::vector<common::Blue<U>> new_blue_vector;
      new_red_vector.reserve(static_cast<size_t>(width) * static_cast<size_t>(height));
      new_green_vector.reserve(static_cast<size_t>(width) * static_cast<size_t>(height));
      new_blue_vector.reserve(static_cast<size_t>(width) * static_cast<size_t>(height));
      for (size_t i = 0; i < static_cast<size_t>(width) * static_cast<size_t>(height); i++) {
        U new_r = std::get<std::vector<common::Red<T>>>(red)[i].getValue() * level / maxlevel;
        U new_g = std::get<std::vector<common::Green<T>>>(green)[i].getValue() * level / maxlevel;
        U new_b = std::get<std::vector<common::Green<T>>>(green)[i].getValue() * level / maxlevel;
        new_red_vector.push_back(common::Red<U>(new_r));
        new_green_vector.push_back(common::Green<U>(new_g));
        new_blue_vector.push_back(common::Blue<U>(new_b));
      }
      red      = std::move(new_red_vector);
      green    = std::move(new_green_vector);
      blue     = std::move(new_blue_vector);
      maxlevel = level;
    }
  }
}  // namespace imgsoa