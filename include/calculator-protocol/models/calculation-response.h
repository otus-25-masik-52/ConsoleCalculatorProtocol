#pragma once

#include "calculator-protocol/codes/status-code.h"
#include "calculator-protocol/types/error-info.h"
#include "calculator-protocol/types/result-info.h"
#include "calculator-protocol/types/result-source.h"
#include "calculator-protocol/types/timing-info.h"
#include "calculator-protocol/version/protocol-version.h"

#include <cstdint>
#include <optional>
#include <string>
#include <utility>

namespace CalculatorProtocol::Models {

class CalculationResponse {
 public:
  static CalculationResponse success(std::string request_id, Types::ResultInfo result_info);
  static CalculationResponse failure(std::string request_id, Codes::StatusCode status_code, std::string message);

  [[nodiscard]] std::uint32_t protocol_version() const noexcept {
    return protocol_version_;
  }

  [[nodiscard]] const std::string& request_id() const noexcept {
    return request_id_;
  }

  [[nodiscard]] Codes::StatusCode status_code() const noexcept {
    return status_code_;
  }

  [[nodiscard]] const std::optional<Types::ResultInfo>& result_info() const noexcept {
    return result_info_;
  }

  [[nodiscard]] const std::optional<Types::ErrorInfo>& error_info() const noexcept {
    return error_info_;
  }

  [[nodiscard]] const std::optional<Types::ResultSource>& result_source() const noexcept {
    return result_source_;
  }

  [[nodiscard]] const std::optional<Types::TimingInfo>& timing_info() const noexcept {
    return timing_info_;
  }

  void set_protocol_version(const std::uint32_t value) noexcept {
    protocol_version_ = value;
  }
  void set_request_id(std::string value) {
    request_id_ = std::move(value);
  }
  void set_status_code(const Codes::StatusCode value) noexcept {
    status_code_ = value;
  }
  void set_result_info(std::optional<Types::ResultInfo> value) {
    result_info_ = std::move(value);
  }
  void set_error_info(std::optional<Types::ErrorInfo> value) {
    error_info_ = std::move(value);
  }
  void set_result_source(const std::optional<Types::ResultSource> value) noexcept {
    result_source_ = value;
  }
  void set_timing_info(const std::optional<Types::TimingInfo>& value) noexcept {
    timing_info_ = value;
  }

 private:
  std::uint32_t protocol_version_{Version::current};
  std::string request_id_;
  Codes::StatusCode status_code_{Codes::StatusCode::OK};
  std::optional<Types::ResultInfo> result_info_;
  std::optional<Types::ErrorInfo> error_info_;
  std::optional<Types::ResultSource> result_source_;
  std::optional<Types::TimingInfo> timing_info_;
};

} // namespace CalculatorProtocol::Models
