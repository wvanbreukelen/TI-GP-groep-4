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
short errorAmount (int inputValue)
{
		return (inputValue - BWOffset);
}
task startPID()
{
	init();
	int BWValue;
	while(!((BWValue = SensorValue[BWSensor]) <= BWBlack + 5 && SensorValue[CSensor] <= CBlack + 5)) //If both sensors are black, break.
	{
		short error = errorAmount(BWValue); //First we calculate the position based on our sensors.
		short derivative = error - lastError; //Next, we calculate the derivative based on our last error.
		short Turn = (Kp * error + Kd * derivative) / 10; //Then we calculate by which amount the two speeds must differ.
		short rightSpeed = Tp - Turn; //We subtract the turn from the speed of our right wheel, making us turn right. Unless turn is negative, then we turn left.
		short leftSpeed = Tp + Turn;
		if (rightSpeed > maxSpeed) rightspeed = maxSpeed; //limiting speed to boundaries.
		else if (rightSpeed < 0) rightSpeed = 0;
		if (leftSpeed > maxSpeed) leftSpeed = maxSpeed;
		else if (leftSpeed < 0) leftSpeed = 0;
		motor[motorB] = rightSpeed;
		motor[motorC] = leftSpeed;
		lastError = error;
	}
}