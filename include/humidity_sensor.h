#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include "Adafruit_HTU21DF.h"
#include "sensor_base.h"

class HumiditySensor : public SensorBase {
  public:
    void begin() override;
    float getTemperature();
    float getHumidity();

  private:
    Adafruit_HTU21DF htu = Adafruit_HTU21DF();
};
#endif