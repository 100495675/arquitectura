#include "imageaos.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <forward_list>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace imgaos {

  void AOS::cut_freq(int new_freq) {
    if (new_freq <= 0) { throw std::invalid_argument("Invalid cutfreq"); }
    if (type == Type::UINT8) {
      cut_freq_generic<uint8_t>(new_freq);
    } else if (type == Type::UINT16) {
      cut_freq_generic<uint16_t>(new_freq);
    }
  }

  template <typename T>
  void
      AOS::sort_first_n(std::vector<std::pair<common::pixel<T>, std::vector<size_t>>> & freq_vector,
                        int number) {
    std::partial_sort(freq_vector.begin(), freq_vector.begin() + number, freq_vector.end(),
                      [](auto const & entry1, auto const & entry2) {
                        if (entry1.second.size() != entry2.second.size()) {  // frecuencias
                          return entry1.second.size() < entry2.second.size();
                        }
                        if (entry1.first.getB() != entry2.first.getB()) {  // colores
                          return entry1.first.getB() > entry2.first.getB();
                        }
                        if (entry1.first.getG() != entry2.first.getG()) {
                          return entry1.first.getG() > entry2.first.getG();
                        }
                        return entry1.first.getR() > entry2.first.getR();
                      });
  }

  template <typename T>
  void AOS::cut_freq_generic(int number) {
    std::vector<common::pixel<T>> pixel_data = std::get<std::vector<common::pixel<T>>>(data);
    std::unordered_map<common::pixel<T>, std::vector<size_t>, common::PixelHash<T>> freq;
    for (size_t i = 0; i < pixel_data.size(); i++) { freq[pixel_data[i]].push_back(i); }
    if (freq.size() <= static_cast<size_t>(number)) {
      throw std::invalid_argument("Invalid cutfreq");
    }
    std::vector<std::pair<common::pixel<T>, std::vector<size_t>>> freq_vector(freq.begin(),
                                                                              freq.end());
    sort_first_n(freq_vector, number);
    for (size_t i = 0; i < static_cast<size_t>(number); ++i) {
      auto const & color1        = freq_vector[i];
      double min_distance2       = std::numeric_limits<double>::max();
      size_t closest_color_index = 0;
      for (auto j = static_cast<size_t>(number); j < freq_vector.size(); ++j) {
        auto const & color2    = freq_vector[j];
        double const distance2 = std::pow(color1.first.getB() - color2.first.getB(), 2) +
                                 std::pow(color1.first.getG() - color2.first.getG(), 2) +
                                 std::pow(color1.first.getR() - color2.first.getR(), 2);
        if (distance2 < min_distance2) {
          min_distance2       = distance2;
          closest_color_index = j;
        }
      }
      for (auto const & pos : freq_vector[i].second) {
        pixel_data[pos] = freq_vector[closest_color_index].first;
      }
    }
    data = std::move(pixel_data);
  }
}  // namespace imgaos