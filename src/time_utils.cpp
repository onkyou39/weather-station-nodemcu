#include "time_utils.h"
#include "config.h"

// Функция для форматирования времени
String parseTime(time_t utcTime, const char *format) {
    time_t localTime = utcTime + TIMEZONE_OFFSET;
    struct tm *timeinfo = localtime(&localTime);

    char buffer[30];
    strftime(buffer, sizeof(buffer), format, timeinfo);

    return String(buffer);
}

// Функция для форматирования даты
String parseDate(time_t utcTime) {
    time_t localTime = utcTime + TIMEZONE_OFFSET;
    struct tm *timeinfo = localtime(&localTime);

    char buffer[30];
    strftime(buffer, sizeof(buffer), "%d.%m.%Y", timeinfo);

    return String(buffer);
}