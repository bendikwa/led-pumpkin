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

int defaultLedBrightness = 255;
int statusLedBrightness = 100;
int ledStripBrightness = 255;
BearSSL::CertStore certStore;

void controlCallback(char *data, uint16_t len)
{
  String payload(data);
  Serial.print("main:           controlCallback payload: ");
  Serial.println(payload);
  ControlMessage cm = parseControlMessage(data);
  if (strcmp(cm.getDevice(), "all") == 0 || strcmp(cm.getDevice(), WiFi.macAddress().c_str()) == 0)
  {
    switch (cm.getType())
    {
    case SET_TXT_COLOR:
      Serial.printf("main:           Command: 'SET_TXT_COLOR' Device: %s color: %s\n", cm.getDevice(), cm.getTXTColor());
      strip.setColor(cm.getTXTColor());
      break;
    case SET_RGB_COLOR:
      uint8_t *rgb_c;
      rgb_c = cm.getRGBColor();
      Serial.printf("main:           Command: 'SET_RGB_COLOR' Device: %s color: [%d,%d,%d]\n", cm.getDevice(), rgb_c[0], rgb_c[1], rgb_c[2]);
      strip.setColor(Adafruit_NeoPixel::Color(rgb_c[0], rgb_c[1], rgb_c[2]));
      break;
    case SET_HSV_COLOR:
      uint16_t *hsv_c;
      hsv_c = cm.getHSVColor();
      Serial.printf("main:           Command: 'SET_HSV_COLOR' Device: %s color: [%d,%d,%d]\n", cm.getDevice(), hsv_c[0], hsv_c[1], hsv_c[2]);
      strip.setColor(Adafruit_NeoPixel::ColorHSV(hsv_c[0], hsv_c[1], hsv_c[2]));
      break;
    case PLAY:
      Serial.printf("main:           Command: PLAY Device: %s\n", cm.getDevice());
      break;
    case INVALID:
      Serial.printf("main:           Command: INVALID Device: %s\n", cm.getDevice());
      break;
    }
  }
  else
  {
    Serial.println("main:           Ignoring control message for somone else...");
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("------------------------------");
  all_pixels.begin();
  all_pixels.setBrightness(defaultLedBrightness);
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
  Mqtt mqtt(c.get("MQTT_SERVER"), atoi(c.get("MQTT_PORT")), c.get("MQTT_USER"), c.get("MQTT_PASS"), c.get("MQTT_CONTROL_TOPIC"));
  mqtt.setCallback(&controlCallback);
  mqtt.MQTT_connect();
  statusLed.green();
  delay(2000);
  statusLed.off();
  strip.setBrightness(50);
  while (1)
  {
    mqtt.processPackets(1);
    delay(50);
  }
}

// the loop function runs over and over again forever
void loop()
{
}