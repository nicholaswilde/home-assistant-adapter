# :shield: Home Assistant Adapter (C++) :robot:

[![task](https://img.shields.io/badge/Task-Enabled-brightgreen?style=for-the-badge&logo=task&logoColor=white)](https://taskfile.dev/#/)
[![ci](https://img.shields.io/github/actions/workflow/status/nicholaswilde/home-assistant-adapter/ci.yml?label=ci&style=for-the-badge&branch=main&logo=github-actions)](https://github.com/nicholaswilde/home-assistant-adapter/actions/workflows/ci.yml)

Example firmware for the ESP32C3-based Home Assistant adapter
[available from FirstBuild](https://firstbuild.com/inventions/home-assistant-adapter/).

## :package: Hardware

The Home Assistant adapter consists of a
[Xiao ESP32C3](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/) and
[carrier board](doc/schematic-v1.0.pdf) that breaks out the serial interface of
the Xiao to an RJ45 jack.

## :hammer_and_wrench: Setup

1. Install [PlatformIO](https://platformio.org/) and [go-task](https://taskfile.dev).
2. Copy `config/Certificate.h.sample` to `config/Certificate.h` and add your
   certificate (if any).
3. Copy `config/Config.h.sample` to `config/Config.h` and add your WiFi
   credentials, MQTT configuration, and your device ID.

In-depth instructions can be found in the [Getting Started](doc/getting-started.md) guide.

## :rocket: Usage

### Build

Builds the firmware into `.pio/build/xiao_c3/firmware.bin`.

```bash
task build
```

### Clean

Deletes all build artifacts.

```bash
task clean
```

### Upload

Uploads/flashes the firmware to the ESP32-C3.

```bash
task upload
```

> [!NOTE]
> The board may need to be reset into bootloader mode by holding the B (boot)
> button and pressing the R (reset) button.

### (Serial) Monitor

Opens the PlatformIO serial monitor to view a connected ESP32-C3's serial output.

```bash
task monitor
```

## :file_folder: Example Home Assistant Configuration

Sample yaml can be found in
[home-assistant-examples](https://github.com/geappliances/home-assistant-examples).

## :balance_scale: License

​[BSD 3-Clause License](LICENSE)

## :writing_hand: Author

​This project was started in 2026 by [Nicholas Wilde][2].

[2]: <https://github.com/nicholaswilde/>
