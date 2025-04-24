#include "lcd.h"
#include "sensor_manager.h"
#include "server.h"
#include "weather_api.h"
#include "wifi_utils.h"
#include <Arduino.h>
#include <OneButton.h>

bool isOnline = false;
const int buttonPin = D8;
const int totalScreens = 2;
int currentScreen = 0;
unsigned long lastUpdate = 0;
const unsigned long updateInterval = 1000; // 1 секунда

TFT_eSPI tft = TFT_eSPI();
SensorManager sensors;
WeatherData weatherData; // Структура с данными о погоде
OneButton button(buttonPin, true, true);

void drawScreen(int screen) {
    switch (screen) {
    case 0:
        displayLocalWeather(true);
        updateApiData(false);           // Устранение двойной отрисовки
        displayApiWeather(weatherData); // Если данные не обновились, отрисовка старых
        break;
    case 1:
        displayLocalWeather(); // перерисовка
        break;
    }
}

void handleClick() {
    currentScreen = (currentScreen + 1) % totalScreens;
    drawScreen(currentScreen);
}

void setup() {
    button.attachClick(handleClick);
    sensors.begin();
    lcdInit();
    initServer();
    Serial.begin(115200);
    isOnline = connectToWiFi();
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - lastUpdate >= updateInterval) {
        lastUpdate = currentMillis;

        if (!connectionStatus())
            isOnline = false;
        if (!isOnline){
            currentScreen = 1;
            //displayLocalWeather(true); // сброс экрана для отображения предупреждения о офлайн режиме
        }

        sensors.updateSensors();

        switch (currentScreen) {
        case 1:
            drawScreen(currentScreen); // Обновление данных с локальных сенсоров
            break;

        default:
            updateApiData();
            break;
        }
    }

    if (isOnline) {
        handleServer(); // обработка HTTP-запросов
        button.tick();  // обработка кнопки
    }
}