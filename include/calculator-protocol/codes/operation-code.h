#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace CalculatorProtocol::Codes {

enum class OperationCode : std::uint8_t {
  UNKNOWN,
  ADDITION,
  SUBTRACTION,
  MULTIPLICATION,
  DIVISION,
  EXPONENTIATION,
  FACTORIAL
};

std::string to_string(OperationCode operation);
std::optional<OperationCode> operation_code_from_string(std::string_view value) noexcept;
bool is_commutative(OperationCode operation) noexcept;
bool is_unary(OperationCode operation) noexcept;
bool is_binary(OperationCode operation) noexcept;

} // namespace CalculatorProtocol::Codes
