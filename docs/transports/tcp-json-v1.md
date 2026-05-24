# TCP JSON Transport v1

- Transport: TCP.
- Encoding: UTF-8.
- Framing: newline-delimited JSON.
- One request: one JSON object followed by `\n`.
- One response: one JSON object followed by `\n`.
- Recommended max message size: 64 KiB.
- Connection may carry one or many requests.
