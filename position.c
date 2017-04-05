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
	}
}
/**
 * Move robot to the left
 * @param pos Position struct
 * @param motorLeft Left motor
 * @return Returns false when failed
 */
bool moveLeft(Position pos, short motorLeft)
{
	// Check
	if (pos.x == 0)
		return false;

	// Do motor stuff
	nMotorEncoder[motorLeft] = 0;
	nMotorEncoderTarget[motorLeft] = 375;
	motor[motorLeft] = CURVE_ROTATION_SPEED;

	// Set new position in struct
	pos.x--;

	while (nMotorRunState(motorLeft) != runStateIdle) {}

	return true;
}

/**
 * Move robot to the right
 * @param pos Position struct
 * @param motorLeft Right motor
 * @return Returns false when failed
 */
bool moveRight(Position pos, short motorRight)
{
	// Check
	if (pos.x == pos.maxX)
		return false;

  // Do motor stuff
	nMotorEncoder[motorRight] = 0;
	nMotorEncoderTarget[motorRight] = 375;
	motor[motorRight] = CURVE_ROTATION_SPEED;

	// Set new position in struct
	pos.x++;

	while (nMotorRunState(motorRight) != runStateIdle) {}

	return true;
}

/**
 * Move robot above
 * @param pos Position struct
 * @param motorLeft Left motor
 * @param motorRight Right motor
 * @return Returns false when failed
 */
bool moveUp(Position pos, short motorLeft, short motorRight)
{
	// Check whether or not we can move up
	if (!canMove(pos, true))
		return false;

  // Start PID task
	startTask(startPID);

	return true;
}

/**
 * Move robot down
 * @param pos Position struct
 * @param motorLeft Left motor
 * @param motorRight Right motor
 * @return Returns false when failed
 */
bool moveDown(Position pos, short motorLeft, short motorRight)
{
	// Make sure we are not out of matrix
	if (!canMove(pos, false))
		return false;

	// Start PID task
	startTask(startPID);

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
