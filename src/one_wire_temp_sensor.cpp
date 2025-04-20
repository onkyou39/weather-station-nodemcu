#include "one_wire_temp_sensor.h"

OneWireTempSensor::OneWireTempSensor(uint8_t pin) 
    : oneWire(pin), ds18b20(&oneWire) {}

void OneWireTempSensor::begin() {
    ds18b20.begin();
    ds18b20.setWaitForConversion(false); //минимизирует задержку в библиотеке
}

float OneWireTempSensor::getTemperature() {
    //ds18b20.requestTemperatures();
    ds18b20.requestTemperaturesByIndex(0);
    
    float tempC = ds18b20.getTempCByIndex(0);
    Serial.println(tempC);
    return isnan(tempC) ? -127.0f : tempC;
}