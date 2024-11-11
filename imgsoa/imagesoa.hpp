#ifndef IMGSOA_HPP
#define IMGSOA_HPP
#include "../common/colors.hpp"
#include "../common/pixel.hpp"
#include "../common/sizes.hpp"

#include <cstdint>
#include <cstring>
#include <forward_list>
#include <string>
#include <variant>
#include <vector>

namespace imgsoa {

  class SOA {
    private:
      int width    = 0;
      int height   = 0;
      int maxlevel = 0;
      enum class Type : uint8_t { UINT8 = 1, UINT16 = 2 };
      Type type;

      std::variant<std::vector<common::Red<uint8_t>>, std::vector<common::Red<uint16_t>>> red;
      std::variant<std::vector<common::Green<uint8_t>>, std::vector<common::Green<uint16_t>>> green;
      std::variant<std::vector<common::Blue<uint8_t>>, std::vector<common::Blue<uint16_t>>> blue;

      void process_uint8_pixels(std::string const & pixel_data, size_t total_pixels);
      void process_uint16_pixels(std::string const & pixel_data, size_t total_pixels);
      void write_pixels(std::vector<uint8_t> & binary) const;
      template <typename T, typename U>
      void max_level_generic(int level);
      template <typename T>
      void resize_generic(common::Width new_width, common::Height new_height);

      template <typename Color>
      Color calculate_color(std::vector<Color> const & old_vector_data, common::Size old_size,
                            int new_x, int new_y);

      template <typename Color>
      Color interpolate_color(std::tuple<float, float> const & positions, float pos,
                              Color const & color_1, Color const & color_2);

      template <typename T>
      void cut_freq_generic(int number);
      template <typename T>
      void sort_first_n(std::vector<std::pair<common::pixel<T>, std::vector<size_t>>> & freq_vector,
                        int number);
      template <typename T>
      void addPixelToTable(common::pixel<T> const & pixel, std::vector<uint8_t> & binary,
                           size_t & index) const;

    public:
      void max_level(int level);
      void resize(int width, int height);
      void cut_freq(int freq);
      //[[nodiscard]] std::vector<uint8_t> compress() const;
      SOA(std::vector<uint8_t> const & binary);
      [[nodiscard]] std::vector<uint8_t> toBinary() const;

      [[nodiscard]] int getWidth() const;
      [[nodiscard]] int getHeight() const;
      [[nodiscard]] int getMaxLevel() const;
  };

}  // namespace imgsoa

#endif