#include "../common/validatefile.hpp"
#include <cstddef>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
// NOLINTBEGIN(cert-err58-cpp)
// NOLINTBEGIN(cppcoreguidelines-owning-memory)
// NOLINTBEGIN(cppcoreguidelines-avoid-goto)
// NOLINTBEGIN(modernize-type-traits)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
namespace common {

TEST(validate_magic_number, valido) {

  const std::string input = "P6";

  ASSERT_NO_THROW(validateFile::validate_magic_number(input));
}

TEST(validate_magic_number, no_valido) {
  const std::string input = "P5";
  try {
    validateFile::validate_magic_number(input);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &ia) {
    ASSERT_EQ("Invalid magic number", std::string(ia.what()));
  }
}

TEST(validate_maxlevel, valido) {
  const std::string input = "123";
  int maxlevel = 0;
  ASSERT_NO_THROW(maxlevel = validateFile::validate_maxlevel(input));
  ASSERT_EQ(123, maxlevel);
}

TEST(validate_maxlevel, texto) {
  const std::string input = "abc";
  try {
    const int _ = validateFile::validate_maxlevel(input);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &ia) {
    ASSERT_EQ("Invalid maxlevel", std::string(ia.what()));
  }
}

TEST(validate_maxlevel, negativo) {
  const std::string input = "-1";
  try {
    const int _ = validateFile::validate_maxlevel(input);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &ia) {
    ASSERT_EQ("Invalid maxlevel", std::string(ia.what()));
  }
}

TEST(validate_maxlevel, grande) {
  const std::string input = "123456";
  try {
    const int _ = validateFile::validate_maxlevel(input);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &ia) {
    ASSERT_EQ("Invalid maxlevel", std::string(ia.what()));
  }
}

TEST(validate_width, texto) {
  const std::string input = "abc";

  try {
    const int _ = validateFile::validate_width(input);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &ia) {
    ASSERT_EQ("Invalid width", std::string(ia.what()));
  }
}

TEST(validate_width, negativo) {
  const std::string input = "-1";

  try {
    const int _ = validateFile::validate_width(input);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &ia) {
    ASSERT_EQ("Invalid width", std::string(ia.what()));
  }
}

TEST(validate_height, texto) {
  const std::string input = "abc";

  try {
    const int _ = validateFile::validate_height(input);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &ia) {
    ASSERT_EQ("Invalid height", std::string(ia.what()));
  }
}

TEST(validate_height, negativo) {
  const std::string input = "-1";

  try {
    const int _ = validateFile::validate_height(input);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &ia) {
    ASSERT_EQ("Invalid height", std::string(ia.what()));
  }
}

TEST(validate_pixels, bueno) {
  const std::string input = "123";
  const size_t number_of_bytes = 3;
  ASSERT_NO_THROW(validateFile::validate_pixels(input, number_of_bytes));
}

TEST(validate_pixels, mucho_datos_de_pixels) {
  const std::string input = "123456789";
  const size_t number_of_bytes = 3;

  try {
    validateFile::validate_pixels(input, number_of_bytes);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &ia) {
    ASSERT_EQ("Invalid number of pixels", std::string(ia.what()));
  }
}

TEST(validate_pixels, pocos_datos_de_pixels) {
  const std::string input = "123";
  const size_t number_of_bytes = 9;
  try {
    validateFile::validate_pixels(input, number_of_bytes);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &ia) {
    ASSERT_EQ("Invalid number of pixels", std::string(ia.what()));
  }
}
} // namespace common

// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(modernize-type-traits)
// NOLINTEND(cppcoreguidelines-avoid-goto)
// NOLINTEND(cppcoreguidelines-owning-memory)
// NOLINTEND(cert-err58-cpp)