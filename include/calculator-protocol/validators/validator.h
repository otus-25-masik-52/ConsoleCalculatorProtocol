#pragma once

#include "calculator-protocol/models/calculation-request.h"
#include "calculator-protocol/models/calculation-response.h"

#include <cstddef>
#include <cstdint>

namespace CalculatorProtocol::Validators {

class Validator {
 public:
  static constexpr std::size_t max_operands_count = 8;
  static constexpr std::uint32_t min_timeout_ms = 1;
  static constexpr std::uint32_t max_timeout_ms = 60000;

  static void validate_request(const Models::CalculationRequest& request);
  static void validate_response(const Models::CalculationResponse& response);

 private:
  static void validate_operands(const Models::CalculationRequest& request);
};

} // namespace CalculatorProtocol::Validators
