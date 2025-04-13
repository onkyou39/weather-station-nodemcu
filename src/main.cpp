#include <Arduino.h>
#include "wifi_utils.h"
#include "weather_api.h"
/*#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "config.h" //файл конфигурации с API ключом и данными WiFi*/


void setup() 
{
    Serial.begin(115200);
    connectToWiFi();
    bool success = fetchWeatherData();
    Serial.print(success);
}

void loop() 
{
    
}