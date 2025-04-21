#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include "wifi_utils.h"
#include "weather_api.h"
#include "lcd.h"
#include "one_wire_temp_sensor.h"

//time_t utcTime = 0; // Текущее время в unixtime
bool isOnline = true;
TFT_eSPI tft = TFT_eSPI();
OneWireTempSensor tempSensor1(D2);

void setup() 
{
    tempSensor1.begin();
    tempSensor1.getTemperature(); // Фикс ошибки при первом считывании
    lcdInit();
    Serial.begin(115200);
    //connectToWiFi();
}

void loop() 
{
    delay(1000);
    //updateApiData();
    displayLocalWeather();
}