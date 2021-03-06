/**
* @file PID.c
* @authors Dylan Rakiman, Wiebe van Breukelen
* @date 30-03-2017
* @brief File responsible PD (Proportional derivative) based line following system
*/

#include <PID.h>

// Maximal range of error constant
#define MAX_RANGE 6

/**
 * Initialise PID task by entering our standard/calibration values and calculating offset & max delta.
 * @param cal Calibration struct pointer, contains calibration values
 * @param fullPID Boolean to toggle crossroads detection
 */
void initPID(Calibration* cal, bool fullPID)
{
	//Set globals in this file to calibration values
	BWBlack = cal->BWBlack;
	BWWhite = cal->BWWhite;
	CWhite = cal->CWhite;
	CBlack = cal->CBlack + 6; // Hard code to fix crossroads detection
	//Calculate offset (average) and max value (difference between calibration values, halfed)
	BWOffset = (BWWhite + BWBlack) / 2;
	COffset = (CWhite + CBlack) / 2;
	BWMax = (BWWhite - BWBlack) / 2.0;
	CMax = (CWhite - CBlack) / 2.0;
	stopForCrossRoads = fullPID;
}

/**
 * Calculate the difference between the two sensors and return this 'error' value.
 * @param BWError Value of our black and white sensor
 * @param CError Value of our color sensor
 * @return Error amount as short
 */
short errorAmountPID (short BWError, short CError)
{
	//The following statement keeps our BWValue within the borders BWBlack to BWWhite.
	BWError = (BWError < BWBlack) ?  BWBlack : (BWError > BWWhite) ? BWWhite : BWError;
	CError = (CError < CBlack) ?  CBlack : (CError > CWhite) ? CWhite : CError;
	//The following two variables will be the maximum output of our delta variable.
	//Using the following formula, our delta has a range of [-1, 1]. Multiply by MAX_RANGE to increase its range.
	return ((CError - COffset) / CMax - (BWError - BWOffset) / BWMax) * MAX_RANGE;
}

/**
 * Conclude whether or not our robot is at a crossroads. If both sensor values are below average, return true.
 * @param BW Value of our black and white sensor
 * @param C Value of our color sensor
 * @return Boolean stating whether or not the robot is on a crossroads.
 */
bool onCrossRoads(short BW, short C)
{
	return (BW <= BWOffset && C <= COffset);
}

/**
 * Turn on right motor until right sensor detects the line
 */
void moveLeftPID()
{
    //Turn on right motor
    motor[motorC] = 0;
    motor[motorB] = BASE_SPEED;

    if (inMatrixMode)
    {
    	wait1Msec(700);
    } else {
    	wait1Msec(500);
    }

    while (SensorValue[CSensor] > COffset) {}
    motor[motorB] = 0;
}

void moveRightPID()
{
    //Turn on right motor
    motor[motorC] = BASE_SPEED;
    motor[motorB] = 0;

    if (inMatrixMode)
    {
    	wait1Msec(700);
    } else {
    	wait1Msec(500);
    }


    while (SensorValue[BWSensor] > BWOffset) {}
    motor[motorC] = 0;
}

/**
 * Our actual PD-task. This contains the main loop for keeping track where we are on the line.
 * We use some constants and our sensor values to calculate what the speed of our motors will have to be.
 */
task startPID()
{
	//We start off by initialising some constants.
	const short Kp = 300;
	const short Kd = 100;
	//Our base speed on a straight line. This is lower for matrix mode.
	const short Tp = BASE_SPEED;
	//Initialising variables used every loop
	short lastError = 0;
	short derivative = 0;
	short error = -1;
	short rightSpeed = 0;
	short leftSpeed = 0;

	// Start loop (unbreakable, startPID is a task so it can be stopped from the outside).
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
