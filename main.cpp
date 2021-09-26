#include <iostream>
#include "BigInteger.hpp"

int main() {
  BigInteger a;
  std::string op;
  BigInteger b;

  std::cin >> a >> op >> b;

  if (op == "+") {
    std::cout << (a + b);
  } else if (op == "-") {
    std::cout << (a - b);
  } else if (op == "<") {
    std::cout << (a < b);
  } else if (op == "<=") {
    std::cout << (a <= b);
  } else if (op == ">") {
    std::cout << (a > b);
  } else if (op == ">=") {
    std::cout << (a >= b);
  } else if (op == "==") {
    std::cout << (a == b);
  } else if (op == "!=") {
    std::cout << (a != b);
  } else if (op == "*") {
    std::cout << (a * b);
  } else if (op == "/") {
    std::cout << (a / b);
  } else if (op == "%") {
    std::cout << (a % b);
  }
}
