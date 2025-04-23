#include "lcd.h"
#include "sensor_manager.h"
#include "server.h"
#include "weather_api.h"
#include "wifi_utils.h"
#include <Arduino.h>

// time_t utcTime = 0; // Текущее время в unixtime
bool isOnline = false;
TFT_eSPI tft = TFT_eSPI();
//OneWireTempSensor tempSensor1(D0);
//HumiditySensor humiditySensor1;
//LightSensor lightSensor;
SensorManager sensors;

void setup() {
    sensors.begin();
    lcdInit();
    Serial.begin(115200);
    // isOnline = connectToWiFi();
}

void loop() {
    delay(1000);
    if (isOnline)
        updateApiData();
    else
        displayLocalWeather();
}