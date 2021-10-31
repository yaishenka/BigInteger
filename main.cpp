#include <iostream>
#include "BigInteger.hpp"
#include "Calculator.hpp"


int main() {
  std::string expr;
  std::getline(std::cin, expr);
  std::cout << calculator::Calculator<int>::CalculateExpr(expr) << std::endl;
}
