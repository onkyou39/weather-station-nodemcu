#include "server.h"
#include "sensor_manager.h"
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
extern SensorManager sensors;

void handleRoot() {
    String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
    html += "<title>Локальная погода</title></head><body>";
    html += "<h1>Локальные данные</h1>";
    html += "<p>Температура 1: " + String(sensors.getTemperature(), 1) + " °C</p>";
    // html += "<p>Температура 2: " + String(sensors.getTemperature2(), 1) + " °C</p>";
    html += "<p>Влажность: " + String(sensors.getHumidity(), 1) + " %</p>";
    html += "<p>Освещенность: " + String(sensors.getLight(), 1) + " lux</p>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}

void initServer() {
    server.on("/", handleRoot);
    server.begin();
}

void handleServer() {
    server.handleClient();
}