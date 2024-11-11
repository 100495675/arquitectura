#include "../common/colors.hpp"

#include <gtest/gtest.h>

// NOLINTBEGIN(cert-err58-cpp)
// NOLINTBEGIN(cppcoreguidelines-owning-memory)
// NOLINTBEGIN(cppcoreguidelines-avoid-goto)
// NOLINTBEGIN(modernize-type-traits)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)

namespace common {

  TEST(AuxTests, RedUInt8) {
    uint8_t const redUInt8Value = 100;
    Red<uint8_t> const redUInt8(redUInt8Value);

    EXPECT_EQ(redUInt8.getValue(), redUInt8Value);
  }

  TEST(AuxTests, RedUInt16) {
    uint16_t const redUInt16Value = 100;
    Red<uint16_t> const redUInt16(redUInt16Value);

    EXPECT_EQ(redUInt16.getValue(), redUInt16Value);
  }

  TEST(AuxTests, GreenUInt8) {
    uint8_t const greenUInt8Value = 150;
    Green<uint8_t> const greenUInt8(greenUInt8Value);

    EXPECT_EQ(greenUInt8.getValue(), greenUInt8Value);
  }

  TEST(AuxTests, GreenUInt16) {
    uint16_t const greenUInt16Value = 150;
    Green<uint16_t> const greenUInt16(greenUInt16Value);

    EXPECT_EQ(greenUInt16.getValue(), greenUInt16Value);
  }

  TEST(AuxTests, BlueUInt8) {
    uint8_t const blueUInt8Value = 200;
    Blue<uint8_t> const blueUInt8(blueUInt8Value);

    EXPECT_EQ(blueUInt8.getValue(), blueUInt8Value);
  }

  TEST(AuxTests, BlueUInt16) {
    uint16_t const blueUInt16Value = 200;
    Blue<uint16_t> const blueUInt16(blueUInt16Value);

    EXPECT_EQ(blueUInt16.getValue(), blueUInt16Value);
  }

}  // namespace common

// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(modernize-type-traits)
// NOLINTEND(cppcoreguidelines-avoid-goto)
// NOLINTEND(cppcoreguidelines-owning-memory)
// NOLINTEND(cert-err58-cpp)