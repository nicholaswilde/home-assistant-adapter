# Plan: Use deviceId as the MQTT client identifier

## Phase 1: Update MQTT Connection

- [ ] Task: Update the MQTT client connection code to use deviceId
    - [ ] Analyze `src/main.cpp` connection logic
    - [ ] Modify `src/main.cpp` to use `deviceId` instead of `""` in the `mqttClient.connect()` call
    - [ ] Run `make` to compile the firmware and verify build success
- [ ] Task: Conductor - User Manual Verification 'Phase 1' (Protocol in workflow.md)
