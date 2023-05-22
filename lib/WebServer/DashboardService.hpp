#pragma once

#include <String.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "LoggerFactory.hpp"

class DashboardService {
private:
    const u_int8_t LED_BLUE_PIN = 12;   // GPIO12
    const u_int8_t LED_RED_PIN = 14;    // GPIO14
    const u_int8_t DHT_PIN = 15;        // GPI15

    DHT* _dht = new DHT(DHT_PIN, DHT11);
    LoggerFactory& _logger;

public:
    DashboardService(LoggerFactory& logger) : _logger(logger) {}

    void bebin() {
        pinMode(LED_BLUE_PIN, OUTPUT);
        pinMode(LED_RED_PIN, OUTPUT);
       _dht->begin();
    }

    void toggleLedBlue(uint8_t value) {
        digitalWrite(LED_BLUE_PIN, value);
    }

    int getLedBlueStatus() {
        return digitalRead(LED_BLUE_PIN);
    }

    void toggleLedRed(uint8_t value) {
        digitalWrite(LED_RED_PIN, value);
    }

    int getLedRedStatus() {
        return digitalRead(LED_RED_PIN);
    }

    float getTemperature() {
        float result = _dht->readTemperature();
        if (isnan(result)) {
            _logger.logWarning(F("Cannot read temperature"));
        }
        
       return result;
    }

    float getHumidity() {
        float result = _dht->readHumidity();
        if (isnan(result)) {
            _logger.logWarning(F("Cannot read humidity"));
        }
        
       return result;
    }
};