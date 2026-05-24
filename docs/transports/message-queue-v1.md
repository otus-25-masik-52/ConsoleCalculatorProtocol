# Message Queue Transport v1

Default topology:

- Request queue: `calculator.requests`
- Response queue: `calculator.responses`

Message body uses the same JSON representation as TCP JSON and REST.

Rules:

- `request_id` is used as correlation id.
- `reply_to` may override response queue.
- Consumer should acknowledge messages only after successful processing.
- Failed messages may be routed to a dead-letter queue.
