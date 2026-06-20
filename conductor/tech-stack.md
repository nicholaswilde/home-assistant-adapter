# Technology Stack: Home Assistant Adapter Firmware

## Hardware Platform
- **Microcontroller:** Seeed Studio XIAO ESP32C3
  - Core: Single-core 32-bit RISC-V processor
  - Features: 2.4GHz Wi-Fi and BLE 5.0

## Build System & Toolchain
- **Toolchain:** PlatformIO
- **Core Framework:** Arduino Framework (Espressif32 platform version `^6.9.0`)
- **Standards:** C++11 (`-std=gnu11`), with strict compiler warnings active (`-Wall -Wextra -Werror`)

## Libraries & Dependencies
- **MQTT client:** `knolleary/PubSubClient@^2.8` - A client library for MQTT messaging supporting MQTT 3.1.1.
- **NTP client:** `arduino-libraries/NTPClient@^3.2.1` - Used to synchronize device time via NTP.
- **Home Assistant integration:** `geappliances/home-assistant-bridge@^1.3.0` - Specialized library for communicating with Home Assistant.

## Security & Protocols
- **Transport Security:** WiFi Client Secure (TLS) support for MQTT (optional, configurable via `#ifdef MQTT_TLS`).
