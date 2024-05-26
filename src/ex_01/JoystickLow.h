#ifndef JOYSTICKLOW_H
#define JOYSTICKLOW_H

#include "stdint.h"

class JoystickLow {
public:
    JoystickLow(int pinX, int pinY, int pinButton);
    void begin();
    void update();
    int16_t getPosX(bool immediate = false);
    int16_t getPosY(bool immediate = false);
    bool getButton(bool immediate = false);
    void setDeadzone(int16_t deadzone);
    int16_t getDeadzone();
    int16_t rawReadValue(int pin);
private:
    int pinX;
    int pinY;
    int pinButton;
    int16_t posX;
    int16_t posY;
    bool button;
    int16_t deadzone;
    int16_t readX();
    int16_t readY();
    bool readButton();
};


#endif JOYSTICKLOW_H
