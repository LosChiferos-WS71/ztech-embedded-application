#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Flowerpot.h"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

#define DOMAIN "https://ztech-edge-server-production.up.railway.app"

#define TEMP_SENSOR_PIN 34
#define HUM_SENSOR_PIN 33
#define SUN_SENSOR_PIN 32
#define I2C_ADDR 0x27

Flowerpot flowerpot(4, TEMP_SENSOR_PIN, HUM_SENSOR_PIN, SUN_SENSOR_PIN, I2C_ADDR);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");

  flowerpot.begin();
}

void loop() {
  flowerpot.updateSensors();
  flowerpot.displayData();

  if (WiFi.status() == WL_CONNECTED) {
    sendTemperatureData(flowerpot.getFlowerpotId(), static_cast<int>(flowerpot.getTemperature()));
    sendHumidityData(flowerpot.getFlowerpotId(), static_cast<int>(flowerpot.getHumidity()));
    sendSunlightData(flowerpot.getFlowerpotId(), static_cast<int>(flowerpot.getSunlight()));
  } else {
    Serial.println("WiFi desconectado");
  }

  delay(5000); // Cambiar a 30000 (30s)
}

void sendTemperatureData(int flowerpotId, int temperature) {
  HTTPClient http;
  String url = String(DOMAIN) + "/api/v1/flowerpot/links/temperature";
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<200> jsonDoc;
  jsonDoc["flowerpotCloudId"] = flowerpotId;
  jsonDoc["temperature"] = temperature;
  
  String requestBody;
  serializeJson(jsonDoc, requestBody);

  int httpResponseCode = http.POST(requestBody);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error en la solicitud: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

void sendHumidityData(int flowerpotId, int humidity) {
  HTTPClient http;
  String url = String(DOMAIN) + "/api/v1/flowerpot/links/humidity";
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<200> jsonDoc;
  jsonDoc["flowerpotCloudId"] = flowerpotId;
  jsonDoc["humidity"] = humidity;
  
  String requestBody;
  serializeJson(jsonDoc, requestBody);

  int httpResponseCode = http.POST(requestBody);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error en la solicitud: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

void sendSunlightData(int flowerpotId, int sunlight) {
  HTTPClient http;
  String url = String(DOMAIN) + "/api/v1/flowerpot/links/sunlight";
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<200> jsonDoc;
  jsonDoc["flowerpotCloudId"] = flowerpotId;
  jsonDoc["sunlight"] = sunlight;
  
  String requestBody;
  serializeJson(jsonDoc, requestBody);

  int httpResponseCode = http.POST(requestBody);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error en la solicitud: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}