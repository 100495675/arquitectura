#ifndef PROGARGS_HPP
#define PROGARGS_HPP

#include <cstdint>
#include <cstdlib>
#include <gtest/gtest_prod.h>
#include <string>
#include <variant>
#include <vector>

namespace common {

struct InputArgs {
  FRIEND_TEST(InputArgs, maxlevel);
  FRIEND_TEST(InputArgs, resize);
  FRIEND_TEST(InputArgs, cutfreq);

public:
  class MaxLevelData {
  public:
    MaxLevelData(int level) : level(level) {}
    [[nodiscard]] int getLevel() const { return level; }

  private:
    int level;
  };
  class ResizeData {
  public:
    ResizeData(int _w, int _h) : width(_w), height(_h) {}
    [[nodiscard]] int getWidth() const { return width; }
    [[nodiscard]] int getHeight() const { return height; }

  private:
    int width, height;
  };
  class CutFreqData {
  public:
    CutFreqData(int freq) : freq(freq) {}
    [[nodiscard]] int getFreq() const { return freq; }

  private:
    int freq;
  };
  enum class Command : uint8_t { Info, MaxLevel, Resize, CutFreq, Compress };

  InputArgs(const std::vector<std::string> &argv_strings);

  [[nodiscard]] std::string getInput() const;
  [[nodiscard]] std::string getOutput() const;
  [[nodiscard]] Command getCommand() const;
  [[nodiscard]] std::string getCommandAsString() const;
  [[nodiscard]] MaxLevelData getMaxLevelData() const;
  [[nodiscard]] ResizeData getResizeData() const;
  [[nodiscard]] CutFreqData getCutFreqData() const;

private:
  std::string input;
  std::string output;

  Command command = Command::MaxLevel; // default, to avoid a compiler warning

  std::variant<MaxLevelData, ResizeData, CutFreqData> values =
      MaxLevelData(0); // default, to avoid a compiler warning

  void validate_info(int argc, const std::vector<std::string> &argv_strings);
  void validate_maxlevel(int argc,
                         const std::vector<std::string> &argv_strings);
  void validate_resize(int argc, const std::vector<std::string> &argv_strings);
  void validate_cutfreq(int argc, const std::vector<std::string> &argv_strings);
  void validate_compress(int argc,
                         const std::vector<std::string> &argv_strings);
};

} // namespace common

#endif