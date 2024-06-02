#include "dibse.h"
#include "Arduino.h"


#define US_TX 8
#define US_RX 4
#define MAX_DISTANCE   200

// LED Matrix pins
#define LED_LATCH 11
#define LED_DATA 16
#define LED_CLOCK 15

unsigned long previousMillis = 0;  // Stores the last time the LED was updated
int ledState = 0;                  // LED state to keep track of which color is on

DibsE::DibsE() : Sonar(US_TX, US_RX, MAX_DISTANCE), matrix(LED_LATCH, LED_CLOCK, LED_DATA) {
    distance = 0;
}

void DibsE::setup() {
    strip.begin();
    strip.show();
}

void DibsE::loop() {

    updateDistance();
    SerialPrintDistance();
    DistanceToMatrix();

    unsigned long currentMillisLED = millis();
    unsigned long currentMillisValue = millis();
    if (currentMillisValue - previousMillis >= 500) { // Update every 500 milliseconds
        previousMillis = currentMillisValue;
        updateDistance();
    }
    if (currentMillisLED - previousMillis >= DibsE::blinkDuration) {
        previousMillis = currentMillisLED; // Update last time the LED was updated

        switch (ledState) {
            case 0:
                simpleBlinkOn(DibsE::blinkDuration, 255, 0, 0); // Red
                break;
            case 1:
                simpleBlinkOn(DibsE::blinkDuration, 0, 255, 0); // Green
                break;
            case 2:
                simpleBlinkOn(DibsE::blinkDuration, 0, 0, 255); // Blue
                break;
                /*
            case 3:
                simpleBlinkOff();
                previousMillis += DibsE::blinkDuration; // TODO check if int is correct, was 500 before
                break;
                 */
        }

        ledState = (ledState + 1) % 3; //4; // Cycle through 0, 1, 2, 3
    }
}

void DibsE::SerialPrintDistance() {
    if (distance < 0) {
        Serial.println("Error: ");
        Serial.println(Sonar.ping_result);
    } else {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
    }
}

void DibsE::updateDistance() {
    distance = Sonar.ping_cm(); // new distance in cm
    DibsE::blinkDuration = map(distance, 0, 200, 2000, 100); // map distance to blink duration
    int v = map(distance, 0, 200, 0, 8);
    DibsE::matrixValues.newVal(v);
}

void DibsE::simpleBlinkOn(int duration, int red, int green, int blue) {
    strip.setPixelColor(0, strip.Color(red, green, blue));
    strip.show();
}

void DibsE::simpleBlinkOff() {
    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
}

void DibsE::DistanceToMatrix() {
    for (int x = 0; x < 8; x++) { // 8 rows - x Value of Matrix
        for (int y = 0; y <= matrixValues.getVal(y); y++) { // y Value of Matrix
            matrix.SetPixel(x, y);
        }
    }
    matrix.UpdateMatrix();
}