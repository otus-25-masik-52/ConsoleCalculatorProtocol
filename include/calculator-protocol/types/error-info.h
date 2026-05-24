#pragma once

#include "calculator-protocol/codes/status-code.h"

#include <map>
#include <optional>
#include <string>
#include <utility>

namespace CalculatorProtocol::Types {

class ErrorInfo {
 public:
  ErrorInfo() = default;
  ErrorInfo(const Codes::StatusCode status_code, std::string message)
      : status_code_(status_code), code_(Codes::to_string(status_code)), message_(std::move(message)) {}

  [[nodiscard]] Codes::StatusCode status_code() const noexcept {
    return status_code_;
  }

  [[nodiscard]] const std::string& code() const noexcept {
    return code_;
  }

  [[nodiscard]] const std::string& message() const noexcept {
    return message_;
  }

  [[nodiscard]] const std::optional<std::string>& field() const noexcept {
    return field_;
  }

  [[nodiscard]] bool retryable() const noexcept {
    return retryable_;
  }

  [[nodiscard]] const std::map<std::string, std::string>& details() const noexcept {
    return details_;
  }

  void set_status_code(const Codes::StatusCode value) {
    status_code_ = value;
    code_ = Codes::to_string(value);
  }

  void set_code(std::string value) {
    code_ = std::move(value);
  }

  void set_message(std::string value) {
    message_ = std::move(value);
  }

  void set_field(std::optional<std::string> value) {
    field_ = std::move(value);
  }

  void set_retryable(const bool value) noexcept {
    retryable_ = value;
  }

  void set_details(std::map<std::string, std::string> value) {
    details_ = std::move(value);
  }

 private:
  Codes::StatusCode status_code_{Codes::StatusCode::UNKNOWN_ERROR};
  std::string code_{Codes::to_string(Codes::StatusCode::UNKNOWN_ERROR)};
  std::string message_;
  std::optional<std::string> field_;
  bool retryable_{false};
  std::map<std::string, std::string> details_;
};

} // namespace CalculatorProtocol::Types
