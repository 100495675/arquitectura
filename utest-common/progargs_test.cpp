#include "../common/progargs.hpp"
#include "gtest/gtest.h"
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

TEST(InputArgs, cero_args) {
  const std::vector<std::string> argv = {"path/to/program"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid number of arguments: 0"));
  }
}

TEST(InputArgs, un_arg) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid number of arguments: 1"));
  }
}

TEST(InputArgs, dos_args) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid number of arguments: 2"));
  }
}

TEST(InputArgs, op_no_valida) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "op_no_valida"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid option: op_no_valida"));
  }
}

TEST(InputArgs, info) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "info"};
  const InputArgs input_args(argv);
  ASSERT_EQ(input_args.getInput(), "archivo.ppm");
  ASSERT_EQ(input_args.getOutput(), "salida.ppm");
  ASSERT_EQ(input_args.getCommand(), InputArgs::Command::Info);
}

TEST(InputArgs, info_1_extra_arg) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "info", "100"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(),
              std::string("Error: Invalid extra arguments for info: 100"));
  }
}

TEST(InputArgs, info_2_extra_arg) {

  const std::vector<std::string> argv = {
      "path/to/program", "archivo.ppm", "salida.ppm", "info", "100", "200"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(),
              std::string("Error: Invalid extra arguments for info: 100 200"));
  }
}

TEST(InputArgs, maxlevel_falta_1_arg) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "maxlevel"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(),
              std::string(
                  "Error: Invalid number of extra arguments for maxlevel: 0"));
  }
}

TEST(InputArgs, maxlevel) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "maxlevel", "100"};
  const InputArgs input_args(argv);
  ASSERT_EQ(input_args.getInput(), "archivo.ppm");
  ASSERT_EQ(input_args.getOutput(), "salida.ppm");
  ASSERT_EQ(input_args.getCommand(), InputArgs::Command::MaxLevel);
  auto maxLevel = std::get<InputArgs::MaxLevelData>(input_args.values);
  ASSERT_EQ(maxLevel.getLevel(), 100);
}

TEST(InputArgs, maxlevel_sobra_1_arg) {

  const std::vector<std::string> argv = {
      "path/to/program", "archivo.ppm", "salida.ppm", "maxlevel", "100", "200"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(),
              std::string(
                  "Error: Invalid number of extra arguments for maxlevel: 2"));
  }
}

TEST(InputArgs, maxlevel_negativo) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "maxlevel", "-1"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid maxlevel: -1"));
  }
}

TEST(InputArgs, maxlevel_grande) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "maxlevel", "70000"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid maxlevel: 70000"));
  }
}

TEST(InputArgs, maxlevel_texto) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "maxlevel", "texto"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid maxlevel: texto"));
  }
}

TEST(InputArgs, resize_faltan_2_args) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "resize"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(
        err.what(),
        std::string("Error: Invalid number of extra arguments for resize: 0"));
  }
}

TEST(InputArgs, resize_falta_1_arg) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "resize", "100"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(
        err.what(),
        std::string("Error: Invalid number of extra arguments for resize: 1"));
  }
}

TEST(InputArgs, resize) {

  const std::vector<std::string> argv = {
      "path/to/program", "archivo.ppm", "salida.ppm", "resize", "100", "200"};
  const InputArgs input_args(argv);
  ASSERT_EQ(input_args.getInput(), "archivo.ppm");
  ASSERT_EQ(input_args.getOutput(), "salida.ppm");
  ASSERT_EQ(input_args.getCommand(), InputArgs::Command::Resize);
  auto resize = std::get<InputArgs::ResizeData>(input_args.values);
  ASSERT_EQ(resize.getWidth(), 100);
  ASSERT_EQ(resize.getHeight(), 200);
}

TEST(InputArgs, resize_sobra_1_arg) {

  const std::vector<std::string> argv = {"path/to/program",
                                         "archivo.ppm",
                                         "salida.ppm",
                                         "resize",
                                         "100",
                                         "200",
                                         "300"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(
        err.what(),
        std::string("Error: Invalid number of extra arguments for resize: 3"));
  }
}

TEST(InputArgs, resize_width_negativo) {

  const std::vector<std::string> argv = {
      "path/to/program", "archivo.ppm", "salida.ppm", "resize", "-100", "200"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid resize width: -100"));
  }
}

TEST(InputArgs, resize_height_negativo) {

  const std::vector<std::string> argv = {
      "path/to/program", "archivo.ppm", "salida.ppm", "resize", "100", "-200"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid resize height: -200"));
  }
}

TEST(InputArgs, resize_texto) {

  const std::vector<std::string> argv = {
      "path/to/program", "archivo.ppm", "salida.ppm", "resize", "100", "texto"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid resize height: texto"));
  }
}

