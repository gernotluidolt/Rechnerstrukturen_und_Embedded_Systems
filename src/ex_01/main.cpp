#include "Arduino.h"  // high level functions for Arduino
#include "bitoperations.h"
#include "stdint.h" // for uint8_t, uint16_t, etc., int are 2 bytes in Arduino
// #include "avr/io.h" // register definitions - avr-libc contains low-level functions for AVR microcontrollers
#include "pins_eduardu.h"
#include "JoystickHigh.h"
#include "JoystickLow.h"
#include "DibsE.h"

#include "excercisesheet1.h"

DibsE dibse;

void setup() {
    Serial.begin(9600);

    // 1.4 DibsE
    dibse.setup();
    dibse.simpleBlinkOn(500, 255, 255, 255);

    // 1.1 Bitweise Operatoren - Testausgabe im seriellen Monitor
    int8_t value = 0; // Initialisierung mit 0
    ExcerciseSheet1::solveExercise1_1(value);
}

void loop() {
    dibse.loop();

    // 1.2 und 1.3 - Testausgabe im seriellen Monitor
    ExcerciseSheet1::solveExercise1_2(PIN_JOYSTICK_X, PIN_JOYSTICK_Y, PIN_JOYSTICK_BUTTON);
    ExcerciseSheet1::solveExercise1_3(PF7, PF6, PIN_JOYSTICK_BUTTON);


}
