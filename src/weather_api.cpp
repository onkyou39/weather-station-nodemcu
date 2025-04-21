#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "config.h"
#include "weather_data.h"
#include "lcd.h"

unsigned long lastApiRequestTime = 0; // Время последнего запроса к API
const unsigned long apiUpdateInterval = 7200000; // Интервал для обновления API в миллисекундах (2 часа)

WeatherData weatherData; // Структура с данными о погоде


JsonDocument ApiRequest() {
    auto client = std::make_unique<BearSSL::WiFiClientSecure>();
    client->setInsecure(); // отключаем проверку SSL
    HTTPClient https;
    https.useHTTP10(true); //запрет chunked mode, принудительный HTTP 1.0
    https.setTimeout(10000); //фикс ошибки IncompleteInput, таймаут потока на 10 секунд
    String url = "https://api.weather.yandex.ru/v2/forecast?lat=" LATITUDE "&lon=" LONGITUDE "&limit=1";
    Serial.print("\n[HTTPS] begin...\n");

    JsonDocument doc;
    JsonDocument filter;
    filter["now"] = true;
    filter["now_dt"] = true;

    JsonObject filter_fact = filter["fact"].to<JsonObject>();
    filter_fact["obs_time"] = true;
    filter_fact["season"] = true;
    filter_fact["source"] = true;
    filter_fact["uptime"] = true;
    filter_fact["cloudness"] = true;
    filter_fact["condition"] = true;
    filter_fact["feels_like"] = true;
    filter_fact["humidity"] = true;
    filter_fact["is_thunder"] = true;
    filter_fact["polar"] = true;
    filter_fact["prec_prob"] = true;
    filter_fact["prec_strength"] = true;
    filter_fact["prec_type"] = true;
    filter_fact["pressure_mm"] = true;
    filter_fact["pressure_pa"] = true;
    filter_fact["temp"] = true;
    filter_fact["uv_index"] = true;
    filter_fact["wind_angle"] = true;
    filter_fact["wind_dir"] = true;
    filter_fact["wind_gust"] = true;
    filter_fact["wind_speed"] = true;

    JsonObject filter_forecasts_0 = filter["forecasts"].add<JsonObject>();
    filter_forecasts_0["date"] = true;
    filter_forecasts_0["date_ts"] = true;
    filter_forecasts_0["week"] = true;
    filter_forecasts_0["sunrise"] = true;
    filter_forecasts_0["sunset"] = true;
    filter_forecasts_0["rise_begin"] = true;
    filter_forecasts_0["set_end"] = true;
    filter_forecasts_0["moon_code"] = true;
    filter_forecasts_0["moon_text"] = true;

    if (https.begin(*client, url)) {
        https.addHeader("X-Yandex-Weather-Key", API_KEY);
  

        int httpCode = https.GET();

        // в случае ошибки httpCode будет отрицательным
        if (httpCode > 0) {
            Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

            // если файл найден на сервере
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                DeserializationError error = deserializeJson(doc, https.getStream(), DeserializationOption::Filter(filter));
                if (error) {
                    Serial.print("deserializeJson failed: ");
                    Serial.println(error.c_str());
                    doc.clear();
                    https.end();
                } else Serial.println("Payload received");
            }
        } else {
            Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
        https.end();
    } else Serial.printf("[HTTPS] Unable to connect\n");
    return doc;
}


bool fetchWeatherData() {
    Serial.println("Trying receive data from API...");
    JsonDocument doc = ApiRequest();
    if (doc.isNull()) {
            Serial.println("Json data error, empty payload");
            return false;
    }
    serializeJsonPretty(doc, Serial); // Для отладки

    // Устанавливаем время с сервера
    weatherData.now = doc["now"];
    Serial.print("\n\nServer UnixTime: "); Serial.println(weatherData.now);
    weatherData.now_dt = doc["now_dt"].as<String>();
    Serial.print("Server Time (String): "); Serial.println(weatherData.now_dt);
    
    
    // Фактическая информация о погоде
    JsonObject fact = doc["fact"];
    FactData factData;

    factData.is_thunder = fact["is_thunder"];
    factData.temp = fact["temp"];
    factData.feels_like = fact["feels_like"];
    //factData.pressure_mm = fact["pressure_mm"];
    factData.humidity = fact["humidity"];
    //factData.temp_water = fact["temp_water"];
    factData.wind_speed = fact["wind_speed"];
    factData.wind_gust = fact["wind_gust"];
    factData.condition = fact["condition"].as<String>();
    factData.wind_dir = fact["wind_dir"].as<String>();
    factData.season = fact["season"].as<String>();
    factData.cloudness = fact["cloudness"];
    factData.prec_type = fact["prec_type"];
    factData.prec_strength = fact["prec_strength"];
    
    weatherData.fact = factData;

    Serial.println("\nFact Data:");

    Serial.print("Is Thunder: "); Serial.println(factData.is_thunder);
    Serial.print("Temperature: "); Serial.println(factData.temp);
    Serial.print("Feels Like: "); Serial.println(factData.feels_like);
    //Serial.print("Pressure (mm Hg): "); Serial.println(factData.pressure_mm);
    Serial.print("Humidity: "); Serial.println(factData.humidity);
    //Serial.print("Water Temperature: "); Serial.println(factData.temp_water);
    Serial.print("Wind Speed: "); Serial.println(factData.wind_speed);
    Serial.print("Wind Gust: "); Serial.println(factData.wind_gust);
    Serial.print("Precipitation Strength: "); Serial.println(factData.prec_strength);
    Serial.print("Precipitation Type: "); Serial.println(factData.prec_type);
    Serial.print("Cloudiness: "); Serial.println(factData.cloudness);
    Serial.print("Condition: "); Serial.println(factData.condition);
    Serial.print("Wind Direction: "); Serial.println(factData.wind_dir);



    // Прогнозная информация о погоде
    JsonObject forecast = doc["forecasts"][0];
    ForecastData forecastData;

    forecastData.week = forecast["week"];
    forecastData.date_ts = forecast["date_ts"];
    forecastData.date = forecast["date"].as<String>();
    forecastData.rise_begin = forecast["rise_begin"].as<String>();
    forecastData.sunset = forecast["sunset"].as<String>();

    weatherData.forecast = forecastData;

    Serial.println("\nForecast Data:");

    Serial.print("Week: "); Serial.println(forecastData.week);
    Serial.print("Date TS (Unixtime): "); Serial.println(forecastData.date_ts);
    Serial.print("Date (YYYY-MM-DD): "); Serial.println(forecastData.date);
    Serial.print("Rise Begin: "); Serial.println(forecastData.rise_begin);
    Serial.print("Sunset: "); Serial.println(forecastData.sunset);
    return true;
}

//функция запроса через интервал
void updateApiData() {
    JsonDocument doc;
    unsigned long currentTime = millis();
    if (currentTime - lastApiRequestTime >= apiUpdateInterval || lastApiRequestTime == 0) {
        tft.setTextColor(TFT_BLACK);
        tft.println(utf8rus("\nПолучение данных от сервера..."));
        Serial.println("Updating data from API...");
        lastApiRequestTime = currentTime;

        if (!fetchWeatherData()) {
            tft.fillScreen(TFT_WHITE);
            tft.setTextColor(TFT_RED);
            tft.print(utf8rus("Ошибка получения данных"));
            Serial.println("Error updating data");
            return;
        } 
        displayApiWeather(weatherData); //Вывод на LCD дисплей
        // Сбрасываем время последнего запроса к API
        
    }
}