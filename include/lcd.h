#ifndef LCD_H
#define LCD_H

#include "time_utils.h"
#include "utf8_converter.h"
#include "weather_data.h"
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

void lcdInit();
void displayApiWeather(const WeatherData &data);
void displayLocalWeather(bool reset = false);
#endif