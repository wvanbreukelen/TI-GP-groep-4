#define maxSpeed 100
#include <calibration.c>

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
short derivative = 0;
short integral = 0;
short error = -1;

/**
 * Initialise PID task
 * @param cal Calibration struct pointer
 */
void initPID(Calibration* cal)
{
	BWBlack = cal->BWBlack;
	BWWhite = cal->BWWhite;
	CWhite = cal->CWhite;
	CBlack = cal->CBlack;
	BWOffset = (BWWhite + BWBlack) / 2;
	COffset = (CWhite + CBlack) / 2;
}

/**
 * Calculate error amount for specified sensor value
 * @param BWValue black and white sensor value
 * @param CValue color sensor value
 * @return Error amount as short
 */
short errorAmountPID (short BWValue, short CValue)
{ //Using the following formula, our delta has a range of [-1, 1].
	//float BWDelta = (BWValue - BWOffset) / ((BWWhite - BWBlack) / 2.0);
	//float CDelta = (CValue - COffset) / ((CWhite - CBlack) / 2.0);
	return (BWValue - BWOffset);
}

task startPID()
{
	// Give PID task full CPU resources
	hogCPU();

	int BWValue, CValue;
	short rightSpeed = 0;
	short leftSpeed = 0;

	while(!((BWValue = SensorValue[BWSensor]) <= BWBlack + 5 && (CValue = SensorValue[CSensor]) <= CBlack + 5)) //If both sensors are black, break.
	{
		error = errorAmountPID(BWValue, CValue); //First we calculate the position based on our sensors.
		derivative = error - lastError;
		short Turn = (Kp * error + Kd * derivative) / 10; //Then we calculate by which amount the two speeds must differ.
		short rightSpeed = Tp - Turn; //We subtract the turn from the speed of our right wheel, making us turn right. Unless turn is negative, then we turn left.
		short leftSpeed = Tp + Turn;
		if (rightSpeed > maxSpeed) rightSpeed = maxSpeed; //limiting speed to boundaries.
		else if (rightSpeed < 0) rightSpeed = 0;
		if (leftSpeed > maxSpeed) leftSpeed = maxSpeed;
		else if (leftSpeed < 0) leftSpeed = 0;
		motor[motorB] = rightSpeed;
		motor[motorC] = leftSpeed;
		lastError = error;
	}

	// Stop motors when crossing was detected
	motor[motorB] = 0;
	motor[motorC] = 0;

	// Release PID task resources
	releaseCPU();

	// Stop task itself
	// @wiebe, @dylan have a look!
	stopTask(startPID);
}
