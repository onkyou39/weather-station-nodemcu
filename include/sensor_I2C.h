#ifndef SENSOR_I2C_H
#define SENSOR_I2C_H

#include "sensor_base.h"
// #include <Adafruit_BME280.h> // для примера

class SensorI2C : public SensorBase {
public:
    SensorI2C();
    void begin() override;
    float getTemperature() override;
    float getHumidity() override;
    float getPressure() override;
    float getLightLevel() override;

private:
    // твой датчик, например:
    // Adafruit_BME280 bme;
};

#endif