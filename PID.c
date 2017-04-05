#define maxSpeed 100
#include <calibration.c>

short BWBlack = 35;
short BWWhite = 60;
short BWOffset = -1;
float BWMax;

short CBlack = 22;
short CWhite = 63;
short COffset = -1;
float CMax;

short Kp = 10;
short Kd = 100;
short Tp = 25;

short lastError = 0;
short derivative = 0;
short integral = 0;
short error = -1;

bool stopForCrossRoads = true;

/**
 * Initialise PID task
 * @param cal Calibration struct pointer, contains calibration values
 * @param fullPID Boolean to toggle crossroads detection
 */
void initPID(Calibration* cal, bool fullPID)
{
	BWBlack = cal->BWBlack;
	BWWhite = cal->BWWhite;
	CWhite = cal->CWhite;
	CBlack = cal->CBlack;
	BWOffset = (BWWhite + BWBlack) / 2;
	COffset = (CWhite + CBlack) / 2;
	BWMax = (BWWhite - BWBlack) / 2.0;
	CMax = (CWhite - CBlack) / 2.0
	stopForCrossRoads = fullPID;
}

/**
 * Calculate error amount for specified sensor value
 * @param BWError black and white sensor value
 * @param CError color sensor value
 * @return Error amount as short
 */
short errorAmountPID (short BWError, short CError)
{
	//The following statement keeps our BWValue within the borders BWBlack to BWWhite.
	BWError = (BWError < BWBlack) ?  BWBlack : (BWError > BWWhite) ? BWWhite : BWError;
	CError = (CError < CBlack) ?  CBlack : (CError > CWhite) ? CWhite : CError;
	//The following two variables will be the maximum output of our delta variable.
	//Using the following formula, our delta has a range of [-1, 1].
	float BWDelta = (BWError - BWOffset) / BWMax;
	float CDelta = (CError - COffset) / CMax;
	return (CDelta - BWDelta) / 2 * BWMax;
}

task startPID()
{

	short BWValue, CValue;
	short rightSpeed = 0;
	short leftSpeed = 0;

	while(1)
	{
		BWValue = SensorValue[BWSensor];
		CValue = SensorValue[CSensor];
		if (stopForCrossRoads && (BWValue > BWBlack + 5 && CValue > CBlack + 5)) //If both sensors are black, break.
		{
			break;
		}
		error = errorAmountPID(BWValue, CValue); //First we calculate the position based on our sensors.
		derivative = error - lastError;
		short Turn = (Kp * error + Kd * derivative) / 10; //Then we calculate by which amount the two speeds must differ.
		short rightSpeed = Tp + Turn; //We subtract the turn from the speed of our right wheel, making us turn right. Unless turn is negative, then we turn left.
		short leftSpeed = Tp - Turn;
		if (rightSpeed > maxSpeed) rightSpeed = maxSpeed; //limiting speed to boundaries.
		else if (rightSpeed < 0) rightSpeed = 0;
		if (leftSpeed > maxSpeed) leftSpeed = maxSpeed;
		else if (leftSpeed < 0) leftSpeed = 0;
		motor[motorB] = rightSpeed;
		motor[motorC] = leftSpeed;
		lastError = error;
	}

	// Stop motors when crossing was detected
	bFloatDuringInactiveMotorPWM = true;
	motor[motorB] = 0;
	motor[motorC] = 0;
}
