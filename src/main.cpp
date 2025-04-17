#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include "wifi_utils.h"
#include "weather_api.h"

/*RTC_DS3231 rtc;  // Инициализируем RTC
unsigned long lastApiRequestTime = 0; // Время последнего запроса к API
const unsigned long apiUpdateInterval = 3600000; // Интервал для обновления API в миллисекундах (1 час)
String payload;  // Для хранения данных из API*/

void setup() 
{
    Serial.begin(115200);
    connectToWiFi();
    //fetchWeatherData();
    //updateApiData();
    
}

void loop() 
{
    updateApiData();
    delay(1000);
}