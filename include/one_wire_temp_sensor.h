#ifndef ONEWIRE_TEMP_SENSOR_H
#define ONEWIRE_TEMP_SENSOR_H

#include "sensor_base.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class OneWireTempSensor : public SensorBase {
    public:
        OneWireTempSensor(uint8_t pin);
        void begin() override;
        float getTemperature();
    
    private:
        OneWire oneWire;
        DallasTemperature ds18b20;
    };

extern OneWireTempSensor tempSensor1;

#endif