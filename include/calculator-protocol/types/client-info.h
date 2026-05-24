#pragma once

#include <optional>
#include <string>
#include <utility>

namespace CalculatorProtocol::Types {

class ClientInfo {
 public:
  ClientInfo() = default;
  ClientInfo(std::string name, std::string version) : name_(std::move(name)), version_(std::move(version)) {}

  [[nodiscard]] const std::string& name() const noexcept {
    return name_;
  }

  [[nodiscard]] const std::string& version() const noexcept {
    return version_;
  }

  [[nodiscard]] const std::optional<std::string>& instance_id() const noexcept {
    return instance_id_;
  }

  [[nodiscard]] const std::optional<std::string>& platform() const noexcept {
    return platform_;
  }

  [[nodiscard]] const std::optional<std::string>& transport() const noexcept {
    return transport_;
  }

  void set_name(std::string value) {
    name_ = std::move(value);
  }

  void set_version(std::string value) {
    version_ = std::move(value);
  }

  void set_instance_id(std::optional<std::string> value) {
    instance_id_ = std::move(value);
  }

  void set_platform(std::optional<std::string> value) {
    platform_ = std::move(value);
  }

  void set_transport(std::optional<std::string> value) {
    transport_ = std::move(value);
  }

 private:
  std::string name_;
  std::string version_;
  std::optional<std::string> instance_id_;
  std::optional<std::string> platform_;
  std::optional<std::string> transport_;
};

} // namespace CalculatorProtocol::Types
