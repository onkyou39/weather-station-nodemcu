#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include "wifi_utils.h"
#include "weather_api.h"
#include "lcd.h"
#include "one_wire_temp_sensor.h"

//time_t utcTime = 0; // Текущее время в unixtime
bool isOnline = true;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
OneWireTempSensor tempSensor1(D4);

void setup() 
{
    tempSensor1.begin();
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