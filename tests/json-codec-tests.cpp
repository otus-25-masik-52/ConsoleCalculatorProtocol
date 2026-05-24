#include "calculator-protocol/codes/operation-code.h"
#include "calculator-protocol/codes/status-code.h"
#include "calculator-protocol/errors/protocol-error.h"
#include "calculator-protocol/formats/json-codec.h"
#include "calculator-protocol/models/calculation-response.h"
#include "calculator-protocol/types/result-info.h"

#include <gtest/gtest.h>

using CalculatorProtocol::Codes::OperationCode;
using CalculatorProtocol::Codes::StatusCode;
using CalculatorProtocol::Errors::ProtocolError;
using CalculatorProtocol::Formats::JsonCodec;
using CalculatorProtocol::Models::CalculationResponse;
using CalculatorProtocol::Types::ResultInfo;

TEST(JsonCodecTests, ParsesValidRequest) {
  const auto request = JsonCodec::parse_request(
      R"({"protocol_version":1,"request_id":"req-1","operation":"addition","operands":[1,2]})");

  EXPECT_EQ(request.request_id(), "req-1");
  EXPECT_EQ(request.operation(), OperationCode::ADDITION);
  ASSERT_EQ(request.operands().size(), 2U);
  EXPECT_EQ(request.operands()[0], 1);
  EXPECT_EQ(request.operands()[1], 2);
}

TEST(JsonCodecTests, RejectsInvalidJson) {
  try {
    (void)JsonCodec::parse_request("{not json");
    FAIL() << "Expected ProtocolError";
  } catch (const ProtocolError& error) {
    EXPECT_EQ(error.status_code(), StatusCode::INVALID_JSON);
  }
}

TEST(JsonCodecTests, SerializesSuccessfulResponse) {
  auto response = CalculationResponse::success("req-1", ResultInfo{3});
  const auto json = JsonCodec::serialize_response(response);

  EXPECT_NE(json.find("req-1"), std::string::npos);
  EXPECT_NE(json.find("OK"), std::string::npos);
  EXPECT_NE(json.find('3'), std::string::npos);
}

TEST(JsonCodecTests, ParsesSuccessfulResponse) {
  const auto response = JsonCodec::parse_response(
      R"({"protocol_version":1,"request_id":"req-1","status":{"code":0,"name":"OK"},"result":{"value":3},"error":null})");

  EXPECT_EQ(response.status_code(), StatusCode::OK);
  ASSERT_TRUE(response.result_info().has_value());
  EXPECT_EQ(response.result_info()->value(), 3);
}
