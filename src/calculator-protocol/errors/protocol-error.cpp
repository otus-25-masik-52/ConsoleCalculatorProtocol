#include "calculator-protocol/errors/protocol-error.h"

#include <utility>

namespace CalculatorProtocol::Errors {

ProtocolError::ProtocolError(const Codes::StatusCode status_code, const std::string& message)
    : ProtocolError(status_code, message, std::nullopt) {}

ProtocolError::ProtocolError(const Codes::StatusCode status_code, const std::string& message, std::string field)
    : ProtocolError(status_code, message, std::optional(std::move(field))) {}

ProtocolError::ProtocolError(const Codes::StatusCode status_code, const std::string& message,
                             std::optional<std::string> field)
    : std::runtime_error(message), status_code_(status_code), field_(std::move(field)) {}

Codes::StatusCode ProtocolError::status_code() const noexcept {
  return status_code_;
}

const std::optional<std::string>& ProtocolError::field() const noexcept {
  return field_;
}

} // namespace CalculatorProtocol::Errors
