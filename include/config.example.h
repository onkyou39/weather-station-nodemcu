#ifndef CONFIG_H
#define CONFIG_H

// Wi-Fi настройки
#define WIFI_SSID     "your-wifi-ssid"
#define WIFI_PASSWORD "your-wifi-password"

// API ключи
#define API_KEY       "your-api-key"

// Геолокация
#define LATITUDE   "your-location-latitude" //широта в градусах
#define LONGITUDE   "your-location-longitude" //долгота в градусах

// Часовой пояс (смещение от UTC в секундах)
constexpr int TIMEZONE_OFFSET = 3 * 3600; // Москва UTC+3

#endif