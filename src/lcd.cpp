#include "LCD.h"


void lcdInit() {
    tft.init(240, 240, SPI_MODE2);  // Инициализация экрана
    tft.setRotation(0);  // Ориентация экрана
    tft.fillScreen(ST77XX_WHITE);  // Очистка экрана
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_BLACK);
}
