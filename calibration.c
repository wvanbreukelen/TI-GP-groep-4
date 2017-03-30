typedef struct
{
	short CBlack;
	short CWhite;
	short BWBlack;
	short BWWhite;
} Calibration;

short BWValue = -1;
short CValue = -1;

void findBoundaries(Calibration cal)
{
	BWValue = SensorValue[BWSensor];
	CValue = SensorValue[CSensor];
	if (BWValue > cal.BWWhite)
	{
		cal.BWWhite = BWValue;
	}
	else if (BWValue < cal.BWBlack)
	{
		cal.BWBlack = BWValue;
	}
	if (CValue > cal.CWhite)
	{
		cal.CWhite = CValue;
	}
	else if (CValue < cal.CBlack)
	{
		cal.CBlack = CValue;
	}
}
void calibrate(Calibration cal)
{
	nSyncedMotors = synchBC;
	nSyncedTurnRatio = -100;
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 180;
	nSyncedMotors = synchNone;
	while (nMotorRunState!= runStateIdle)
	{
		findBoundaries(cal);
	}
	nSyncedMotors = synchCB;
	nSyncedTurnRatio = -100;
	nMotorEncoder[motorC] = 0;
	nMotorEncoderTarget[motorC] = 360;
	nSyncedMotors = synchNone;
	while (nMotorRunState!= runStateIdle)
	{
		findBoundaries(cal);
	}
	nSyncedMotors = synchBC;
	nSyncedTurnRatio = -100;
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 180;
	nSyncedMotors = synchNone;
	while (nMotorRunState!= runStateIdle)
	{
		findBoundaries(cal);
	}
}

task main()
{
	Calibration calb;

	calibrate(calb);
}
