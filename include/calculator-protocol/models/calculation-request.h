#pragma once

#include "calculator-protocol/codes/operation-code.h"
#include "calculator-protocol/types/client-info.h"
#include "calculator-protocol/types/request-options.h"
#include "calculator-protocol/version/protocol-version.h"

#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace CalculatorProtocol::Models {

class CalculationRequest {
 public:
  [[nodiscard]] std::uint32_t protocol_version() const noexcept {
    return protocol_version_;
  }

  [[nodiscard]] const std::string& request_id() const noexcept {
    return request_id_;
  }

  [[nodiscard]] Codes::OperationCode operation() const noexcept {
    return operation_;
  }

  [[nodiscard]] const std::vector<std::int64_t>& operands() const noexcept {
    return operands_;
  }

  [[nodiscard]] const std::optional<Types::ClientInfo>& client_info() const noexcept {
    return client_info_;
  }

  [[nodiscard]] const Types::RequestOptions& request_options() const noexcept {
    return request_options_;
  }

  void set_protocol_version(const std::uint32_t value) noexcept {
    protocol_version_ = value;
  }

  void set_request_id(std::string value) {
    request_id_ = std::move(value);
  }

  void set_operation(const Codes::OperationCode value) noexcept {
    operation_ = value;
  }

  void set_operands(std::vector<std::int64_t> value) {
    operands_ = std::move(value);
  }

  void set_client_info(std::optional<Types::ClientInfo> value) {
    client_info_ = std::move(value);
  }

  void set_request_options(const Types::RequestOptions value) noexcept {
    request_options_ = value;
  }

 private:
  std::uint32_t protocol_version_{Version::current};
  std::string request_id_;
  Codes::OperationCode operation_{Codes::OperationCode::UNKNOWN};
  std::vector<std::int64_t> operands_;
  std::optional<Types::ClientInfo> client_info_;
  Types::RequestOptions request_options_;
};

} // namespace CalculatorProtocol::Models
