#include "server.h"
#include "sensor_manager.h"
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
extern SensorManager sensors;

void handleRoot() {
    String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
    html += "<title>Локальная погода</title>";
    html += "<style>";
    html += "body { font-family: sans-serif; text-align: center; }";
    html += "table { border-collapse: collapse; width: 60%; margin: 0 auto; }";
    html += "th, td { border: 1px solid #ccc; padding: 10px; }";
    html += "th { background-color: #444; color: white; }";
    html += "tr:nth-child(even) { background-color: #f2f2f2; }";
    html += "</style></head><body>";
    html += "<h1>Локальные данные</h1>";
    html += "<table>";
    html += "<tr><th>Параметр</th><th>Значение</th></tr>";
    html += "<tr><td>Температура</td><td>" + String(sensors.getTemperature(), 1) + " &deg;C</td></tr>";
    html += "<tr><td>Влажность</td><td>" + String(sensors.getHumidity(), 1) + " %</td></tr>";
    html += "<tr><td>Освещённость</td><td>" + String((int)sensors.getLight()) + " lux</td></tr>";
    html += "</table>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}

void handleNotFound() {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";

    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }

    server.send(404, "text/plain", message);
}

void initServer() {
    server.on("/", handleRoot);
    server.begin();
    server.onNotFound(handleNotFound);
}

void handleServer() {
    server.handleClient();
}

void stopServer() {
    server.stop();
}