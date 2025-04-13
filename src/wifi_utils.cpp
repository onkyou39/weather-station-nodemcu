#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "config.h"  // путь до файла с WIFI_SSID и WIFI_PASSWORD

void connectToWiFi() 
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}