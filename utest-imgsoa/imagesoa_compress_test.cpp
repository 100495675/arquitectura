#include "../imgsoa/imagesoa.hpp"

#include <cstdint>
#include <gtest/gtest.h>
#include <string>
#include <vector>

// NOLINTBEGIN(cert-err58-cpp)
// NOLINTBEGIN(cppcoreguidelines-owning-memory)
// NOLINTBEGIN(cppcoreguidelines-avoid-goto)
// NOLINTBEGIN(modernize-type-traits)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
namespace imgsoa {

  TEST(compress, uint8_menos_de_256_colores) {
    std::string const inputs_str = "P6\n2 "
                                   "8\n255\n"
                                   "\x01\x02\x01\x30\x30\x30\x30\x30\x30\x30\x30"
                                   "\x30\x30\x30\x30\x30\x30\x30\x30"
                                   "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30"
                                   "\x30\x30\x30\x30\x30\x30\x30\x30"
                                   "\x30\x30\x30\x30\x30\x30\x30\x01\x01\x01";
    std::vector<std::uint8_t> const inputs(inputs_str.begin(), inputs_str.end());

    const SOA img(inputs);

    std::vector<uint8_t> const binary = img.compress();

    std::string const expected_str = {
      'C',    '6',    ' ',    '2',    ' ',    '8',    ' ',    '2',    '5',    '5',
      ' ',    '3',    '\n',   '\x01', '\x01', '\x01', '\x01', '\x02', '\x01', '\x30',
      '\x30', '\x30', '\x01', '\x02', '\x02', '\x02', '\x02', '\x02', '\x02', '\x02',
      '\x02', '\x02', '\x02', '\x02', '\x02', '\x02', '\x02', '\x00'};
    std::vector<std::uint8_t> const expected(expected_str.begin(), expected_str.end());

    ASSERT_EQ(expected, binary);
  }

  TEST(compress, unint16_menos_de_256_colores) {
    std::string const inputs_str = "P6\n2 "
                                   "2\n256\n"
                                   "\x01\x01\x01\x01\x01\x01"
                                   "\x30\x30\x30\x30\x30\x30"
                                   "\x30\x30\x30\x30\x30\x30"
                                   "\x01\x01\x01\x02\x01\x01";
    std::vector<std::uint8_t> const inputs(inputs_str.begin(), inputs_str.end());

    const SOA img(inputs);

    std::vector<uint8_t> const binary = img.compress();

    std::string const expected_str = {'C',    '6',    ' ',    '2',    ' ',    '2',    ' ',
                                      '2',    '5',    '6',    ' ',    '3',    '\n',   '\x01',
                                      '\x01', '\x01', '\x01', '\x01', '\x01', '\x01', '\x01',
                                      '\x01', '\x02', '\x01', '\x01', '\x30', '\x30', '\x30',
                                      '\x30', '\x30', '\x30', '\x00', '\x02', '\x02', '\x01'};
    std::vector<std::uint8_t> const expected(expected_str.begin(), expected_str.end());

    ASSERT_EQ(expected, binary);
  }

}  // namespace imgsoa

// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(modernize-type-traits)
// NOLINTEND(cppcoreguidelines-avoid-goto)
// NOLINTEND(cppcoreguidelines-owning-memory)
// NOLINTEND(cert-err58-cpp)
