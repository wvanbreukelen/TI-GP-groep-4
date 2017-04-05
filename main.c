#pragma config(Sensor, S1,     CSensor,        sensorColorNxtRED)
#pragma config(Sensor, S2,     sonar,          sensorSONAR)
#pragma config(Sensor, S4,     BWSensor,       sensorLightActive)
#pragma config(Motor,  motorA,          headMotor,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          MotorLeft,     tmotorNXT, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          MotorRight,    tmotorNXT, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define CURVE_ROTATION_SPEED 25

#include <display.c>
#include <soundEngine.c>
#include <PID.c>
#include <position.c>
#include <calibration.c>
#include <regulation.c>
#include <HeadSensor.c>

task main()
{
	initPID(calibrate(), true);

	//startTask(avoidObjectsTask);
	startTask(startPID);

	wait10Msec(20000);
}
