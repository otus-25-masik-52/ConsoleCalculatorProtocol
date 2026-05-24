# gRPC Transport v1

The gRPC representation must preserve the same semantic model as `CalculationRequest` and `CalculationResponse`.

Service:

```proto
service CalculatorService {
  rpc Calculate(CalculationRequest) returns (CalculationResponse);
}
```

The `.proto` schema lives in `schemas/proto/calculator.proto`.
