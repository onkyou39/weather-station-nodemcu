#include "lcd.h"
#include "sensor_manager.h"
#include "server.h"
#include "weather_api.h"
#include "wifi_utils.h"
#include <Arduino.h>

bool isOnline = false;
TFT_eSPI tft = TFT_eSPI();
SensorManager sensors;

unsigned long lastUpdate = 0;
const unsigned long updateInterval = 1000; // 1 секунда

void setup() {
    sensors.begin();
    lcdInit();
    initServer();
    Serial.begin(115200);
    connectToWiFi();
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - lastUpdate >= updateInterval) {
        lastUpdate = currentMillis;
        sensors.updateSensors();
        if (isOnline)
        updateApiData();
        else {
            displayLocalWeather();
        }
    }
    handleServer(); //if isOnline
}