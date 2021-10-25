#include "commandParsing.h"
#include <ArduinoJson.h>

// TODO: Optimize capacity of char arrays and JSON docs

/*
 * Control:
 * {"command": "(set|play)"} 
 */

ControlMessage parseControlMessage(char* message) {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, message);
    if (error) {
        Serial.printf("commandParsing: Failed to deserialize control message: %s\n", message);
        Serial.println(error.c_str());
        return ControlMessage(INVALID, 0);
    }

    const char* command = doc["command"];
    const char* device = doc["device"];
    if (!doc["command"]) {
        Serial.println("commandParsing: Failed to deserialize control message: Missing command type");
    }
    if (!doc["device"]) {
        Serial.println("commandParsing: Failed to deserialize control message: Missing device address");
        return ControlMessage(INVALID, 0);
    }

    if (strcmp(command, "set") == 0) {
        return ControlMessage(SET, atoi(device));
    } else if (strcmp(command, "play") == 0) {
        return ControlMessage(PLAY, atoi(device));
    } else {
        Serial.printf("commandParsing: Failed to deserialize control message: Command type '%s' is not valid\n", command);
        return ControlMessage(INVALID, 0);
    }
}