# Console Calculator Protocol errors

Status code format: `ABCD`.

- `0xxx` — success
- `1xxx` — user/input/domain errors
- `2xxx` — client-side/local errors
- `3xxx` — protocol/contract errors
- `4xxx` — server/runtime errors
- `9xxx` — internal/unknown/reserved errors

## Public status codes

| Code | Name | Description |
|---:|---|---|
| 0 | OK | Request completed successfully. |
| 1101 | INVALID_OPERATION | Operation is unknown or invalid. |
| 1102 | UNSUPPORTED_OPERATION | Operation is known by the protocol but unsupported by current server. |
| 1103 | OPERATION_DISABLED | Operation is disabled by server configuration. |
| 1201 | INVALID_OPERANDS | Generic operands error. |
| 1202 | OPERANDS_COUNT_MISMATCH | Operation received wrong number of operands. |
| 1203 | OPERAND_OUT_OF_RANGE | Operand is outside allowed range. |
| 1204 | DIVISION_BY_ZERO | Division by zero. |
| 1205 | FACTORIAL_OF_NEGATIVE_NUMBER | Factorial input is negative. |
| 1206 | NUMERIC_OVERFLOW | Calculation overflowed numeric type. |
| 1207 | RESULT_NOT_REPRESENTABLE | Result cannot be represented by current protocol model. |
| 1301 | INVALID_REQUEST_OPTIONS | Request options are invalid. |
| 1302 | TIMEOUT_OUT_OF_RANGE | timeout_ms is outside allowed range. |
| 1303 | INVALID_CLIENT_INFO | Client metadata is invalid. |
| 1304 | INVALID_REQUEST_ID | request_id is missing or invalid. |
| 2101 | CLIENT_CONNECTION_FAILED | Client could not connect. |
| 2201 | CLIENT_TIMEOUT | Client-side timeout. |
| 2202 | CLIENT_CANCELLED | Client cancelled request. |
| 2301 | CLIENT_CONFIGURATION_ERROR | Client configuration is invalid. |
| 2302 | CLIENT_SERIALIZATION_ERROR | Client failed to serialize request. |
| 2303 | CLIENT_RESPONSE_PARSE_ERROR | Client failed to parse response. |
| 3101 | INVALID_JSON | Message is not valid JSON. |
| 3102 | MALFORMED_MESSAGE | Message is structurally malformed. |
| 3103 | EMPTY_MESSAGE | Message is empty. |
| 3201 | MISSING_REQUIRED_FIELD | Required field is missing. |
| 3202 | INVALID_FIELD_TYPE | Field has invalid type. |
| 3203 | INVALID_FIELD_VALUE | Field has invalid value. |
| 3301 | UNSUPPORTED_PROTOCOL_VERSION | Protocol version is not supported. |
| 3302 | INCOMPATIBLE_PROTOCOL_VERSION | Protocol version is known but incompatible. |
| 3401 | MESSAGE_TOO_LARGE | Message exceeds max allowed size. |
| 3402 | INVALID_MESSAGE_FRAMING | Transport message framing is invalid. |
| 3501 | UNSUPPORTED_TRANSPORT | Transport is unsupported. |
| 3502 | UNSUPPORTED_CONTENT_TYPE | Content-Type is unsupported. |
| 3503 | CORRELATION_ID_MISMATCH | Correlation id does not match request id. |
| 4101 | STORAGE_UNAVAILABLE | Storage is unavailable. |
| 4102 | STORAGE_CONNECTION_FAILED | Storage connection failed. |
| 4103 | STORAGE_ERROR | Generic storage error. |
| 4104 | CACHE_ERROR | Generic cache error. |
| 4201 | CALCULATION_ERROR | Generic calculation error. |
| 4202 | CALCULATOR_LIBRARY_ERROR | Calculator library returned unexpected error. |
| 4203 | CALCULATION_TIMEOUT | Calculation exceeded timeout. |
| 4301 | SERVER_CONNECTION_CLOSED | Server closed connection. |
| 4302 | SERVER_SESSION_ERROR | Server session failed. |
| 4401 | SERVER_UNAVAILABLE | Server is unavailable. |
| 4402 | SERVICE_SHUTTING_DOWN | Service is shutting down. |
| 4403 | SERVICE_NOT_READY | Service is not ready. |
| 4404 | RESOURCE_EXHAUSTED | Server resource limit reached. |
| 9101 | INTERNAL_ERROR | Internal implementation error. |
| 9102 | UNHANDLED_EXCEPTION | Unhandled exception. |
| 9103 | INVARIANT_VIOLATION | Internal invariant violation. |
| 9201 | UNKNOWN_ERROR | Unknown error. |
| 9202 | NOT_IMPLEMENTED | Feature is not implemented. |
