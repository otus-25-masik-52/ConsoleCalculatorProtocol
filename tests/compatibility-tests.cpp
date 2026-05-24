#include "calculator-protocol/codes/status-code.h"
#include "calculator-protocol/errors/protocol-error.h"
#include "calculator-protocol/formats/json-codec.h"

#include <gtest/gtest.h>

using CalculatorProtocol::Codes::StatusCode;
using CalculatorProtocol::Errors::ProtocolError;
using CalculatorProtocol::Formats::JsonCodec;

TEST(CompatibilityTests, IgnoresUnknownOptionalFields) {
  EXPECT_NO_THROW((void)JsonCodec::parse_request(
      R"({"protocol_version":1,"request_id":"req-1","operation":"addition","operands":[1,2],"future_field":42})"));
}

TEST(CompatibilityTests, RejectsMissingRequiredField) {
  try {
    (void)JsonCodec::parse_request(R"({"protocol_version":1,"request_id":"req-1","operands":[1,2]})");
    FAIL() << "Expected ProtocolError";
  } catch (const ProtocolError& error) {
    EXPECT_EQ(error.status_code(), StatusCode::MISSING_REQUIRED_FIELD);
  }
}

TEST(CompatibilityTests, RejectsUnsupportedProtocolVersion) {
  try {
    (void)JsonCodec::parse_request(
        R"({"protocol_version":999,"request_id":"req-1","operation":"addition","operands":[1,2]})");
    FAIL() << "Expected ProtocolError";
  } catch (const ProtocolError& error) {
    EXPECT_EQ(error.status_code(), StatusCode::UNSUPPORTED_PROTOCOL_VERSION);
  }
}
