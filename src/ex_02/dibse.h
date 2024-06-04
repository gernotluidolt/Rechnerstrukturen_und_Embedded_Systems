#ifndef DIBSE_H
#define DIBSE_H
#include <Adafruit_NeoPixel.h>
#include "LedMatrix.h"
#include "pins_eduardu.h"

#include "NewPing.h"
#include "MatrixValues.h"


// LED Matrix pins
#define LED_LATCH 11
#define LED_DATA 16
#define LED_CLOCK 15

class DibsE {
public:
    DibsE();
    void setup();
    void loop();
    void simpleBlinkOn(int duration, int red, int green, int blue);
    void simpleBlinkOff();
    void SerialPrintDistance();
    void DistanceToMatrix();
    MatrixValues matrixValues;
    int distance;
private:
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN_RGB_LED, NEO_GRB + NEO_KHZ800);
    static LedMatrix matrix;
    NewPing Sonar;
    void updateDistance();
    int blinkDuration = 100;
};

#endif //DIBSE_H