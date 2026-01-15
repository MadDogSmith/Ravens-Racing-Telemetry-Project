# Ravens Racing Live Telemetry System
## Project Startup Outline

This document defines the recommended approach for developing the Ravens Racing
Live Telemetry System. It is intended to guide long-term development and ensure
the project is built in a structured, professional, and maintainable manner.

--------------------------------------------------

## 0. Project Scope Definition

Version 1:
- One Arduino generates telemetry data (simulated initially)
- Data is transmitted to a second Arduino
- Second Arduino forwards data to a laptop via USB serial
- Python reads and parses serial data
- A basic frontend displays live numeric values


--------------------------------------------------

## 1. Target System Architecture

Sensors
-> Arduino A (Vehicle Side)
-> Arduino B (Base Station)
-> Python Backend
-> Frontend Visualization

--------------------------------------------------

## 2. Phase 1 — Single Arduino to Laptop

Objective:
Establish reliable communication between one Arduino and a Python application.

Arduino responsibilities:
- Generate simulated telemetry data
- Output data over USB serial
- Maintain a consistent data format

Rules:
- One packet per line
- Fixed field names and order
- Newline-terminated output

Python responsibilities:
- Open and manage the serial connection
- Read incoming data line-by-line
- Parse telemetry fields
- Handle malformed data without crashing

Deliverable:
A Python script that can run continuously without failure.

--------------------------------------------------

## 3. Phase 2 — Dual Arduino Communication

Objective:
Transmit telemetry data between two Arduinos before forwarding to the laptop.

Communication method:
- UART (TX/RX)
- Shared ground between boards

Arduino A (Transmitter):
- Generate telemetry packets
- Send packets over UART

Arduino B (Receiver):
- Receive packets from Arduino A
- Forward packets unchanged to USB serial

The Python backend should not change between Phase 1 and Phase 2.

--------------------------------------------------

## 4. Phase 3 — Telemetry Protocol Definition

A formal telemetry protocol must be defined and versioned.

Telemetry Packet v1 fields:
- TIME (milliseconds)
- SPEED (float, m/s)
- RPM (integer)
- THROTTLE (float, 0–1)

Example packet:
TIME=124532,SPEED=12.3,RPM=4021,THROTTLE=0.58

Protocol rules:
- Fixed field names and units
- No optional fields in v1
- Backward compatibility for future versions

--------------------------------------------------

## 5. Phase 4 — Python Backend Architecture

Objective:
Centralize telemetry handling in Python.

Recommended structure:
/backend
- serial_interface.py
- parser.py
- telemetry_state.py
- main.py

Responsibilities:
- Read and validate serial data
- Parse telemetry packets into structured objects
- Maintain the latest telemetry state in memory
- Provide clean interfaces for frontend use

No visualization should be implemented during this phase.

--------------------------------------------------

## 6. Phase 5 — Frontend Visualization

Objective:
Display live telemetry data in a stable interface.

Acceptable approaches:
- Python + Tkinter
- Python + PyQt
- Python backend + web frontend (Flask + JavaScript)

Minimum frontend requirements:
- Live numeric telemetry values
- Connection status indicator
- Update rate visibility

Graphs and advanced UI features should be added later.

--------------------------------------------------

## 7. Phase 6 — Reliability and Logging

Professional system requirements:
- Timestamped data logging (CSV or similar)
- Connection loss detection
- Automatic reconnection handling
- Graceful failure without crashes

--------------------------------------------------

## 8. Versioning and Milestones

Recommended tags:
- v0.1 — Single Arduino to Python
- v0.2 — Dual Arduino communication
- v0.3 — Telemetry protocol finalized
- v0.4 — Live dashboard implemented
- v1.0 — Track-ready system

--------------------------------------------------

## 9. Short-Term Development Plan

Week 1 priorities:
- Implement Arduino telemetry output
- Develop Python serial reader and parser
- Validate long-duration stability
- Add second Arduino passthrough

Frontend development should only begin after these steps are complete.

--------------------------------------------------

## Notes

This project prioritizes reliability, clarity, and incremental development.
Each subsystem must be validated independently before integration.
