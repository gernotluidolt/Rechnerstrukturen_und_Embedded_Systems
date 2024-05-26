#include <Arduino.h>

#define LIGHTSENSOR_PIN 	A2
#define LED_PIN				12



/**
 * Ein Arduino Programm hat keine main()-Funktion. Stattdessen müssen zwei Funktionen implementiert werden, setup() und loop().
 * setup() enthält Initialisierungscode, der von der Arduino Bibliothek einmal am Anfang ausgeführt wird.
 * loop() wird von der Arduino Bibliothek regelmässig in einer Endlosschleife aufgerufen, und enthält den eigentlichen Programmcode.
 */



/*******************************************************
 * 1. Teil: Globale Konfiguration des Mikrocontrollers *
 *******************************************************/
void setup() {
	/**
	 * Konfiguriere die serielle Schnittstelle
	 **/

	// Setze Baud-Rate auf 115200 baud
	Serial.begin(115200);

	/**
	 * Konfiguriere den digitalen Ausgang, der die LED steuert
	 **/

	//Konfiguriere Pin 12 als Output Pin.
	pinMode(LED_PIN, OUTPUT);

	/**
	 * Konfiguriere den Analog/Digital-Wandler, an dem der Helligkeitssensor hängt
	 **/

	// Hier ist nichts zu tun, die Arduino-Bibliothek macht alles automatisch
}



/****************************************
 * 2. Teil: Das eigentliche Programm *
 ****************************************/
unsigned long lastTime = 0;

void loop() {
	// Lese then Helligkeitssensor aus
	int helligkeit = analogRead(LIGHTSENSOR_PIN);
	unsigned long time = millis();

	// Gebe jede Sekunde den Helligkeitswert über die serielle Schnittstelle aus
	if (time - lastTime >= 1000) {
		Serial.print("Helligkeit: ");
		Serial.println(helligkeit); // println schreibt am Ende noch zusätzlich ein newline nach serial out
		lastTime = time;
	}

	if (helligkeit <= 750) {
		// Helligkeitswert ist kleiner-gleich als Schwellwert
		digitalWrite(LED_PIN, HIGH); // Setzte LED-Pin auf HIGH, d.h. LED leuchtet
	} else {
		// Helligkeitswert ist größer als Schwellwert
		digitalWrite(LED_PIN, LOW); // Setzte LED-Pin auf LOW, d.h. LED leuchtet nicht
	}
}