TEST(InputArgs, cutfreq_faltan_1_arg) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "cutfreq"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(
        err.what(),
        std::string("Error: Invalid number of extra arguments for cutfreq: 0"));
  }
}

TEST(InputArgs, cutfreq) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "cutfreq", "100"};
  const InputArgs input_args(argv);
  ASSERT_EQ(input_args.getInput(), "archivo.ppm");
  ASSERT_EQ(input_args.getOutput(), "salida.ppm");
  ASSERT_EQ(input_args.getCommand(), InputArgs::Command::CutFreq);
  auto cutfreq = std::get<InputArgs::CutFreqData>(input_args.values);
  ASSERT_EQ(cutfreq.getFreq(), 100);
}

TEST(InputArgs, cutfreq_sobra_1_arg) {

  const std::vector<std::string> argv = {
      "path/to/program", "archivo.ppm", "salida.ppm", "cutfreq", "100", "200"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(
        err.what(),
        std::string("Error: Invalid number of extra arguments for cutfreq: 2"));
  }
}

TEST(InputArgs, cutfreq_freq_negativa) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "cutfreq", "-100"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid cutfreq: -100"));
  }
}

TEST(InputArgs, cutfreq_texto) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "cutfreq", "texto"};
  try {
    const InputArgs input_args(argv);
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid cutfreq: texto"));
  }
}

TEST(InputArgs, compress) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "compress"};
  const InputArgs input_args(argv);
  ASSERT_EQ(input_args.getInput(), "archivo.ppm");
  ASSERT_EQ(input_args.getOutput(), "salida.ppm");
  ASSERT_EQ(input_args.getCommand(), InputArgs::Command::Compress);
}

TEST(InputArgs, compress_sobra_1_arg) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "compress", "100"};
  try {
    const InputArgs input_args(argv);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(),
              std::string("Error: Invalid extra arguments for compress: 100"));
  }
}

TEST(getCommandAsString, Info) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "info"};
  const InputArgs input_args(argv);

  EXPECT_EQ("info", input_args.getCommandAsString());
}

TEST(getCommandAsString, MaxLevel) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "maxlevel", "100"};
  const InputArgs input_args(argv);

  EXPECT_EQ("maxlevel", input_args.getCommandAsString());
}

TEST(getCommandAsString, Resize) {

  const std::vector<std::string> argv = {
      "path/to/program", "archivo.ppm", "salida.ppm", "resize", "100", "200"};
  const InputArgs input_args(argv);
  EXPECT_EQ("resize", input_args.getCommandAsString());
}

TEST(getCommandAsString, CutFreq) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "cutfreq", "100"};
  const InputArgs input_args(argv);
  EXPECT_EQ("cutfreq", input_args.getCommandAsString());
}

TEST(getCommandAsString, Compress) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "compress"};
  const InputArgs input_args(argv);
  EXPECT_EQ("compress", input_args.getCommandAsString());
}

TEST(getMaxLevelData, normal) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "maxlevel", "100"};
  const InputArgs input_args(argv);
  EXPECT_EQ(100, input_args.getMaxLevelData().getLevel());
}

TEST(getMaxLevelData, invalid) {

  const std::vector<std::string> argv = {
      "path/to/program", "archivo.ppm", "salida.ppm", "resize", "100", "200"};
  const InputArgs input_args(argv);
  try {
    auto _ = input_args.getMaxLevelData();
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid command for maxlevel"));
  }
}

TEST(getResizeData, normal) {

  const std::vector<std::string> argv = {
      "path/to/program", "archivo.ppm", "salida.ppm", "resize", "100", "200"};
  const InputArgs input_args(argv);
  EXPECT_EQ(100, input_args.getResizeData().getWidth());
  EXPECT_EQ(200, input_args.getResizeData().getHeight());
}

TEST(getResizeData, invalid) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "cutfreq", "100"};
  const InputArgs input_args(argv);
  try {
    auto _ = input_args.getResizeData();
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid command for resize"));
  }
}

TEST(getCutFreqData, normal) {

  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "cutfreq", "100"};
  const InputArgs input_args(argv);
  EXPECT_EQ(100, input_args.getCutFreqData().getFreq());
}

TEST(getCutFreqData, invalid) {
  const std::vector<std::string> argv = {"path/to/program", "archivo.ppm",
                                         "salida.ppm", "maxlevel", "100"};
  const InputArgs input_args(argv);
  try {
    auto _ = input_args.getCutFreqData();
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("Error: Invalid command for cutfreq"));
  }
}
} // namespace common
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(modernize-type-traits)
// NOLINTEND(cppcoreguidelines-avoid-goto)
// NOLINTEND(cppcoreguidelines-owning-memory)
// NOLINTEND(cert-err58-cpp)