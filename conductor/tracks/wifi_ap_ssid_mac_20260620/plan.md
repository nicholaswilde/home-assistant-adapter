# Plan: Dynamic WiFi AP SSID with Abbreviated MAC Address

## Phase 1: Implement Dynamic WiFi AP SSID

- [ ] Task: Implement dynamic SSID generation in `src/main.cpp`
    - [ ] Retrieve WiFi MAC address inside `configureWifi()`
    - [ ] Extract the last 3 octets (6 hex characters) and convert to uppercase
    - [ ] Retrieve `deviceId` from `Config.h`
    - [ ] Concatenate `<deviceId>-<short mac address>` to form the SSID
    - [ ] Pass the constructed SSID to `wm.autoConnect()`
- [ ] Task: Build project and verify compilation
    - [ ] Run `task build` to verify compilation succeeds without warning or error
- [ ] Task: Conductor - User Manual Verification 'Phase 1' (Protocol in workflow.md)
