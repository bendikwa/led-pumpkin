#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <status_led.h>
#include <wifi.h>
// NeoPixel data pin
#define NEOPIXEL_PIN 5
// Number of NeoPixeles (Not counting status pixel)
#define NEOPIXEL_COUNT 24
#define NEOPIXEL_TOTAL NEOPIXEL_COUNT + 1
#define NEOPIXEL_STRIP_START 1
#define NEOPIXEL_STATUS_LED 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEOPIXEL_TOTAL, NEOPIXEL_PIN);
Status_LED status_led = Status_LED(NEOPIXEL_STATUS_LED, &strip);

int maxBrightness = 100;

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.clear();
  strip.show();
  status_led.red();
  start_wifi();
  status_led.blue();
  delay(1000);
  status_led.green();
  delay(1000);
  status_led.off();
}

// the loop function runs over and over again forever
void loop() {
  delay(10000);
}