#ifndef DIBSE_H
#define DIBSE_H
#include <Adafruit_NeoPixel.h>
#include <Olimex_LED_Matrix_L.h>
#include "pins_eduardu.h"


#include "NewPing.h"



class DibsE {
public:
    DibsE();
    void setup();
    void loop();
    void simpleBlinkOn(int duration, int red, int green, int blue);
    void simpleBlinkOff();
    void DisplayDistance();
    int distance;
private:
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN_RGB_LED, NEO_GRB + NEO_KHZ800);
    Olimex_LED_Matrix_L matrix;
    NewPing Sonar;
    void updateDistance();
};


#endif //DIBSE_H