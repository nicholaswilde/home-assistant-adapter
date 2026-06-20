# Specification: Implement Web OTA firmware updates

## Overview
Currently, the firmware can only be updated via a physical serial connection. If the device is installed in an enclosure or inside an appliance, updating the firmware is difficult and inconvenient.
This track introduces Web OTA (Over-the-Air) updates. The firmware will host a simple web page on the ESP32-C3 that is accessible via a web browser. Users will be able to upload a compiled firmware binary file (`.bin`) to update the device wirelessly over WiFi.

## Functional Requirements
- **Web OTA Endpoint:** Host an HTTP update server on port 80 (or a dedicated port) running in the background when connected to WiFi.
- **Update Web Interface:** Serve a simple upload HTML page where users can select the `.bin` file and upload it.
- **Dual Security Modes:**
  - By default, allow updates without authorization (for quick developer setup).
  - Support password protection (configurable via `#define OTA_PASSWORD "..."` or similar in `Config.h`).
- **Visual Status Feedback:** The heartbeat/status LEDs should show distinct patterns (e.g. blinking rapidly) during the upload process.
- **Post-Update Restart:** Automatically restart the ESP32-C3 after a successful update to boot into the new firmware.

## Non-Functional Requirements
- **Reliability:** Avoid bricking the device on failed uploads. The ESP32-C3 dual-partition (OTA partitions) setup should fallback to the active partition on upload failure.
- **Resource Footprint:** Ensure the HTTP update server has minimal impact on the bridge's main loop performance and serial latency.

## Acceptance Criteria
1. The project compiles successfully with standard `<WebServer.h>` and `<Update.h>` dependencies.
2. The device starts the update server in the background once WiFi is connected.
3. Accessing the device IP address (e.g. `http://<device_ip>/update`) serves the firmware upload page.
4. Uploading a valid `.bin` file successfully flashes the device and reboots it.
5. If an `OTA_PASSWORD` is configured, the browser prompts for credentials (basic auth) before showing the upload page.

## Out of Scope
- Secure updates using HTTPS (TLS web server) on the device due to resource constraints.
- Custom styled styling or logo branding of the Web OTA interface.
