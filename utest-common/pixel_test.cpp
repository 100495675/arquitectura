#include "../common/pixel.hpp"

#include <gtest/gtest.h>

// NOLINTBEGIN(cert-err58-cpp)
// NOLINTBEGIN(cppcoreguidelines-owning-memory)
// NOLINTBEGIN(cppcoreguidelines-avoid-goto)
// NOLINTBEGIN(modernize-type-traits)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)

namespace common {

  TEST(pixel, PixelUInt8) {
    uint8_t const redUInt8Value   = 100;
    uint8_t const greenUInt8Value = 150;
    uint8_t const blueUInt8Value  = 200;
    pixel<uint8_t> const pixelUInt8(redUInt8Value, greenUInt8Value, blueUInt8Value);

    EXPECT_EQ(pixelUInt8.getR(), redUInt8Value);
    EXPECT_EQ(pixelUInt8.getG(), greenUInt8Value);
    EXPECT_EQ(pixelUInt8.getB(), blueUInt8Value);
  }

  TEST(pixel, PixelUInt16) {
    uint16_t const redUInt16Value   = 1000;
    uint16_t const greenUInt16Value = 1500;
    uint16_t const blueUInt16Value  = 2000;
    pixel<uint16_t> const pixelUInt16(redUInt16Value, greenUInt16Value, blueUInt16Value);

    EXPECT_EQ(pixelUInt16.getR(), redUInt16Value);
    EXPECT_EQ(pixelUInt16.getG(), greenUInt16Value);
    EXPECT_EQ(pixelUInt16.getB(), blueUInt16Value);
  }

  TEST(pixel, PixelFloat) {
    float const redFloatValue   = 0.1F;
    float const greenFloatValue = 0.2F;
    float const blueFloatValue  = 0.3F;
    pixel<float> const pixelFloat(redFloatValue, greenFloatValue, blueFloatValue);

    EXPECT_FLOAT_EQ(pixelFloat.getR(), redFloatValue);
    EXPECT_FLOAT_EQ(pixelFloat.getG(), greenFloatValue);
    EXPECT_FLOAT_EQ(pixelFloat.getB(), blueFloatValue);
  }

  TEST(pixel, PixelWriteToBinaryUInt8) {
    uint8_t const redUInt8Value   = 100;
    uint8_t const greenUInt8Value = 150;
    uint8_t const blueUInt8Value  = 200;
    pixel<uint8_t> const pixelUInt8(redUInt8Value, greenUInt8Value, blueUInt8Value);

    std::vector<uint8_t> binary;
    pixelUInt8.write_to_binary(binary);

    EXPECT_EQ(binary.size(), 3);
    EXPECT_EQ(binary[0], redUInt8Value);
    EXPECT_EQ(binary[1], greenUInt8Value);
    EXPECT_EQ(binary[2], blueUInt8Value);
  }

  TEST(pixel, PixelWriteToBinaryUInt16) {
    uint16_t const redUInt16Value   = 1000;
    uint16_t const greenUInt16Value = 1500;
    uint16_t const blueUInt16Value  = 2000;
    pixel<uint16_t> const pixelUInt16(redUInt16Value, greenUInt16Value, blueUInt16Value);

    std::vector<uint8_t> binary;
    pixelUInt16.write_to_binary(binary);

    EXPECT_EQ(binary.size(), 6);
    EXPECT_EQ(binary[0], static_cast<uint8_t>(redUInt16Value >> UINT8_WIDTH));
    EXPECT_EQ(binary[1], static_cast<uint8_t>(redUInt16Value & UINT8_MAX));
    EXPECT_EQ(binary[2], static_cast<uint8_t>(greenUInt16Value >> UINT8_WIDTH));
    EXPECT_EQ(binary[3], static_cast<uint8_t>(greenUInt16Value & UINT8_MAX));
    EXPECT_EQ(binary[4], static_cast<uint8_t>(blueUInt16Value >> UINT8_WIDTH));
    EXPECT_EQ(binary[5], static_cast<uint8_t>(blueUInt16Value & UINT8_MAX));
  }

  TEST(pixel, PixelEqual) {
    pixel<uint8_t> const pixel1(100, 150, 200);
    pixel<uint8_t> const pixel2(100, 150, 200);
    pixel<uint8_t> const pixel3(100, 150, 201);

    EXPECT_EQ(pixel1, pixel2);
    EXPECT_NE(pixel1, pixel3);
  }

  TEST(PixelHash, PixelHashOperation) {
    pixel<uint8_t> const pixel1(100, 150, 200);
    pixel<uint8_t> const pixel2(100, 150, 200);
    pixel<uint8_t> const pixel3(100, 150, 201);

    PixelHash<uint8_t> const pixelHash;
    size_t const hash1 = pixelHash(pixel1);
    size_t const hash2 = pixelHash(pixel2);
    size_t const hash3 = pixelHash(pixel3);

    EXPECT_EQ(hash1, hash2);
    EXPECT_NE(hash1, hash3);
  }
}  // namespace common

// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(modernize-type-traits)
// NOLINTEND(cppcoreguidelines-avoid-goto)
// NOLINTEND(cppcoreguidelines-owning-memory)
// NOLINTEND(cert-err58-cpp)