#ifndef LCD_H
#define LCD_H

#include <TFT_eSPI.h>
#include "weather_data.h"
#include "utf8_converter.h"
#include "time_utils.h"


extern TFT_eSPI tft;

void lcdInit();
void displayApiWeather(const WeatherData &data);
void displayLocalWeather();
#endif