#include "LCD.h"


LCD::LCD() {
    // Конструктор
}

void LCD::begin() {
    tft.init(240, 240, SPI_MODE2);  // Инициализация экрана
    tft.setRotation(0);  // Ориентация экрана
    tft.fillScreen(ST77XX_WHITE);  // Очистка экрана
}

void LCD::displayWeather(int temp, float windSpeed, const String& windDirection, const String& sunset) {
    tft.setCursor(0, 0);
    tft.setTextColor(ST77XX_BLACK);
    tft.setTextSize(2);
    
    tft.print("Temperature: ");
    tft.println(temp);

    tft.print("Wind: ");
    tft.print(windDirection);
    tft.print(" ");
    tft.println(windSpeed);

    tft.print("Sunset: ");
    tft.println(sunset);
}

void LCD::displayInternalTemperature(int temperature) {
    tft.setCursor(0, 100);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(2);
    tft.print("Internal temp: ");
    tft.println(temperature);
}

void LCD::clearScreen() {
    tft.fillScreen(ST77XX_WHITE);  // Очистить экран
}

void LCD::printMessage(const String& message, int x, int y) {
    tft.setCursor(x, y);
    tft.print(message);
}

void LCD::update() {
    // Дополнительные обновления, если потребуется
}
