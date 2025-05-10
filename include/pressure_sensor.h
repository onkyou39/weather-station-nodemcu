#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include "sensor_base.h"
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class PressureSensor : public SensorBase {
  public:
    void begin() override;
    float getTemperature();
    float getHumidity();
    float getPressure();     // Давление в гектопаскалях
    float getPressureMmHg(); // Давление в мм. рт. ст.
    float getAltitude();

  private:
    Adafruit_BME280 bme;
};

#endif