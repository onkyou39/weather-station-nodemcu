#ifndef ONEWIRE_TEMP_SENSOR_H
#define ONEWIRE_TEMP_SENSOR_H

#include "sensor_base.h"
#include <DallasTemperature.h>
#include <OneWire.h>

class OneWireTempSensor : public SensorBase {
  public:
    OneWireTempSensor(uint8_t pin);
    void begin() override;
    float getTemperature();

  private:
    OneWire oneWire;
    DallasTemperature ds18b20;
};

#endif