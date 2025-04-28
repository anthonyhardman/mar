#pragma once

#include <utility>

struct OkTag {};
struct ErrTag {};

template <typename T, typename E> class Result {
public:
  static Result ok(T &&v) noexcept { return Result(OkTag{}, std::move(v)); }
  static Result err(E &&e) noexcept { return Result(ErrTag{}, std::move(e)); }

  bool is_ok() const noexcept { return has_value_; }

  bool is_err() const noexcept { return !has_value_; }

  T &unwrap() noexcept { return value_; }

  const T &unwrap() const noexcept { return value_; }

  E &error() noexcept { return error_; }

  const E &error() const noexcept { return error_; }

  ~Result() {
    if (has_value_) {
      value_.~T();
    } else {
      error_.~E();
    }
  }

  Result(Result &&other) noexcept(std::is_nothrow_move_constructible_v<T> &&
                                  std::is_nothrow_move_constructible_v<E>)
      : has_value_(other.has_value_) {
    if (has_value_) {
      new (&value_) T(std::move(other.value_));
    } else {
      new (&error_) E(std::move(other.error_));
    }
  }

  Result &
  operator=(Result &&other) noexcept(std::is_nothrow_move_constructible_v<T> &&
                                     std::is_nothrow_move_constructible_v<E>) {
    if (this != &other) {
      this->~Result(); // Destroy current
      has_value_ = other.has_value_;
      if (has_value_) {
        new (&value_) T(std::move(other.value_));
      } else {
        new (&error_) E(std::move(other.error_));
      }
    }
    return *this;
  }

  Result(const Result &) = delete;
  Result &operator=(const Result &) = delete;

private:
  union {
    T value_;
    E error_;
  };
  bool has_value_;

  explicit Result(OkTag, T &&v) noexcept : has_value_(true) {
    new (&value_) T(std::move(v));
  }

  explicit Result(ErrTag, E &&e) noexcept : has_value_(false) {
    new (&error_) E(std::move(e));
  }
};
