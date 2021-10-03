#include "wifi.h"

boolean start_wifi()
{
	// Connect to WiFi access point.
	Serial.println(); Serial.println();
	Serial.print("start_wifi:   Connecting to ");
	Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);

	
	int wifiStatus = WiFi.status();
	Serial.print("start_wifi:   ");
	while (wifiStatus != WL_CONNECTED) {
		delay( 50 );
		wifiStatus = WiFi.status();
		Serial.print(".");
	}
	Serial.println();
	Serial.println("start_wifi:   WiFi connected");
	Serial.print("start_wifi:   IP address: "); Serial.println(WiFi.localIP());
	Serial.print("start_wifi:   MAC address: "); Serial.println(WiFi.macAddress());
	return true;
}
