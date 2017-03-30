void soundError()
{
	playSound(soundException);

	while (bSoundActive == 1) {}
}

void soundCrossing()
{
	playSound(soundBeepBeep);

	while (bSoundActive == 1) {}
}

task main()
{
	soundCrossing();
	soundError();
}
