#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <Arduino.h>

bool connectToWiFi();
bool connectionStatus();
String getIP();

#endif