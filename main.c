#pragma config(Sensor, S1,     CSensor,        sensorColorNxtRED)
#pragma config(Sensor, S2,     sonar,          sensorSONAR)
#pragma config(Sensor, S4,     BWSensor,       sensorLightActive)
#pragma config(Motor,  motorA,          headMotor,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          MotorLeft,     tmotorNXT, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          MotorRight,    tmotorNXT, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define BASE_SPEED 25
#define DETECT_CROSSROADS 1
#define AVOID_OBJECTS 1
#define PLAY_ENV_SOUNDS 0
#define MATRIX_SIZE_X 4
#define MATRIX_SIZE_Y 4

bool inMatrixMode = false;

#include <queue.c>

Queue q;

#include <display.c>
#include <soundEngine.c>
#include <calibration.c>
#include <regulation.c>
#include <PID.c>

#include <position.c>

Position* pos;

#include <HeadSensor.c>
#include <commands.c>


void startTasks()
{
	if (AVOID_OBJECTS) startTask(avoidObjectsTask);
	startTask(startPID);
	if (DETECT_CROSSROADS) startTask(handleCrossroads);
	// Play sound continuesly with a low CPU priority
	if (PLAY_ENV_SOUNDS) startTask(constantPlay);
}

task main()
{
	startTask(commandHandlerTask);
	initPID(calibrate(), true);
	initPosition(pos, MATRIX_SIZE_X, MATRIX_SIZE_Y);

	startTasks();

	// Wait forever
	while (1)
	{
		wait1Msec(200);
	}
}
