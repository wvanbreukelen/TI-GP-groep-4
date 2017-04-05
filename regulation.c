void acceleration(short ml, short mr, short targetSpeed, short alcOffset = 1)
{
	short currentMotorSpeed = motor[ml];
	while (currentMotorSpeed < targetSpeed){
		currentMotorSpeed += alcOffset;

		motor[ml] = currentMotorSpeed;
		motor[mr] = currentMotorSpeed;
		wait1Msec(50);
	}
}

void deceleration(short ml, short mr, short targetSpeed, short breakOffset = 1)
{
	short currentMotorSpeed = motor[ml];
	while (currentMotorSpeed > targetSpeed){
			currentMotorSpeed -= breakOffset;

			motor[ml] = currentMotorSpeed;
			motor[mr] = currentMotorSpeed;
			wait1Msec(50);
		}
}

// Example code, remove it later @wiebe

/**task main()
{
	short currentspeed=0;

	currentspeed=Acceleration(motorB,motorC,currentspeed);
	wait1Msec(1000);
	Deceleration(motorB,motorC,currentspeed);


}**/
