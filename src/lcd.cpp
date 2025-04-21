#include "LCD.h"
#include "weather_utils.h"
#include "one_wire_temp_sensor.h"
#include "humidity_sensor.h"

void lcdInit() {
    tft.begin();
    tft.setAttribute(UTF8_SWITCH, false);
    tft.setAttribute(CP437_SWITCH, true);
    tft.setRotation(2);  // Ориентация экрана
    tft.fillScreen(TFT_WHITE);  // Очистка экрана
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLACK);
}

void displayApiWeather(const WeatherData& data) {
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK);
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


TFT_eSprite localWeatherSprite = TFT_eSprite(&tft);

void initSprites() {
    localWeatherSprite.setColorDepth(8);
    localWeatherSprite.createSprite(240, 80); // Пример: одна строка заголовка + температура
    localWeatherSprite.setTextColor(TFT_BLACK, TFT_WHITE);
    localWeatherSprite.setTextSize(2);
}

extern OneWireTempSensor tempSensor1;
extern humiditySensor humiditySensor1;
  
void displayLocalWeather() {
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK);
    tft.setCursor(0, 0);
    tft.setTextSize(2);

    tft.println(utf8rus("Локальные данные:"));
    tft.println(utf8rus("Темп. датчик 1: ") + String(tempSensor1.getTemperature(), 1) + char(176) + "C");
    tft.println(utf8rus("Темп. с д. вл. :") + String(humiditySensor1.getTemperature(), 1) + char(176) + "C");
    tft.println(utf8rus("Влажность воздуха: ") + String(humiditySensor1.getHumidity()) + "%");
}