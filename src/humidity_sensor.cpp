#include "humidity_sensor.h"

void HumiditySensor::begin() {
    if (!htu.begin())
        Serial.println("Couldn't find HTU21D sensor");
}

float HumiditySensor::getTemperature() {
    float temp = htu.readTemperature();
    Serial.print("Humidity temp: ");
    Serial.println(temp);
    return temp;
}

float HumiditySensor::getHumidity() {
    float hum = htu.readHumidity();
    Serial.print("Humidity: ");
    Serial.println(hum);
    return hum;
}
