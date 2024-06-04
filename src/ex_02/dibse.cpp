#include "dibse.h"
#include "Arduino.h"


#define US_TX 8
#define US_RX 4
#define MAX_DISTANCE   200

LedMatrix DibsE::matrix = LedMatrix(LED_LATCH, LED_DATA, LED_CLOCK);

unsigned long previousMillis = 0;  // Stores the last time the LED was updated
int ledState = 0;                  // LED state to keep track of which color is on

DibsE::DibsE() : Sonar(US_TX, US_RX, MAX_DISTANCE){
    distance = 0;
}

void DibsE::setup() {
    strip.begin();
    strip.show();
}

void DibsE::loop() {
    DistanceToMatrix(); // Update the matrix
    static unsigned long lastUpdate = 0; // Stores the last time the matrix was updated

    unsigned long currentMillis = millis(); // Get the current time

    if (currentMillis - lastUpdate >= 3000) { // Check if 300 milliseconds have passed since the last update
        lastUpdate = currentMillis; // Update the last update time
        updateDistance(); // Update the distance
    }

    unsigned long currentMillisLED = millis();

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
        }

        ledState = (ledState + 1) % 3;
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
    DibsE::blinkDuration = map(distance, 0, 200, 50, 500); // map distance to blink duration
    int v = map(distance, 0, 200, 8, 0);
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
    matrix.clear();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < matrixValues.getVal(i); j++) {
            matrix.drawPixel(i, j, 1);
        }
    }
    matrix.update();
}