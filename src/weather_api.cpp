#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "config.h"

unsigned long lastApiRequestTime = 0; // Время последнего запроса к API
const unsigned long apiUpdateInterval = 3600000; // Интервал для обновления API в миллисекундах (1 час)

String parseWindDirection(const String& wind_dir) {
      const String directions[] = {"nw", "n", "ne", "e", "se", "s", "sw", "w"};
    const String names[] = {"NW", "N", "NE", "E", "SE", "S", "SW", "W"};

    for (int i = 0; i < 8; i++) {
        if (wind_dir == directions[i]) {
        return names[i];
        }
    }
    return wind_dir;
}

String ApiRequest() {
    auto client = std::make_unique<BearSSL::WiFiClientSecure>();
    client->setInsecure(); // отключаем проверку SSL
    HTTPClient https;
    https.useHTTP10(true); //запрет chunked mode, принудительный HTTP 1.0
    https.setTimeout(10000); //фикс ошибки IncompleteInput, таймаут потока на 10 секунд
    String payload = ""; // строка json ответа от сервера
    String url = "https://api.weather.yandex.ru/v2/forecast?lat=" LATITUDE "&lon=" LONGITUDE "&limit=1";
    Serial.print("\n[HTTPS] begin...\n");


    if (https.begin(*client, url)) {
        https.addHeader("X-Yandex-Weather-Key", API_KEY);
  

        int httpCode = https.GET();

        // в случае ошибки httpCode будет отрицательным
        if (httpCode > 0) {
            Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

            // если файл найден на сервере
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            payload = https.getString();
            Serial.println("Payload received");
            }
        } else {
            Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
        https.end();
    } else Serial.printf("[HTTPS] Unable to connect\n");
    return payload;
}


void fetchWeatherData() {

    String payload = ApiRequest();
    delay(100);
    if (payload.isEmpty()) {
        Serial.println("Json data error, empty payload");
        return;
    }
    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, payload);
    serializeJsonPretty(doc, Serial);
    

    if (error) {
        Serial.print("deserializeJson failed: ");
        Serial.println(error.c_str());
        return;
    }

    JsonObject fact = doc["fact"];
    int temp = fact["temp"];
    String wind_dir = fact["wind_dir"];
    float wind_speed = fact["wind_speed"];

    JsonObject forecast = doc["forecast"];
    const char* sunset = forecast["sunset"];

    Serial.println("\nWeather data:");
    Serial.print("Temperature: "); Serial.println(temp);
    Serial.print("Wind: "); Serial.print(parseWindDirection(wind_dir)); Serial.print(" ");
    Serial.print(wind_speed); Serial.println(" m/s");
    Serial.print("Sunset: "); Serial.println(sunset);
}

//функция запроса через интервал
void updateApiData() {
    String payload = "";
    unsigned long currentTime = millis();
    if (currentTime - lastApiRequestTime >= apiUpdateInterval || lastApiRequestTime == 0) {
        Serial.println("Updating data from API...");

        payload = ApiRequest();
        delay(100);
        if (payload.isEmpty()) {
            Serial.println("Json data error, empty payload");
            return;
        }
        JsonDocument doc;

        DeserializationError error = deserializeJson(doc, payload);
        serializeJsonPretty(doc, Serial);
    

        if (error) {
            Serial.print("deserializeJson failed: ");
            Serial.println(error.c_str());
            return;
        }
        lastApiRequestTime = currentTime;

        JsonObject fact = doc["fact"];
        int temp = fact["temp"];
        String wind_dir = fact["wind_dir"];
        float wind_speed = fact["wind_speed"];

        JsonObject forecast = doc["forecast"];
        const char* sunset = forecast["sunset"];

        Serial.println("\nWeather data:");
        Serial.print("Temperature: "); Serial.println(temp);
        Serial.print("Wind: "); Serial.print(parseWindDirection(wind_dir)); Serial.print(" ");
        Serial.print(wind_speed); Serial.println(" m/s");
        Serial.print("Sunset: "); Serial.println(sunset);

    }
    else {
        Serial.print("currentTime = "); Serial.println(currentTime); //для отладки
    }
}