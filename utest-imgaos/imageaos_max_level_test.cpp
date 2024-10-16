#include "../imgaos/imageaos.hpp"
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
namespace imgaos {

TEST(max_level, uint8_to_uint8) {
  const std::string inputs_str = "P6\n2 "
                                 "8\n255\n"
                                 "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30"
                                 "\x30\x30\x30\x30\x30\x30\x30\x30"
                                 "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30"
                                 "\x30\x30\x30\x30\x30\x30\x30\x30"
                                 "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30";
  const std::vector<std::uint8_t> inputs(inputs_str.begin(), inputs_str.end());
  // se supone que funciona
  AOS img(inputs);

  img.max_level(100);

  // se supone que funciona
  const std::vector<uint8_t> binary = img.toBinary();

  const std::string expected_str =
      "P6\n2 "
      "8\n100\n"
      "\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12"
      "\x12\x12\x12\x12\x12\x12\x12\x12"
      "\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12"
      "\x12\x12\x12\x12\x12\x12\x12\x12"
      "\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12";
  const std::vector<std::uint8_t> expected(expected_str.begin(),
                                           expected_str.end());

  ASSERT_EQ(expected, binary);
}

TEST(max_level, uint8_to_uint16) {
  const std::string inputs_str = "P6\n2 "
                                 "8\n255\n"
                                 "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30"
                                 "\x30\x30\x30\x30\x30\x30\x30\x30"
                                 "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30"
                                 "\x30\x30\x30\x30\x30\x30\x30\x30"
                                 "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30";
  const std::vector<std::uint8_t> inputs(inputs_str.begin(), inputs_str.end());
  // se supone que funciona
  AOS img(inputs);

  img.max_level(510);

  // se supone que funciona
  const std::vector<uint8_t> binary = img.toBinary();

  const std::string expected_str = {
      'P',    '6',    '\n',   '2',    ' ',    '8',    '\n',   '5',    '1',
      '0',    '\n',   '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60'};
  const std::vector<std::uint8_t> expected(expected_str.begin(),
                                           expected_str.end());

  ASSERT_EQ(expected, binary);
}

TEST(max_level, uint16_to_uint8) {
  const std::string inputs_str{
      'P',    '6',    '\n',   '2',    ' ',    '8',    '\n',   '5',    '1',
      '0',    '\n',   '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60'};
  const std::vector<std::uint8_t> inputs(inputs_str.begin(), inputs_str.end());
  // se supone que funciona
  AOS img(inputs);

  img.max_level(255);

  // se supone que funciona
  const std::vector<uint8_t> binary = img.toBinary();

  const std::string expected_str =
      "P6\n2 "
      "8\n255\n"
      "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30"
      "\x30\x30\x30\x30\x30\x30\x30\x30"
      "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30"
      "\x30\x30\x30\x30\x30\x30\x30\x30"
      "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30";
  const std::vector<std::uint8_t> expected(expected_str.begin(),
                                           expected_str.end());

  ASSERT_EQ(expected, binary);
}

TEST(max_level, uint16_to_uint16) {
  const std::string inputs_str{
      'P',    '6',    '\n',   '2',    ' ',    '8',    '\n',   '5',    '1',
      '0',    '\n',   '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00',
      '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60',
      '\x00', '\x60', '\x00', '\x60', '\x00', '\x60', '\x00', '\x60'};
  const std::vector<std::uint8_t> inputs(inputs_str.begin(), inputs_str.end());
  // se supone que funciona
  AOS img(inputs);

  img.max_level(1020);

  // se supone que funciona
  const std::vector<uint8_t> binary = img.toBinary();

  const std::string expected_str = {
      'P',    '6',    '\n',   '2',    ' ',    '8',    '\n',   '1',    '0',
      '2',    '0',    '\n',   '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0',
      '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00',
      '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0',
      '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00',
      '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0',
      '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00',
      '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0',
      '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00',
      '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0',
      '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00',
      '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0', '\x00', '\xC0'};
  const std::vector<std::uint8_t> expected(expected_str.begin(),
                                           expected_str.end());

  ASSERT_EQ(expected, binary);
}
} // namespace imgaos
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(modernize-type-traits)
// NOLINTEND(cppcoreguidelines-avoid-goto)
// NOLINTEND(cppcoreguidelines-owning-memory)
// NOLINTEND(cert-err58-cpp)