#include "JoystickLow.h"
#include "avr/io.h"

int16_t map(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int16_t abs(int16_t x) {
    return (x > 0) ? x : -x;
}

JoystickLow::JoystickLow(int pinX, int pinY, int pinButton) {
    this->pinX = pinX;
    this->pinY = pinY;
    this->pinButton = pinButton;
    this->posX = 0;
    this->posY = 0;
    this->button = false;
    this->deadzone = 20;
}

void JoystickLow::begin() {
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));

    // Set pins as input
    DDRD &= ~(1 << this->pinX);
    DDRD &= ~(1 << this->pinY);
    DDRD &= ~(1 << this->pinButton);
    // Enable pullup resistor
    PORTD |= (1 << this->pinX);
    PORTD |= (1 << this->pinY);
    PORTD |= (1 << this->pinButton);
}

void JoystickLow::update() {
    this->posX = this->readX();
    this->posY = this->readY();
    this->button = this->readButton();
}

int16_t JoystickLow::getPosX(bool immediate) {
    if (immediate) {
        return this->readX();
    }
    return this->posX;
}

int16_t JoystickLow::getPosY(bool immediate) {
    if (immediate) {
        return this->readY();
    }
    return this->posY;
}

bool JoystickLow::getButton(bool immediate) {
    if (immediate) {
        return this->readButton();
    }
    return this->button;
}

void JoystickLow::setDeadzone(int16_t deadzone) {
    this->deadzone = deadzone;
}

int16_t JoystickLow::getDeadzone() {
    return this->deadzone;
}

int16_t JoystickLow::readX() {
    int16_t val = rawReadValue(pinX);
    val = val - 512;
    if (abs(val) < deadzone) {
        return 0;
    }
    return val;
}

int16_t JoystickLow::readY() {
    int16_t val = rawReadValue(pinY);
    val = val - 512;
    if (abs(val) < deadzone) {
        return 0;
    }
    return val;
}

bool JoystickLow::readButton() {
    return false;
}

int16_t JoystickLow::rawReadValue(int pin) {
    // Wähle den ADC-Kanal aus
    ADMUX = (ADMUX & 0xF8) | (pin & 0x07);
    // Starte die Wandlung
    ADCSRA |= (1 << ADSC);
    // Warte bis die Wandlung abgeschlossen ist
    while (ADCSRA & (1 << ADSC));
    // Gebe das Ergebnis zurück
    return ADC;
}