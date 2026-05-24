#include "calculator-protocol/formats/json-codec.h"

#include "calculator-protocol/errors/protocol-error.h"
#include "calculator-protocol/types/result-source.h"
#include "calculator-protocol/validators/validator.h"

#include <nlohmann/json.hpp>

#include <string>

namespace CalculatorProtocol::Formats {

using Codes::OperationCode;
using Codes::StatusCode;
using Errors::ProtocolError;
using nlohmann::json;
using std::string_literals::operator""s;

namespace {

json parse_json_object(const std::string_view json_text) {
  if (json_text.empty()) {
    throw ProtocolError{StatusCode::EMPTY_MESSAGE, "message is empty"};
  }

  try {
    auto parsed = json::parse(json_text.begin(), json_text.end());
    if (!parsed.is_object()) {
      throw ProtocolError{StatusCode::MALFORMED_MESSAGE, "top-level JSON value must be object"};
    }
    return parsed;
  } catch (const json::parse_error& error) {
    throw ProtocolError{StatusCode::INVALID_JSON, error.what()};
  }
}

std::string require_string(const json& object, const char* field) {
  if (!object.contains(field)) {
    throw ProtocolError{StatusCode::MISSING_REQUIRED_FIELD, std::string("missing required field: ") + field,
                        std::string(field)};
  }
  if (!object.at(field).is_string()) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, std::string("field must be string: ") + field,
                        std::string(field)};
  }
  return object.at(field).get<std::string>();
}

std::uint32_t require_uint32(const json& object, const char* field) {
  if (!object.contains(field)) {
    throw ProtocolError{StatusCode::MISSING_REQUIRED_FIELD, std::string("missing required field: ") + field,
                        std::string(field)};
  }
  if (!object.at(field).is_number_unsigned()) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, std::string("field must be unsigned integer: ") + field,
                        std::string(field)};
  }
  return object.at(field).get<std::uint32_t>();
}

template <typename JsonTypeCheck>
std::pair<nlohmann::basic_json<>::const_iterator, bool>
get_value_it_with_condition(const json& object, const std::string_view field_name, JsonTypeCheck type_check) {
  auto it = object.find(field_name);

  if (it == object.end() || it->is_null()) {
    return {object.end(), false};
  }

  if (std::invoke(type_check, it.value())) {
    return {it, true};
  }

  return {object.end(), true};
}

} // namespace

namespace {

void parse_request_with_client(const json& object, Models::CalculationRequest& request) {
  const auto [client, exists] = get_value_it_with_condition(object, "client", &json::is_object);

  if (!exists) {
    return;
  }

  if (client == object.end()) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "client must be object", "client"s};
  }

  Types::ClientInfo client_info;
  if (const auto [name, e] = get_value_it_with_condition(*client, "name", &json::is_string); name != client->end()) {
    client_info.set_name(name->get<std::string>());
  } else if (e) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "client.name must be string", "client.name"s};
  }

  if (const auto [version, e] = get_value_it_with_condition(*client, "version", &json::is_string);
      version != client->end()) {
    client_info.set_version(version->get<std::string>());
  } else if (e) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "client.version must be string", "client.version"s};
  }

  if (const auto [instance_id, _] = get_value_it_with_condition(*client, "instance_id", &json::is_string);
      instance_id != client->end()) {
    client_info.set_instance_id(instance_id->get<std::string>());
  }

  if (const auto [platform, _] = get_value_it_with_condition(*client, "platform", &json::is_string);
      platform != client->end()) {
    client_info.set_platform(platform->get<std::string>());
  }

  if (const auto [transport, _] = get_value_it_with_condition(*client, "transport", &json::is_string);
      transport != client->end()) {
    client_info.set_transport(transport->get<std::string>());
  }

  request.set_client_info(std::move(client_info));
}

