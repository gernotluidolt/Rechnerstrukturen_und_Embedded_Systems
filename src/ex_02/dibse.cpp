#include "dibse.h"
#include "Arduino.h"

#define LEDDURATION 500

unsigned long previousMillis = 0;  // Stores the last time the LED was updated
int ledState = 0;                  // LED state to keep track of which color is on

void DibsE::setup() {
    strip.begin();
    strip.show();
}

void DibsE::loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= LEDDURATION) {
        previousMillis = currentMillis; // Update last time the LED was updated

        switch (ledState) {
            case 0:
                simpleBlinkOn(LEDDURATION, 255, 0, 0); // Red
                break;
            case 1:
                simpleBlinkOn(LEDDURATION, 0, 255, 0); // Green
                break;
            case 2:
                simpleBlinkOn(LEDDURATION, 0, 0, 255); // Blue
                break;
            case 3:
                simpleBlinkOff();
                previousMillis += 500;
                break;
        }

        ledState = (ledState + 1) % 4; // Cycle through 0, 1, 2, 3
    }
}

void DibsE::simpleBlinkOn(int duration, int red, int green, int blue) {
    strip.setPixelColor(0, strip.Color(red, green, blue));
    strip.show();
}

void DibsE::simpleBlinkOff() {
    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
}
