#include "imageaos.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <unordered_map>

namespace imgaos {
  size_t AOS::calculatePixelByteSize(size_t freq_vector_size) {
    if (freq_vector_size < UINT8_MAX) { return 1; }
    if (freq_vector_size < UINT16_MAX) { return 2; }
    if (freq_vector_size < UINT32_MAX) { return 4; }
    throw std::runtime_error("No se soportan tablas de colores mayores");
  }

  template <typename T>
  std::vector<uint8_t> AOS::compress_generic() const {
    auto pixel_data = std::get<std::vector<common::pixel<T>>>(data);
    std::unordered_map<common::pixel<T>, std::vector<size_t>, common::PixelHash<T>> freq;
    for (size_t i = 0; i < pixel_data.size(); i++) { freq[pixel_data[i]].push_back(i); }
    // Explicar en la memoria: el ordenarlo NO sirve para nada (tampoco el pasarlo a vector), pero
    // en la imagen de ejemplo está ordenado, asi que lo hacemos aunque sea un gasto innecesario.
    std::vector<std::pair<common::pixel<T>, std::vector<size_t>>> freq_vector(freq.begin(),
                                                                              freq.end());
    std::sort(freq_vector.begin(), freq_vector.end(), [](auto const & entry1, auto const & entry2) {
      if (entry1.first.getR() != entry2.first.getR()) {
        return entry1.first.getR() < entry2.first.getR();
      }
      if (entry1.first.getG() != entry2.first.getG()) {
        return entry1.first.getG() < entry2.first.getG();
      }
      return entry1.first.getB() < entry2.first.getB();
    });
    size_t const table_size      = freq_vector.size() * 3 * static_cast<size_t>(type);
    size_t const pixel_byte_size = calculatePixelByteSize(freq_vector.size());
    size_t const pixel_size      = pixel_data.size() * pixel_byte_size;
    std::string const header = "C6 " + std::to_string(width) + " " + std::to_string(height) + " " +
                               std::to_string(maxlevel) + " " + std::to_string(freq_vector.size()) +
                               "\n";
    std::vector<uint8_t> binary;
    binary.reserve(header.size() + table_size + pixel_size);
    binary.resize(binary.capacity());
    std::ranges::copy(header.begin(), header.end(), binary.begin());
    size_t index       = header.size();
    size_t table_index = 0;
    for (auto const & [pixel, freqs] : freq_vector) {
      addPixelToTable<T>(pixel, binary, index);
      for (auto const & position : freqs) {
        std::memcpy(&binary[header.size() + table_size + (position * pixel_byte_size)],
                    &table_index, pixel_byte_size);
      }
      table_index++;
    }
    return binary;
  }

  std::vector<uint8_t> AOS::compress() const {
    switch (type) {
      case Type::UINT8:
        return compress_generic<uint8_t>();
      case Type::UINT16:
        return compress_generic<uint16_t>();
    }
    // unreachable
    return {};
  }

}  // namespace imgaos*/