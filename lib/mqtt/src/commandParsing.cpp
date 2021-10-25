#include "commandParsing.h"
#include <ArduinoJson.h>

// TODO: Optimize capacity of char arrays and JSON docs

/*
 * Control:
 * {"command": "(set|play)"}
 */

ControlMessage parseControlMessage(char *message)
{
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, message);
    if (error)
    {
        Serial.printf("commandParsing: Failed to deserialize control message: %s\n", message);
        Serial.println(error.c_str());
        return ControlMessage(INVALID, "", "", 0, 0, 0, 0, 0, 0);
    }

    const char *command = doc["command"];
    const char *device = doc["device"];
    const char *color = doc["color"];
    if (!doc["command"])
    {
        Serial.println("commandParsing: Failed to deserialize control message: Missing command type");
        command = "invalid";
    }
    if (!doc["device"])
    {
        Serial.println("commandParsing: Failed to deserialize control message: Missing device address");
        device = "all";
        command = "invalid";
    }
    if (!doc["color"])
    {
        Serial.println("commandParsing: Failed to deserialize control message: Missing color");
        color = "off";
        command = "invalid";
    }

    if (strcmp(command, "setTxtColor") == 0)
    {
        return ControlMessage(SET_TXT_COLOR, device, color, 0, 0, 0, 0, 0, 0);
    }
    else if (strcmp(command, "setRgbColor") == 0)
    {
        char *pt;
        char color_copy[11];
        strcpy (color_copy,color);
        pt = strtok(color_copy, ",");
        uint8_t r = atoi(pt);
        pt = strtok(NULL, ",");
        uint8_t g = atoi(pt);
        pt = strtok(NULL, ",");
        uint8_t b = atoi(pt);
        return ControlMessage(SET_RGB_COLOR, device, "RGB", r, g, b, 0, 0, 0);
    }
    else if (strcmp(command, "setHsvColor") == 0)
    {
        char *pt;
        char color_copy[11];
        strcpy (color_copy,color);
        pt = strtok(color_copy, ",");
        uint16_t h = atoi(pt);
        pt = strtok(NULL, ",");
        uint16_t s = atoi(pt);
        pt = strtok(NULL, ",");
        uint16_t v = atoi(pt);
        return ControlMessage(SET_HSV_COLOR, device, "HSV", 0, 0, 0, h, s, v);
    }
    else if (strcmp(command, "play") == 0)
    {
        return ControlMessage(PLAY, device, color, 0, 0, 0, 0, 0, 0);
    }
    else
    {
        Serial.printf("commandParsing: Failed to deserialize control message: Command type '%s' is not valid\n", command);
        return ControlMessage(INVALID, "", "", 0, 0, 0, 0, 0, 0);
    }
}