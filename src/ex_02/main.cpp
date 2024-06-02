#include "Arduino.h"
#include "DibsE.h"


DibsE dibse;

void setup() {
    dibse.setup();
    dibse.simpleBlinkOn(500, 255, 255, 255);
}

void loop() {
    dibse.loop();
}

