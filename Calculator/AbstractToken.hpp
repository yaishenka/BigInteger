/**
 * @file AbstractToken.hpp
 * @author yaishenka
 * @date 16.10.2021
 */
#pragma once
#include <string>
#include <utility>

namespace calculator {
class AbstractToken {
 public:
  AbstractToken() = default;
  virtual ~AbstractToken() = default;
  explicit AbstractToken(std::string string_token): string_token_(std::move(string_token)) {}
  [[nodiscard]] const std::string& GetStringToken() const {return string_token_; }

  [[nodiscard]] virtual size_t GetPriority() const = 0;
 protected:
  std::string string_token_;
};
}
