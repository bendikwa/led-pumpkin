#include "wifi.h"

boolean startWifi(const String& ssid, const String& passphrase)
{
	// Connect to WiFi access point.
	Serial.printf("startWifi:      Connecting to %s\n", ssid.c_str());

  WiFi.begin(ssid, passphrase);

	
	int wifiStatus = WiFi.status();
	Serial.print("startWifi:      ");
	while (wifiStatus != WL_CONNECTED) {
		delay( 50 );
		wifiStatus = WiFi.status();
		Serial.print(".");
	}
	Serial.println();
	Serial.printf("startWifi:      WiFi connected\n");
	Serial.printf("startWifi:      IP address: %s\n", WiFi.localIP().toString().c_str());
	Serial.printf("startWifi:      MAC address: %s\n", WiFi.macAddress().c_str());
	return true;
}
