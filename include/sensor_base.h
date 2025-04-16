#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

//абстрактный интерфейс для сенсоров

class SensorBase {
public:
    virtual void begin() = 0;
//   virtual void update() = 0;

    virtual float getTemperature() = 0;
    virtual float getHumidity() { return -1.0f; }
    virtual float getPressure() { return -1.0f; }
    virtual float getLightLevel() { return -1.0f; }

    virtual ~SensorBase() = default;
};

#endif