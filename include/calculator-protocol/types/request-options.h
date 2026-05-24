#pragma once

#include <cstdint>
#include <optional>

namespace CalculatorProtocol::Types {

class RequestOptions {
 public:
  [[nodiscard]] const std::optional<std::uint32_t>& timeout_ms() const noexcept {
    return timeout_ms_;
  }

  [[nodiscard]] bool debug_enabled() const noexcept {
    return debug_enabled_;
  }

  [[nodiscard]] bool include_timing() const noexcept {
    return include_timing_;
  }

  [[nodiscard]] bool include_result_source() const noexcept {
    return include_result_source_;
  }

  [[nodiscard]] bool strict_validation() const noexcept {
    return strict_validation_;
  }

  void set_timeout_ms(const std::optional<std::uint32_t> value) noexcept {
    timeout_ms_ = value;
  }

  void set_debug_enabled(const bool value) noexcept {
    debug_enabled_ = value;
  }

  void set_include_timing(const bool value) noexcept {
    include_timing_ = value;
  }

  void set_include_result_source(const bool value) noexcept {
    include_result_source_ = value;
  }

  void set_strict_validation(const bool value) noexcept {
    strict_validation_ = value;
  }

 private:
  std::optional<std::uint32_t> timeout_ms_;
  bool debug_enabled_{false};
  bool include_timing_{false};
  bool include_result_source_{false};
  bool strict_validation_{false};
};

} // namespace CalculatorProtocol::Types
