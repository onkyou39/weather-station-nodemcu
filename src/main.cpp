#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include "wifi_utils.h"
#include "weather_api.h"
#include "lcd.h"

//time_t utcTime = 0; // Текущее время в unixtime
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() 
{
    lcdInit();
    Serial.begin(115200);
    connectToWiFi();
}

void loop() 
{
    delay(1000);
    updateApiData();
}