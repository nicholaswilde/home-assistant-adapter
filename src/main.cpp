#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <WebServer.h>
#include <Update.h>
#include "Config.h"
#include "HomeAssistantBridge.h"

#ifdef MQTT_TLS
static WiFiClientSecure wifiClient;
#else
static WiFiClient wifiClient;
#endif
static PubSubClient mqttClient(wifiClient);
static HomeAssistantBridge bridge;
static WebServer server(80);

static void connectToWifi()
{
  if(WiFi.status() == WL_CONNECTED) {
    return;
  }

  Serial.println("Connecting to WiFi...");

  unsigned retries = 0;
  while(WiFi.status() != WL_CONNECTED) {
    if(retries++ > 100) {
      Serial.println("WiFi connection failed, restarting...");
      ESP.restart();
    }

    digitalWrite(LED_WIFI, LOW);
    delay(100);
    Serial.print(".");
  }
}

static void configureWifi()
{
  WiFiManager wm;

  // Prevent compiler warnings for unused configuration variables
  Serial.print("Default SSID: ");
  Serial.println(ssid);
  (void)password;

  // Set WiFi status LED low (indicating connecting)
  digitalWrite(LED_WIFI, LOW);

  // Set SSID for Access Point to HA-Adapter-<deviceId>
  String apName = "HA-Adapter-" + String(deviceId);

  Serial.println("Starting WiFiManager...");
  
  // Automatically connect using saved credentials,
  // or start the captive portal Access Point if connection fails
  if (!wm.autoConnect(apName.c_str())) {
    Serial.println("Failed to connect and hit timeout. Restarting...");
    delay(3000);
    ESP.restart();
  }

  // Once connected, set WiFi status LED high
  digitalWrite(LED_WIFI, HIGH);

#ifdef MQTT_TLS
#ifdef MQTT_TLS_VERIFY
  X509List* cert = new X509List(CERT);
  wifiClient.setTrustAnchors(cert);
#else
  wifiClient.setInsecure();
#endif
#endif

  Serial.println("WiFi connected");

  server.on("/update", HTTP_GET, []() {
#ifdef OTA_PASSWORD
    if (!server.authenticate("admin", OTA_PASSWORD)) {
      return server.requestAuthentication();
    }
#endif
    server.sendHeader("Connection", "close");
    server.send(200, "text/html",
      "<form method='POST' action='/update' enctype='multipart/form-data'>"
      "<input type='file' name='update'>"
      "<input type='submit' value='Update'>"
      "</form>"
    );
  });

  server.on("/update", HTTP_POST, []() {
#ifdef OTA_PASSWORD
    if (!server.authenticate("admin", OTA_PASSWORD)) {
      return server.requestAuthentication();
    }
#endif
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    delay(1000);
    ESP.restart();
  }, []() {
#ifdef OTA_PASSWORD
    if (!server.authenticate("admin", OTA_PASSWORD)) {
      return;
    }
#endif
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
      static bool ledState = false;
      ledState = !ledState;
      digitalWrite(LED_WIFI, ledState ? HIGH : LOW);
      digitalWrite(LED_MQTT, ledState ? HIGH : LOW);
      digitalWrite(LED_HEARTBEAT, ledState ? LOW : HIGH);
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) {
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });

  server.begin();
  Serial.println("HTTP update server started");
}

static void configureMqtt()
{
  mqttClient.setServer(mqtt_server, mqtt_server_port);
}

static void connectToMqtt()
{
  connectToWifi();
  digitalWrite(LED_WIFI, HIGH);

  if(!mqttClient.connected()) {
    digitalWrite(LED_MQTT, LOW);

    unsigned retries = 0;
    while(!mqttClient.connected()) {
      if(retries++ > 10) {
        Serial.println("MQTT connection failed, restarting...");
        ESP.restart();
      }

      Serial.print("Attempting MQTT connection...");

      if(mqttClient.connect(deviceId, mqttUser, mqttPassword)) {
        Serial.println("connected");
        digitalWrite(LED_MQTT, HIGH);
      }
      else {
        Serial.println("failed, rc=" + String(mqttClient.state()) + " will try again in 1 second");
        delay(1000);
      }
    }

    bridge.notifyMqttDisconnected();
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  pinMode(LED_HEARTBEAT, OUTPUT);
  pinMode(LED_WIFI, OUTPUT);
  pinMode(LED_MQTT, OUTPUT);

  configureWifi();
  configureMqtt();

  Serial1.begin(HomeAssistantBridge::baud, SERIAL_8N1, D7, D6);
  bridge.begin(mqttClient, Serial1, deviceId);
}

void loop()
{
  connectToMqtt();
  bridge.loop();
  server.handleClient();
  digitalWrite(LED_HEARTBEAT, millis() % 1000 < 500);
}
