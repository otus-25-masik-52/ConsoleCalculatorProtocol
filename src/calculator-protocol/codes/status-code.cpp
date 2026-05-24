#include "calculator-protocol/codes/status-code.h"

#include <array>
#include <string_view>

namespace CalculatorProtocol::Codes {

namespace {

struct StatusCodeEntry {
  StatusCode code;
  std::string_view name;
};

constexpr auto status_code_table = std::to_array<StatusCodeEntry>({
    StatusCodeEntry{.code=StatusCode::OK, .name="OK"},

    StatusCodeEntry{.code=StatusCode::INVALID_OPERATION, .name="INVALID_OPERATION"},
    StatusCodeEntry{.code=StatusCode::UNSUPPORTED_OPERATION, .name="UNSUPPORTED_OPERATION"},
    StatusCodeEntry{.code=StatusCode::OPERATION_DISABLED, .name="OPERATION_DISABLED"},

    StatusCodeEntry{.code=StatusCode::INVALID_OPERANDS, .name="INVALID_OPERANDS"},
    StatusCodeEntry{.code=StatusCode::OPERANDS_COUNT_MISMATCH, .name="OPERANDS_COUNT_MISMATCH"},
    StatusCodeEntry{.code=StatusCode::OPERAND_OUT_OF_RANGE, .name="OPERAND_OUT_OF_RANGE"},
    StatusCodeEntry{.code=StatusCode::DIVISION_BY_ZERO, .name="DIVISION_BY_ZERO"},
    StatusCodeEntry{.code=StatusCode::FACTORIAL_OF_NEGATIVE_NUMBER, .name="FACTORIAL_OF_NEGATIVE_NUMBER"},
    StatusCodeEntry{.code=StatusCode::NUMERIC_OVERFLOW, .name="NUMERIC_OVERFLOW"},
    StatusCodeEntry{.code=StatusCode::RESULT_NOT_REPRESENTABLE, .name="RESULT_NOT_REPRESENTABLE"},

    StatusCodeEntry{.code=StatusCode::INVALID_REQUEST_OPTIONS, .name="INVALID_REQUEST_OPTIONS"},
    StatusCodeEntry{.code=StatusCode::TIMEOUT_OUT_OF_RANGE, .name="TIMEOUT_OUT_OF_RANGE"},
    StatusCodeEntry{.code=StatusCode::INVALID_CLIENT_INFO, .name="INVALID_CLIENT_INFO"},
    StatusCodeEntry{.code=StatusCode::INVALID_REQUEST_ID, .name="INVALID_REQUEST_ID"},

    StatusCodeEntry{.code=StatusCode::CLIENT_CONNECTION_FAILED, .name="CLIENT_CONNECTION_FAILED"},
    StatusCodeEntry{.code=StatusCode::CLIENT_TIMEOUT, .name="CLIENT_TIMEOUT"},
    StatusCodeEntry{.code=StatusCode::CLIENT_CANCELLED, .name="CLIENT_CANCELLED"},
    StatusCodeEntry{.code=StatusCode::CLIENT_CONFIGURATION_ERROR, .name="CLIENT_CONFIGURATION_ERROR"},
    StatusCodeEntry{.code=StatusCode::CLIENT_SERIALIZATION_ERROR, .name="CLIENT_SERIALIZATION_ERROR"},
    StatusCodeEntry{.code=StatusCode::CLIENT_RESPONSE_PARSE_ERROR, .name="CLIENT_RESPONSE_PARSE_ERROR"},

    StatusCodeEntry{.code=StatusCode::INVALID_JSON, .name="INVALID_JSON"},
    StatusCodeEntry{.code=StatusCode::MALFORMED_MESSAGE, .name="MALFORMED_MESSAGE"},
    StatusCodeEntry{.code=StatusCode::EMPTY_MESSAGE, .name="EMPTY_MESSAGE"},

    StatusCodeEntry{.code=StatusCode::MISSING_REQUIRED_FIELD, .name="MISSING_REQUIRED_FIELD"},
    StatusCodeEntry{.code=StatusCode::INVALID_FIELD_TYPE, .name="INVALID_FIELD_TYPE"},
    StatusCodeEntry{.code=StatusCode::INVALID_FIELD_VALUE, .name="INVALID_FIELD_VALUE"},

    StatusCodeEntry{.code=StatusCode::UNSUPPORTED_PROTOCOL_VERSION, .name="UNSUPPORTED_PROTOCOL_VERSION"},
    StatusCodeEntry{.code=StatusCode::INCOMPATIBLE_PROTOCOL_VERSION, .name="INCOMPATIBLE_PROTOCOL_VERSION"},

    StatusCodeEntry{.code=StatusCode::MESSAGE_TOO_LARGE, .name="MESSAGE_TOO_LARGE"},
    StatusCodeEntry{.code=StatusCode::INVALID_MESSAGE_FRAMING, .name="INVALID_MESSAGE_FRAMING"},

    StatusCodeEntry{.code=StatusCode::UNSUPPORTED_TRANSPORT, .name="UNSUPPORTED_TRANSPORT"},
    StatusCodeEntry{.code=StatusCode::UNSUPPORTED_CONTENT_TYPE, .name="UNSUPPORTED_CONTENT_TYPE"},
    StatusCodeEntry{.code=StatusCode::CORRELATION_ID_MISMATCH, .name="CORRELATION_ID_MISMATCH"},

    StatusCodeEntry{.code=StatusCode::STORAGE_UNAVAILABLE, .name="STORAGE_UNAVAILABLE"},
    StatusCodeEntry{.code=StatusCode::STORAGE_CONNECTION_FAILED, .name="STORAGE_CONNECTION_FAILED"},
    StatusCodeEntry{.code=StatusCode::STORAGE_ERROR, .name="STORAGE_ERROR"},
    StatusCodeEntry{.code=StatusCode::CACHE_ERROR, .name="CACHE_ERROR"},

    StatusCodeEntry{.code=StatusCode::CALCULATION_ERROR, .name="CALCULATION_ERROR"},
    StatusCodeEntry{.code=StatusCode::CALCULATOR_LIBRARY_ERROR, .name="CALCULATOR_LIBRARY_ERROR"},
    StatusCodeEntry{.code=StatusCode::CALCULATION_TIMEOUT, .name="CALCULATION_TIMEOUT"},

    StatusCodeEntry{.code=StatusCode::SERVER_CONNECTION_CLOSED, .name="SERVER_CONNECTION_CLOSED"},
    StatusCodeEntry{.code=StatusCode::SERVER_SESSION_ERROR, .name="SERVER_SESSION_ERROR"},

    StatusCodeEntry{.code=StatusCode::SERVER_UNAVAILABLE, .name="SERVER_UNAVAILABLE"},
    StatusCodeEntry{.code=StatusCode::SERVICE_SHUTTING_DOWN, .name="SERVICE_SHUTTING_DOWN"},
    StatusCodeEntry{.code=StatusCode::SERVICE_NOT_READY, .name="SERVICE_NOT_READY"},
    StatusCodeEntry{.code=StatusCode::RESOURCE_EXHAUSTED, .name="RESOURCE_EXHAUSTED"},

    StatusCodeEntry{.code=StatusCode::INTERNAL_ERROR, .name="INTERNAL_ERROR"},
    StatusCodeEntry{.code=StatusCode::UNHANDLED_EXCEPTION, .name="UNHANDLED_EXCEPTION"},
    StatusCodeEntry{.code=StatusCode::INVARIANT_VIOLATION, .name="INVARIANT_VIOLATION"},

    StatusCodeEntry{.code=StatusCode::UNKNOWN_ERROR, .name="UNKNOWN_ERROR"},
    StatusCodeEntry{.code=StatusCode::NOT_IMPLEMENTED, .name="NOT_IMPLEMENTED"},
});

} // namespace

std::int32_t to_numeric_code(const StatusCode code) noexcept {
  return static_cast<std::int32_t>(code);
}

std::string to_string(const StatusCode code) {
  for (const auto& [e_code, e_name] : status_code_table) {
    if (e_code == code) {
      return std::string{e_name};
    }
  }

  return "UNKNOWN_ERROR";
}

std::optional<StatusCode> status_code_from_string(const std::string_view value) noexcept {
  for (const auto& [e_code, e_name] : status_code_table) {
    if (e_name == value) {
      return e_code;
    }
  }

  return std::nullopt;
}

std::optional<StatusCode> status_code_from_numeric(const std::int32_t value) noexcept {
  for (const auto& [e_code, e_name] : status_code_table) {
    if (to_numeric_code(e_code) == value) {
      return e_code;
    }
  }

  return std::nullopt;
}

bool is_success(const StatusCode code) noexcept {
  return code == StatusCode::OK;
}

bool is_error(const StatusCode code) noexcept {
  return !is_success(code);
}

} // namespace CalculatorProtocol::Codes
