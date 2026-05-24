# 0001. Protocol shape

## Status

Accepted.

## Context

The calculator ecosystem is split into several repositories:

- `ConsoleCalculatorMathLib` — arithmetic implementation.
- `ConsoleCalculatorProtocol` — shared protocol contract.
- `ConsoleCalculatorServer` — long-running service, storage and transports.
- `ConsoleCalculatorClient` — client application.

The protocol library must be transport-independent. The same semantic request and response model should be usable by TCP JSON, gRPC, REST API and message queue integrations.

## Decision

The protocol is divided into three layers.

### 1. Semantic model

The public C++ API contains transport-independent models:

- `OperationCode`
- `StatusCode`
- `CalculationRequest`
- `CalculationResponse`
- `ClientInfo`
- `RequestOptions`
- `ResultInfo`
- `ResultSource`
- `TimingInfo`
- `ErrorInfo`

These types do not open sockets, start servers, access storage, call the calculator library, or depend on a concrete transport.

### 2. Formats

The protocol library owns conversion between semantic models and wire formats.

The first implemented format is JSON:

- `JsonCodec::parse_request`
- `JsonCodec::serialize_request`
- `JsonCodec::parse_response`
- `JsonCodec::serialize_response`

`JsonCodec` is a format adapter, not a transport implementation. It does not know whether JSON is sent over TCP, REST, or a message queue.

### 3. Transport specifications

Transport-specific rules are documented separately:

- TCP JSON — newline-delimited JSON over TCP.
- gRPC — protobuf service contract.
- REST — HTTP endpoint contract.
- Message Queue — request/response queues with correlation id.

Transport implementations live in client/server projects, not in this protocol library.

## Consequences

### Positive

- Client and server share one stable semantic contract.
- JSON, gRPC, REST and message queue transports can evolve around the same models.
- The protocol library stays small and testable.
- Server-side storage, cache and calculation logic do not leak into the client.

### Negative

- Some mapping code is required between protocol models and concrete transports.
- The protocol repository must keep documentation and schemas in sync with C++ models.

## Rules

- Public wire operation names are words, not symbols: `addition`, `division`, `factorial`, etc.
- `OperationCode::UNKNOWN` is an internal fallback value, not a valid wire value.
- Unknown operation strings must fail parsing.
- `StatusCode` contains stable public protocol statuses only.
- Detailed implementation errors belong to `ErrorInfo` and server logs.
- Debug metadata such as `ResultSource` and `TimingInfo` should not be required by client business logic.
