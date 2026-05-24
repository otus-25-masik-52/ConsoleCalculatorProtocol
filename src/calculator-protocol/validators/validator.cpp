#include "calculator-protocol/validators/validator.h"

#include "calculator-protocol/errors/protocol-error.h"
#include "calculator-protocol/version/protocol-version.h"

#include <string>

namespace CalculatorProtocol::Validators {

using Codes::OperationCode;
using Codes::StatusCode;
using Errors::ProtocolError;
using std::string_literals::operator""s;

void Validator::validate_request(const Models::CalculationRequest& request) {
  if (request.protocol_version() != Version::current) {
    throw ProtocolError{StatusCode::UNSUPPORTED_PROTOCOL_VERSION, "unsupported protocol version", "protocol_version"s};
  }

  if (request.request_id().empty()) {
    throw ProtocolError{StatusCode::INVALID_REQUEST_ID, "request_id must not be empty", "request_id"s};
  }

  if (request.operation() == OperationCode::UNKNOWN) {
    throw ProtocolError{StatusCode::INVALID_OPERATION, "operation is unknown", "operation"s};
  }

  if (request.operands().size() > max_operands_count) {
    throw ProtocolError{StatusCode::INVALID_OPERANDS, "too many operands", "operands"s};
  }

  if (const auto& timeout = request.request_options().timeout_ms(); timeout.has_value()) {
    if (*timeout < min_timeout_ms || *timeout > max_timeout_ms) {
      throw ProtocolError{StatusCode::TIMEOUT_OUT_OF_RANGE, "timeout_ms is out of allowed range",
                          "options.timeout_ms"s};
    }
  }

  if (const auto& client_info = request.client_info(); client_info.has_value()) {
    if (client_info->name().empty() || client_info->version().empty()) {
      throw ProtocolError{StatusCode::INVALID_CLIENT_INFO, "client name and version must not be empty", "client"s};
    }
  }

  validate_operands(request);
}

void Validator::validate_response(const Models::CalculationResponse& response) {
  if (response.protocol_version() != Version::current) {
    throw ProtocolError{StatusCode::UNSUPPORTED_PROTOCOL_VERSION, "unsupported response protocol version",
                        "protocol_version"s};
  }

  if (response.request_id().empty()) {
    throw ProtocolError{StatusCode::INVALID_REQUEST_ID, "response request_id must not be empty", "request_id"s};
  }

  if (response.status_code() == StatusCode::OK) {
    if (!response.result_info().has_value()) {
      throw ProtocolError{StatusCode::MALFORMED_MESSAGE, "successful response must contain result", "result"s};
    }
    if (response.error_info().has_value()) {
      throw ProtocolError{StatusCode::MALFORMED_MESSAGE, "successful response must not contain error", "error"s};
    }
    return;
  }

  if (response.result_info().has_value()) {
    throw ProtocolError{StatusCode::MALFORMED_MESSAGE, "error response must not contain result", "result"s};
  }

  if (!response.error_info().has_value()) {
    throw ProtocolError{StatusCode::MALFORMED_MESSAGE, "error response must contain error", "error"s};
  }
}

void Validator::validate_operands(const Models::CalculationRequest& request) {
  const auto count = request.operands().size();

  switch (request.operation()) {
  case OperationCode::ADDITION:
  case OperationCode::SUBTRACTION:
  case OperationCode::MULTIPLICATION:
  case OperationCode::DIVISION:
  case OperationCode::EXPONENTIATION:
    if (count != 2) {
      throw ProtocolError{StatusCode::OPERANDS_COUNT_MISMATCH, "operation requires exactly two operands", "operands"s};
    }
    break;
  case OperationCode::FACTORIAL:
    if (count != 1) {
      throw ProtocolError{StatusCode::OPERANDS_COUNT_MISMATCH, "factorial requires exactly one operand", "operands"s};
    }
    if (request.operands().front() < 0) {
      throw ProtocolError{StatusCode::FACTORIAL_OF_NEGATIVE_NUMBER, "factorial operand must be non-negative",
                          "operands[0]"s};
    }
    break;
  case OperationCode::UNKNOWN:
  default:
    throw ProtocolError{StatusCode::INVALID_OPERATION, "operation is unknown", "operation"s};
  }
}

} // namespace CalculatorProtocol::Validators
