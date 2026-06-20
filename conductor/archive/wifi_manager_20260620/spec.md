# Specification: Implement WiFi Manager for dynamic WiFi configuration

## Overview
Currently, the Home Assistant Adapter firmware relies on hardcoded WiFi credentials defined in `Config.h`. If the WiFi network changes, the user must update the source code and reflash the firmware.
This track introduces dynamic WiFi configuration using the `tzapu/WiFiManager` library. If the device fails to connect to the saved WiFi credentials, it will spin up a local Access Point (AP) and launch a captive portal, allowing users to select a network and enter credentials dynamically via a web browser.

## Functional Requirements
- **Automated Fallback:** If the device fails to connect to the saved WiFi network within a timeout (e.g., 30 seconds), it must start an Access Point and captive portal.
- **Captive Portal UI:** The web portal must scan and list nearby WiFi networks, allowing the user to select one and input the password.
- **Persistence:** Configured credentials must be saved permanently on the device (using the library's built-in flash storage mechanism).
- **AP Configuration:** The configuration Access Point name should be unique and descriptive, incorporating the device ID (e.g., `HA-Adapter-<device_id>`).
- **Indefinite Running:** The captive portal must remain active in AP mode until a configuration is successfully saved.

## Non-Functional Requirements
- **Robustness:** Ensure connection failure handling does not crash the device or block serial communication.
- **Feedback:** Print AP status and web server port over the serial monitor for diagnostics.

## Acceptance Criteria
1. The project compiles successfully with `tzapu/WiFiManager` dependency in `platformio.ini`.
2. When booted with no saved credentials (or incorrect credentials), the device starts a WiFi Access Point with SSID `HA-Adapter-<deviceId>`.
3. The device successfully serves a captive portal configuration page.
4. Saving credentials via the portal connects the device to the new WiFi network, saves them, and subsequent boots automatically connect without launching the portal.

## Out of Scope
- Custom branded HTML/CSS styling for the captive portal interface (default library styling is sufficient for this stage).
- Dynamic MQTT broker configuration via the captive portal (configured via `Config.h` for now).
