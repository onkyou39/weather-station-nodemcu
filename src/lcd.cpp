#include "lcd.h"
#include "sensor_manager.h"
#include "weather_api.h"
#include "weather_utils.h"
#include "wifi_utils.h"

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

void displayLocalWeather(bool reset) {
    static bool initialized = false;
    extern bool isOnline;
    extern bool isConnected;
    extern SensorManager sensors;
    constexpr uint8_t lineHeight = 16; // Высота строки в пикселях при размере шрифта 2

    // TextSize(1) → каждый символ: 6×8 пикселей (5 + 1 на отступ по ширине, и 7 + 1 по высоте)
    // TextSize(2) → каждый символ: 12×16 пикселей
    // TextSize(3) → 18×24 пикселя

    if (reset) {
        initialized = false;
        return;
    }

    tft.setTextSize(2);

    if (!initialized) {
        tft.setTextColor(TFT_BLACK, TFT_WHITE);

        tft.fillScreen(TFT_WHITE);
        //  Заголовки и постоянные надписи
        // tft.setTextColor(TFT_BLUE, TFT_WHITE);
        tft.setCursor(0, 0);
        tft.println(utf8rus("Локальные данные\n"));

        // tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.println(utf8rus("Температура:\n"));

        // tft.setTextColor(TFT_MAGENTA, TFT_WHITE);
        tft.println(utf8rus("Влажность воздуха:\n"));

        // tft.setTextColor(TFT_CYAN, TFT_WHITE);
        tft.println(utf8rus("Освещенность:\n"));

        tft.println(utf8rus("Атмосферное давление\n"));

        if (isOnline) {
            tft.setCursor(0, lineHeight * 13);
            tft.println(utf8rus("IP-адрес:"));
            tft.print(getIP());
        } else if (!isConnected) {
            tft.setCursor(0, lineHeight * 14);
            tft.setTextColor(TFT_RED, TFT_WHITE);
            tft.print(utf8rus("Офлайн режим"));
        } else {
            tft.setCursor(0, lineHeight * 12);
            tft.println(utf8rus("IP-адрес:"));
            tft.println(getIP());
            tft.setTextColor(TFT_RED, TFT_WHITE);
            tft.print(utf8rus("Ошибка API"));
        }

        initialized = true;
    }

    tft.setTextColor(TFT_BLACK, TFT_WHITE); // Чёрный текст на белом фоне (для перезаписи)
    float temp = sensors.getTemperature();
    float humidity = sensors.getHumidity();
    float light = sensors.getLight();
    float pressure = sensors.getPressure();

    // Температура с первого датчика
    tft.setCursor(0, lineHeight * 3); // 4 строка
    tft.print("     ");               // Очистка предыдущего значения
    tft.setCursor(0, lineHeight * 3);
    tft.print(String(temp, 1) + (char)176 + "C");

    // Влажность
    tft.setCursor(0, lineHeight * 5); // 6 строка
    tft.print("     ");
    tft.setCursor(0, lineHeight * 5);
    tft.print(String(humidity, 1) + "%");

    // Освещённость
    tft.setCursor(0, lineHeight * 7); // 8 строка
    tft.print("          ");
    tft.setCursor(0, lineHeight * 7);
    tft.print(String((int)light) + " lux");

    // Давление
    tft.setCursor(0, lineHeight * 9); // 10 строка
    tft.print("                   ");
    tft.setCursor(0, lineHeight * 9);
    tft.print(String((int)pressure));
    tft.print(utf8rus(" мм рт. ст."));
}

void drawScreen(int screen) {
    extern WeatherData weatherData;
    switch (screen) {
    case 0:
        displayLocalWeather(true);      // Сброс экрана локальных данных
        updateApiData(false);           // Устранение двойной отрисовки
        displayApiWeather(weatherData); // Если данные не обновились, отрисовка старых
        break;
    case 1:
        displayLocalWeather(); // перерисовка
        break;
    }
}