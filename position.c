#include <regulation.c>

typedef struct {
	short x, y;
	short orientation; //0 is North, 1 is East, 2 is South, 3 is West.
	short maxX, maxY;
} Position;

/**
 * Initialise position struct holder
 *
 * @param pos Position struct, contains our current position and orientation.
 * @param maxX Maximal horizontal value. Increments when going east.
 * @param maxY Maximal vertical value. Increments when going north.
 * @param orientation Robot orientation. 0 is North, 1 is East, 2 is South, 3 is West.
 */
void initPosition(Position pos, short maxX = 4, short maxY = 4, char orientation = 0)
{
	pos.x = 0;
	pos.y = 0;
	pos.orientation = orientation;
	pos.maxX = maxX;
	pos.maxY = maxY;
}
/**
 * Calculate whether or not we can move and adjusts position struct accordingly, AHEAD OF TIME!
 * @param pos Position struct
 * @param forward Boolean indicating if we are to move up or down.
 * @return Returns boolean on whether or not the robot is allowed to move.
 */
bool canMove(Position pos, bool forward)
{
	short incrementer = -1;
	if (forward) incrementer = 1;
	switch (pos.orientation)
	{
		case 0: //Moving north, increment y
			if (pos.maxY <= pos.y + incrementer) //If we are within boundaries,
			{
				pos.y++; //edit our position in the struct to represent the next node our robot will drive to.
				return true;
			}
			return false;
		case 1: //Moving east, increment x
			if (pos.maxX <= pos.x + incrementer)
			{
				pos.x++;
				return true;
			}
			return false;
		case 2: //Moving south, decrement y
			if (pos.y - incrementer >= 0)
			{
				pos.y--;
				return true;
			}
			return false;
		case 3: //Moving west, decrement x
			if (pos.x - incrementer >= 0)
			{
				pos.x--;
				return true;
			}
			return false;

		default:
			return false;
	}
}
/**
 * Move robot 90 degrees to the left
 * @param pos Position struct
 */
void moveLeft(Position pos)
{
	// Do motor stuff
	nMotorEncoder[motorC] = 0;
	nSyncedMotors = synchCB;
	nSyncedTurnRatio = -100;
	nMotorEncoderTarget[motorC] = 188;
	motor[motorC] = CURVE_ROTATION_SPEED;
	while (nMotorRunState(motorC) != runStateIdle) {}
	nSyncedMotors = synchNone;
	//Change our orientation. If it's north, change to west. Else decrement orientation.
	pos.orientation = (pos.orientation == 0) ? 3 : pos.orientation - 1;
}

/**
 * Move robot 90 degrees to the right
 * @param pos Position struct
 */
void moveRight(Position pos)
{

  nMotorEncoder[motorB] = 0;
	nSyncedMotors = synchBC;
	nSyncedTurnRatio = -100;
	nMotorEncoderTarget[motorB] = 188;
	motor[motorB] = CURVE_ROTATION_SPEED;

	while (nMotorRunState(motorB) != runStateIdle) {}
	nSyncedMotors = synchNone;
	pos.orientation = (pos.orientation == 3) ? 0 : pos.orientation + 1;
}

/**
 * Move robot forwards
 * @param pos Position struct
 * @param motorLeft Left motor
 * @param motorRight Right motor
 * @return Returns false when failed
 */
bool moveUp(Position pos)
{
	// Check whether or not we can move up
	if (!canMove(pos, true))
		return false;

  // Start PID task
	//startTask(startPID);
	//After crossroads detection, make motor speeds the same and decelerate.
	motor[motorB] = motor[motorC];
	deceleration(motorB, motorC, 0);
	return true;
}

/**
 * Move robot down
 * @param pos Position struct
 * @param motorLeft Left motor
 * @param motorRight Right motor
 * @return Returns false when failed
 */
bool moveDown(Position pos)
{
	// Make sure we are not out of matrix
	if (!canMove(pos, false))
		return false;
	//Turn 180 degrees
	moveLeft(pos);
	moveLeft(pos);

	// Start PID task
	//startTask(startPID);
	//After crossroads detection, make motor speeds the same and decelerate.
	motor[motorB] = motor[motorC];
	deceleration(motorB, motorC, 0);
	return true;
}

// @tony @nino @dylan Is this really needed
bool isOutOfMatrix(Position pos)
{
	return (pos.x > pos.maxX || pos.y > pos.maxY || pos.x < 0 || pos.y < 0);
}

/**
 * Display current position on NXT display
 * @param pos Position struct
 */
void displayPosition(Position pos)
{
	clearDisplay();

	displayString(1, "x: %d", pos.x);
	displayString(2, "y: %d", pos.y);
	displayString(3, "Orientation: %c", pos.orientation);
}
/**
 * Turn on right motor until right sensor detects the line
 */
void moveLeftPID(short avgValue)
{
	//Turn on right motor
	motor[motorC] = 0;
	motor[motorB] = 25;

	wait1Msec(200);

	while (sensorValue[CSensor] > avgValue);
	motor[motorB] = 0;
}

void moveRightPID(short avgValue)
{
	//Turn on right motor
	motor[motorC] = 25;
	motor[motorB] = 0;

	wait1Msec(200);

	while (sensorValue[BWSensor] > avgValue);
	motor[motorC] = 0;
}
