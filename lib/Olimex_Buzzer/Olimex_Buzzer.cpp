/*-------------------------------------------------------------------------
  Arduino library for controlling a Buzzer.

  Olimex_Buzzer (int _Pin) - initializes the class (to be used with the Arduino pin on which the buzzer is attached)
  void Beep (int Frequency) - plays sound with a specific frequency
  void Note (int Frequency, int Duration) - plays sound with a specific frequency for a specified duration
  void Mute () - silences the buzzer
  void Play (const int Notes[], const float Durations[], int Tempo) - plays musical notes at a certain tempo with specified durations for each note
  -------------------------------------------------------------------------*/

#include "Olimex_Buzzer.h"

Olimex_Buzzer::Olimex_Buzzer (int _Pin)
{
	Pin = _Pin;
	pinMode (Pin, OUTPUT);
}

void Olimex_Buzzer::Beep (int Frequency)
{
	tone(Pin, Frequency);
}

void Olimex_Buzzer::Note (int Frequency, int Duration)
{
	//Play tone on buzzerPin
	if (Frequency != _P)
		tone(Pin, Frequency);
	delay(Duration);
	//Stop tone on buzzerPin
	noTone(Pin);

	delay(20);  // very short silence between the notes to distinguish the equal tones (not to be mistaken with the pauses)
}

void Olimex_Buzzer::Mute ()
{
	noTone (Pin);
}

void Olimex_Buzzer::Play (const int Notes[], const float Durations[], int Tempo)
{
  int i, TPQ = 60000/Tempo;	// TPQ stands for Time Per Quarter (note). Calculates duration of a quarter note in milliseconds
  for (i=0; Notes[i] != _END; i++)
    Note(Notes[i], Durations[i]*TPQ);
}
