#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "humidity_sensor.h"
#include "light_sensor.h"
#include "one_wire_temp_sensor.h"
#include "pressure_sensor.h"

class SensorManager {
  public:
    void begin();
    void updateSensors();
    float getTemperature();
    float getHumidity();
    float getLight();
    float getPressure();

  private:
    OneWireTempSensor tempSensor1{D0};
    HumiditySensor humiditySensor1;
    LightSensor lightSensor1;
    PressureSensor pressureSensor1;

    float temperature = 0;
    float humidity = 0;
    float lux = 0;
    float pressure = 0;
};

#endif
