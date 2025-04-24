#ifndef WEATHER_DATA_H
#define WEATHER_DATA_H

#include <Arduino.h>

enum class PrecipitationType : uint8_t {
    None = 0,         // Без осадков
    Rain = 1,         // Дождь
    RainWithSnow = 2, // Дождь со снегом
    Snow = 3,         // Снег
    Hail = 4          // Град
};

enum class PrecipitationStrength : uint8_t {
    None = 0,
    Light = 25,     // 0.25
    Moderate = 50,  // 0.5
    Heavy = 75,     // 0.75
    VeryHeavy = 100 // 1.0
};

enum class Cloudness : uint8_t {
    Clear = 0,
    FewClouds = 25,
    PartlyCloudy = 50,
    MostlyCloudy = 75,
    Overcast = 100
};

struct FactData {
    bool is_thunder;     // Признак грозы
    short prec_type;     // Тип осадков
    int temp;            // Температура (°C)
    int feels_like;      // Ощущаемая температура (°C)
    int pressure_mm;     // Давление (в мм рт. ст.)
    int humidity;        // Влажность воздуха (в процентах)
    int temp_water;      // Температура воды (°C)
    float wind_speed;    // Скорость ветра (в м/с)
    float wind_gust;     // Скорость порывов ветра (в м/с)
    float prec_strength; // Сила осадков
    float cloudness;     // Облачность
    String condition;    // Код расшифровки погодного описания
    String wind_dir;     // Направление ветра
    String season;       // Время года в данном населенном пункте
    // String phenom_condition; // Код расшифровки дополнительного погодного описания
};

struct ForecastData {
    // short moon_code; // Код фазы Луны
    // short prec_type; // Тип осадков
    // int uv_index; // Ультрафиолетовый индекс
    // int pressure_mm; // Давление (в мм рт. ст.)
    // int humidity; // Влажность воздуха (в процентах)
    // int prec_mm; // Прогнозируемое количество осадков (в мм)
    // int prec_prob; // Вероятность выпадения осадков (в процентах)
    int week; // Порядковый номер недели
    // int temp_min; // Минимальная температура для времени суток (°C)
    // int temp_max; // Максимальная температура для времени суток (°C)
    // int temp_avg; // Средняя температура для времени суток (°C)
    // int feels_like; // Ощущаемая температура (°C)
    // float wind_speed; // Скорость ветра (в м/с)
    // float prec_strength; // Сила осадков
    // float cloudness; // Облачность
    // float wind_gust; // Скорость порывов ветра (в м/с)
    unsigned long date_ts; // Дата прогноза в формате Unixtime
    String date;           // Дата прогноза в формате ГГГГ-ММ-ДД
    String rise_begin;     // Время начала восхода Солнца
    String sunset;         // Время начала заката Солнца
                           // String condition; // Код расшифровки погодного описания
};

struct WeatherData {
    unsigned long now;     // Время сервера в формате Unixtime
    String now_dt;         // Время сервера в UTC
    FactData fact;         // Фактическая информация о погоде
    ForecastData forecast; // Прогнозная информация о погоде
};

#endif