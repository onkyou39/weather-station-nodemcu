#include "humidity_sensor.h"
#include "lcd.h"
#include "one_wire_temp_sensor.h"
#include "weather_api.h"
#include "wifi_utils.h"
#include <Arduino.h>
#include <RTClib.h>
#include <Wire.h>

// time_t utcTime = 0; // Текущее время в unixtime
bool isOnline = true;
TFT_eSPI tft = TFT_eSPI();
OneWireTempSensor tempSensor1(D0);
humiditySensor humiditySensor1;

void setup() {
    tempSensor1.begin();
    humiditySensor1.begin();
    tempSensor1.getTemperature(); // Фикс ошибки при первом считывании
    lcdInit();
    Serial.begin(115200);
    // connectToWiFi();
}

void loop() {
    delay(1000);
    // updateApiData();
    displayLocalWeather();
}