#include "imageaos.hpp"

#include <cstring>
#include <iostream>
#include <unordered_map>

namespace imgaos {
  template <typename T>
  std::vector<uint8_t> AOS::compress_generic() const {
    auto pixel_data = std::get<std::vector<pixel<T>>>(data);
    std::unordered_map<pixel<T>, std::pair<size_t, std::forward_list<size_t>>, PixelHash<T>> freq;
    freq.reserve(pixel_data.size() / 2);
    for (size_t i = 0; i < pixel_data.size(); i++) {
      freq[pixel_data[i]].first++;
      freq[pixel_data[i]].second.push_front(i);
    }
    size_t const table_size = freq.size() * 3 * static_cast<size_t>(type);
    size_t pixel_byte_size  = 0;
    if (freq.size() < UINT8_MAX) {
      pixel_byte_size = 1;
    } else if (freq.size() < UINT16_MAX) {
      pixel_byte_size = 2;
    } else if (freq.size() < UINT32_MAX) {
      pixel_byte_size = 4;
    } else {
      throw std::runtime_error("No se soportan tablas de colores mayores");
    }
    size_t const pixel_size  = pixel_data.size() * pixel_byte_size;
    std::string const header = "C6 " + std::to_string(width) + " " + std::to_string(height) + " " +
                               std::to_string(maxlevel) + " " + std::to_string(freq.size()) + "\n";
    std::vector<uint8_t> binary;
    binary.reserve(header.size() + table_size + pixel_size);
    binary.resize(binary.capacity());
    std::copy(header.begin(), header.end(), binary.begin());
    size_t index       = header.size();
    size_t table_index = 0;
    for (auto const & [pixel, freqs] : freq) {
      addPixelToTable<T>(pixel, binary, index);
      for (auto const & position : freqs.second) {
        // no estoy seguro de que esto funcione :P
        std::memcpy(&binary[header.size() + table_size + position * pixel_byte_size], &table_index,
                    pixel_byte_size);
      }
      table_index++;
    }
    // for (auto const & coso : binary) { std::cout << std::hex << static_cast<int>(coso) << ", "; }
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