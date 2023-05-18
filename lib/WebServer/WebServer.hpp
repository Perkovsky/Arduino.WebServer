#pragma once

#include <String.h>
#include <SdFat.h>
#include <ArduinoJson.h>
#include "ESPAsyncWebServer.h"
#include "LoggerFactory.hpp"
#include "DashboardService.hpp"

class WebServer {
private:
    const String SWAGGER_JSON_FIlE_NAME = F("swagger.json");
    const String SWAGGER_UI_FIlE_NAME = F("swaggerUI.html");
    const char* swaggerJSON;
    const char* swaggerUI;

    LoggerFactory& _logger;
    DashboardService& _dashboard;
    AsyncWebServer* _server;

    void addRouteHandlers() {
        _server->on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
            request->send_P(200, "text/html", "Welcome to ESP32 Web Server");
        });

        _server->on("/swagger/index.html", HTTP_GET, [this](AsyncWebServerRequest *request) {
            request->send_P(200, "text/html", swaggerUI);
        });

         _server->on("/swagger.json", HTTP_GET, [this](AsyncWebServerRequest *request) {
            request->send_P(200, "application/json", swaggerJSON);
        });

        _server->on("/temperature", HTTP_GET, [this](AsyncWebServerRequest *request) {
            float result = _dashboard.getTemperature();
            char buffer[10];
            dtostrf(result, 5, 2, buffer);
            request->send_P(200, "text/plain", buffer);
        });

        _server->on("/humidity", HTTP_GET, [this](AsyncWebServerRequest *request) {
            float result = _dashboard.getHumidity();
            char buffer[10];
            dtostrf(result, 5, 2, buffer);
            request->send_P(200, "text/plain", buffer);
        });

        _server->on("/led-blue-status", HTTP_GET, [this](AsyncWebServerRequest *request) {
            int result = _dashboard.getLedBlueStatus();
            request->send_P(200, "text/plain", result == 0 ? "false" : "true");
        });

        _server->on("/led-red-status", HTTP_GET, [this](AsyncWebServerRequest *request) {
            int result = _dashboard.getLedRedStatus();
            request->send_P(200, "text/plain", result == 0 ? "false" : "true");
        });

        _server->on("/toggle-led-blue", HTTP_POST, 
            [this](AsyncWebServerRequest *request) {/* do nothing */},
            [this](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final) {/* do nothing */},
            [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
                StaticJsonDocument<32> doc;
                DeserializationError error = deserializeJson(doc, data);
                if (error) {
                    _logger.logWarning(error.c_str());
                    request->send(400, "text/plain", "Invalid JSON.");
                    return;
                }
                
                if (doc["value"].isNull()) {
                    request->send(400, "text/plain", "Value is required.");
                    return;
                }

                if (!doc["value"].is<uint8_t>()) {
                    request->send(400, "text/plain", "Value has incorrect type. Should be integer.");
                    return;
                }

                auto value = doc["value"].as<uint8_t>();
                _dashboard.toggleLedBlue(value);
                request->send(204);
            }
        );

        _server->on("/toggle-led-red", HTTP_POST, 
            [this](AsyncWebServerRequest *request) {/* do nothing */},
            [this](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final) {/* do nothing */},
            [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
                StaticJsonDocument<32> doc;
                DeserializationError error = deserializeJson(doc, data);
                if (error) {
                    _logger.logWarning(error.c_str());
                    request->send(400, "text/plain", "Invalid JSON.");
                    return;
                }
                
                if (doc["value"].isNull()) {
                    request->send(400, "text/plain", "Value is required.");
                    return;
                }

                if (!doc["value"].is<uint8_t>()) {
                    request->send(400, "text/plain", "Value has incorrect type. Should be integer.");
                    return;
                }

                auto value = doc["value"].as<uint8_t>();
                _dashboard.toggleLedRed(value);
                request->send(204);
            }
        );

        _server->onNotFound([](AsyncWebServerRequest *request) {
            if (request->method() == HTTP_OPTIONS) {
                request->send(200);
            } else if (request->method() == HTTP_GET) {
                request->redirect("/");
            } else {
                request->send(404);
            }
        });
    }

    char* getFileContent(SdFat& sd, const String& filename) {
        if (!sd.exists(filename)) {
            String error(filename);
            error.reserve(filename.length() + 16);
            error += " does not exist";
            _logger.logError(error);
            return nullptr;
        }

        auto file = sd.open(filename, 0); // FILE_READ
        if (!file) {
            file.close();
            String error("Failed to open ");
            error.reserve(filename.length() + 16);
            error += filename;
            _logger.logError(error);
            return nullptr;
        }

        size_t fileSize = file.size();
        char* content = new char[fileSize + 1]; // add 1 for null terminator
        file.read(content, fileSize);
        content[fileSize] = '\0'; // add null terminator
        file.close();

        return content;
    }

public:
    WebServer(DashboardService& dashboard, LoggerFactory& logger, SdFat& sd)
        : _dashboard(dashboard), _logger(logger)
    {
        swaggerJSON = getFileContent(sd, SWAGGER_JSON_FIlE_NAME);
        swaggerUI = getFileContent(sd, SWAGGER_UI_FIlE_NAME);
    }

    void bebin(uint16_t port = 80) {
        _server = new AsyncWebServer(port);
        
        // enable CORS headers
        DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
        DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

        addRouteHandlers();
        _server->begin();
        _logger.logInfo("Web Server has been started");
    }

    void end() {
        _server->end();
        _logger.logInfo("Web Server has been ended");
    }
};