/** @author yaishenka
    @date 21.10.2021 */
#include "BracketToken.hpp"

using namespace calculator;

BracketToken::BracketToken(const std::string& string_token) :
    AbstractToken(string_token) {}

size_t BracketToken::GetPriority() const  {
  return std::numeric_limits<size_t>::max();
}

size_t BracketToken::IsOpening() const {
  return GetStringToken() == "(";
}

bool BracketToken::IsBracket(char symbol) {
  return symbol == '(' || symbol == ')';
}