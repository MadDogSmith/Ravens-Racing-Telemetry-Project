# Ravens Racing - Live Telemetry System

## Overview
This repository contains the Live Telemetry System developed for Ravens Racing.
The system collects, transmits, processes, and displays vehicle data in real time
to support testing, debugging, and performance analysis.

## Objectives
- Collect real-time vehicle sensor data
- Transmit telemetry data to a ground station
- Display live data for engineers and drivers
- Support post-session data analysis

## Telemetry Data
Supported data may include:
- Vehicle speed
- Throttle position
- Brake pressure
- Steering angle
- Motor RPM
- Battery voltage and current
- Temperature sensors (motor, inverter, battery)
- GPS position and lap timing

Data availability depends on vehicle configuration.

## System Architecture
Vehicle Sensors
-> On-board Controller / ECU
-> Wireless Communication Link
-> Ground Station Receiver
-> Data Processing and Visualization

## Technology Stack
- Languages: Python, C++
- Communication: CAN, Serial, UDP/TCP
- Hardware: Microcontroller-based telemetry unit
- Visualization: Custom desktop dashboard
- Version Control: Git, GitHub

## Installation
Prerequisites:
- Python 3.x
- Compatible telemetry hardware

Setup:
git clone https://github.com/<your-username>/ravens-racing-live-telemetry.git
cd ravens-racing-live-telemetry
pip install -r requirements.txt

## Usage
Run the telemetry client:
python main.py

## Development Status
This project is under active development.
Interfaces and features may change.

## Contributing
Contributions are limited to members of Ravens Racing unless approved.
All changes should follow team coding standards.

## License
This repository is for internal team use only.
Redistribution is not permitted without approval.