#ifndef MQTT_H_
#define MQTT_H_

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <commandParsing.h>
#include <config.h>
#include <list>

class Mqtt
{
private:
    Adafruit_MQTT_Client mqttClient;
    WiFiClient wifiClient;
    Adafruit_MQTT_Subscribe sub;

public:
    Mqtt(const char *MQTT_SERVER, uint16_t MQTT_PORT, const char *MQTT_USER, const char *MQTT_PASS, const char *MQTT_TOPIC);
    void setCallback(void (*callback)(char *, uint16_t));
    void MQTT_connect();
    void processPackets(int16_t timeout);
};




#endif /* MQTT_H_ */
