/**
 * @file OperatorToken.hpp
 * @author yaishenka
 * @date 16.10.2021
 */
#pragma once
#include <functional>
#include <type_traits>
#include <unordered_map>

#include "AbstractToken.hpp"
#include "OperandToken.hpp"

namespace calculator {

/**
 * @struct UnsupportedOperator
 * @brief Exception is throwing when we trying to calculate unsupported operator
 */
struct UnsupportedOperator : std::exception {
  [[nodiscard]] const char* what() const noexcept override {
    return "Find unsupported operator!";
  }
};

/*
 * @class OperatorToken
 * @brief Class for contain operators tokens
 */
template <typename T, bool is_binary>
class OperatorToken : public AbstractToken {
 public:
  using ValueType = typename OperandToken<T>::ValueType;
  using BinaryOperatorMapType = const std::unordered_map<
      std::string,
      std::function<ValueType(const ValueType&, const ValueType&)>>;

  using UnaryOperatorMapType =
      const std::unordered_map<std::string,
                               std::function<ValueType(const ValueType&)>>;

  using OperatorToPriorityMap = const std::unordered_map<std::string, size_t>;

  explicit OperatorToken(const std::string& string_token)
      : AbstractToken(string_token) {}

  [[nodiscard]] static bool IsOperator(const std::string& string_token) {
    return operator_to_priority_.find(string_token) !=
           operator_to_priority_.end();
  }

  [[nodiscard]] bool IsBinary() const { return is_binary; }



  [[nodiscard]] size_t GetPriority() const override {
    if (!IsBinary()) {
      return max_priority_ + 1;
    }

    if (operator_to_priority_.find(GetStringToken()) ==
        operator_to_priority_.end()) {
      throw UnsupportedOperator();
    }

    return operator_to_priority_.at(GetStringToken());
  }

  template <typename U = T>
  std::enable_if_t<is_binary, std::shared_ptr<OperandToken<U>>>
  Calculate(
      std::shared_ptr<OperandToken<U>> first_operand,
      std::shared_ptr<OperandToken<U>> second_operand) const {
    if (binary_operators_map_.find(GetStringToken()) ==
        binary_operators_map_.end()) {
      throw UnsupportedOperator();
    }

    return std::make_shared<OperandToken<U>>(binary_operators_map_.at(GetStringToken())(
        first_operand->GetValue(), second_operand->GetValue()));
  }

  template <typename U = T>
  std::enable_if_t<!is_binary, std::shared_ptr<OperandToken<U>>>
  Calculate(std::shared_ptr<OperandToken<U>> operand) const {
    if (unary_operators_map_.find(GetStringToken()) ==
        unary_operators_map_.end()) {
      throw UnsupportedOperator();
    }

    return std::make_shared<OperandToken<U>>(unary_operators_map_.at(GetStringToken())(operand->GetValue()));
  }

 private:
  static BinaryOperatorMapType binary_operators_map_;
  static UnaryOperatorMapType unary_operators_map_;
  static OperatorToPriorityMap operator_to_priority_;
  static const size_t max_priority_;
};

template <typename T, bool is_binary>
typename OperatorToken<T, is_binary>::BinaryOperatorMapType
    OperatorToken<T, is_binary>::binary_operators_map_ = {
        {"+", [](const T& first, const T& second) { return first + second; }},
        {"-", [](const T& first, const T& second) { return first - second; }},
        {"*", [](const T& first, const T& second) { return first * second; }},
        {"/", [](const T& first, const T& second) { return first / second; }},
        {"%", [](const T& first, const T& second) { return first % second; }}};

template <typename T, bool is_binary>
typename OperatorToken<T, is_binary>::UnaryOperatorMapType
    OperatorToken<T, is_binary>::unary_operators_map_ = {
        {"+", [](const T& value) { return value; }},
        {"-", [](const T& value) { return -value; }}};

template <typename T, bool is_binary>
typename OperatorToken<T, is_binary>::OperatorToPriorityMap
    OperatorToken<T, is_binary>::operator_to_priority_ = {
        {"+", 1}, {"-", 1}, {"%", 1}, {"*", 2}, {"/", 2},
};

template <typename T, bool is_binary>
const size_t OperatorToken<T, is_binary>::max_priority_ = 2;

}  // namespace calculator