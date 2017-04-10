#define maxSpeed 100
#define MAX_RANGE 5
#include <calibration.c>
#include <regulation.c>
#include <position.c>

short BWBlack = 35;
short BWWhite = 60;
short BWOffset = -1;
float BWMax;

short CBlack = 22;
short CWhite = 63;
short COffset = -1;
float CMax;

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
	CBlack = cal->CBlack + 6; //Hard code to fix crossroads detection
	BWOffset = (BWWhite + BWBlack) / 2;
	COffset = (CWhite + CBlack) / 2;
	BWMax = (BWWhite - BWBlack) / 2.0;
	CMax = (CWhite - CBlack) / 2.0;
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
	return ((CError - COffset) / CMax - (BWError - BWOffset) / BWMax) * MAX_RANGE;
}

bool onCrossRoads(short BW, short C)
{
	return (BW <= BWBlack + BWMax && C <= CBlack + CMax);
}

short BWValue, CValue;

task startPID()
{
	short Kp = 400;
	short Ki = 0;
	short Kd = 100;
	short Tp = 25;

	short lastError = 0;
	short derivative = 0;
	short error = -1;


	short rightSpeed = 0;
	short leftSpeed = 0;

	while(1)
	{
		//We start by reading out sensor values.
		BWValue = SensorValue[BWSensor];
		CValue = SensorValue[CSensor];

		error = errorAmountPID(BWValue, CValue); //First we calculate the position based on our sensors.
		derivative = error - lastError; //Then, we calculate the derivative.
		float Turn = (Kp * error + Kd * derivative) / 100; //Using those we calculate by which amount the speed of our motors must differ.
		rightSpeed = Tp + Turn;
		leftSpeed = Tp - Turn;
		motor[motorB] = rightSpeed;
		motor[motorC] = leftSpeed;
		lastError = error;
	}
}

/**
 * Turn on right motor until right sensor detects the line
 */
void moveLeftPID()
{
	//Turn on right motor
	motor[motorC] = 0;
	motor[motorB] = 25;

	wait1Msec(500);

	while (SensorValue[CSensor] > COffset) {}
	motor[motorB] = 0;
}

void moveRightPID()
{
	//Turn on right motor
	motor[motorC] = 25;
	motor[motorB] = 0;

	wait1Msec(500);

	while (SensorValue[BWSensor] > BWOffset) {}
	motor[motorC] = 0;
}

task handleCrossroads()
{
	while (1)
	{
		//If we set the PID system to stop at crossroads, check for crossroads and break on detection.
		if (stopForCrossRoads && onCrossRoads(BWValue, CValue))
		{
			stopTask(startPID);
			motor[motorB] = 0;
			motor[motorC] = 0;
		}

		wait1Msec(50);
	}
}
