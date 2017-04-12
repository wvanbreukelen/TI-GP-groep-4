#include <display.h>

/**
 * Clear the entire NXT display
 */
void clearDisplay()
{
	for (int i = 0; i < 8; i++)
	{
		displayClearTextLine(i);
	}

	wait1Msec(100);
}
