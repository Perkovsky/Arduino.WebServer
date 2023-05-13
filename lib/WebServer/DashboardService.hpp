#pragma once

#include <String.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "LoggerFactory.hpp"

class DashboardService {
private:
    const u_int8_t LED_BLUE_PIN = 12;   // GPIO12
    const u_int8_t LED_RED_PIN = 14;    // GPIO14
    const u_int8_t DHT_PIN = 21;        // GPIO21

    DHT* _dht = new DHT(DHT_PIN, DHT11);
    LoggerFactory& _logger;

public:
    DashboardService(LoggerFactory& logger) : _logger(logger) {}

    void bebin() {
        pinMode(LED_BLUE_PIN, OUTPUT);
        pinMode(LED_RED_PIN, OUTPUT);
       _dht->begin();
    }

    void onLedBlue() {
        digitalWrite(LED_BLUE_PIN, HIGH);
    }

    void offLedBlue() {
        digitalWrite(LED_BLUE_PIN, LOW);
    }

    int getLedBlueStatus() {
        return digitalRead(LED_BLUE_PIN);
    }

    void onLedRed() {
        digitalWrite(LED_RED_PIN, HIGH);
    }

    void offLedRed() {
        digitalWrite(LED_RED_PIN, LOW);
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