short acceleration(short ml, short mr, short speed){
	while (speed<=25){
		speed++;

		motor[motorB]=speed;
		motor[motorC]=speed;
		wait1Msec(50);

	}
	return speed;
}

short deceleration(short ml, short mr, short speed){
		while(speed>=0){
			speed--;

			motor[motorB]=speed;
			motor[motorC]=speed;
			wait1Msec(50);
		}
		return speed;
}

// Example code, remove it later @wiebe

/**task main()
{
	short currentspeed=0;

	currentspeed=Acceleration(motorB,motorC,currentspeed);
	wait1Msec(1000);
	Deceleration(motorB,motorC,currentspeed);


}**/
