#include "calculator-protocol/models/calculation-response.h"

#include <utility>

namespace CalculatorProtocol::Models {

CalculationResponse CalculationResponse::success(std::string request_id, Types::ResultInfo result_info) {
  CalculationResponse response;
  response.set_request_id(std::move(request_id));
  response.set_status_code(Codes::StatusCode::OK);
  response.set_result_info(std::move(result_info));
  response.set_error_info(std::nullopt);
  return response;
}

CalculationResponse CalculationResponse::failure(std::string request_id, const Codes::StatusCode status_code,
                                                 std::string message) {
  CalculationResponse response;
  response.set_request_id(std::move(request_id));
  response.set_status_code(status_code);
  response.set_result_info(std::nullopt);
  response.set_error_info(Types::ErrorInfo{status_code, std::move(message)});
  return response;
}

} // namespace CalculatorProtocol::Models
