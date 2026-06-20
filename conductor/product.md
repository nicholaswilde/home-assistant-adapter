# Product Guide: Home Assistant Adapter Firmware

## Product Vision

The ESP32C3-based Home Assistant adapter firmware acts as a reliable, secure, and easy-to-use bridge between local serial devices and a Home Assistant home automation server. It empowers users to integrate legacy or non-smart serial appliances into their Home Assistant smart home system via MQTT, utilizing standard IoT protocols (WiFi, MQTT, Arduino, and Home Assistant Discovery).

## Target Audience

- **Home automation enthusiasts** looking to integrate serial-communicating appliances (e.g., GE appliances, smart meters, HVAC systems) into Home Assistant.
- **Hardware developers and makers** utilizing the ESP32-C3 based FirstBuild carrier board for smart home projects.

## Core Features

1. **Serial-to-MQTT Bridge:** Seamlessly forward data from the hardware serial port (RJ45 breakout) of the carrier board to MQTT topics and vice versa.
2. **Home Assistant Integration:** Integrate with Home Assistant using the `home-assistant-bridge` library for automatic discovery or manual entity configuration.
3. **Dynamic WiFi Configuration & Captive Portal:** Automatically falls back to a temporary Access Point and captive portal (SSID: `HA-Adapter-<deviceId>`) to configure WiFi credentials dynamically via a web browser if connections fail. Standard automated connection management and watchdog resets remain active.
4. **Status Indicators:** LED status feedback for WiFi connectivity, MQTT broker connection status, and heartbeat activity.
5. **Configurable Settings:** Externalized certificates and broker configurations for custom MQTT environments (supported via Certificate.h and Config.h), while WiFi credentials are dynamically configured.
6. **TLS Support (Optional):** Secure connection to the MQTT broker using TLS with optional server certificate validation.

## Hardware Details

- **Microcontroller:** Xiao ESP32C3 (Espressif ESP32-C3 single-core RISC-V processor).
- **Carrier Board:** FirstBuild Home Assistant Adapter board breaking out Xiao serial lines (D6/TX, D7/RX) to an RJ45 jack.
- **LED Mappings:**
    - D0: Heartbeat LED (LED_HEARTBEAT).
    - D1: MQTT status LED (LED_MQTT).
    - D2: WiFi status LED (LED_WIFI).
