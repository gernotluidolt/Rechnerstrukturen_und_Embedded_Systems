#ifndef DIBSE_H
#define DIBSE_H
#include <Adafruit_NeoPixel.h>
#include "pins_eduardu.h"

class DibsE {
public:
    void setup();
    void loop();
    void simpleBlinkOn(int duration, int red, int green, int blue);
    void simpleBlinkOff();
private:
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN_RGB_LED, NEO_GRB + NEO_KHZ800);
};


#endif //DIBSE_H
