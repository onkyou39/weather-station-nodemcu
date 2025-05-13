#include "server.h"
#include "sensor_manager.h"
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
extern SensorManager sensors;

void handleRoot() {
    String html = R"rawliteral(
  <!DOCTYPE html>
  <html lang="ru">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Метеостанция</title>
    <style>
      body {
        font-family: sans-serif;
        text-align: center;
        background-color: #f9f9f9;
        padding: 1rem;
      }
      h1 {
        color: #004B8D;
      }
      table {
        border-collapse: collapse;
        width: 90%;
        max-width: 600px;
        margin: 1rem auto;
        background-color: #fff;
      }
      th, td {
        border: 1px solid #ccc;
        padding: 10px;
      }
      th {
        background-color: #444;
        color: white;
      }
      tr:nth-child(even) {
        background-color: #f2f2f2;
      }
      .link-block {
        margin-top: 2rem;
      }
      .link-button {
        display: inline-block;
        padding: 0.6rem 1.2rem;
        font-size: 1rem;
        background-color: #004B8D;
        color: white;
        text-decoration: none;
        border-radius: 5px;
        transition: background-color 0.3s ease;
      }
      .link-button:hover {
        background-color: #0066cc;
      }
    </style>
  </head>
  <body>
    <h1>Локальные данные</h1>
    <table>
      <tr><th>Параметр</th><th>Значение</th></tr>
      <tr><td>Температура</td><td>)rawliteral";

    html += String(sensors.getTemperature(), 1) + " &deg;C</td></tr>\n";
    html += "<tr><td>Влажность</td><td>" + String(sensors.getHumidity(), 1) + " %</td></tr>\n";
    html += "<tr><td>Освещённость</td><td>" + String((int)sensors.getLight()) + " lux</td></tr>\n";
    html += "<tr><td>Атмосферное давление</td><td>" + String((int)sensors.getPressure()) + " мм рт. ст.</td></tr>\n";
    html += R"rawliteral(
    </table>
  
    <div class="link-block">
      <a class="link-button" href="/manual">Открыть инструкцию</a>
    </div>
  </body>
  </html>
  )rawliteral";

    server.send(200, "text/html", html);
}

void handleManual() {
    String html = R"rawliteral(
<!DOCTYPE html>
<html lang="ru">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Инструкция пользователя</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      max-width: 800px;
      margin: 0 auto;
      padding: 1rem;
      background-color: #f9f9f9;
      color: #333;
    }
    h1, h2 {
      color: #004B8D;
    }
    ul {
      padding-left: 1.2rem;
    }
    li {
      margin-bottom: 0.5rem;
    }
    .section {
      margin-bottom: 2rem;
    }
    .link-block {
      text-align: center;
      margin-top: 3rem;
    }
    .link-button {
      display: inline-block;
      padding: 0.6rem 1.2rem;
      font-size: 1rem;
      background-color: #004B8D;
      color: white;
      text-decoration: none;
      border-radius: 5px;
      transition: background-color 0.3s ease;
    }
    .link-button:hover {
      background-color: #0066cc;
    }
  </style>
</head>
<body>
  <h1>Инструкция пользователя</h1>

  <div class="section">
    <h2>1. Комплектация</h2>
    <ul>
      <li>Модуль ESP8266 (NodeMCU)</li>
      <li>Дисплей ST7789</li>
      <li>Датчики HTU21D, TSL2561, BME280, DS18B20</li>
      <li>Печатная плата с кнопкой, резисторами, входом питания и разъемами</li>
    </ul>
  </div>

  <div class="section">
    <h2>2. Подключение и питание</h2>
    <ul>
      <li>Устройство подключается через microUSB или внешний источник питания 5 В, не менее 500 мА</li>
      <li>При первом запуске необходимо загрузить прошивку, настроив файл <code>config.h</code></li>
      <li>Убедитесь в наличии стабильного Wi-Fi-соединения</li>
    </ul>
  </div>

  <div class="section">
    <h2>3. Подключение к Wi-Fi</h2>
    <ul>
      <li>Устройство автоматически подключается к последней сохранённой сети</li>
      <li>При неудаче устройство переходит в офлайн-режим (отображается на экране)</li>
    </ul>
  </div>

  <div class="section">
    <h2>4. Режимы отображения</h2>
    <ul>
      <li>Экран №1: данные с API (температура, давление, облачность, иконка)</li>
      <li>Экран №2: данные с сенсоров и IP локального сервера</li>
      <li>Переключение — кнопкой</li>
      <li>При офлайн-режиме экран №1 показывает последние полученные данные</li>
    </ul>
  </div>

  <div class="section">
    <h2>5. Использование кнопки</h2>
    <ul>
      <li>Одиночное нажатие — переключение экрана</li>
      <li>При совпадении с обновлением данных возможна задержка реакции на нажатие кнопки</li>
    </ul>
  </div>

  <div class="section">
    <h2>6. Локальный веб-интерфейс</h2>
    <ul>
      <li>Работает при подключении к Wi-Fi</li>
      <li>Доступ по IP-адресу (отображается на экране №2)</li>
      <li>Показывает текущие данные с датчиков</li>
    </ul>
  </div>

  <div class="section">
    <h2>7. Режимы работы</h2>
    <ul>
      <li><strong>Онлайн:</strong> доступ к API, работает локальный сервер</li>
      <li><strong>Офлайн:</strong> API недоступен, отображаются локальные данные, сервер выключается</li>
      <li>Экран №1 показывает последние данные, экран №2 — текущие локальные</li>
    </ul>
  </div>

  <div class="section">
    <h2>8. Технические характеристики</h2>
    <ul>
      <li>Питание: 5 В</li>
      <li>Потребление: до 200 мА</li>
      <li>Обновление: каждые 5 секунд (сенсоры), каждые 2 часа (API)</li>
      <li>Протоколы: I²C, SPI, 1-Wire, HTTP</li>
    </ul>
  </div>

  <div class="link-block">
    <a class="link-button" href="/">Перейти к локальным данным</a>
  </div>

</body>
</html>
    )rawliteral";
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
    server.on("/manual", handleManual);
    server.begin();
    server.onNotFound(handleNotFound);
}

void handleServer() {
    server.handleClient();
}

void stopServer() {
    server.stop();
}