void parse_request_with_options(const json& object, Models::CalculationRequest& request) {
  const auto [options, exists] = get_value_it_with_condition(object, "options", &json::is_object);

  if (!exists) {
    return;
  }

  if (options == object.end()) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "options must be object", "options"s};
  }

  Types::RequestOptions request_options;

  if (const auto [timeout_ms, e] = get_value_it_with_condition(*options, "timeout_ms", &json::is_number_unsigned);
      timeout_ms != options->end()) {
    request_options.set_timeout_ms(timeout_ms->get<std::uint32_t>());
  } else if (e) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "options.timeout_ms must be unsigned integer",
                        "options.timeout_ms"s};
  }

  if (const auto [debug_enabled, _] = get_value_it_with_condition(*options, "debug_enabled", &json::is_boolean);
      debug_enabled != options->end()) {
    request_options.set_debug_enabled(debug_enabled->get<bool>());
  }

  if (const auto [include_timing, _] = get_value_it_with_condition(*options, "include_timing", &json::is_boolean);
      include_timing != options->end()) {
    request_options.set_include_timing(include_timing->get<bool>());
  }

  if (const auto [include_result_source, _] =
          get_value_it_with_condition(*options, "include_result_source", &json::is_boolean);
      include_result_source != options->end()) {
    request_options.set_include_result_source(include_result_source->get<bool>());
  }

  if (const auto [strict_validation, _] = get_value_it_with_condition(*options, "strict_validation", &json::is_boolean);
      strict_validation != options->end()) {
    request_options.set_strict_validation(strict_validation->get<bool>());
  }

  request.set_request_options(request_options);
}

} // namespace

Models::CalculationRequest JsonCodec::parse_request(const std::string_view json_text) {
  const auto object = parse_json_object(json_text);

  Models::CalculationRequest request;
  request.set_protocol_version(require_uint32(object, "protocol_version"));
  request.set_request_id(require_string(object, "request_id"));

  const auto operation_text = require_string(object, "operation");
  const auto operation = Codes::operation_code_from_string(operation_text);
  if (!operation.has_value()) {
    throw ProtocolError{StatusCode::INVALID_OPERATION, "unknown operation", "operation"s};
  }
  request.set_operation(*operation);

  auto [operands_obj, exists_operands_obj] = get_value_it_with_condition(object, "operands", &json::is_array);
  if (!exists_operands_obj) {
    throw ProtocolError{StatusCode::MISSING_REQUIRED_FIELD, "missing required field: operands", "operands"s};
  }
  if (operands_obj == object.end()) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "operands must be array", "operands"s};
  }

  std::vector<std::int64_t> operands;
  for (const auto& item : *operands_obj) {
    if (!item.is_number_integer()) {
      throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "operand must be integer", "operands"s};
    }
    operands.push_back(item.get<std::int64_t>());
  }
  request.set_operands(std::move(operands));

  parse_request_with_client(object, request);
  parse_request_with_options(object, request);

  Validators::Validator::validate_request(request);
  return request;
}

namespace {

void parse_response_result(const json& object, Models::CalculationResponse& response) {
  if (const auto [result, result_exists] = get_value_it_with_condition(object, "result", &json::is_object);
      result != object.end()) {
    if (const auto [value, value_exists] = get_value_it_with_condition(*result, "value", &json::is_number_integer);
        value != result->end()) {
      response.set_result_info(Types::ResultInfo{value->get<std::int64_t>()});
    } else if (value_exists) {
      throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "result.value must be integer", "result.value"s};
    }
  } else if (result_exists) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "result must be object or null", "result"s};
  }
}

void parse_response_error(const json& object, Models::CalculationResponse& response, const StatusCode status_code) {
  if (const auto [error, error_exists] = get_value_it_with_condition(object, "error", &json::is_object);
      error != object.end()) {
    if (const auto [message, message_exists] = get_value_it_with_condition(*error, "message", &json::is_string);
        message != error->end()) {
      response.set_error_info(Types::ErrorInfo{status_code, message->get<std::string>()});
    } else if (message_exists) {
      throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "error.message must be string", "error.message"s};
    } else {
      response.set_error_info(Types::ErrorInfo{status_code, Codes::to_string(status_code)});
    }
  } else if (error_exists) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "error must be object or null", "error"s};
  }
}

void parse_response_source(const json& object, Models::CalculationResponse& response) {
  if (const auto [source_obj, source_exists] = get_value_it_with_condition(object, "source", &json::is_string);
      source_obj != object.end()) {
    const auto source = Types::result_source_from_string(source_obj->get<std::string>());
    if (!source.has_value()) {
      throw ProtocolError{StatusCode::INVALID_FIELD_VALUE, "unknown result source", "source"s};
    }
    response.set_result_source(source);
  } else if (source_exists) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "source must be string", "source"s};
  }
}

