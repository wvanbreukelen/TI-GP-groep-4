#pragma config(Sensor, S1,     CSensor,  sensorColorNxtRED)
#pragma config(Sensor, S4,     BWSensor,       sensorLightActive)
#pragma config(Motor,  motorA,          MotorLeft,     tmotorNXT, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          MotorRight,    tmotorNXT, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#define maxSpeed 100

short BWBlack = 35;
short BWWhite = 60;
short BWOffset = -1;

short CBlack = 22;
short CWhite = 63;
short COffset = -1;

short Kp = 10;
short Kd = 100;
short Tp = 25;

short lastError = 0;
short integral = 0;

void init()
{
	BWOffset = (BWWhite + BWBlack) / 2;
	COffset = (CWhite + CBlack) / 2;
}
short errorAmount (short inputValue)
{
		return (inputValue - BWOffset);
}
task main()
{
	init();
	while(1)
	{
		short error = errorAmount(sensorValue[BWSensor]); //First we calculate the position based on our sensors.
		short derivative = error - lastError;
		short Turn = (Kp * error + Kd * derivative) / 10;
		short rightSpeed = Tp - Turn;
		short leftSpeed = Tp + Turn;
		if (rightSpeed > maxSpeed) rightspeed = maxSpeed;
		else if (rightSpeed < 0) rightSpeed = 0;
		if (leftSpeed > maxSpeed) leftSpeed = maxSpeed;
		else if (leftSpeed < 0) leftSpeed = 0;
		motor[motorB] = rightSpeed;
		motor[motorC] = leftSpeed;
		lastError = error;
	}
}
