#include "calculator-protocol/codes/operation-code.h"

#include <string_view>

#include "calculator-protocol/utils/switch-strings-by-hash.h"

namespace CalculatorProtocol::Codes {

using Utils::lower_hash;
using Utils::operator ""_lw;

std::string to_string(const OperationCode operation) {
  switch (operation) {
  case OperationCode::ADDITION:
    return "addition";
  case OperationCode::SUBTRACTION:
    return "subtraction";
  case OperationCode::MULTIPLICATION:
    return "multiplication";
  case OperationCode::DIVISION:
    return "division";
  case OperationCode::EXPONENTIATION:
    return "exponentiation";
  case OperationCode::FACTORIAL:
    return "factorial";
  case OperationCode::UNKNOWN:
  default:
    return "unknown";
  }
}

std::optional<OperationCode> operation_code_from_string(const std::string_view value) noexcept {
  switch (lower_hash(value)) {
  case "addition"_lw:
  case "add"_lw:
    return OperationCode::ADDITION;

  case "subtraction"_lw:
  case "sub"_lw:
    return OperationCode::SUBTRACTION;

  case "multiplication"_lw:
  case "mul"_lw:
    return OperationCode::MULTIPLICATION;

  case "division"_lw:
  case "div"_lw:
    return OperationCode::DIVISION;

  case "exponentiation"_lw:
  case "pow"_lw:
    return OperationCode::EXPONENTIATION;

  case "factorial"_lw:
  case "fact"_lw:
    return OperationCode::FACTORIAL;

  default:
    return std::nullopt;
  }
}

bool is_commutative(const OperationCode operation) noexcept {
  return operation == OperationCode::ADDITION || operation == OperationCode::MULTIPLICATION;
}

bool is_unary(const OperationCode operation) noexcept {
  return operation == OperationCode::FACTORIAL;
}

bool is_binary(const OperationCode operation) noexcept {
  return operation == OperationCode::ADDITION || operation == OperationCode::SUBTRACTION ||
         operation == OperationCode::MULTIPLICATION || operation == OperationCode::DIVISION ||
         operation == OperationCode::EXPONENTIATION;
}

} // namespace CalculatorProtocol::Codes
