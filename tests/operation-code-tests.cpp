#include "calculator-protocol/codes/operation-code.h"

#include <gtest/gtest.h>

using CalculatorProtocol::Codes::is_binary;
using CalculatorProtocol::Codes::is_commutative;
using CalculatorProtocol::Codes::is_unary;
using CalculatorProtocol::Codes::operation_code_from_string;
using CalculatorProtocol::Codes::OperationCode;
using CalculatorProtocol::Codes::to_string;

TEST(OperationCodeTests, ConvertsOperationCodeToString) {
  EXPECT_EQ(to_string(OperationCode::ADDITION), "addition");
  EXPECT_EQ(to_string(OperationCode::SUBTRACTION), "subtraction");
  EXPECT_EQ(to_string(OperationCode::MULTIPLICATION), "multiplication");
  EXPECT_EQ(to_string(OperationCode::DIVISION), "division");
  EXPECT_EQ(to_string(OperationCode::EXPONENTIATION), "exponentiation");
  EXPECT_EQ(to_string(OperationCode::FACTORIAL), "factorial");
}

TEST(OperationCodeTests, ConvertsStringToOperationCode) {
  EXPECT_EQ(operation_code_from_string("addition"), OperationCode::ADDITION);
  EXPECT_EQ(operation_code_from_string("add"), OperationCode::ADDITION);
  EXPECT_EQ(operation_code_from_string("subtraction"), OperationCode::SUBTRACTION);
  EXPECT_EQ(operation_code_from_string("mul"), OperationCode::MULTIPLICATION);
  EXPECT_EQ(operation_code_from_string("division"), OperationCode::DIVISION);
  EXPECT_EQ(operation_code_from_string("pow"), OperationCode::EXPONENTIATION);
  EXPECT_EQ(operation_code_from_string("fact"), OperationCode::FACTORIAL);
}

TEST(OperationCodeTests, UnknownOperationIsInvalidWireValue) {
  EXPECT_FALSE(operation_code_from_string("unknown").has_value());
  EXPECT_FALSE(operation_code_from_string("").has_value());
  EXPECT_FALSE(operation_code_from_string("+").has_value());
}

TEST(OperationCodeTests, DetectsCommutativeOperations) {
  EXPECT_TRUE(is_commutative(OperationCode::ADDITION));
  EXPECT_TRUE(is_commutative(OperationCode::MULTIPLICATION));
  EXPECT_FALSE(is_commutative(OperationCode::SUBTRACTION));
  EXPECT_FALSE(is_commutative(OperationCode::DIVISION));
  EXPECT_FALSE(is_commutative(OperationCode::EXPONENTIATION));
  EXPECT_FALSE(is_commutative(OperationCode::FACTORIAL));
}

TEST(OperationCodeTests, DetectsArityShape) {
  EXPECT_TRUE(is_unary(OperationCode::FACTORIAL));
  EXPECT_FALSE(is_unary(OperationCode::ADDITION));
  EXPECT_TRUE(is_binary(OperationCode::ADDITION));
  EXPECT_TRUE(is_binary(OperationCode::EXPONENTIATION));
  EXPECT_FALSE(is_binary(OperationCode::FACTORIAL));
}
