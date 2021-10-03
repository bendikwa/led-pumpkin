#include "status_led.h"

// Date constructor
Status_LED::Status_LED(short unsigned int status_led_index, Adafruit_NeoPixel *ledstrip)
{
    
    this->status_led_index = status_led_index;
    this->ledstrip = ledstrip;
}

void Status_LED::blue(){
    this->ledstrip->setPixelColor(this->status_led_index, this->ledstrip->Color(0,0,150));
    this->ledstrip->show();
}

void Status_LED::green(){
    this->ledstrip->setPixelColor(this->status_led_index, this->ledstrip->Color(0,150,0));
    this->ledstrip->show();
}

void Status_LED::red(){
    this->ledstrip->setPixelColor(this->status_led_index, this->ledstrip->Color(150,0,0));
    this->ledstrip->show();
}

void Status_LED::off(){
    this->ledstrip->setPixelColor(this->status_led_index, this->ledstrip->Color(0,0,0));
    this->ledstrip->show();
}