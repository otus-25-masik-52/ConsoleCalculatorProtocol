#pragma once

#include "calculator-protocol/models/calculation-request.h"
#include "calculator-protocol/models/calculation-response.h"

#include <string>
#include <string_view>

namespace CalculatorProtocol::Formats {

class JsonCodec {
 public:
  static Models::CalculationRequest parse_request(std::string_view json_text);
  static Models::CalculationResponse parse_response(std::string_view json_text);

  static std::string serialize_request(const Models::CalculationRequest& request);
  static std::string serialize_response(const Models::CalculationResponse& response);
};

} // namespace CalculatorProtocol::Formats
