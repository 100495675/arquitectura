#include "../imgsoa/imagesoa.hpp"

#include <cstdint>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

// NOLINTBEGIN(cert-err58-cpp)
// NOLINTBEGIN(cppcoreguidelines-owning-memory)
// NOLINTBEGIN(cppcoreguidelines-avoid-goto)
// NOLINTBEGIN(modernize-type-traits)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
// NOLINTBEGIN(readability-magic-numbers)
namespace imgsoa {
  TEST(resize, invalid_width) {
    std::string const inputs_str = "P6\n2 "
                                   "2\n255\n"
                                   "\x10\x20\x30\x40\x50\x60\x70\x80\x90\xA0\xB0\xC0";

    std::vector<std::uint8_t> const inputs(inputs_str.begin(), inputs_str.end());

    SOA img(inputs);

    try {
      img.resize(0, 4);
      FAIL() << "Expected std::invalid_argument";
    } catch (std::invalid_argument const & ia) {
      ASSERT_EQ("Invalid width", std::string(ia.what()));
    }
  }

  TEST(resize, invalid_height) {
    std::string const inputs_str = "P6\n2 "
                                   "2\n255\n"
                                   "\x10\x20\x30\x40\x50\x60\x70\x80\x90\xA0\xB0\xC0";

    std::vector<std::uint8_t> const inputs(inputs_str.begin(), inputs_str.end());

    SOA img(inputs);

    try {
      img.resize(4, 0);
      FAIL() << "Expected std::invalid_argument";
    } catch (std::invalid_argument const & ia) {
      ASSERT_EQ("Invalid height", std::string(ia.what()));
    }
  }

  TEST(resize, uint8_ampliar) {
    std::string const inputs_str = "P6\n2 "
                                   "2\n255\n"
                                   "\x64\x64\x64\x32\x32\x32\x46\x46\x46\x14\x14\x14";

    std::vector<std::uint8_t> const inputs(inputs_str.begin(), inputs_str.end());

    SOA img(inputs);

    img.resize(3, 3);

    std::vector<uint8_t> const binary = img.toBinary();

    std::string const expected_str = "P6\n3 "
                                     "3\n255\n"
                                     "\x64\x64\x64\x4B\x4B\x4B\x32\x32\x32"
                                     "\x55\x55\x55\x3C\x3C\x3C\x23\x23\x23"
                                     "\x46\x46\x46\x2D\x2D\x2D\x14\x14\x14";
    std::vector<std::uint8_t> const expected(expected_str.begin(), expected_str.end());

    ASSERT_EQ(expected, binary);
  }

  TEST(resize, uint8_reduzir) {
    std::string const inputs_str = "P6\n3 "
                                   "3\n255\n"
                                   "\x64\x64\x64\x4B\x4B\x4B\x32\x32\x32"
                                   "\x55\x55\x55\x3C\x3C\x3C\x23\x23\x23"
                                   "\x46\x46\x46\x2D\x2D\x2D\x14\x14\x14";

    std::vector<std::uint8_t> const inputs(inputs_str.begin(), inputs_str.end());

    SOA img(inputs);

    img.resize(2, 2);

    std::vector<uint8_t> const binary = img.toBinary();

    std::string const expected_str = "P6\n2 "
                                     "2\n255\n"
                                     "\x64\x64\x64\x32\x32\x32\x46\x46\x46\x14\x14\x14";
    std::vector<std::uint8_t> const expected(expected_str.begin(), expected_str.end());

    ASSERT_EQ(expected, binary);
  }

  TEST(resize, uint16_ampliar) {
    std::string const inputs_str = "P6\n2 "
                                   "2\n256\n"
                                   "\x64\x64\x64\x64\x64\x64\x32\x32\x32\x32\x32\x32\x46\x46\x46"
                                   "\x46\x46\x46\x14\x14\x14\x14\x14\x14";

    std::vector<std::uint8_t> const inputs(inputs_str.begin(), inputs_str.end());

    SOA img(inputs);

    img.resize(3, 3);

    std::vector<uint8_t> const binary = img.toBinary();

    std::string const expected_str =
        "P6\n3 "
        "3\n256\n"
        "\x64\x64\x64\x64\x64\x64\x4B\x4B\x4B\x4B\x4B\x4B\x32\x32\x32\x32\x32\x32"
        "\x55\x55\x55\x55\x55\x55\x3C\x3C\x3C\x3C\x3C\x3C\x23\x23\x23\x23\x23\x23"
        "\x46\x46\x46\x46\x46\x46\x2D\x2D\x2D\x2D\x2D\x2D\x14\x14\x14\x14\x14\x14";
    std::vector<std::uint8_t> const expected(expected_str.begin(), expected_str.end());

    ASSERT_EQ(expected, binary);
  }
}  // namespace imgsoa

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(modernize-type-traits)
// NOLINTEND(cppcoreguidelines-avoid-goto)
// NOLINTEND(cppcoreguidelines-owning-memory)
// NOLINTEND(cert-err58-cpp)