# Product Guidelines: Home Assistant Adapter Firmware

## 1. Development & Design Principles

- **Reliability First:** Firmware must be self-healing. Any connection loss (WiFi or MQTT) should trigger retries, and persistent failures must trigger a system restart.
- **Non-blocking Loop:** The main loop (`loop()`) must remain non-blocking. Avoid long delays (`delay()`) inside main loops; use timer variables or non-blocking schedules where possible to maintain responsiveness.
- **State Feedback (LEDs):** Keep the user informed of the hardware state:
    - Heartbeat: Blinking at 1Hz indicates normal system operation.
    - WiFi LED: ON when connected to WiFi, blinking during connection.
    - MQTT LED: ON when connected to broker, blinking during connection.
- **Descriptive Logging:** Serial output must use standard prefixes (e.g., `[WIFI]`, `[MQTT]`, `[BRIDGE]`, `[ERROR]`) for easier diagnostics and debugging.

## 2. Communication Standards

- **Topic Naming:** MQTT topics must follow a clean, hierarchical structure, incorporating the device ID:
    - `homeassistant/sensor/<device_id>/config` (for discovery)
    - `<device_id>/status` (for availability/online status)
    - `<device_id>/command` (for incoming commands)
- **JSON Payloads:** Structured data payloads should be encoded as compact JSON to minimize transmission overhead and maintain compatibility with Home Assistant parsers.

## 3. Documentation Style

- **Clear Instructions:** Setup and customization instructions (like configuring Config.h) must be written in a step-by-step, plain-text format.
- **Security Warning:** Explicitly instruct users never to commit files containing credentials (like Config.h or Certificate.h) to version control.
