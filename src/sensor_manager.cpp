#include "sensor_manager.h"

void SensorManager::begin() {
    tempSensor1.begin();
    tempSensor1.getTemperature(); // Фикс ошибки при первом считывании
    humiditySensor1.begin();
    lightSensor1.begin();
}

void SensorManager::updateSensors() {
    temperature = tempSensor1.getTemperature();
    humidity = humiditySensor1.getHumidity();
    lux = lightSensor1.getLux();
}

float SensorManager::getTemperature() {
    return temperature;
}

float SensorManager::getHumidity() {
    return humidity;
}

float SensorManager::getLight() {
    return lux;
}
