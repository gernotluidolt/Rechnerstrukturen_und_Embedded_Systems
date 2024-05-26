#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define RGB_LED_PIN A4

/*
 * Benötigte Bibliotheken (unter "Projekt Properties" => "Libraries" einzustellen):
 * - Adafruit GFX Library (unter "Display" zu finden)
 * - Adafruit NeoPixel (unter "Display" zu finden)
 * - SPI (unter "Platform Libraries" => "Arduino AVR Boards" zu finden)
 */


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel rgbLED(1, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
	// Initialisiert das RGB-LED
	rgbLED.begin();
}


void loop() {
	uint8_t red, green, blue;

	// Sets color of the RGB LED to red
	red = 255;
	green = 0;
	blue = 0;
	rgbLED.setPixelColor(0, red, green, blue);
	// Needs to be called to push the color change to the RGB LED
	rgbLED.show();
	delay(1000);

	// Sets color of the RGB LED to green
	red = 0;
	green = 255;
	blue = 0;
	rgbLED.setPixelColor(0, red, green, blue);
	// Needs to be called to push the color change to the RGB LED
	rgbLED.show();
	delay(1000);

	// Sets color of the RGB LED to blue
	red = 0;
	green = 0;
	blue = 255;
	rgbLED.setPixelColor(0, red, green, blue);
	// Needs to be called to push the color change to the RGB LED
	rgbLED.show();
	delay(1000);

	// Sets color of the RGB LED to white
	red = 255;
	green = 255;
	blue = 255;
	rgbLED.setPixelColor(0, red, green, blue);
	// Needs to be called to push the color change to the RGB LED
	rgbLED.show();
	delay(1000);

	// Sets color of the RGB LED to yellow
	red = 255;
	green = 255;
	blue = 0;
	// Sets color of the RGB LED
	rgbLED.setPixelColor(0, red, green, blue);
	// Needs to be called to push the color change to the RGB LED
	rgbLED.show();
	delay(1000);

	// Sets color of the RGB LED to purple
	red = 255;
	green = 0;
	blue = 255;
	rgbLED.setPixelColor(0, red, green, blue);
	// Needs to be called to push the color change to the RGB LED
	rgbLED.show();
	delay(1000);

	// Sets color of the RGB LED to turquoise
	red = 0;
	green = 255;
	blue = 255;
	rgbLED.setPixelColor(0, red, green, blue);
	// Needs to be called to push the color change to the RGB LED
	rgbLED.show();
	delay(1000);
}
