#include <avr/io.h>


int main() {

	/*******************************************************
	 * 1. Teil: Globale Konfiguration des Mikrocontrollers *
	 *******************************************************/

	/**
	 * Konfiguriere den digitalen Eingang, an dem der Bewegungssensor hängt
	 **/

	// Hier ist nichts zu tun, da der Pin eh schon standardmäßig als digitaler Eingang konfiguriert ist.

	/**
	 * Konfiguriere den digitalen Ausgang, der die LED steuert
	 **/

	//Konfiguriere Pin PD6 als Output Pin.
	DDRD = (1 << 6);


	/****************************************
	 * 2. Teil: Das eigentliche Programm *
	 ****************************************/

	/**
	 * Mikrocontroller Programme bestehen i.d.R. aus einer Endlosschleife,
	 * in der das eigentliche Programm wiederholt abläuft.
	 **/
	for(;;) {

		// Lese den Zustand des Bewegungssensors aus. (Wenn eine Bewegung erkannt wurde, dann ist das entsprechende Bit 1, ansonsten 0)
		// Der Bewegungssensor hängt am Pin PC6, d.h. wir müssen das Bit 6 im Register PINC auslesen.
		int value = PINC & (1 << 6);

		if (value) {
			// Bewegung wurde erkannt
			PORTD = PORTD | (1 << 6); // Setzte LED-Pin auf HIGH, d.h. LED leuchtet
		} else {
			// Keine Bewegung wurde erkannt
			PORTD = PORTD & ~(1 << 6); // Setzte LED-Pin auf LOW, d.h. LED leuchtet nicht
		}
	}
}
