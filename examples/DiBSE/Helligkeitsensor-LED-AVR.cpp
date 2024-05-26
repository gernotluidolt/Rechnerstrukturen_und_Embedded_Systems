#include <avr/io.h>


int main() {

	/*******************************************************
	 * 1. Teil: Globale Konfiguration des Mikrocontrollers *
	 *******************************************************/

	/**
	 * Konfiguriere den digitalen Ausgang, der die LED steuert
	 **/

	//Konfiguriere Pin PD6 als Output Pin.
	DDRD = (1 << 6);

	/**
	 * Konfiguriere den Analog/Digital-Wandler, an dem der Helligkeitssensor hängt
	 **/

	// Konfiguriere die Betriebsspannung als Referenzspannung, und wähle Analogeingang ADC5 aus
	ADMUX = (1 << REFS0) | 5;

	// Schalte den Analog/Digital-Wandler ein, und setzt einen passenden Prescaler-Wert
	// Analog/Digital-Wandler-Frequenz = CPU-Frequenz / Prescaler-Wert
	// Die Wandler-Frequenz sollte zwischen 50kHz und 200kHz liegen
	// In unserem Fall: 16MHz / 128 = 125kHz
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);


	/****************************************
	 * 2. Teil: Das eigentliche Programm *
	 ****************************************/

	/**
	 * Mikrocontroller Programme bestehen i.d.R. aus einer Endlosschleife,
	 * in der das eigentliche Programm wiederholt abläuft.
	 **/
	for(;;) {

		// Starte den Umwandlungsprozess zum Auslesen des Helligkeitssensors
		ADCSRA = ADCSRA | (1 << ADSC);

		// Solange das ADSC-Bit im ADCSRA Register 1 ist, ist der Umwandlungsprozess noch nicht abgeschlossen
		// Daher warten wir, bis dieses Bit 0 ist
		while (ADCSRA & (1 << ADSC));

		// Lese das Umwandlungsergebnis aus
		int low = ADCL; // Zuerst immer ADCL auslesen!
		int high = ADCH; // Erst dann ADCH auslesen!
		int value = (high << 8) | low; // Das endgültige Ergebnis zusammenbauen

		if (value <= 750) {
			// Helligkeitswert ist kleiner-gleich als Schwellwert
			PORTD = PORTD | (1 << 6); // Setzte LED-Pin auf HIGH, d.h. LED leuchtet
		} else {
			// Helligkeitswert ist größer als Schwellwert
			PORTD = PORTD & ~(1 << 6); // Setzte LED-Pin auf LOW, d.h. LED leuchtet nicht
		}
	}
}


