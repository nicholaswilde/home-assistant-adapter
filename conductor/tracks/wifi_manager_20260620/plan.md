# Plan: Implement WiFi Manager for dynamic WiFi configuration

## Phase 1: Dependency Setup and Porting Connection Logic

- [x] Task: Add WiFiManager dependency [6053cb2]
    - [x] Add `tzapu/WiFiManager` dependency to `platformio.ini`
    - [x] Compile the project to verify that the library downloads and builds correctly
- [ ] Task: Integrate WiFiManager in src/main.cpp
    - [ ] Update `src/main.cpp` to include `<WiFiManager.h>`
    - [ ] Replace `configureWifi()` with WiFiManager's connection loop, setting the AP name to `HA-Adapter-<deviceId>`
    - [ ] Verify that compiling the project passes
- [ ] Task: Conductor - User Manual Verification 'Phase 1' (Protocol in workflow.md)
