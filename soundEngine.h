#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

// Set frequency to notes
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976

//Star Wars Imperial March melody
const short melody0[] = {NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4, 0, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5,
								 			 NOTE_CS5,NOTE_GS4, NOTE_F4, NOTE_C5, NOTE_A4, 0};

// Rick ashley - never gonna give you up melody
const short melody1[] = {NOTE_C4, NOTE_D4, NOTE_F4, NOTE_D4, NOTE_A4, 0, NOTE_A4, NOTE_G4, 0, NOTE_C4, NOTE_D4, NOTE_F4, NOTE_D4, NOTE_G4, 0,
								 			 NOTE_G4, NOTE_F4, 0};

// Darude - Sandstorm melody
const short melody2[] = {NOTE_A3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, 0,			 0,				0,			 0,				0,
												 NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, 0,			 0,				0,			 0,				0,
												 NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3,
												 NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
												 NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
												 NOTE_A3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3};

// Lazytown: Robby Rotten - We are number one melody
const short melody3[] = {NOTE_F5, NOTE_C6, NOTE_B5, NOTE_C6, NOTE_B5, NOTE_C6, NOTE_B5, NOTE_C6, NOTE_GS5, NOTE_F5,
												 NOTE_F5, NOTE_GS5, NOTE_C6, NOTE_CS6, NOTE_GS5, NOTE_CS6, NOTE_DS6, NOTE_C6, NOTE_CS6, NOTE_C6, NOTE_CS6, NOTE_C6};



// Star Wars Imperial March tempo
const short tempo0[] =  {50, 50, 50, 35, 15, 50, 35, 15, 65, 50, 50, 50, 50, 35, 15, 50, 35, 15, 65, 100};

// Rick ashley - never gonna give you up tempo
const short tempo1[] =  {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};

// Darude - Sandstorm tempo
const short tempo2[] =  {7, 7, 7, 7, 7, 9, 9, 9, 9, 9,   7, 7, 7, 7, 7, 9, 9, 9, 9, 9,   9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
												 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,   9, 9, 9, 9, 9, 9};

// Lazytown: Robby Rotten - We are number one tempo
const short tempo3[] = {55, 15, 5, 5, 5, 5, 15, 15, 35, 55, 15, 15, 15, 35, 35, 35, 35, 15, 15, 15, 15, 35};

// Base variables
	short lengthTone;
	short size = 0;
	short theNote;
	short *tempo;
	short *melody;

#endif SOUNDENGINE_H
