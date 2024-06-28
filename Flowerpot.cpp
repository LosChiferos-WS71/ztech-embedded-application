#include "Flowerpot.h"

Flowerpot::Flowerpot(int id, uint8_t tempPin, uint8_t humPin, uint8_t sunPin, uint8_t lcdAddr)
  : flowerpotId(id), tempSensor(tempPin), humSensor(humPin), sunSensor(sunPin), lcd(lcdAddr, 16, 2) {}

void Flowerpot::begin() {
  tempSensor.begin();
  humSensor.begin();
  sunSensor.begin();
  lcd.init();
  lcd.backlight();
}

void Flowerpot::updateSensors() {
  temperature = tempSensor.readTemperature();
  humidity = humSensor.readHumidity();
  sunlight = sunSensor.readSunlight();
}

void Flowerpot::displayData() {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C  ");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" %");

  lcd.setCursor(8, 1);
  lcd.print("Sun: ");
  lcd.print(sunlight);
  lcd.print(" UV");
}

int Flowerpot::getFlowerpotId() {
  return flowerpotId;
}

float Flowerpot::getTemperature() {
  return temperature;
}

float Flowerpot::getHumidity() {
  return humidity;
}

float Flowerpot::getSunlight() {
  return sunlight;
}