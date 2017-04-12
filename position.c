#include <position.h>

/**
 * Initialise position struct holder
 *
 * @param pos Position struct, contains our current position and orientation.
 * @param maxX Maximal horizontal value. Increments when going east.
 * @param maxY Maximal vertical value. Increments when going north.
 * @param orientation Robot orientation. 0 is North, 1 is East, 2 is South, 3 is West.
 */
void initPosition(Position* pos, short maxX, short maxY, char orientation)
{
	pos->x = 0;
	pos->y = 0;
	pos->orientation = orientation;
	pos->maxX = maxX;
	pos->maxY = maxY;
}
/**
 * Calculate whether or not we can move and adjusts position struct accordingly, AHEAD OF TIME!
 * @param pos Position struct
 * @return Returns boolean on whether or not the robot is allowed to move.
 */
bool canMove(Position* pos)
{
	if (SensorValue[sonar] < 25) return false;

	switch (pos->orientation)
	{
		case 0: // Moving north, increment y
			if (pos->maxY >= pos->y + 1) // If we are within boundaries,
			{
				pos->y++; // edit our position in the struct to represent the next node our robot will drive to.
				return true;
			}
			return false;
		case 1: // Moving east, increment x
			if (pos->maxX >= pos->x + 1)
			{
				pos->x++;
				return true;
			}
			return false;
		case 2: // Moving south, decrement y
			if (pos->y - 1 >= 0)
			{
				pos->y--;
				return true;
			}
			return false;
		case 3: // Moving west, decrement x

			if (pos->x - 1 >= 0)
			{

				pos->x--;
				return true;
			}

			startTask(soundErrorTask);
			return false;

		default:
			return false;
	}
}

void robotTurn(short m, short deg)
{
    nMotorEncoder[m] = 0;
    nMotorEncoderTarget[m] = deg;
    int power = 25;

    if (deg < 0)
    {
        power *= -1;
    }

    motor[m] = power;
    while(nMotorRunState(m) != runStateIdle){}
}

/**
 * Display current position on NXT display
 * @param pos Position struct
 */
void displayPosition(Position* pos)
{
	clearDisplay();

	displayString(1, "x: %d", pos->x);
	displayString(2, "y: %d", pos->y);
	displayString(3, "Orientation: %d", pos->orientation);
}
