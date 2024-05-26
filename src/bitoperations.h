#ifndef BITOPERATIONS_H
#define BITOPERATIONS_H

// Setzt das Bit an der Stelle POSITION (setzt es auf 1)
#define SB(VALUE, POSITION) ((VALUE) |= (1U << (POSITION)))

// Löscht das Bit an der Stelle POSITION (setzt es auf 0)
#define CB(VALUE, POSITION) ((VALUE) &= ~(1U << (POSITION)))

// Prüft, ob das Bit an der Stelle POSITION gesetzt ist (ob es 1 ist)
#define IBS(VALUE, POSITION) (((VALUE) & (1U << (POSITION))) != 0)

// Toggelt das Bit an der Stelle POSITION (schaltet es hin und her)
#define TB(VALUE, POSITION) ((VALUE) ^= (1U << (POSITION)))

#endif // BITOPERATIONS_H
