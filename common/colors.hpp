#ifndef COLORS_HPP
#define COLORS_HPP

namespace common {
  template <typename T>
  struct Red {
    public:
      using value_type = T;
      Red(T value);
      [[nodiscard]] T getValue() const;

    private:
      T value;
  };

  template <typename T>
  struct Green {
    public:
      using value_type = T;
      Green(T value);
      [[nodiscard]] T getValue() const;

    private:
      T value;
  };

  template <typename T>
  struct Blue {
    public:
      using value_type = T;
      Blue(T value);
      [[nodiscard]] T getValue() const;

    private:
      T value;
  };

  // Implementation
  template <typename T>
  Red<T>::Red(T value) : value(value) { }

  template <typename T>
  T Red<T>::getValue() const {
    return value;
  }

  template <typename T>
  Green<T>::Green(T value) : value(value) { }

  template <typename T>
  T Green<T>::getValue() const {
    return value;
  }

  template <typename T>
  Blue<T>::Blue(T value) : value(value) { }

  template <typename T>
  T Blue<T>::getValue() const {
    return value;
  }
}  // namespace common
#endif