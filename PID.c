#define maxSpeed 100
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
	CBlack = cal->CBlack;
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
float errorAmountPID (short BWError, short CError)
{
	//The following statement keeps our BWValue within the borders BWBlack to BWWhite.
	BWError = (BWError < BWBlack) ?  BWBlack : (BWError > BWWhite) ? BWWhite : BWError;
	CError = (CError < CBlack) ?  CBlack : (CError > CWhite) ? CWhite : CError;
	//The following two variables will be the maximum output of our delta variable.
	//Using the following formula, our delta has a range of [-1, 1].
	return (float) ((CError - COffset) / CMax - (BWError - BWOffset) / BWMax);
}

bool onCrossRoads(short BW, short C)
{
	return (BW <= BWBlack + BWMax && C <= CBlack + CMax);
}

short BWValue, CValue;

task startPID()
{
	short Kp = 1;
	short Ki = 0;
	short Kd = 0;
	short Tp = 30;

	short lastError = 0;
	short derivative = 0;
	short integral = 0;
	short error = -1;


	float rightSpeed = 0;
	float leftSpeed = 0;

	while(1)
	{
		//We start by reading out sensor values.
		BWValue = SensorValue[BWSensor];
		CValue = SensorValue[CSensor];

		error = errorAmountPID(BWValue, CValue); //First we calculate the position based on our sensors.
		derivative = error - lastError; //Then, we calculate the derivative.
		float Turn = (Kp * error + Ki * integral + Kd * derivative); //Using those we calculate by which amount the speed of our motors must differ.
		if (Turn > 0)
		{
			rightSpeed = Tp;
			leftSpeed = Tp - Turn;
		} else
		{
			rightSpeed = Tp + Turn;
			leftSpeed = Tp;
		}
		motor[motorB] = rightSpeed;
		motor[motorC] = leftSpeed;
		lastError = error;
	}
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
