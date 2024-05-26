#include "dibse.h"
#include "Arduino.h"

#define LEDDURATION 500

void DibsE::setup() {
    strip.begin();
}

void DibsE::loop() {
    simpleBlinkOn(LEDDURATION, 255, 0, 0);
    delay(LEDDURATION);
    simpleBlinkOn(LEDDURATION, 0, 255, 0);
    delay(LEDDURATION);
    simpleBlinkOn(LEDDURATION, 0, 0, 255);
    delay(LEDDURATION);
    simpleBlinkOff();
    delay(1000);
}

void DibsE::simpleBlinkOn(int duration, int red, int green, int blue) {
    strip.setPixelColor(0, strip.Color(red, green, blue));
    strip.show();
    delay(duration);
}

void DibsE::simpleBlinkOff() {
    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
}

