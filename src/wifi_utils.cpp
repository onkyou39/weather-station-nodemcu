#include "wifi_utils.h"
#include "config.h" // путь до файла с WIFI_SSID и WIFI_PASSWORD
#include "lcd.h"
#include <ESP8266WiFi.h>

uint8_t tries = 20; // Число попыток подключения

bool connectToWiFi() {
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

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("\nNot connected to WiFi");
        tft.fillScreen(TFT_WHITE);
        tft.setTextColor(TFT_RED);
        tft.println(utf8rus("\n\nОшибка подключения к WiFi"));
        tft.setTextColor(TFT_BLACK);
        tft.print(utf8rus("Переход в offline режим"));
        delay(2000);
        return false;
    } else {
        Serial.println("\nWiFi connected");
        tft.setTextColor(TFT_GREEN);
        tft.print(utf8rus("\n\nПодключено"));
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        return true;
    }
}

bool connectionStatus() {
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    } else {
        return false;
    }
}

String getIP() {
    return WiFi.localIP().toString();
}
