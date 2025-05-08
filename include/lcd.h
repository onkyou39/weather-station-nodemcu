#ifndef LCD_H
#define LCD_H

#define DISABLE_ALL_LIBRARY_WARNINGS 1 // Отключение предупреждения библиотеки о неподключенном тачскрине
#pragma GCC diagnostic ignored "-Wdeprecated-declarations" // Отключение предупреждений об устаревшем api (SPIFFS)

#include "time_utils.h"
#include "utf8_converter.h"
#include "weather_data.h"
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

void lcdInit();
void displayApiWeather(const WeatherData &data);
void displayLocalWeather(bool reset = false);
void drawScreen(int screen);
#endif