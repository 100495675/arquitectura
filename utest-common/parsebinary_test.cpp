#include "../common/parsebinary.hpp"
#include <cstdint>
#include <cstdio>
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

namespace common {
TEST(parse, normal) {

  const std::string data_str =
      "numero_magico\nanchura altura\nmax_color_value\ninformacion_de_pixeles";
  const std::vector<uint8_t> data(data_str.begin(), data_str.end());

  const std::vector<std::string> result = ParseBinary::parse(data);
  const std::vector<std::string> expected = {"numero_magico", "anchura",
                                             "altura", "max_color_value",
                                             "informacion_de_pixeles"};

  ASSERT_EQ(expected, result);
}

TEST(parse, empty) {

  const std::string data_str = "";
  const std::vector<uint8_t> data(data_str.begin(), data_str.end());

  try {
    ParseBinary::parse(data);
    FAIL() << "Expected std::runtime_error";
  } catch (const std::runtime_error &e) {
    EXPECT_EQ(std::string("Error archivo vacio"), e.what());
  }
}

TEST(parse, espacios_mix) {
  const std::string data_str =
      "numero_magico\nanchura altura\tmax_color_value\tinformacion_de_pixeles";
  const std::vector<uint8_t> data(data_str.begin(), data_str.end());

  const std::vector<std::string> result = ParseBinary::parse(data);
  const std::vector<std::string> expected = {"numero_magico", "anchura",
                                             "altura", "max_color_value",
                                             "informacion_de_pixeles"};
  ASSERT_EQ(expected, result);
}

TEST(parse, muchos_espacios) {
  const std::string data_str =
      "numero_magico\n\n\n\nanchura                "
      "altura\t\t\t\t\tmax_color_value\tinformacion_de_pixeles";
  const std::vector<uint8_t> data(data_str.begin(), data_str.end());

  const std::vector<std::string> result = ParseBinary::parse(data);
  const std::vector<std::string> expected = {"numero_magico", "anchura",
                                             "altura", "max_color_value",
                                             "informacion_de_pixeles"};

  ASSERT_EQ(expected, result);
}

TEST(parse, muchos_espacios_mix) {
  const std::string data_str =
      "numero_magico\n\t  \nanchura      \n      \n\n    \taltura\t           "
      "\t\nmax_color_value\ninformacion_de_pixeles";
  const std::vector<uint8_t> data(data_str.begin(), data_str.end());

  const std::vector<std::string> result = ParseBinary::parse(data);
  const std::vector<std::string> expected = {"numero_magico", "anchura",
                                             "altura", "max_color_value",
                                             "informacion_de_pixeles"};
  ASSERT_EQ(expected, result);
}

TEST(parse, sin_espacios) {
  const std::string data_str =
      "numero_magicoanchuraalturamax_color_valueinformacion_de_pixeles";
  const std::vector<uint8_t> data(data_str.begin(), data_str.end());

  try {
    ParseBinary::parse(data);
    FAIL() << "Expected std::runtime_error";
  } catch (const std::runtime_error &e) {
    EXPECT_EQ(std::string("Error en la lectura de la cadena"), e.what());
  }
}

TEST(parse, espacios_al_inicio) {
  const std::string data_str =
      "\n\n\n\nnumero_magico\nanchura "
      "altura\tmax_color_value\tinformacion_de_pixeles";
  const std::vector<uint8_t> data(data_str.begin(), data_str.end());

  try {
    ParseBinary::parse(data);
    FAIL() << "Expected std::runtime_error";
  } catch (const std::runtime_error &e) {
    EXPECT_EQ(std::string("Error en los espacios al inicio"), e.what());
  }
}

TEST(parse, espacios_al_final) {
  const std::string data_str =
      "numero_magico\nanchura altura\t\n\n  \t\n \n\t\t ";
  const std::vector<uint8_t> data(data_str.begin(), data_str.end());

  try {
    ParseBinary::parse(data);
    FAIL() << "Expected std::runtime_error";
  } catch (const std::runtime_error &e) {
    EXPECT_EQ(std::string("Error en los espacios"), e.what());
  }
}
} // namespace common
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(modernize-type-traits)
// NOLINTEND(cppcoreguidelines-avoid-goto)
// NOLINTEND(cppcoreguidelines-owning-memory)
// NOLINTEND(cert-err58-cpp)