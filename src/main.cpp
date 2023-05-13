#include <Arduino.h>
#include <SdFat.h>
#include <uRTCLib.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "WiFiManager.hpp"
#include "TelegramNotifier.hpp"
#include "RtcDateTimeProvider.hpp"
#include "LoggerFactory.hpp"
#include "SettingsAccessor.hpp"
#include "DashboardService.hpp"
//#include "WebServer.hpp"

uRTCLib rtc(0x68);
RtcDateTimeProvider dateTimeProvider(rtc);
SdFat sd;
TelegramNotifier* notifier;
LoggerFactory* logger;
WiFiManager* wifiManager;
DashboardService* dashboard;
//WebServer* WebServer; 

void setup() {
    Serial.begin(9600);
    sd.begin(4, SPI_HALF_SPEED);
    URTCLIB_WIRE.begin();
    rtc.refresh();

    // settings
    SettingsAccessor settingsAccessor(sd);
    Settings settings = settingsAccessor.getSettings();
    
    // notifier
    notifier = new TelegramNotifier(settings.telegram.botId, settings.telegram.chatId);
    
    // logger
    logger = new LoggerFactory(dateTimeProvider, notifier);
    logger->writeToSerial(settings.logLevel.serial, Serial);
    logger->writeToSdCard(settings.logLevel.sd, sd);

    // WiFi
    wifiManager = new WiFiManager(settings.wifi.ssid, settings.wifi.password, *logger);
    wifiManager->connect();
    delay(1000);
    wifiManager->checkConnection();

    // Web Server
    dashboard = new DashboardService(*logger);
    dashboard->bebin();
    // webServer = new WebServer(*tcpCommandProcessor, *logger);
    // webServer->bebin(settings.tcpServerPort);
}

void loop() {
    rtc.refresh();
    
    // Demo
    delay(3000);
    logger->logInfo("Temterature: " + String(dashboard->getTemperature()) + "C");
    logger->logInfo("Humidity   : " + String(dashboard->getHumidity()) + "%");
    if (dashboard->getLedBlueStatus() == HIGH) {
        dashboard->offLedBlue();
    } else {
        dashboard->onLedBlue();
    }
    if (dashboard->getLedRedStatus() == HIGH) {
        dashboard->offLedRed();
    } else {
        dashboard->onLedRed();
    }
    
}