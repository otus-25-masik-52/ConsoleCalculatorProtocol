# ConsoleCalculatorProtocol
A C++ protocol library for connecting client and server parts of ConsoleCalculator.

![Static Badge](https://img.shields.io/badge/otus--25--masik--52-ConsoleCalculatorProtocol-darkblue)
![GitHub top language](https://img.shields.io/github/languages/top/otus-25-masik-52/ConsoleCalculatorProtocol)
![GitHub](https://img.shields.io/github/license/otus-25-masik-52/ConsoleCalculatorProtocol)
![GitHub Repo stars](https://img.shields.io/github/stars/otus-25-masik-52/ConsoleCalculatorProtocol)

## Documentation

### Components overview
| Component            | Description                                      | Main responsibility                              | Notes                                                  |
|---------------------|--------------------------------------------------|--------------------------------------------------|--------------------------------------------------------|
| OperationCode        | Public operation identifiers                     | Describes requested calculator operation         | Uses stable wire names like `addition` and `division`  |
| StatusCode           | Public protocol status/error codes              | Describes result class visible to clients        | Details belong to `ErrorInfo` and server logs          |
| CalculationRequest   | Request DTO                                      | Carries protocol version, request id, operation, operands, client metadata and options | Transport-independent model |
| CalculationResponse  | Response DTO                                     | Carries protocol version, request id, status, result/error and optional debug metadata | Transport-independent model |
| JsonCodec            | JSON serializer/parser                           | Converts protocol DTOs to/from wire JSON         | Does not open sockets and does not calculate           |
| Validator            | Semantic request/response validation             | Checks required protocol invariants              | Does not parse JSON and does not call MathLib          |
| ProtocolError        | Protocol-level exception                         | Reports malformed input and invalid protocol data | Stores stable `StatusCode`                             |
| Schemas              | JSON Schema, OpenAPI and proto descriptions      | Documents external protocol contracts            | Used as documentation and compatibility reference      |

> This repository defines the contract. It does not implement a server, a client transport, PostgreSQL storage or mathematical calculations.

### Protocol boundaries

The protocol layer is intentionally transport-independent:

```text
ConsoleCalculatorClient
        |
        | uses
        v
ConsoleCalculatorProtocol
        ^
        | uses
        |
ConsoleCalculatorServer
        |
        | adapts
        v
ConsoleCalculatorMathLib
```

`ConsoleCalculatorProtocol` knows about requests, responses, operation names, status codes, validation rules and JSON format.
It must not know about TCP sockets, REST controllers, gRPC services, PostgreSQL, cache repositories or MathLib internal error enums.

### Documentation map

This directory contains the protocol-level documentation for the Console Calculator ecosystem.
The protocol is intentionally separated from concrete client/server implementations: it defines the shared semantic contract, stable error model, wire representations and transport mapping rules.

Start with the core protocol description, then move to error semantics and transport-specific integration notes.

#### Core documents

- [Protocol v1](./docs/protocol-v1.md)  
  Defines the public request/response contract, JSON shape, supported operations, required fields and compatibility rules for protocol version 1.

- [Errors](./docs/errors.md)  
  Describes the stable public `StatusCode` model, status code groups, client/server/domain error classes and how protocol errors should be represented in responses.

- [ADR-0001: Protocol shape](./docs/decisions/0001-protocol-shape.md)  
  Explains the architectural decision behind the protocol design: semantic models, format adapters, transport independence and repository boundaries.

### Transport specifications

- [TCP JSON Transport v1](./docs/transports/tcp-json-v1.md)  
  Specifies newline-delimited JSON over TCP, framing rules, encoding and recommended message size limits.

- [REST Transport v1](./docs/transports/rest-v1.md)  
  Defines the HTTP mapping for protocol v1, including endpoint shape, content type and request/response body semantics.

- [gRPC Transport v1](./docs/transports/grpc-v1.md)  
  Describes how the same protocol model is represented as a protobuf/gRPC service contract.

- [Message Queue Transport v1](./docs/transports/message-queue-v1.md)  
  Defines asynchronous request/response communication using queues, `request_id` correlation and reply routing rules.

### Reading order

Recommended order for understanding the protocol:

1. [ADR-0001: Protocol shape](./docs/decisions/0001-protocol-shape.md)
2. [Protocol v1](./docs/protocol-v1.md)
3. [Errors](./docs/errors.md)
4. Transport-specific document:
    - [TCP JSON](./docs/transports/tcp-json-v1.md)
    - [REST](./docs/transports/rest-v1.md)
    - [gRPC](./docs/transports/grpc-v1.md)
    - [Message Queue](./docs/transports/message-queue-v1.md)

The main rule is simple: `ConsoleCalculatorProtocol` owns the contract, models, formats and schemas; concrete networking, server lifecycle, storage, caching and calculation execution belong to client/server repositories.

## Usage

### As a standalone project

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
ctest --test-dir build --output-on-failure
```

### As a dependency with FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(
  ConsoleCalculatorProtocol
  GIT_REPOSITORY https://github.com/otus-25-masik-52/ConsoleCalculatorProtocol.git
  GIT_TAG master
)

FetchContent_MakeAvailable(ConsoleCalculatorProtocol)

target_link_libraries(my_target PRIVATE calculator_protocol)
```

For reproducible builds, replace `master` with a concrete commit hash or release tag.

## Support
If you have any difficulties or questions about using this library, create a [discussion](https://github.com/otus-25-masik-52/ConsoleCalculatorProtocol/issues/new/choose) in this repository.

## Dependencies
This library is implemented in C++20.
To use it, you need:
- a **C++20-compatible compiler**
- **CMake**
- **nlohmann/json** for JSON serialization/parsing
- **GoogleTest** for tests

Project dependencies are pulled by CMake through `FetchContent`.

## Description of commits
All comments are written according to [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/).