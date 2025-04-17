#ifndef LCD_H
#define LCD_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_CS    D8     // Пин для CS
#define TFT_DC    D1     // Пин для DC
#define TFT_RST   D2     // Пин для RESET

class LCD {
public:
    LCD();
    void begin();
    void displayWeather(int temp, float windSpeed, const String& windDirection, const String& sunset);
    void displayInternalTemperature(int temperature);
    void clearScreen();
    void printMessage(const String& message, int x, int y);
    void update();

private:
    Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
};

#endif
