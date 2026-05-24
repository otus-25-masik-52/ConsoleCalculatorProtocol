#include "calculator-protocol/codes/status-code.h"

#include <gtest/gtest.h>

using CalculatorProtocol::Codes::is_error;
using CalculatorProtocol::Codes::is_success;
using CalculatorProtocol::Codes::status_code_from_numeric;
using CalculatorProtocol::Codes::status_code_from_string;
using CalculatorProtocol::Codes::StatusCode;
using CalculatorProtocol::Codes::to_numeric_code;
using CalculatorProtocol::Codes::to_string;

TEST(StatusCodeTests, NumericCodesAreStable) {
  EXPECT_EQ(to_numeric_code(StatusCode::OK), 0);
  EXPECT_EQ(to_numeric_code(StatusCode::INVALID_OPERATION), 1101);
  EXPECT_EQ(to_numeric_code(StatusCode::DIVISION_BY_ZERO), 1204);
  EXPECT_EQ(to_numeric_code(StatusCode::INVALID_JSON), 3101);
  EXPECT_EQ(to_numeric_code(StatusCode::STORAGE_ERROR), 4103);
  EXPECT_EQ(to_numeric_code(StatusCode::INTERNAL_ERROR), 9101);
}

TEST(StatusCodeTests, ConvertsStatusCodeToString) {
  EXPECT_EQ(to_string(StatusCode::OK), "OK");
  EXPECT_EQ(to_string(StatusCode::DIVISION_BY_ZERO), "DIVISION_BY_ZERO");
  EXPECT_EQ(to_string(StatusCode::UNSUPPORTED_PROTOCOL_VERSION), "UNSUPPORTED_PROTOCOL_VERSION");
  EXPECT_EQ(to_string(StatusCode::UNKNOWN_ERROR), "UNKNOWN_ERROR");
}

TEST(StatusCodeTests, ConvertsStringToStatusCode) {
  EXPECT_EQ(status_code_from_string("OK"), StatusCode::OK);
  EXPECT_EQ(status_code_from_string("DIVISION_BY_ZERO"), StatusCode::DIVISION_BY_ZERO);
  EXPECT_EQ(status_code_from_string("STORAGE_ERROR"), StatusCode::STORAGE_ERROR);
  EXPECT_FALSE(status_code_from_string("NO_SUCH_STATUS").has_value());
}

TEST(StatusCodeTests, ConvertsNumericToStatusCode) {
  EXPECT_EQ(status_code_from_numeric(0), StatusCode::OK);
  EXPECT_EQ(status_code_from_numeric(1204), StatusCode::DIVISION_BY_ZERO);
  EXPECT_EQ(status_code_from_numeric(4103), StatusCode::STORAGE_ERROR);
  EXPECT_FALSE(status_code_from_numeric(7777).has_value());
}

TEST(StatusCodeTests, KnowsSuccessAndError) {
  EXPECT_TRUE(is_success(StatusCode::OK));
  EXPECT_FALSE(is_error(StatusCode::OK));
  EXPECT_FALSE(is_success(StatusCode::INTERNAL_ERROR));
  EXPECT_TRUE(is_error(StatusCode::INTERNAL_ERROR));
}
