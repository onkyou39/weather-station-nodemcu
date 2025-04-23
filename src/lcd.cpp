#include "LCD.h"
#include "humidity_sensor.h"
#include "light_sensor.h"
#include "one_wire_temp_sensor.h"
#include "weather_utils.h"

void lcdInit() {
    tft.begin();
    tft.setAttribute(UTF8_SWITCH, false);
    tft.setAttribute(CP437_SWITCH, true);
    tft.setRotation(2);        // Ориентация экрана
    tft.fillScreen(TFT_WHITE); // Очистка экрана
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLACK);
}

void displayApiWeather(const WeatherData &data) {
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK);
    tft.setCursor(0, 0);
    tft.setTextSize(2);

    tft.println(utf8rus("По данным Я.погоды:"));

    tft.println(utf8rus("Температура: ") + String(data.fact.temp) + char(176) + "C");
    tft.println(utf8rus("Ощущается как: ") + String(data.fact.feels_like) + char(176) + "C");
    tft.println(utf8rus("Влажность: ") + String(data.fact.humidity) + "%");
    tft.println(utf8rus("Ветер ") + utf8rus(parseWindDirection(data.fact.wind_dir)) + ", " +
                String(data.fact.wind_speed) + utf8rus(" м/с"));
    // tft.println(utf8rus("Облачность: ") + parseCloudness(data.fact.cloudness));
    tft.println(utf8rus("Состояние: ") + utf8rus(parseCondition(data.fact.condition)));

    tft.println(utf8rus("\nПрогноз на ") + data.forecast.date + ":");
    tft.println(utf8rus("Рассвет: ") + data.forecast.rise_begin);
    tft.println(utf8rus("Закат: ") + data.forecast.sunset);
    tft.println(utf8rus("\nОбновлено: ") + parseTime(data.now));
}

void displayLocalWeather() {
    static bool initialized = false;
    extern OneWireTempSensor tempSensor1;
    extern HumiditySensor humiditySensor1;
    extern LightSensor lightSensor;

    tft.setTextSize(2);

    if (!initialized) {
        // tft.fillScreen(TFT_WHITE);
        //  Заголовки и постоянные надписи
        tft.setTextColor(TFT_BLUE, TFT_WHITE);
        tft.setCursor(0, 0);
        tft.println(utf8rus("Локальные данные"));

        // tft.setCursor(0, 30);
        tft.setTextColor(TFT_GREEN, TFT_WHITE);
        tft.println(utf8rus("Темп. датчик 1:\n"));

        // tft.setCursor(0, 60);
        tft.setTextColor(TFT_CYAN, TFT_WHITE);
        tft.println(utf8rus("Темп. датчик 2:\n"));

        // tft.setCursor(0, 90);
        tft.setTextColor(TFT_MAGENTA, TFT_WHITE);
        tft.println(utf8rus("Влажность воздуха:\n"));

        initialized = true;
    }
    tft.setTextColor(TFT_BLACK, TFT_WHITE); // Чёрный текст на белом фоне (для перезаписи)
    float temp1 = tempSensor1.getTemperature();
    float temp2 = humiditySensor1.getTemperature();
    float humidity = humiditySensor1.getHumidity();
    float light = lightSensor.getLux();
    constexpr uint8_t lineHeight = 16; // Высота строки в пикселях при размере шрифта 2

    // Температура с первого датчика
    tft.setCursor(0, lineHeight * 2); // 3 строка
    tft.print("     ");               // Очистка предыдущего значения
    tft.setCursor(0, lineHeight * 2);
    tft.print(String(temp1, 1) + (char)176 + "C");

    // Температура с датчика влажности
    tft.setCursor(0, lineHeight * 4); // 5 строка
    tft.print("     ");
    tft.setCursor(0, lineHeight * 4);
    tft.print(String(temp2, 1) + (char)176 + "C");

    // Влажность
    tft.setCursor(0, lineHeight * 6); // 7 строка
    tft.print("     ");
    tft.setCursor(0, lineHeight * 6);
    tft.print(String(humidity, 1) + "%");
}
