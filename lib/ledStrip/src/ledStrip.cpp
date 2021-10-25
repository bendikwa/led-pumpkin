#include "ledStrip.h"

LedStrip::LedStrip(short unsigned int startPixel, short unsigned int count, Adafruit_NeoPixel *neoPixels)
{

    this->startPixel = startPixel;
    this->count = count;
    this->neoPixels = neoPixels;
}

void LedStrip::setBrightness(short unsigned int brightness)
{
    this->brightness = brightness;
}

void LedStrip::setColor(uint32_t c)
{
    this->neoPixels->fill(c, startPixel, count);
    this->neoPixels->show();
}

void LedStrip::red()
{
    this->neoPixels->fill(this->neoPixels->ColorHSV(hue_red, 255, this->brightness), startPixel, count);
    this->neoPixels->show();
}

void LedStrip::orange()
{
    this->neoPixels->fill(this->neoPixels->ColorHSV(hue_orange, 255, this->brightness), startPixel, count);
    this->neoPixels->show();
}

void LedStrip::yellow()
{
    this->neoPixels->fill(this->neoPixels->ColorHSV(hue_yellow, 255, this->brightness), startPixel, count);
    this->neoPixels->show();
}

void LedStrip::green()
{
    this->neoPixels->fill(this->neoPixels->ColorHSV(hue_green, 255, this->brightness), startPixel, count);
    this->neoPixels->show();
}

void LedStrip::blue()
{
    this->neoPixels->fill(this->neoPixels->ColorHSV(hue_blue, 255, this->brightness), startPixel, count);
    this->neoPixels->show();
}

void LedStrip::violet()
{
    this->neoPixels->fill(this->neoPixels->ColorHSV(hue_violet, 255, this->brightness), startPixel, count);
    this->neoPixels->show();
}

void LedStrip::off()
{
    this->neoPixels->fill(this->neoPixels->Color(0,0,0), startPixel, count);
    this->neoPixels->show();
}