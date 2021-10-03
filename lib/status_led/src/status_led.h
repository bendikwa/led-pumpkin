#include <Adafruit_NeoPixel.h>

class Status_LED {
    private:
        short unsigned int status_led_index;   // Index of the status led
        Adafruit_NeoPixel *ledstrip;    // Pointer to the led strip to use

    public:
        Status_LED(short unsigned int status_led_index, Adafruit_NeoPixel *ledstrip);

        void blue();
        void green();
        void red();
        void off();
};