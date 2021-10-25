#ifndef COMMANDS_H_
#define COMMANDS_H_

enum ControlMessageType {
    SET, PLAY, INVALID
};

class ControlMessage {
    ControlMessageType messageType;
    short unsigned int deviceAddress;

public:
    ControlMessage(ControlMessageType type, short unsigned int device) {
        messageType = type;
        deviceAddress = device;
    }

    ControlMessageType getType() {
        return messageType;
    }

    short unsigned int getDevice() {
        return deviceAddress;
    }
};

#endif /* COMMANDS_H_ */