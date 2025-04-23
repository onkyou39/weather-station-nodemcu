#include "light_sensor.h"

void LightSensor::begin() {
    if (!tsl.begin()) {
        Serial.println("No TSL2561 detected");
        return;
    }
    tsl.enableAutoRange(true);                             // Автоматическая настройка усиления
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS); // Средняя точность измерения
}

float LightSensor::getLux() {

    sensors_event_t event;
    tsl.getEvent(&event);

    if (event.light) {
        Serial.print(event.light);
        Serial.println(" lux");
        return event.light;
    } else {
        Serial.println("Sensor overload");
        return 0; // ошибка
    }
}

void LightSensor::displaySensorDetails() {
    sensor_t sensor;
    tsl.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print("Sensor:       ");
    Serial.println(sensor.name);
    Serial.print("Driver Ver:   ");
    Serial.println(sensor.version);
    Serial.print("Unique ID:    ");
    Serial.println(sensor.sensor_id);
    Serial.print("Max Value:    ");
    Serial.print(sensor.max_value);
    Serial.println(" lux");
    Serial.print("Min Value:    ");
    Serial.print(sensor.min_value);
    Serial.println(" lux");
    Serial.print("Resolution:   ");
    Serial.print(sensor.resolution);
    Serial.println(" lux");
    Serial.println("------------------------------------");
    Serial.println("");
}