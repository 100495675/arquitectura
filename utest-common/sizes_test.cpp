#include "../common/sizes.hpp"

#include <gtest/gtest.h>

// NOLINTBEGIN(cert-err58-cpp)
// NOLINTBEGIN(cppcoreguidelines-owning-memory)
// NOLINTBEGIN(cppcoreguidelines-avoid-goto)
// NOLINTBEGIN(modernize-type-traits)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)

namespace common {

  TEST(AuxTests, Width) {
    int const widthValue = 10;
    Width const width(widthValue);

    EXPECT_EQ(width.getValue(), widthValue);
  }

  TEST(AuxTests, Height) {
    int const heightValue = 20;
    Height const height(heightValue);

    EXPECT_EQ(height.getValue(), heightValue);
  }

  TEST(AuxTests, Size) {
    int const widthValue  = 10;
    int const heightValue = 20;

    Width const width(widthValue);
    Height const height(heightValue);
    Size const size(height, width);

    EXPECT_EQ(size.getHeight().getValue(), heightValue);
    EXPECT_EQ(size.getWidth().getValue(), widthValue);
  }
}  // namespace common

// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast,-warnings-as-errors)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(modernize-type-traits)
// NOLINTEND(cppcoreguidelines-avoid-goto)
// NOLINTEND(cppcoreguidelines-owning-memory)
// NOLINTEND(cert-err58-cpp)