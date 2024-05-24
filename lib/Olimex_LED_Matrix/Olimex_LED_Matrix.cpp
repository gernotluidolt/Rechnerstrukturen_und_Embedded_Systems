/*-------------------------------------------------------------------------
  Arduino library for the Olimex 8x8 (non-rgb) matrix. Based on the original library LED_Matrix created by Lutz Reiter, Dec 2014.

  Olimex_LED_Matrix(int latchPin, int dataPin, int clockPin) - initializes the class
  void Clear() - clears matrix
  void SetBrightness (int Brightness) - sets the brightness of the matrix
  void ChangeBrightness (int X) - changes the brightness by X
  void CharIntoBuffer (unsigned char C, int Index) - sets a character in the buffer at the specified index
  void StringIntoBuffer (unsigned char Str[], int Index) - sets a string in the buffer at the specified index
  void DisplayText(unsigned char Str[]) - sets text in the buffer and updates the matrix
  void DisplayText(unsigned char Str[], int Offset) - sets text in the buffer with an offset and updates the matrix
  void UpdateText() - refreshes text on the matrix
  void SlideLeft (int Positions) - moves text to the left and updates the matrix
  void SlideRight (int Positions) - moves text to the right and updates the matrix
  void UpdateMatrix() - updates the matrix with the content in the buffer
  -------------------------------------------------------------------------*/
#include "Olimex_LED_Matrix.h"

Olimex_LED_Matrix::Olimex_LED_Matrix(int latchPin, int dataPin, int clockPin)
{
	this->dataPin = dataPin;
	this->latchPin = latchPin;
	this->clockPin = clockPin;

	pinMode (latchPin, OUTPUT);
	pinMode (clockPin, OUTPUT);
	pinMode (dataPin, OUTPUT);

	this->brightness = 255;

	LED_Offset = 0;

	this->Clear();
}

// clears matrix
void Olimex_LED_Matrix::Clear()
{
	for (int i=0;i<ROWS;i++)
	this->matrix[i] = 0;
}

void Olimex_LED_Matrix::SetBrightness (int Brightness)
{
	if (Brightness > 255)
		Brightness = 255;
	if (Brightness < 0)
		Brightness = 0;
	brightness = Brightness;
}

void Olimex_LED_Matrix::ChangeBrightness (int X)
{
	brightness = brightness + X;
	if (brightness > 255)
		brightness = 255;
	if (brightness < 0)
		brightness = 0;
}



// uncomment one of the lines depending on the orientation of the LED_Matrix
void Olimex_LED_Matrix::DrawColumn(int Column, unsigned char Byte)
{
	matrix[7-Column] = BitReverseTable256[Byte];
	//matrix[7-Column] = Byte;
	//matrix[Column] = BitReverseTable256[Byte];
	//matrix[Column] = Byte;
}

void Olimex_LED_Matrix::CharIntoBuffer (unsigned char C, int Index)
{
	int i;
	for (i=0; i<CHAR_WIDTH; i++)
		if (i==CHAR_WIDTH - 1)
			TextBuffer[Index*CHAR_WIDTH + i] = 0;
		else
			TextBuffer[Index*CHAR_WIDTH + i] = FontLookup[C-0x20][i];
}

void Olimex_LED_Matrix::StringIntoBuffer (unsigned char Str[], int Index)
{
	int i;
	for (i=0; Str[i]; i++)
		CharIntoBuffer(Str[i], Index+i);
	TextLen = i;
}

void Olimex_LED_Matrix::DisplayText(unsigned char Str[])
{
	int i;
	StringIntoBuffer (Str, 0);
	Clear();
	for (i=0; i<8; i++)
		DrawColumn (i, TextBuffer[(LED_Offset + i)%(CHAR_WIDTH * TextLen)]);
	UpdateMatrix();
}

void Olimex_LED_Matrix::DisplayText(unsigned char Str[], int Offset)
{
	int i;
	StringIntoBuffer (Str, 0);
	LED_Offset = Offset;
	Clear();
	for (i=0; i<8; i++)
		DrawColumn (i, TextBuffer[(LED_Offset + i)%(CHAR_WIDTH * TextLen)]);
	UpdateMatrix();
}

void Olimex_LED_Matrix::UpdateText()
{
	int i;
	Clear();
	for (i=0; i<8; i++)
		DrawColumn (i, TextBuffer[(LED_Offset + i)%(CHAR_WIDTH * TextLen)]);
	UpdateMatrix();
}

void Olimex_LED_Matrix::SlideRight (int Positions)
{
	LED_Offset=LED_Offset - Positions;
	if (LED_Offset < 0)
		LED_Offset = LED_Offset + (CHAR_WIDTH * TextLen);
	UpdateText ();
}

void Olimex_LED_Matrix::SlideLeft (int Positions)
{
	LED_Offset = (LED_Offset + Positions) % (CHAR_WIDTH * TextLen);
	UpdateText ();
}

// shifts the data to the led-matrix to display it
//the multiplexing has to be done by the arduino, so this function has to be called constantly
void Olimex_LED_Matrix::UpdateMatrix()
{
	for (byte i=0; i<ROWS; i++)
	{
		// bitwise operations are faster
		PORTB = PORTB & 0x7F;	//digitalWrite(this->latchPin, LOW);
		shiftOut(this->dataPin, this->clockPin, LSBFIRST, matrix[i]);
		shiftOut(this->dataPin, this->clockPin, LSBFIRST, 1 << i);
		PORTB = PORTB | 0x80;	//digitalWrite(this->latchPin, HIGH);
		//delayMicroseconds(20);

		// make the display less bright
		if (this->brightness < 255)
		{
			PORTB = PORTB & 0x7F;	//digitalWrite(this->latchPin, LOW);
			shiftOut(this->dataPin, this->clockPin, LSBFIRST, 0);
			shiftOut(this->dataPin, this->clockPin, LSBFIRST, 1 << i);
			PORTB = PORTB | 0x80;	//digitalWrite(this->latchPin, HIGH);
			delayMicroseconds((255 - this->brightness)*8);
		}
	}
}
