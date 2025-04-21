#include "humidity_sensor.h"

void humiditySensor::begin() {
    if (!htu.begin())
        Serial.println("Couldn't find HTU21D sensor");
}

float humiditySensor::getTemperature() {
    float temp = htu.readTemperature();
    Serial.print("Humidity temp: ");
    Serial.println(temp);
    return temp;
}

float humiditySensor::getHumidity() {
    float hum = htu.readHumidity();
    Serial.print("Humidity: ");
    Serial.println(hum);
    return hum;
}
