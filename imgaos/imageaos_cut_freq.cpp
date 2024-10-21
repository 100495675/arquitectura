#include "imageaos.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <forward_list>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace imgaos {

  void AOS::cut_freq(int new_freq) {
    if (new_freq < 0) { throw std::invalid_argument("Invalid cutfreq"); }
    if (type == Type::UINT8) {
      cut_freq_generic<uint8_t>(new_freq);
    } else if (type == Type::UINT16) {
      cut_freq_generic<uint16_t>(new_freq);
    }
  }

  template <typename T>
  void AOS::cut_freq_generic(int number) {
    std::vector<pixel<T>> pixel_data = std::get<std::vector<pixel<T>>>(data);

    std::unordered_map<pixel<T>, std::pair<size_t, std::forward_list<size_t>>, PixelHash<T>> freq;

    // habra que encontrar un optimo, este lo he puesto por poner algo
    freq.reserve(pixel_data.size() / 2);

    for (size_t i = 0; i < pixel_data.size(); i++) {
      freq[pixel_data[i]].first++;
      freq[pixel_data[i]].second.push_front(i);
    }
    if (freq.size() <= static_cast<size_t>(number)) {
      throw std::invalid_argument("Invalid cutfreq");
    }

    // Ineficiente pero no hay mas, se tiene que clonar para hacer cosas
    std::vector<std::pair<pixel<T>, std::pair<size_t, std::forward_list<size_t>>>> freq_vector(
        freq.begin(), freq.end());

    std::partial_sort(freq_vector.begin(), freq_vector.begin() + number, freq_vector.end(),
                      [](auto const & a, auto const & b) {
                        if (a.second.first != b.second.first) {  // frecuencias
                          return a.second.first < b.second.first;
                        }
                        if (a.first.getB() != b.first.getB()) {  // colores
                          return a.first.getB() > b.first.getB();
                        }
                        if (a.first.getG() != b.first.getG()) {
                          return a.first.getG() > b.first.getG();
                        }
                        return a.first.getR() > b.first.getR();
                      });

    for (size_t i = 0; i < static_cast<size_t>(number); ++i) {
      auto const & color1        = freq_vector[i];
      double min_distance        = std::numeric_limits<double>::max();
      size_t closest_color_index = 0;
      for (auto j = static_cast<size_t>(number); j < freq_vector.size(); ++j) {
        auto const & color2 = freq_vector[j];

        double const distance = std::sqrt(std::pow(color1.first.getB() - color2.first.getB(), 2) +
                                          std::pow(color1.first.getG() - color2.first.getG(), 2) +
                                          std::pow(color1.first.getR() - color2.first.getR(), 2));
        if (distance < min_distance) {
          min_distance        = distance;
          closest_color_index = j;
        }
      }
      for (auto const & pos : freq_vector[i].second.second) {
        pixel_data[pos] = freq_vector[closest_color_index].first;
      }
    }
    data = std::move(pixel_data);
  }
}  // namespace imgaos