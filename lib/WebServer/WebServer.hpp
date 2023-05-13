#pragma once

#include <String.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "LoggerFactory.hpp"
#include "DashboardService.hpp"

class WebServer {
private:
    LoggerFactory& _logger;
    DashboardService& _dashboard;
    AsyncWebServer* _server;

    void addRouteHandlers() {
        _server->on("/", HTTP_GET, [this](AsyncWebServerRequest *request){
            request->send_P(200, "text/html", "Just a simple text");
        });

        _server->on("/temperature", HTTP_GET, [this](AsyncWebServerRequest *request){
            float result = _dashboard.getTemperature();
            char buffer[10];
            dtostrf(result, 5, 2, buffer);
            _logger.logInfo("Temperature: " + String(result));
            request->send_P(200, "text/plain", buffer);
        });

        _server->on("/humidity", HTTP_GET, [this](AsyncWebServerRequest *request){
            float result = _dashboard.getHumidity();
            char buffer[10];
            dtostrf(result, 5, 2, buffer);
            request->send_P(200, "text/plain", buffer);
        });
    }

public:
    WebServer(DashboardService& dashboard, LoggerFactory& logger)
        : _dashboard(dashboard), _logger(logger) {}

    void bebin(uint16_t port) {
        _server = new AsyncWebServer(80);
        addRouteHandlers();
        _server->begin();
        _logger.logInfo("Web Server has been started");
    }

    void end() {
        _server->end();
        _logger.logInfo("Web Server has been ended");
    }
};