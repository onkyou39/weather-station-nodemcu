#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include "wifi_utils.h"
#include "weather_api.h"
#include "lcd.h"

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() 
{
    lcdInit();
    Serial.begin(115200);
    connectToWiFi();
}

void loop() 
{
    //updateApiData();
    delay(1000);
}