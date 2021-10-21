/**
 * @file OperandToken.hpp
 * @author yaishenka
 * @date 19.10.2021
 */
#pragma once

#include <iostream>
#include <sstream>
#include "Utils.hpp"
#include "AbstractToken.hpp"

namespace calculator {

/**
 * @struct NotConstructible
 * @brief Exception is throwing when we can't construct value from string
 */
struct NotConstructible : std::exception {
  [[nodiscard]] const char *what() const noexcept override {
    return "We can't construct value from string!";
  }
};

template <typename T>
class OperandToken : public AbstractToken {
 public:
  using ValueType = T;

  explicit OperandToken(const std::string& string_token) : AbstractToken(string_token) {
    CalculateValue();
  }

  template <typename U = T, typename = std::enable_if_t<utils::HasOstreamOperatorV<U>>>
  explicit OperandToken(const T& value): value_(value) {
    std::stringstream is;
    is << value_;
    is >> string_token_;
  };

  [[nodiscard]] const T& GetValue() const { return value_; }

  [[nodiscard]] size_t GetPriority() const override {return 0; }
 private:
  template <typename U = T>
  std::enable_if_t<std::is_constructible_v<U, std::string>, void>
  CalculateValue() {
    value_ = T(GetStringToken());
  }

  template <typename U = T>
  std::enable_if_t<!std::is_constructible_v<U, std::string>
                       && utils::HasIstreamOperatorV<U>, void>
  CalculateValue() {
    std::stringstream is;
    is << GetStringToken();
    is >> value_;
    return;
  }

  template <typename U = T>
  std::enable_if_t<!std::is_constructible_v<U, std::string>
                       && !utils::HasIstreamOperatorV<U>, void>
  CalculateValue() {
    throw NotConstructible();
  }

  T value_;
};

}