#pragma once

#include <String.h>
#include <SdFat.h>
#include <AsyncTCP.h>
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
            request->send_P(200, "text/html", "The Dashboard has not yet been implemented.");
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

         //TODO: POST -> response code: 204
         // toggleLedBlue
         // toggleLedBRed

        _server->onNotFound([](AsyncWebServerRequest *request){
            request->redirect("/");
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