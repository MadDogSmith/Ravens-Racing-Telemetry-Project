# Phase 1 — Single Arduino to Laptop

## Objective:
Establish reliable communication between one Arduino and a Python application.

## Arduino responsibilities:
- Generate simulated telemetry data
- Output data over USB serial
- Maintain a consistent data format

## Rules:
- One packet per line
- Fixed field names and order
- Newline-terminated output

## Python responsibilities:
- Open and manage the serial connection
- Read incoming data line-by-line
- Parse telemetry fields
- Handle malformed data without crashing

## Deliverable:
- A Python script that can run continuously without failure.

## Current Status:
✅ Telemetry generation logic implemented on the Seeeduino
✅ Consistent serial data format defined and validated
✅ Python serial read and parsing logic implemented
⚠️ Toolchain integration in progress (VS Code upload workflow is not stable)

## Known Issues:
- Arduino firmware upload from VS Code is currently unreliable due to Arduino CLI / extension configuration
- Serial port conflicts can occur if multiple applications attempt to access the same COM port

## Blockers:
- VS Code Arduino extension failing to properly invoke Arduino CLI
- Manual upload via Arduino IDE may be required temporarily

## Workarounds:
- Use the Arduino IDE to compile and upload firmware while continuing Python development in VS Code
- Verify serial communication using the Arduino Serial Monitor before switching to Python

## Validation Criteria:
Telemetry data is streamed continuously over USB serial
Python successfully parses incoming packets without failure
System can run for extended periods without crashing or data corruption
