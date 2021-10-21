/**
 * @file Calculator.hpp
 * @author yaishenka
 * @date 16.10.2021
 */
#pragma once
#include "ExprInPolishNotation.hpp"

namespace calculator {
template <typename T>
class Calculator {
 public:
  using OperandTokenType = OperandToken<T>;
  using ValueType = typename OperandTokenType::ValueType;
  using BinaryOperatorType = OperatorToken<T, true>;
  using UnaryOperatorType = OperatorToken<T, false>;

  static ValueType CalculateExpr(const std::string& expression);
};

template <typename T>
typename Calculator<T>::ValueType Calculator<T>::CalculateExpr(const std::string& expression) {
  ExprInPolishNotation<T> expr(expression);
  auto tokens = expr.GetTokens();
  std::stack<std::shared_ptr<AbstractToken>> calculating_stack;

  for (const auto& token : *(tokens.get())) {
    {
      auto operand_token = std::dynamic_pointer_cast<OperandTokenType>(token);
      if (operand_token != nullptr) {
        calculating_stack.push(operand_token);
        continue;
      }
    }

    {
      auto binary_operator_token = std::dynamic_pointer_cast<BinaryOperatorType>(token);
      if (binary_operator_token != nullptr) {
        auto second_operand = std::dynamic_pointer_cast<OperandTokenType>(calculating_stack.top());
        calculating_stack.pop();
        auto first_operand = std::dynamic_pointer_cast<OperandTokenType>(calculating_stack.top());
        calculating_stack.pop();
        auto result = binary_operator_token->Calculate(first_operand, second_operand);
        calculating_stack.push(result);
        continue;
      }
    }

    {
      auto unary_operator_token = std::dynamic_pointer_cast<UnaryOperatorType>(token);
      if (unary_operator_token != nullptr) {
        auto operand = std::dynamic_pointer_cast<OperandTokenType>(calculating_stack.top());
        calculating_stack.pop();
        auto result = unary_operator_token->Calculate(operand);
        calculating_stack.push(result);
        continue;
      }
    }

    throw InvalidExpr();
  }

  if (calculating_stack.empty() || calculating_stack.size() > 1) {
    throw InvalidExpr();
  }

  auto result = std::dynamic_pointer_cast<OperandTokenType>(calculating_stack.top());
  calculating_stack.pop();

  return result->GetValue();
}
}