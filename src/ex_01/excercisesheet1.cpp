#include "excercisesheet1.h"
#include "Arduino.h"
#include "bitoperations.h"
#include "JoystickHigh.h"
#include "JoystickLow.h"
#include "DibsE.h"

void printBits(uint8_t value) {
    for (int i = 8; i >= 0; --i) {
        bool isBitSet = IBS(value, i);
        if (isBitSet) {
            Serial.print("1");
        } else {
            Serial.print("0");
        }
    }
    Serial.print("\n");
}

void ExcerciseSheet1::solveExercise1_1(int8_t value) { // 1.1 Bitweise Operatoren mit bitoperations.h
    Serial.println("**************************************************************");
    Serial.println("*              Aufgabe 1.1 Bitweise Operatoren               *");
    Serial.println("**************************************************************");

    Serial.print("Ursprünglicher Wert:\n");
    printBits(value);

    Serial.print("Setze Bit an Position 3:\n");
    SB(value, 3);
    printBits(value);

    Serial.print("Lösche Bit an Position 3:\n");
    CB(value, 3);
    printBits(value);


    Serial.print("Ist bit 3 gesetzt?\n");
    bool isSet = IBS(value, 3);
    Serial.print(isSet ? "Ja\n" : "Nein\n");

    Serial.print("Togglen des Bits an Position 3:\n");
    TB(value, 3);
    printBits(value);

    Serial.print("Ist bit 3 gesetzt?\n");
    isSet = IBS(value, 3);
    Serial.print(isSet ? "Ja\n" : "Nein\n");
}

void ExcerciseSheet1::solveExercise1_2(int pinX, int pinY, int pinButton) {
    Serial.println("**************************************************************");
    Serial.println("*              Aufgabe 1.2 JoystickHigh                        *");
    Serial.println("**************************************************************");

    JoystickHigh joystick(pinX, pinY, pinButton);
    joystick.begin();
    // 5 Sekunden Demo
    for (int i = 0; i < 10; ++i) {
        joystick.update();
        int16_t posX = joystick.getPosX();
        int16_t posY = joystick.getPosY();
        bool button = joystick.getButton();

        Serial.print("HighX: ");
        Serial.print(posX);
        Serial.print("\nHighY: ");
        Serial.print(posY);
        Serial.print("\nHighButton: ");
        Serial.println(button);
        Serial.print("\n");

        delay(500);
    }
}

void ExcerciseSheet1::solveExercise1_3(int pinX, int pinY, int pinButton) {
    Serial.println("**************************************************************");
    Serial.println("*              Aufgabe 1.3 JoystickLow                        *");
    Serial.println("**************************************************************");

    JoystickLow joystick(pinX, pinY, pinButton);
    joystick.begin();

    // 5 Sekunden Demo
    for (int i = 0; i < 10; ++i) {
        joystick.update();
        int16_t posX = joystick.getPosX();
        int16_t posY = joystick.getPosY();
        bool button = joystick.getButton();

        Serial.print("LowX: ");
        Serial.print(posX);
        Serial.print("\nLowY: ");
        Serial.print(posY);
        Serial.print("\nLowButton: ");
        Serial.println(button);
        Serial.print("\n");

        delay(500);
    }
}

void ExcerciseSheet1::solveExercise1_4() {
    Serial.println("**************************************************************");
    Serial.println("*                 Aufgabe 1.4 DibsE                          *");
    Serial.println("**************************************************************");

    DibsE dibsE;
    dibsE.loop();
}