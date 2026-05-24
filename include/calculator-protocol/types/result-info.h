#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <utility>

namespace CalculatorProtocol::Types {

class ResultInfo {
 public:
  ResultInfo() = default;
  explicit ResultInfo(const std::int64_t value) noexcept : value_(value) {}

  [[nodiscard]] std::int64_t value() const noexcept {
    return value_;
  }

  [[nodiscard]] const std::optional<std::string>& numeric_type() const noexcept {
    return numeric_type_;
  }

  [[nodiscard]] const std::optional<std::string>& representation() const noexcept {
    return representation_;
  }

  void set_value(const std::int64_t value) noexcept {
    value_ = value;
  }

  void set_numeric_type(std::optional<std::string> value) {
    numeric_type_ = std::move(value);
  }

  void set_representation(std::optional<std::string> value) {
    representation_ = std::move(value);
  }

 private:
  std::int64_t value_{};
  std::optional<std::string> numeric_type_;
  std::optional<std::string> representation_;
};

} // namespace CalculatorProtocol::Types
