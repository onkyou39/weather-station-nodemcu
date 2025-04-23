#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "sensor_base.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

class LightSensor : public SensorBase {
  public:
    void begin() override;
    float getLux();
    void displaySensorDetails();

  private:
    Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
};

#endif