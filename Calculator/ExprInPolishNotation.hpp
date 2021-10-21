/**
 * @file ExprInPolishNotation.hpp
 * @author yaishenka
 * @date 19.10.2021
 */
#pragma once
#include <vector>
#include <stack>
#include <cctype>
#include "BracketToken.hpp"
#include "OperatorToken.hpp"

namespace calculator {

/**
 * @struct InvalidExpr
 */
struct InvalidExpr : std::exception {
  [[nodiscard]] const char *what() const noexcept override {
    return "Invalid expression!";
  }
};

template <typename T>
class ExprInPolishNotation {
 public:
  using OperandTokenType = OperandToken<T>;
  using ValueType = typename OperandTokenType::ValueType;
  using BinaryOperatorType = OperatorToken<T, true>;
  using UnaryOperatorType = OperatorToken<T, false>;

  explicit ExprInPolishNotation(const std::string& expr) {
    ParseExpr(expr);
  }

  [[nodiscard]] std::shared_ptr<std::vector<std::shared_ptr<AbstractToken>>> GetTokens() const {
    return tokens_;
  }
 private:
  void ProcessOperatorToken(const std::shared_ptr<AbstractToken>& token);
  void ProcessClosingBracket();
  void ParseExpr(const std::string& expr);
  std::shared_ptr<std::vector<std::shared_ptr<AbstractToken>>> tokens_;
  std::stack<std::shared_ptr<AbstractToken>> operators_stack_;
};

template <typename T>
void ExprInPolishNotation<T>::ProcessOperatorToken(const std::shared_ptr<
    AbstractToken>& token) {
  while (!operators_stack_.empty()) {
    auto prev_token = operators_stack_.top();
    {
      auto bracket_token =
          std::dynamic_pointer_cast<BracketToken>(prev_token);

      if (bracket_token != nullptr) {
        if (bracket_token->IsOpening()) {
          break;
        }

        throw InvalidExpr();
      }
    }

    if (prev_token->GetPriority() < token->GetPriority()) {
      break;
    }

    tokens_->push_back(prev_token);
    operators_stack_.pop();
  }

  operators_stack_.push(token);
}

template <typename T>
void ExprInPolishNotation<T>::ProcessClosingBracket() {
  while (!operators_stack_.empty()) {
    auto current_token = operators_stack_.top();
    {
      auto bracket_token =
          std::dynamic_pointer_cast<BracketToken>(current_token);
      if (bracket_token != nullptr) {
        if (bracket_token->IsOpening()) {
          operators_stack_.pop();
          return;
        }
        throw InvalidExpr();
      }
    }

    tokens_->push_back(current_token);
    operators_stack_.pop();
  }
}

template <typename T>
void ExprInPolishNotation<T>::ParseExpr(const std::string& expr) {
  operators_stack_ = std::stack<std::shared_ptr<AbstractToken>>();
  tokens_ = std::make_shared<std::vector<std::shared_ptr<AbstractToken>>>();

  bool can_be_unary = true;
  for (size_t current_pos = 0; current_pos < expr.size(); ++current_pos) {
    char current_symbol = expr[current_pos];
    std::string current_string_token;
    current_string_token += current_symbol;

    if (std::isspace(current_symbol)) {
      continue;
    }

    if (BinaryOperatorType::IsOperator(current_string_token)) {
      std::shared_ptr<AbstractToken> token;

      if (can_be_unary) {
        token = std::make_shared<UnaryOperatorType>(current_string_token);
      } else {
        token = std::make_shared<BinaryOperatorType>(current_string_token);
      }

      ProcessOperatorToken(token);
      can_be_unary = true;
      continue;
    }

    if (BracketToken::IsBracket(current_symbol)) {
      auto bracket_token = std::make_shared<BracketToken>(current_string_token);
      if (bracket_token->IsOpening()) {
        can_be_unary = true;
        operators_stack_.push(bracket_token);
        continue;
      }

      can_be_unary = false;
      ProcessClosingBracket();
      continue;
    }

    if (!std::isdigit(current_symbol)) {
      throw InvalidExpr();
    }

    std::string number_token;

    while (current_pos < expr.size()) {
      current_symbol = expr[current_pos];
      if (!std::isdigit(current_symbol)) {
        break;
      }

      number_token += current_symbol;
      current_pos += 1;
    }
    current_pos -= 1;

    auto token = std::make_shared<OperandToken<T>>(number_token);
    tokens_->push_back(token);

    can_be_unary = false;
  }

  while (!operators_stack_.empty()) {
    auto current_token = operators_stack_.top();
    tokens_->push_back(current_token);
    operators_stack_.pop();
  }
}
}

