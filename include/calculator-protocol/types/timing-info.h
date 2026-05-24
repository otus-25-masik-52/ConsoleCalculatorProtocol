#pragma once

#include <cstdint>
#include <optional>

namespace CalculatorProtocol::Types {

class TimingInfo {
 public:
  [[nodiscard]] std::uint64_t total_duration_ms() const noexcept {
    return total_duration_ms_;
  }

  [[nodiscard]] const std::optional<std::uint64_t>& validation_duration_ms() const noexcept {
    return validation_duration_ms_;
  }

  [[nodiscard]] const std::optional<std::uint64_t>& storage_duration_ms() const noexcept {
    return storage_duration_ms_;
  }

  [[nodiscard]] const std::optional<std::uint64_t>& calculation_duration_ms() const noexcept {
    return calculation_duration_ms_;
  }

  [[nodiscard]] const std::optional<std::uint64_t>& serialization_duration_ms() const noexcept {
    return serialization_duration_ms_;
  }

  void set_total_duration_ms(const std::uint64_t value) noexcept {
    total_duration_ms_ = value;
  }

  void set_validation_duration_ms(const std::optional<std::uint64_t> value) noexcept {
    validation_duration_ms_ = value;
  }

  void set_storage_duration_ms(const std::optional<std::uint64_t> value) noexcept {
    storage_duration_ms_ = value;
  }

  void set_calculation_duration_ms(const std::optional<std::uint64_t> value) noexcept {
    calculation_duration_ms_ = value;
  }

  void set_serialization_duration_ms(const std::optional<std::uint64_t> value) noexcept {
    serialization_duration_ms_ = value;
  }

 private:
  std::uint64_t total_duration_ms_{};
  std::optional<std::uint64_t> validation_duration_ms_;
  std::optional<std::uint64_t> storage_duration_ms_;
  std::optional<std::uint64_t> calculation_duration_ms_;
  std::optional<std::uint64_t> serialization_duration_ms_;
};

} // namespace CalculatorProtocol::Types
