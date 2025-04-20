#ifndef LCD_H
#define LCD_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "weather_data.h"
#include "utf8_converter.h"
#include "time_utils.h"

#define TFT_CS    D8     // Пин для CS
#define TFT_DC    D1     // Пин для DC
#define TFT_RST   D2     // Пин для RESET

extern Adafruit_ST7789 tft;

void lcdInit();
void displayApiWeather(const WeatherData &data);
void displayLocalWeather();
#endif