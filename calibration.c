#include <calibration.h>

void findBoundaries(Calibration* cal)
{
	short BWValue = SensorValue[BWSensor];
	short CValue = SensorValue[CSensor];
	//If our sensor inputs return 0, they are turned off. Skip findBoundaries for now.
	if (BWValue == 0 || CValue == 0) return;
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

Calibration* calibrate()
{
	Calibration cal;

	cal.BWBlack = 100;
	cal.CBlack = 100;

	//Turning motor 90 degrees
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 375;
	motor[motorB] = 20;
	while (nMotorRunState[motorB] != runStateIdle)
	{ //While turning, calculate maximum and minimum values
		findBoundaries(&cal);
		wait1Msec(10);
	}
	//Turning the same motor 90 degrees backwards
	//bMotorReflected[motorB] = true;
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 375;
	motor[motorB] = -20;
	while (nMotorRunState[motorB] != runStateIdle)
	{
		findBoundaries(&cal);
		wait1Msec(10);
	}

	bMotorReflected[motorB] = false;
	//Finally, return our values.
	clearDisplay();
	displayString(2, "CSensor: %d-%d", cal.CBlack, cal.CWhite);
	displayString(3, "BWSensor: %d-%d", cal.BWBlack, cal.BWWhite);
	return &cal;
}
