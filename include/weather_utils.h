#ifndef WEATHER_UTILS_H
#define WEATHER_UTILS_H

#include <Arduino.h>

String parseCondition(const String& conditionCode);
String parseWindDirection(const String& windDirCode);
String parseCloudness(float value);

#endif