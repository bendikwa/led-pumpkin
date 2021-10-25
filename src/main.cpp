#include <Arduino.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Adafruit_NeoPixel.h>
#include <CertStoreBearSSL.h>
#include <configReader.h>
#include <ESP8266WiFi.h>
#include <https.h>
#include <LedStrip.h>
#include <mqtt.h>
#include <otaUpdate.h>
#include <statusLed.h>
#include <wifi.h>

// NeoPixel data pin
#define NEOPIXEL_PIN 5
// Number of NeoPixeles (Not counting status pixel)
#define NEOPIXEL_COUNT 24
#define NEOPIXEL_TOTAL NEOPIXEL_COUNT + 1
#define NEOPIXEL_STRIP_START 1
#define NEOPIXEL_STATUS_LED 0

Adafruit_NeoPixel all_pixels = Adafruit_NeoPixel(NEOPIXEL_TOTAL, NEOPIXEL_PIN);
StatusLED statusLed = StatusLED(NEOPIXEL_STATUS_LED, &all_pixels);
LedStrip strip = LedStrip(1, 9, &all_pixels);
Mqtt *mqtt_client;

int statusLedBrightness = 100;
BearSSL::CertStore certStore;

void controlCallback(char *data, uint16_t len)
{
  String payload(data);
  Serial.print("main:           controlCallback payload: ");
  Serial.println(payload);
  ControlMessage cm = parseControlMessage(data);
  switch (cm.getType()){
    case SET:
      Serial.printf("main:           Command: SET Device: %d\n", cm.getDevice());
      strip.setColor(Adafruit_NeoPixel::ColorHSV(21840,0,0));
      strip.red();
      break;
    case PLAY:
      Serial.printf("main:           Command: PLAY Device: %d\n", cm.getDevice());
      break;
    case INVALID:
      Serial.printf("main:           Command: INVALID Device: %d\n", cm.getDevice());
      break;
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("-------------------");
  all_pixels.begin();
  all_pixels.clear();
  all_pixels.show();
  Config c = Config();
  startWifi(c.get("WLAN_SSID"), c.get("WLAN_PASS"));
  statusLed.setBrightness(statusLedBrightness);
  statusLed.blue();

  if (!loadCerts(&certStore))
  {
    statusLed.red();
    return;
  }

  setClock();

  checkForUpdate(&certStore, c.get("OTA_URL"));
  Mqtt mqtt(c.get("MQTT_SERVER"),atoi(c.get("MQTT_PORT")),c.get("MQTT_USER"),c.get("MQTT_PASS"),c.get("MQTT_CONTROL_TOPIC"));
  mqtt.setCallback(&controlCallback);
  mqtt.MQTT_connect();
  mqtt_client = &mqtt;
  statusLed.green();
  delay(2000);
  statusLed.off();
  strip.setBrightness(50);
  while (1){
      mqtt_client->processPackets(1);
      delay(50);
  }
}

// the loop function runs over and over again forever
void loop()
{

}