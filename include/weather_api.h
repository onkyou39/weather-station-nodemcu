#ifndef WEATHER_API_H
#define WEATHER_API_H

String ApiRequest();
bool fetchWeatherData();
bool updateApiData(bool drawIfUpdated = true);

#endif