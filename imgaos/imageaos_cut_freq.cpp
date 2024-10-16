#include "imageaos.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <forward_list>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
namespace imgaos {

void AOS::cut_freq(int new_freq) {
  if (new_freq < 0) {
    throw std::invalid_argument("Invalid cutfreq");
  }
  if (type == Type::UINT8) {
    cut_freq_generic<uint8_t>(new_freq);
  } else if (type == Type::UINT16) {
    cut_freq_generic<uint16_t>(new_freq);
  }
}

template <typename T> void AOS::cut_freq_generic(int number) {

  std::vector<pixel<T>> pixel_data = std::get<std::vector<pixel<T>>>(data);

  std::unordered_map<pixel<T>, std::pair<size_t, std::forward_list<size_t>>,
                     PixelHash<T>>
      freq;

  // habra que encontrar un optimo, este lo he puesto por poner algo
  freq.reserve(pixel_data.size() / 2);

  for (size_t i = 0; i < pixel_data.size(); i++) {
    freq[pixel_data[i]].first++;
    freq[pixel_data[i]].second.push_front(i);
  }

  // Ineficiente pero no hay mas, se tiene que clonar para hacer cosas
  std::vector<std::pair<pixel<T>, std::pair<size_t, std::forward_list<size_t>>>>
      freq_vector(freq.begin(), freq.end());

  std::partial_sort(freq_vector.begin(), freq_vector.begin() + number,
                    freq_vector.end(), [](const auto &a, const auto &b) {
                      if (a.second.first != b.second.first) // frecuencias
                        return a.second.first < b.second.first;
                      if (a.first.getB() != b.first.getB()) // colores
                        return a.first.getB() > b.first.getB();
                      if (a.first.getG() != b.first.getG())
                        return a.first.getG() > b.first.getG();
                      return a.first.getR() > b.first.getR();
                    });

  std::unordered_set<pixel<T>, PixelHash<T>> pixels_to_delete;
  pixels_to_delete.reserve(static_cast<size_t>(number));
  for (size_t i = 0; i < static_cast<size_t>(number); i++) {
    pixels_to_delete.insert(freq_vector[i].first);
  }

  for (size_t i = 0; i < static_cast<size_t>(number); i++) {
    for (auto &i : freq_vector[i].second.second) {
      constexpr auto x = static_cast<size_t>(3 + 2 * 267);
      pixel_data[i] = closest_pixel<T>(x, pixels_to_delete);
    }
  }

  data = std::move(pixel_data);
}
template <typename T>
const AOS::pixel<T> AOS::closest_pixel(
    size_t origen,
    std::unordered_set<pixel<T>, AOS::PixelHash<T>> &pixels_to_delete) const {}
} // namespace imgaos
