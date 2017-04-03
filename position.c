typedef struct {
	short x, y;
	char orientation;
	short maxX, maxY;
} Position;

// 375; degrees for 90 degrees robotturn

/**
 * Initialise position struct holder
 *
 * @param pos Position struct
 * @param maxX Maximal horizontal value
 * @param maxY Maximal vertical value
 * @param orientation Robot orientation
 */
void initPosition(Position pos, short maxX = 4, short maxY = 4, char orientation = 'N')
{
	pos.x = 0;
	pos.y = 0;
	pos.orientation = orientation;
	pos.maxX = maxX;
	pos.maxY = maxY;
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
	nMotorEncoderTarget[motorLeft] = 375;

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
	nMotorEncoderTarget[motorRight] = 375;

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
	// Check
	if (pos.y == pos.maxY)
		return false;

  // Start PID task


	// Set new position in struct
	pos.y++;

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
	if (pos.y == 0)
		return false;

	// Start PID task

	// Set new position in struct
	pos.y--;

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
