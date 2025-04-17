/*#include <Arduino.h>
#include "sensor_manager.h"

void SensorManager::addSensor(SensorBase *sensor) {
    sensors.push_back(sensor);
}

void SensorManager::beginAll() {
    for (auto sensor : sensors) {
        sensor->begin();
    }
}

void SensorManager::logAll() {
    for (size_t i = 0; i < sensors.size(); ++i) {
        Serial.printf("Sensor %u:\n", i + 1);
        Serial.print("  Temp: "); Serial.println(sensors[i]->getTemperature());
        Serial.print("  Hum:  "); Serial.println(sensors[i]->getHumidity());
        Serial.print("  Press:"); Serial.println(sensors[i]->getPressure());
        Serial.print("  Light:"); Serial.println(sensors[i]->getLightLevel());
    }
}*/