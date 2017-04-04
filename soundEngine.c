task soundErrorTask()
{
	playSound(soundException);

	wait1Msec(500);
	//while (bSoundActive == 1) {}
}

task soundCrossingTask()
{
	playSound(soundBeepBeep);

	wait1Msec(500);

	//while (bSoundActive == 1) {}
}

task constantPlay()
{
	while (1)
	{
		playSound(soundBeepBeep);

		wait1Msec(500);
	}
}
