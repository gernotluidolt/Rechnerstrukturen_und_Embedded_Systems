#include <Arduino.h>
#include <LedMatrix.h>

// LED Matrix pins
#define LED_LATCH 11
#define LED_DATA 16
#define LED_CLOCK 15

LedMatrix ledMatrix(LED_LATCH,LED_DATA,LED_CLOCK);


void setup() {
}

void loop() {
	// Clears the display buffer.
	ledMatrix.clear();
    
	// Draws an x into the display buffer.
	for (uint8_t x = 0; x < 8; x++) {
			ledMatrix.drawPixel(x, x, true);
			ledMatrix.drawPixel(x, 7-x, true);
	}
	
	// Display everything on the display.
	ledMatrix.update();
}
