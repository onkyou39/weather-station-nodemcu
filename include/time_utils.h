#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <Arduino.h>

const int TIMEZONE_OFFSET = 3 * 3600; // Москва UTC+3

// Функции для работы с временем и датой
String parseTime(time_t utcTime, const char* format = "%H:%M:%S");
String parseDate(time_t utcTime);

#endif