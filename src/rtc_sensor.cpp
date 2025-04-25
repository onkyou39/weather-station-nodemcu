#include "rtc_sensor.h"
#include <RTClib.h>
#include <Wire.h>

// Создаем объект RTC
RTC_DS3231 rtc;

void RtcSensor::begin() {
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1)
            ; // Ожидаем в случае ошибки
    }

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, setting the time!");
        // Устанавливаем время, если потерялась батарейка
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // устанавливается текущее время на момент компиляции
    }
}

void RtcSensor::getTimeAndDate() {
    // Получаем текущую дату и время
    DateTime now = rtc.now();

    // Преобразуем время в строку
    time = String(now.hour()) + ":" + (now.minute() < 10 ? "0" : "") + String(now.minute()) + ":" +
           (now.second() < 10 ? "0" : "") + String(now.second());
    date = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
}

void RtcSensor::setTimeUnix(uint32_t unixTime) {
    // Конвертируем Unix время в DateTime и устанавливаем его в RTC
    DateTime dt(unixTime);
    rtc.adjust(dt); // Устанавливаем дату и время в одном вызове
    Serial.println("Time and Date have been set from Unix timestamp.");
}

String RtcSensor::getTime() {
    return time; // Возвращаем текущее время
}

String RtcSensor::getDate() {
    return date; // Возвращаем текущую дату
}