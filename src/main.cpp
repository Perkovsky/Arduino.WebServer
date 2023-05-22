#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

const char* ssid = "Verizon_4CGXRN";
const char* password = "famous9-fox-apt";

AsyncWebServer server(80);

void initSDCard(){
  if(!SD.begin(4)){
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    Serial.println("MMC");
  } else if(cardType == CARD_SD){
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.localIP().toString());
}

void setup() {
  Serial.begin(9600);
  initWiFi();
  initSDCard();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("request--->>");
    //request->send(SD, "/index.html", "text/html");
    //request->send(SD, "/swaggerUI.html", "text/html");
    request->send(SD, "/logo-3f834fa8.svg", "text/html");
  });

  server.serveStatic("/", SD, "/");

  server.begin();
}

void loop() {
  
}