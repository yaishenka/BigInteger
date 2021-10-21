add_library(CalculatorLibrary SHARED Calculator.hpp OperatorToken.hpp OperandToken.hpp ExprInPolishNotation.hpp BracketToken.cpp)


install(
    TARGETS CalculatorLibrary
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
    LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/bin
)