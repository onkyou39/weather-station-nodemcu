#include "lcd.h"
#include "sensor_manager.h"
#include "server.h"
#include "weather_api.h"
#include "wifi_utils.h"
#include <Arduino.h>
#include <OneButton.h>

bool isOnline = false;    // Офлайн режим
bool isConnected = false; // Статус подключения к WiFi
const int buttonPin = D8;
const int totalScreens = 2;
int currentScreen = 0;
unsigned long lastUpdate = 0;
const unsigned long updateInterval = 5000; // 5 секунд

TFT_eSPI tft = TFT_eSPI();
SensorManager sensors;
WeatherData weatherData; // Структура с данными о погоде
OneButton button;

void handleClick() {
    currentScreen = (currentScreen + 1) % totalScreens;
    drawScreen(currentScreen);
}

void setup() {
    button.setup(buttonPin, INPUT, false);
    button.attachClick(handleClick);
    sensors.begin();
    lcdInit();
    initServer();
    Serial.begin(115200);
    isOnline = connectToWiFi();
    if (!isOnline) {
        currentScreen = 1;
        stopServer();
    }
}

void loop() {
    button.tick(); // Обработка кнопки
    unsigned long currentMillis = millis();
    if (currentMillis - lastUpdate >= updateInterval) {
        lastUpdate = currentMillis;

        isConnected = connectionStatus(); // Проверка подключения к WiFi

        if (!isConnected && isOnline) { // Случай с отключением WiFi во время работы
            isOnline = false;
            displayLocalWeather(true); // Cброс экрана для отображения предупреждения о офлайн режиме
            currentScreen = 1;         // Переход на экран с локальными данными
            stopServer();              // Выключение локального сервера
        }

        sensors.updateSensors();

        switch (currentScreen) {
        case 1:
            drawScreen(currentScreen); // Обновление данных с локальных сенсоров
            break;

        default:
            updateApiData(); // Отрисовка данных с API через интервал
            break;
        }
    }
    if (isConnected)
        handleServer(); // Обработка HTTP-запросов
}