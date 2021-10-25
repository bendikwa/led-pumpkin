#include "configReader.h"

/*
 * Config file example:
 * {
 *     "WLAN_SSID": "<YOUR_WIFI_SSID>",
 *     "WLAN_PASS": "<YOUR_WIFI_PASS>"
 */
Config::Config()
{
    parseConfig();
}

boolean Config::parseConfig()
{
    String config = readConfig("/config.json");
    DeserializationError error = deserializeJson(json_config, config);
    if (error)
    {
        Serial.printf("config:         Failed to deserialize config file content\n");
        Serial.println(error.c_str());
        Serial.println(config);
        return false;
    }
    return true;
}

String Config::readConfig(const char *configFileName)
{
    Serial.printf("config:         Start reading config\n");
    if (!LittleFS.begin())
    {
        Serial.printf("config:         Failed to open file system\n");
        return "{}";
    }
    File file = LittleFS.open(configFileName, "r");
    String read_ = file.readString();
    file.close();
    LittleFS.end();
    Serial.printf("config:         Config file: read complete\n");
    return read_;
}

const char * Config::get(String configName)
{
    if (json_config[configName]){
    return json_config[configName];

    } else {
        return "UNDEFINED";
    }
}
