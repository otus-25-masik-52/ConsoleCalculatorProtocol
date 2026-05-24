#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace CalculatorProtocol::Codes {

/**
 * Four-digit public protocol status code.
 *
 * Code shape: ABCD
 *   A — error domain/source
 *   B — subsystem
 *   C-D — subsystem-local error number
 *
 * 0xxx — success
 * 1xxx — user/input/domain errors
 * 2xxx — client-side/local errors
 * 3xxx — protocol/contract errors
 * 4xxx — server/runtime errors
 * 9xxx — internal/unknown/reserved errors
 */
enum class StatusCode : std::uint16_t {
  OK = 0,

  // 11xx — operation errors
  INVALID_OPERATION = 1101,
  UNSUPPORTED_OPERATION = 1102,
  OPERATION_DISABLED = 1103,

  // 12xx — operands/value errors
  INVALID_OPERANDS = 1201,
  OPERANDS_COUNT_MISMATCH = 1202,
  OPERAND_OUT_OF_RANGE = 1203,
  DIVISION_BY_ZERO = 1204,
  FACTORIAL_OF_NEGATIVE_NUMBER = 1205,
  NUMERIC_OVERFLOW = 1206,
  RESULT_NOT_REPRESENTABLE = 1207,

  // 13xx — request options / user metadata errors
  INVALID_REQUEST_OPTIONS = 1301,
  TIMEOUT_OUT_OF_RANGE = 1302,
  INVALID_CLIENT_INFO = 1303,
  INVALID_REQUEST_ID = 1304,

  // 21xx — client connection errors
  CLIENT_CONNECTION_FAILED = 2101,

  // 22xx — client timeout/cancellation errors
  CLIENT_TIMEOUT = 2201,
  CLIENT_CANCELLED = 2202,

  // 23xx — client configuration / local processing errors
  CLIENT_CONFIGURATION_ERROR = 2301,
  CLIENT_SERIALIZATION_ERROR = 2302,
  CLIENT_RESPONSE_PARSE_ERROR = 2303,

  // 31xx — wire format errors
  INVALID_JSON = 3101,
  MALFORMED_MESSAGE = 3102,
  EMPTY_MESSAGE = 3103,

  // 32xx — schema / field errors
  MISSING_REQUIRED_FIELD = 3201,
  INVALID_FIELD_TYPE = 3202,
  INVALID_FIELD_VALUE = 3203,

  // 33xx — protocol version / compatibility errors
  UNSUPPORTED_PROTOCOL_VERSION = 3301,
  INCOMPATIBLE_PROTOCOL_VERSION = 3302,

  // 34xx — framing / message boundary / size errors
  MESSAGE_TOO_LARGE = 3401,
  INVALID_MESSAGE_FRAMING = 3402,

  // 35xx — transport contract errors
  UNSUPPORTED_TRANSPORT = 3501,
  UNSUPPORTED_CONTENT_TYPE = 3502,
  CORRELATION_ID_MISMATCH = 3503,

  // 41xx — storage errors
  STORAGE_UNAVAILABLE = 4101,
  STORAGE_CONNECTION_FAILED = 4102,
  STORAGE_ERROR = 4103,
  CACHE_ERROR = 4104,

  // 42xx — calculation execution errors
  CALCULATION_ERROR = 4201,
  CALCULATOR_LIBRARY_ERROR = 4202,
  CALCULATION_TIMEOUT = 4203,

  // 43xx — server communication/session errors
  SERVER_CONNECTION_CLOSED = 4301,
  SERVER_SESSION_ERROR = 4302,

  // 44xx — service lifecycle / resource errors
  SERVER_UNAVAILABLE = 4401,
  SERVICE_SHUTTING_DOWN = 4402,
  SERVICE_NOT_READY = 4403,
  RESOURCE_EXHAUSTED = 4404,

  // 91xx — internal implementation errors
  INTERNAL_ERROR = 9101,
  UNHANDLED_EXCEPTION = 9102,
  INVARIANT_VIOLATION = 9103,

  // 92xx — unknown / reserved / future errors
  UNKNOWN_ERROR = 9201,
  NOT_IMPLEMENTED = 9202
};

std::int32_t to_numeric_code(StatusCode code) noexcept;
std::string to_string(StatusCode code);
std::optional<StatusCode> status_code_from_string(std::string_view value) noexcept;
std::optional<StatusCode> status_code_from_numeric(std::int32_t value) noexcept;
bool is_success(StatusCode code) noexcept;
bool is_error(StatusCode code) noexcept;

} // namespace CalculatorProtocol::Codes
