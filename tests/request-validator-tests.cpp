#include "calculator-protocol/errors/protocol-error.h"
#include "calculator-protocol/models/calculation-request.h"
#include "calculator-protocol/validators/validator.h"

#include <gtest/gtest.h>

using CalculatorProtocol::Codes::OperationCode;
using CalculatorProtocol::Codes::StatusCode;
using CalculatorProtocol::Errors::ProtocolError;
using CalculatorProtocol::Models::CalculationRequest;
using CalculatorProtocol::Types::RequestOptions;
using CalculatorProtocol::Validators::Validator;

namespace {
CalculationRequest valid_request() {
  CalculationRequest request;
  request.set_request_id("req-1");
  request.set_operation(OperationCode::ADDITION);
  request.set_operands({1, 2});
  return request;
}
} // namespace

TEST(RequestValidatorTests, AcceptsValidRequest) {
  EXPECT_NO_THROW(Validator::validate_request(valid_request()));
}

TEST(RequestValidatorTests, RejectsEmptyRequestId) {
  auto request = valid_request();
  request.set_request_id("");

  try {
    Validator::validate_request(request);
    FAIL() << "Expected ProtocolError";
  } catch (const ProtocolError& error) {
    EXPECT_EQ(error.status_code(), StatusCode::INVALID_REQUEST_ID);
  }
}

TEST(RequestValidatorTests, RejectsUnsupportedProtocolVersion) {
  auto request = valid_request();
  request.set_protocol_version(999);

  try {
    Validator::validate_request(request);
    FAIL() << "Expected ProtocolError";
  } catch (const ProtocolError& error) {
    EXPECT_EQ(error.status_code(), StatusCode::UNSUPPORTED_PROTOCOL_VERSION);
  }
}

TEST(RequestValidatorTests, RejectsWrongOperandsCount) {
  auto request = valid_request();
  request.set_operands({1});

  try {
    Validator::validate_request(request);
    FAIL() << "Expected ProtocolError";
  } catch (const ProtocolError& error) {
    EXPECT_EQ(error.status_code(), StatusCode::OPERANDS_COUNT_MISMATCH);
  }
}

TEST(RequestValidatorTests, RejectsNegativeFactorial) {
  auto request = valid_request();
  request.set_operation(OperationCode::FACTORIAL);
  request.set_operands({-1});

  try {
    Validator::validate_request(request);
    FAIL() << "Expected ProtocolError";
  } catch (const ProtocolError& error) {
    EXPECT_EQ(error.status_code(), StatusCode::FACTORIAL_OF_NEGATIVE_NUMBER);
  }
}

TEST(RequestValidatorTests, RejectsTimeoutOutOfRange) {
  auto request = valid_request();
  RequestOptions options;
  options.set_timeout_ms(0);
  request.set_request_options(options);

  try {
    Validator::validate_request(request);
    FAIL() << "Expected ProtocolError";
  } catch (const ProtocolError& error) {
    EXPECT_EQ(error.status_code(), StatusCode::TIMEOUT_OUT_OF_RANGE);
  }
}
