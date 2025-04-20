#include "LCD.h"
#include "weather_utils.h"

void lcdInit() {
    tft.init(240, 240, SPI_MODE2);  // Инициализация экрана
    tft.setRotation(0);  // Ориентация экрана
    tft.fillScreen(ST77XX_WHITE);  // Очистка экрана
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_BLACK);
    tft.cp437(true); // Необходимо для отображения символа градуса
}

void displayApiWeather(const WeatherData& data) {
    tft.fillScreen(ST77XX_WHITE);
    tft.setTextColor(ST77XX_BLACK);
    tft.setCursor(0, 0);
    tft.setTextSize(2);


    tft.println(utf8rus("По данным Я.погоды:"));
    
    tft.println(utf8rus("Температура: ") + String(data.fact.temp) + char(176) + "C");
    tft.println(utf8rus("Ощущается как: ") + String(data.fact.feels_like)+ char(176) + "C");
    tft.println(utf8rus("Влажность: ") + String(data.fact.humidity) + "%");
    tft.println(utf8rus("Ветер ") + utf8rus(parseWindDirection(data.fact.wind_dir)) + ", "  + String(data.fact.wind_speed) + utf8rus(" м/с"));
    //tft.println(utf8rus("Облачность: ") + parseCloudness(data.fact.cloudness));
    tft.println(utf8rus("Состояние: ") + utf8rus(parseCondition(data.fact.condition)));

    tft.println(utf8rus("\nПрогноз на ") + data.forecast.date + ":");
    tft.println(utf8rus("Рассвет: ") + data.forecast.rise_begin);
    tft.println(utf8rus("Закат: ") + data.forecast.sunset);
    tft.println(utf8rus("\nОбновлено: ") + parseTime(data.now));
}
