#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "config.h"  // путь до файла с WIFI_SSID и WIFI_PASSWORD
#include "lcd.h"

uint8_t tries = 20; // Число попыток подключения

bool connectToWiFi() 
{
    tft.print(utf8rus("Подключение к "));
    tft.println(WIFI_SSID);
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (tries-- && WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
        tft.print(".");
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("\nNot connected to WiFi");
        tft.fillScreen(ST77XX_WHITE);
        tft.setTextColor(ST77XX_RED);
        tft.print(utf8rus("\n\nОшибка подключения к WiFi"));
        return false;
    }
    else {
        Serial.println("\nWiFi connected");
        tft.setTextColor(ST77XX_GREEN);
        tft.print(utf8rus("\n\nПодключено"));
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        return true;
    }
}