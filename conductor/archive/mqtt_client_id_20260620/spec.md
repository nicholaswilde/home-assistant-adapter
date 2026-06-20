# Specification: Use deviceId as the MQTT client identifier

## Problem

In `src/main.cpp`, the MQTT client connects to the broker using an empty client identifier (`""`):

```cpp
if(mqttClient.connect("", mqttUser, mqttPassword)) {
```

While an empty client identifier is allowed by the MQTT 3.1.1 specification (prompting the broker to generate a random identifier), it makes tracking, access control, and troubleshooting difficult. The device ID configuration is already defined in `Config.h` but is not utilized for the MQTT connection.

## Proposed Solution

Update `connectToMqtt()` in `src/main.cpp` to pass the configured `deviceId` as the client identifier:

```cpp
if(mqttClient.connect(deviceId, mqttUser, mqttPassword)) {
```

## Impacted Files

- `src/main.cpp`

## Verification Plan

1. Compile the code using `make` to verify that there are no compilation errors.
2. Manually flash the firmware to an ESP32-C3 device and verify that it connects to the MQTT broker using the configured `deviceId`.
