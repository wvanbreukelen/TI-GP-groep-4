/**
ml = Left motor
mr = Right motor
speed = What the speed is

return = new speed after the function
**/
short Acceleration(short ml, short mr, short speed){
	while (speed<=25){
		speed++;

		motor[ml]=speed;
		motor[mr]=speed;
		wait1Msec(50);

	}
	return speed;
}

/**
ml = Left motor
mr = Right motor
speed = What the speed is

return = new speed after the function
**/
short Deceleration(short ml, short mr, short speed){
		while(speed>=0){
			speed--;

			motor[ml]=speed;
			motor[mr]=speed;
			wait1Msec(50);
		}
		return speed;
}
/*
small test for acceleration and deceleration
*/
task main()
{
	short currentspeed=0;

	currentspeed=Acceleration(motorB,motorC,currentspeed);
	wait1Msec(1000);
	Deceleration(motorB,motorC,currentspeed);


}
