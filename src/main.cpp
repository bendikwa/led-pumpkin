#include <Arduino.h>
#include <wifi.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
// NeoPixel data pin
#define NEOPIXEL_PIN 5
// Number of NeoPixeles (Not counting status pixel)
#define NEOPIXEL_COUNT 24
#define NEOPIXEL_TOTAL NEOPIXEL_COUNT + 1
#define NEOPIXEL_STRIP_START 1
#define NEOPIXEL_STATUS_LED 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEOPIXEL_TOTAL, NEOPIXEL_PIN);
int maxBrightness = 100;

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.clear();

  start_wifi();
}

// the loop function runs over and over again forever
void loop() {
  delay(10000);
}