#ifndef FLOWERPOT_H
#define FLOWERPOT_H

#include <Arduino.h>
#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "SunlightSensor.h"
#include <LiquidCrystal_I2C.h>

class Flowerpot {
  public:
    Flowerpot(int id, uint8_t tempPin, uint8_t humPin, uint8_t sunPin, uint8_t lcdAddr);
    void begin();
    void updateSensors();
    void displayData();
    int getFlowerpotId();
    float getTemperature();
    float getHumidity();
    float getSunlight();

  private:
    int flowerpotId;
    TemperatureSensor tempSensor;
    HumiditySensor humSensor;
    SunlightSensor sunSensor;
    LiquidCrystal_I2C lcd;
    float temperature;
    float humidity;
    float sunlight;
};

#endif