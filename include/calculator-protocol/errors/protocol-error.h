#pragma once

#include "calculator-protocol/codes/status-code.h"

#include <optional>
#include <stdexcept>
#include <string>

namespace CalculatorProtocol::Errors {

class ProtocolError : public std::runtime_error {
 public:
  ProtocolError(Codes::StatusCode status_code, const std::string& message);
  ProtocolError(Codes::StatusCode status_code, const std::string& message, std::string field);

  [[nodiscard]] Codes::StatusCode status_code() const noexcept;
  [[nodiscard]] const std::optional<std::string>& field() const noexcept;

 private:
  ProtocolError(Codes::StatusCode status_code, const std::string& message, std::optional<std::string> field);
  
  Codes::StatusCode status_code_;
  std::optional<std::string> field_;
};

} // namespace CalculatorProtocol::Errors
