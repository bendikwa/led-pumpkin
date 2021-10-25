#include "mqtt.h"

Mqtt::Mqtt(const char *MQTT_SERVER, uint16_t MQTT_PORT, const char *MQTT_USER, const char *MQTT_PASS, const char *MQTT_TOPIC):
mqttClient(&wifiClient, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASS),
sub(&mqttClient, MQTT_TOPIC)
{
  Serial.printf("mqtt:           New mqtt client connecting to %s on port %d\n", MQTT_SERVER, MQTT_PORT);
}

void Mqtt::setCallback(void (*callback)(char *, uint16_t)){
  sub.setCallback(callback);
  mqttClient.subscribe(&sub);
}

void Mqtt::MQTT_connect()
{
  int8_t ret;

  // Stop if already connected.
  if (mqttClient.connected())
  {
    return;
  }



  Serial.print("mqtt:           Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqttClient.connect()) != 0)
  { // connect will return 0 for connected
    Serial.println(mqttClient.connectErrorString(ret));
    Serial.println("mqtt:           Retrying MQTT connection in 5 seconds...");
    mqttClient.disconnect();
    delay(5000); // wait 5 seconds
    retries--;
    if (retries == 0)
    {
      // basically die and wait for WDT to reset me
      Serial.println("mqtt:           Could not connect to MQTT broker");
      while (1)
        ;
    }
  }

  Serial.println("mqtt:           MQTT Connected!");
}

void Mqtt::processPackets(int16_t timeout){
  mqttClient.processPackets(timeout);
}