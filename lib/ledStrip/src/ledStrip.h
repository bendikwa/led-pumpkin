#ifndef LEDSTRIP_H_
#define LEDSTRIP_H_

#include <Adafruit_NeoPixel.h>

class LedStrip
{
private:
    short unsigned int startPixel;          // Index of the first pixel
    short unsigned int count;               // Number of pixel in segment
    short unsigned int brightness = 150;    // Brightness for the strip segment
    Adafruit_NeoPixel *neoPixels;         // Pointer to the led strip to use

    uint16_t hue_red = 0;
    uint16_t hue_orange = 5460;
    uint16_t hue_yellow = 10920;
    uint16_t hue_green = 21840;
    uint16_t hue_blue = 43680;
    uint16_t hue_violet = 49686;

public:
    LedStrip(short unsigned int startPixel, short unsigned int count, Adafruit_NeoPixel *neoPixels);

    void setBrightness(short unsigned int brightness);
    void setColor(uint32_t color);
    void red();
    void orange();
    void yellow();
    void blue();
    void green();
    void violet();
    void off();
};

#endif /* LEDSTRIP_H_ */