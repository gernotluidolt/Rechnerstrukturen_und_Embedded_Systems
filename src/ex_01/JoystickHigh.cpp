#include "JoystickHigh.h"
#include "Arduino.h"
#include "avr/io.h"

JoystickHigh::JoystickHigh(int pinX, int pinY, int pinButton) {
    this->pinX = pinX;
    this->pinY = pinY;
    this->pinButton = pinButton;
    this->posX = 0;
    this->posY = 0;
    this->button = false;
    this->deadzone = 15;
}

void JoystickHigh::begin() {
    pinMode(pinX, INPUT);
    pinMode(pinY, INPUT);

    // Setze PE2 als digitalen Eingang
    DDRE &= ~(1 << 4);
    /*
     * Habs leider nicht geschafft den Button zum Laufen zu bringen
     */

}

void JoystickHigh::update() {
    posX = readX();
    posY = readY();
    button = readButton();
}

int16_t JoystickHigh::getPosX(bool immediate) {
    if (immediate) {
        return readX();
    }
    return posX;
}

int16_t JoystickHigh::getPosY(bool immediate) {
    if (immediate) {
        return readY();
    }
    return posY;
}

bool JoystickHigh::getButton(bool immediate) {
    if (immediate) {
        return readButton();
    }
    return button;
}

void JoystickHigh::setDeadzone(int16_t deadzone) {
    this->deadzone = deadzone;
}

int16_t JoystickHigh::getDeadzone() {
    return deadzone;
}

int16_t JoystickHigh::readX() {
    int16_t val = analogRead(pinX);
    val = map(val, 0, 1023, -512, 512);
    if (abs(val) < deadzone) {
        return 0;
    }
    return val;
}

int16_t JoystickHigh::readY() {
    int16_t val = analogRead(pinY);
    val = map(val, 0, 1023, -512, 512);
    if (abs(val) < deadzone) {
        return 0;
    }
    return val;
}

bool JoystickHigh::readButton() {
    return digitalRead(pinButton);
}

