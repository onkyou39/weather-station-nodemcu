#include "pressure_sensor.h"

#define SEALEVELPRESSURE_HPA (1013.25)

void PressureSensor::begin() {
    unsigned status;
    status = bme.begin(0x76);
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x");
        Serial.println(bme.sensorID(), 16);
    }
}

float PressureSensor::getTemperature() {
    float temperature = bme.readTemperature();
    Serial.print("BME 280 temperature = ");
    Serial.print(temperature);
    Serial.println(" °C");
    return temperature;
}

float PressureSensor::getHumidity() {
    float humidity = bme.readHumidity();
    Serial.print("BME 280 humidity = ");
    Serial.print(humidity);
    Serial.println(" %");
    return humidity;
}

float PressureSensor::getPressure() {
    float pressure = bme.readPressure() / 100.0F;
    Serial.print("BME 280 pressure = ");
    Serial.print(pressure);
    Serial.println(" hPa");
    return pressure;
}

float PressureSensor::getPressureMmHg() {
    float pressure = bme.readPressure() * 0.00750061683F;
    Serial.print("BME 280 pressure = ");
    Serial.print(pressure);
    Serial.println(" mm Hg");
    return pressure;
}

float PressureSensor::getAltitude() {
    float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    Serial.print("Approx. Altitude = ");
    Serial.print(altitude);
    Serial.println(" m");
    return altitude;
}