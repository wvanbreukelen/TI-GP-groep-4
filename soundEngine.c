#include <soundEngine.h>
/**
* Infinitely plays the Imperial March looped, except when told to play one of the other songs.
*
* @param song Song to play
**/
void playSong(short song = 0)
{
	//set pointers to song
	if(song == 0)
	{
		size = sizeof(tempo1)/sizeof(tempo1[0]);
		tempo = &tempo0;
		melody = &melody0;
	}
	if(song == 1)
	{
		size = sizeof(tempo0)/sizeof(tempo0[0]);
		tempo = &tempo1;
		melody = &melody1;
	}
	if(song == 2)
	{
		size = sizeof(tempo2)/sizeof(tempo2[0]);
		tempo = &tempo2;
		melody = &melody2;
	}
	if(song == 3)
	{
		size = sizeof(tempo3)/sizeof(tempo3[0]);
		tempo = &tempo3;
		melody = &melody3;
	}
	//play note for note
	for(short curTone = 0; curTone < size; curTone++)
	{
		lengthTone =  tempo[curTone];
		theNote = melody[curTone];
		playTone(theNote, lengthTone);
		while(bSoundActive){}
	}
}
task constantPlay()//loop playlist
{
	while (1)
	{
		wait1Msec(500);
		playSong(0);

		wait1Msec(500);
		playSong(1);

		wait1Msec(500);
		playSong(2);

		wait1Msec(500);
		playSong(3);
	}
}

task soundErrorTask()
{
	playSound(soundException);

	wait1Msec(500);
}

task soundCrossingTask()
{
	playSound(soundBeepBeep);

	wait1Msec(500);
}
