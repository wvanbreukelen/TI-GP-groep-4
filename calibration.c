/**
* @file calibration.c
* @authors Wiebe van Breukelen, Dylan Rakiman
* @date 31-03-2017
* @brief Calibrates the robot's light and color sensor
*/

#include <calibration.h>
/**
 * Read our sensor values and compare them to our maximum and minimum values, adjusting accordingly
 * @param cal Calibration struct, to contain all maximum and minimum values
 */
void findBoundaries(Calibration* cal)
{
	//Read sensor values
	short BWValue = SensorValue[BWSensor];
	short CValue = SensorValue[CSensor];
	// If our sensor inputs return 0, they are turned off. Skip findBoundaries for now.
	if (BWValue == 0 || CValue == 0) return;
	//If the value of our black-and-white sensor is bigger than our maximum, it is our new maximum
	if (BWValue > cal->BWWhite)
	{
		cal->BWWhite = BWValue;
	}
	else if (BWValue < cal->BWBlack)
	{
		cal->BWBlack = BWValue;
	}

	if (CValue > cal->CWhite)
	{
		cal->CWhite = CValue;
	}
	else if (CValue < cal->CBlack)
	{
		cal->CBlack = CValue;
	}
}
/**
 * Calibrate our robot by turning 90 degrees left and back, use this when standing on a line
 * @return Returns a calibration struct containing our maximum and minimum values
 */
Calibration* calibrate()
{
	//Initialisation
	Calibration cal;
	cal.BWBlack = 100;
	cal.CBlack = 100;

	// Turning motor 90 degrees
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 375;
	motor[motorB] = 20;
	while (nMotorRunState[motorB] != runStateIdle)
	{ // While turning, calculate maximum and minimum values
		findBoundaries(&cal);
		wait1Msec(10);
	}
	// Turning the motor 90 degrees backwards, doing the same thing
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 375;
	motor[motorB] = -20;
	while (nMotorRunState[motorB] != runStateIdle)
	{
		findBoundaries(&cal);
		wait1Msec(10);
	}

	bMotorReflected[motorB] = false;
	// Finally, return our values.
	clearDisplay();
	displayString(2, "CSensor: %d-%d", cal.CBlack, cal.CWhite);
	displayString(3, "BWSensor: %d-%d", cal.BWBlack, cal.BWWhite);
	return &cal;
}
