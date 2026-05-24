# Console Calculator Protocol v1

## Request

```json
{
  "protocol_version": 1,
  "request_id": "req-1",
  "client": {
    "name": "console-calculator-client",
    "version": "1.0.0"
  },
  "operation": "addition",
  "operands": [1, 2],
  "options": {
    "timeout_ms": 5000,
    "debug_enabled": false,
    "include_timing": false,
    "include_result_source": false
  }
}
```

Required fields:

- `protocol_version`
- `request_id`
- `operation`
- `operands`

Optional fields:

- `client`
- `options`

## Response: success

```json
{
  "protocol_version": 1,
  "request_id": "req-1",
  "status": {
    "code": 0,
    "name": "OK"
  },
  "result": {
    "value": 3
  },
  "error": null
}
```

## Response: error

```json
{
  "protocol_version": 1,
  "request_id": "req-1",
  "status": {
    "code": 1204,
    "name": "DIVISION_BY_ZERO"
  },
  "result": null,
  "error": {
    "code": "DIVISION_BY_ZERO",
    "message": "division by zero"
  }
}
```

## Operations

| Operation | Arity | Notes |
|---|---:|---|
| `addition` / `add` | 2 | Commutative. |
| `subtraction` / `sub` | 2 | Non-commutative. |
| `multiplication` / `mul` | 2 | Commutative. |
| `division` / `div` | 2 | Non-commutative. |
| `exponentiation` / `pow` | 2 | Non-commutative. |
| `factorial` / `fact` | 1 | Operand must be non-negative. |

## Compatibility rules

- Unknown optional fields must be ignored by default.
- Missing required fields produce `MISSING_REQUIRED_FIELD`.
- Unsupported protocol version produces `UNSUPPORTED_PROTOCOL_VERSION`.
- New optional fields may be added without breaking v1 clients.
