/**
* @file display.c
* @author Wiebe van Breukelen
* @date 30-03-2017
* @brief This file contains helper functions used to control the NXT brick's display
*/

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
