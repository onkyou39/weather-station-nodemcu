#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

// абстрактный интерфейс для сенсоров

class SensorBase {
  public:
    virtual void begin() = 0;
    virtual ~SensorBase() = default;
};

#endif