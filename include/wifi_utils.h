#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <Arduino.h>

struct Config {
    char ssid[32];
    char password[32];
    char apiKey[32];
    char latitude[16];
    char longitude[16];
    bool isValid = false;
};
void saveConfigToEEPROM();
void loadConfigFromEEPROM();
bool isConfigValid();
bool connectToWiFi();
bool connectionStatus();
String getIP();

#endif