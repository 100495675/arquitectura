#ifndef SIZES_HPP
#define SIZES_HPP

namespace common {
  class Width {
    public:
      explicit Width(int value);
      [[nodiscard]] int getValue() const;

    private:
      int value;
  };

  class Height {
    public:
      explicit Height(int value);
      [[nodiscard]] int getValue() const;

    private:
      int value;
  };

  class Size {
    public:
      explicit Size(Height height, Width width);
      [[nodiscard]] Height getHeight() const;
      [[nodiscard]] Width getWidth() const;

    private:
      Height height;
      Width width;
  };
}  // namespace common
#endif