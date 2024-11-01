#ifndef AUX_HPP
#define AUX_HPP

class Width {
  public:
    explicit Width(int value) : value(value) { }

    [[nodiscard]] int getValue() const { return value; }

  private:
    int value;
};

class Height {
  public:
    explicit Height(int value) : value(value) { }

    [[nodiscard]] int getValue() const { return value; }

  private:
    int value;
};

class Size {
  public:
    explicit Size(Height height, Width width) : height(height), width(width) { }

    [[nodiscard]] Height getHeight() const { return height; }

    [[nodiscard]] Width getWidth() const { return width; }

  private:
    Height height;
    Width width;
};

template <typename T>
struct Red {
  public:
    Red(T value) : value(value) { }

    [[nodiscard]] T getValue() const { return value; }

  private:
    T value;
};

template <typename T>
struct Green {
  public:
    Green(T value) : value(value) { }

    [[nodiscard]] T getValue() const { return value; }

  private:
    T value;
};

template <typename T>
struct Blue {
  public:
    Blue(T value) : value(value) { }

    [[nodiscard]] T getValue() const { return value; }

  private:
    T value;
};

#endif  // AUX_HPP