#include <display.c>

typedef struct {
	short x, y;
	char orientation;
	short maxX, maxY;
} Position;

// 375; degrees for 90 degrees robotturn

/**
* Initialise struct
*/
void initPosition(Position pos, short maxX = 4, short maxY = 4, char orientation = 'N')
{
	pos.x = 0;
	pos.y = 0;
	pos.orientation = orientation;
	pos.maxX = maxX;
	pos.maxY = maxY;
}

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

void displayPosition(Position pos)
{
	clearDisplay();

	displayString(1, "x: %d", pos.x);
	displayString(2, "y: %d", pos.y);
	displayString(3, "Orientation: %c", pos.orientation);
}

task main() {
	Position pos;
	initPosition(pos);

	displayPosition(pos);

	wait1Msec(2000);

	moveRight(pos, motorB);
	moveDown(pos, motorB, motorC);

	displayPosition(pos);

	wait1Msec(2000);
}
