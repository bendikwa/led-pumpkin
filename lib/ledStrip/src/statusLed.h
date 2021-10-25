#ifndef STATUSLED_H_
#define STATUSLED_H_

#include <ledStrip.h>

class StatusLED : public LedStrip
{
private:

public:
    StatusLED(short unsigned int statusLedIndex, Adafruit_NeoPixel *ledStrip) : LedStrip(statusLedIndex, 1, ledStrip){}
};

#endif /* STATUSLED_H_ */