#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

const u_int8_t LED_PIN_1 = 12;
const u_int8_t LED_PIN_2 = 14;
const u_int8_t DHT_PIN = 21;

DHT dht(DHT_PIN, DHT11);

void printTemperature() {
  float result = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(result);
  Serial.println("C");
}

void printHumidity() {
  float result = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(result);
  Serial.println("%");
}

void setup() {
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);

  // testing
  digitalWrite(LED_PIN_1, HIGH);
  digitalWrite(LED_PIN_2, HIGH);

  Serial.begin(9600);
  dht.begin();
}

void loop() {
  printTemperature();
  printHumidity();
  delay(2000);
}
