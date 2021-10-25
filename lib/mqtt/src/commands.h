#ifndef COMMANDS_H_
#define COMMANDS_H_

enum ControlMessageType
{
    SET_HSV_COLOR,
    SET_RGB_COLOR,
    SET_TXT_COLOR,
    PLAY,
    INVALID
};

class ControlMessage
{
    ControlMessageType messageType;
    const char *deviceAddress;
    const char *color;
    unsigned char RGB [3];
    unsigned short HSV [3];

public:
    ControlMessage(
        ControlMessageType messageType,
        const char *deviceAddress,
        const char *color,
        unsigned char r,
        unsigned char g,
        unsigned char b,
        unsigned short h,
        unsigned short s,
        unsigned short v) : messageType(messageType),
                                deviceAddress(deviceAddress),
                                color(color)
    {
        RGB[0] = r;
        RGB[1] = g;
        RGB[2] = b;
        HSV[0] = h;
        HSV[1] = s;
        HSV[2] = v;
    }

    ControlMessageType getType()
    {
        return messageType;
    }

    const char *getDevice()
    {
        return deviceAddress;
    }

    const char * getTXTColor()
    {
        return color;
    }
    unsigned char * getRGBColor()
    {
        return RGB;
    }
    unsigned short * getHSVColor()
    {
        return HSV;
    }
};

#endif /* COMMANDS_H_ */