# Plan: Implement Web OTA firmware updates

## Phase 1: Integrate Web OTA Server

- [x] Task: Configure Partition Table for OTA (Verified that default.csv has two 1.25MB OTA partitions, which is sufficient) [3d917d5]
    - [x] Inspect default partition table used in `platformio.ini`
    - [x] If necessary, configure/assert custom partition layout to support two OTA partitions
- [x] Task: Implement Web Update Server in main.cpp [839124e]
    - [x] Update `src/main.cpp` to include `<WebServer.h>` and `<Update.h>`
    - [x] Create a `WebServer` instance running on port 80
    - [x] Add update route `http://<device_ip>/update` that handles file upload using `Update` class
    - [x] Implement optional Basic Authentication check if `OTA_PASSWORD` is defined in `Config.h`
    - [x] Compile the project to verify that it builds successfully
- [ ] Task: Conductor - User Manual Verification 'Phase 1' (Protocol in workflow.md)
