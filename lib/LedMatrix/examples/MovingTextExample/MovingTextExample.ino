#include <Arduino.h>
#include <LedMatrix.h>

// LED Matrix pins
#define LED_LATCH 11
#define LED_DATA 16
#define LED_CLOCK 15

LedMatrix ledMatrix(LED_LATCH,LED_DATA,LED_CLOCK);
LedMatrixTextBuffer textBuffer(ledMatrix);


void setup() {
	// Write text into text buffer
	textBuffer.drawText("Hello World! ");
}

unsigned long lastTime = 0;

void loop() {
	unsigned long time = millis();

	// Every 100 milliseconds shift text left
	if (time - lastTime >= 100) {
		textBuffer.slideLeft(1);
		lastTime = time;
	}

	// Write changes onto the display.
	textBuffer.update();
}
 