void parse_response_timing(const json& object, Models::CalculationResponse& response) {
  if (const auto [timing_obj, timing_exists] = get_value_it_with_condition(object, "timing", &json::is_object);
      timing_obj != object.end()) {
    Types::TimingInfo timing;

    if (const auto [total_duration_ms, total_exists] =
            get_value_it_with_condition(*timing_obj, "total_duration_ms", &json::is_number_unsigned);
        total_duration_ms != timing_obj->end()) {
      timing.set_total_duration_ms(total_duration_ms->get<std::uint64_t>());
    } else if (total_exists) {
      throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "timing.total_duration_ms must be unsigned integer",
                          "timing.total_duration_ms"s};
    }

    response.set_timing_info(timing);
  } else if (timing_exists) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "timing must be object", "timing"s};
  }
}

} // namespace

Models::CalculationResponse JsonCodec::parse_response(const std::string_view json_text) {
  const auto object = parse_json_object(json_text);

  Models::CalculationResponse response;
  response.set_protocol_version(require_uint32(object, "protocol_version"));
  response.set_request_id(require_string(object, "request_id"));

  auto [status, exists_status] = get_value_it_with_condition(object, "status", &json::is_object);

  if (!exists_status || status == object.end()) {
    throw ProtocolError{StatusCode::MISSING_REQUIRED_FIELD, "status object is required", "status"s};
  }

  auto [code, exists_code] = get_value_it_with_condition(*status, "code", &json::is_number_integer);

  if (!exists_code || code == status->end()) {
    throw ProtocolError{StatusCode::INVALID_FIELD_TYPE, "status.code must be integer", "status.code"s};
  }

  const auto status_code = Codes::status_code_from_numeric(code->get<std::int32_t>());
  if (!status_code.has_value()) {
    throw ProtocolError{StatusCode::INVALID_FIELD_VALUE, "unknown status code", "status.code"s};
  }
  response.set_status_code(*status_code);

  parse_response_result(object, response);
  parse_response_error(object, response, *status_code);
  parse_response_source(object, response);
  parse_response_timing(object, response);

  Validators::Validator::validate_response(response);
  return response;
}

std::string JsonCodec::serialize_request(const Models::CalculationRequest& request) {
  json object;
  object["protocol_version"] = request.protocol_version();
  object["request_id"] = request.request_id();
  object["operation"] = Codes::to_string(request.operation());
  object["operands"] = request.operands();

  if (request.client_info().has_value()) {
    const auto& client = *request.client_info();
    object["client"]["name"] = client.name();
    object["client"]["version"] = client.version();
    if (client.instance_id().has_value()) {
      object["client"]["instance_id"] = *client.instance_id();
    }
    if (client.platform().has_value()) {
      object["client"]["platform"] = *client.platform();
    }
    if (client.transport().has_value()) {
      object["client"]["transport"] = *client.transport();
    }
  }

  if (const auto& options = request.request_options(); options.timeout_ms().has_value() || options.debug_enabled() ||
                                                       options.include_timing() || options.include_result_source() ||
                                                       options.strict_validation()) {
    if (options.timeout_ms().has_value()) {
      object["options"]["timeout_ms"] = *options.timeout_ms();
    }
    object["options"]["debug_enabled"] = options.debug_enabled();
    object["options"]["include_timing"] = options.include_timing();
    object["options"]["include_result_source"] = options.include_result_source();
    object["options"]["strict_validation"] = options.strict_validation();
  }

  return object.dump();
}

std::string JsonCodec::serialize_response(const Models::CalculationResponse& response) {
  json object;
  object["protocol_version"] = response.protocol_version();
  object["request_id"] = response.request_id();
  object["status"]["code"] = Codes::to_numeric_code(response.status_code());
  object["status"]["name"] = Codes::to_string(response.status_code());

  if (response.result_info().has_value()) {
    object["result"]["value"] = response.result_info()->value();
  } else {
    object["result"] = nullptr;
  }

  if (response.error_info().has_value()) {
    object["error"]["code"] = response.error_info()->code();
    object["error"]["message"] = response.error_info()->message();
    if (response.error_info()->field().has_value()) {
      object["error"]["field"] = *response.error_info()->field();
    }
    object["error"]["retryable"] = response.error_info()->retryable();
  } else {
    object["error"] = nullptr;
  }

  if (response.result_source().has_value()) {
    object["source"] = Types::to_string(*response.result_source());
  }

  if (response.timing_info().has_value()) {
    object["timing"]["total_duration_ms"] = response.timing_info()->total_duration_ms();
  }

  return object.dump();
}

} // namespace CalculatorProtocol::Formats
