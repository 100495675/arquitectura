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
// NOLINTBEGIN(readability-magic-numbers)
namespace imgsoa {

  TEST(imgsoa, normal_uint8) {
    std::string const inputs_str =
        "P6\n2 "
        "8\n255\n"
        "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
        "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x20\x21"
        "\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F\x30";
    std::vector<std::uint8_t> const inputs(inputs_str.begin(), inputs_str.end());
    const SOA img(inputs);
    ASSERT_EQ(2, img.getWidth());
    ASSERT_EQ(8, img.getHeight());
    ASSERT_EQ(255, img.getMaxLevel());
    ASSERT_EQ(SOA::Type::UINT8, img.type);
    std::vector<uint8_t> const expected_red   = {0x01, 0x04, 0x07, 0x0A, 0x0D, 0x10, 0x13, 0x16,
                                                 0x19, 0x1C, 0x1F, 0x22, 0x25, 0x28, 0x2B, 0x2E};
    std::vector<uint8_t> const expected_green = {0x02, 0x05, 0x08, 0x0B, 0x0E, 0x11, 0x14, 0x17,
                                                 0x1A, 0x1D, 0x20, 0x23, 0x26, 0x29, 0x2C, 0x2F};
    std::vector<uint8_t> const expected_blue  = {0x03, 0x06, 0x09, 0x0C, 0x0F, 0x12, 0x15, 0x18,
                                                 0x1B, 0x1E, 0x21, 0x24, 0x27, 0x2A, 0x2D, 0x30};
    auto const & red   = std::get<std::vector<common::Red<uint8_t>>>(img.red);
    auto const & green = std::get<std::vector<common::Green<uint8_t>>>(img.green);
    auto const & blue  = std::get<std::vector<common::Blue<uint8_t>>>(img.blue);
    for (size_t i = 0; i < 16; i++) {
      ASSERT_EQ(expected_red[i], red[i].getValue());
      ASSERT_EQ(expected_green[i], green[i].getValue());
      ASSERT_EQ(expected_blue[i], blue[i].getValue());
    }
  }

  TEST(imgsoa, normal_uint16) {
    std::string const inputs_str =
        "P6\n2 "
        "4\n256\n"
        "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
        "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x20\x21"
        "\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F\x30";
    std::vector<std::uint8_t> const inputs(inputs_str.begin(), inputs_str.end());

    const SOA img(inputs);

    ASSERT_EQ(2, img.getWidth());
    ASSERT_EQ(4, img.getHeight());
    ASSERT_EQ(256, img.getMaxLevel());
    ASSERT_EQ(SOA::Type::UINT16, img.type);

    std::vector<uint16_t> const expected_red   = {0x0102, 0x0708, 0x0D0E, 0x1314,
                                                  0x191A, 0x1F20, 0x2526, 0x2B2C};
    std::vector<uint16_t> const expected_green = {0x0304, 0x090A, 0x0F10, 0x1516,
                                                  0x1B1C, 0x2122, 0x2728, 0x2D2E};
    std::vector<uint16_t> const expected_blue  = {0x0506, 0x0B0C, 0x1112, 0x1718,
                                                  0x1D1E, 0x2324, 0x292A, 0x2F30};
    auto const & red   = std::get<std::vector<common::Red<uint16_t>>>(img.red);
    auto const & green = std::get<std::vector<common::Green<uint16_t>>>(img.green);
    auto const & blue  = std::get<std::vector<common::Blue<uint16_t>>>(img.blue);
    for (size_t i = 0; i < 8; i++) {
      ASSERT_EQ(expected_red[i], red[i].getValue());
      ASSERT_EQ(expected_green[i], green[i].getValue());
      ASSERT_EQ(expected_blue[i], blue[i].getValue());
    }
  }

  TEST(toBinary, normal_uint8) {
    std::string const inputs_str =
        "P6\n2 "
        "8\n255\n"
        "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
        "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x20\x21"
        "\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F\x30";
    std::vector<std::uint8_t> const inputs(inputs_str.begin(), inputs_str.end());
    // se supone que funciona
    const SOA img(inputs);

    std::vector<uint8_t> const binary = img.toBinary();
    ASSERT_EQ(binary, inputs);
  }

  TEST(toBinary, normal_uint16) {
    std::string const inputs_str =
        "P6\n2 "
        "4\n256\n"
        "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
        "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x20\x21"
        "\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F\x30";
    std::vector<std::uint8_t> const inputs(inputs_str.begin(), inputs_str.end());

    // se supone que funciona
    const SOA img(inputs);

    std::vector<uint8_t> const binary = img.toBinary();
    ASSERT_EQ(binary, inputs);
  }

}  // namespace imgsoa

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(modernize-type-traits)
// NOLINTEND(cppcoreguidelines-avoid-goto)
// NOLINTEND(cppcoreguidelines-owning-memory)
// NOLINTEND(cert-err58-cpp)