#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <Arduino.h>

// Функции для работы с временем и датой
String parseTime(time_t utcTime, const char *format = "%H:%M:%S");
String parseDate(time_t utcTime);

#endif