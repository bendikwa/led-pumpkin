#ifndef CONFIGREADER_H_
#define CONFIGREADER_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

class Config
{
private:
    StaticJsonDocument<512> json_config;
    short unsigned int getConfigLength(const char *configFileName);
    boolean parseConfig();
    String readConfig(const char *configFileName);
public:
    Config();
    const char* get(String configName);
};

#endif /* CONFIGREADER_H_ */