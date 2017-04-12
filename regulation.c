#include <regulation.h>

/**
 * Accelerate two motors to a specified target speed. Offset can be set to influence acceleration
 * @param ml Motor left
 * @param mr Motor right
 * @param targetSpeed Target speed
 * @param alcOffset Acceleration offset (default = 1)
 */
void acceleration(short ml, short mr, short targetSpeed, short alcOffset)
{
	short currentMotorSpeed = motor[ml];

	while (currentMotorSpeed < targetSpeed)
	{
		currentMotorSpeed += alcOffset;

		motor[ml] = currentMotorSpeed;
		motor[mr] = currentMotorSpeed;
		wait1Msec(50);
	}
}

/**
 * Decelerate two motors to a desired target speed. Offset can be set to influence deceleration
 * @param ml Motor left
 * @param mr Motor right
 * @param targetSpeed Target speed
 * @param breakOffset Deceleration offset (default = 1)
 */
void deceleration(short ml, short mr, short targetSpeed, short declOffset)
{
	short currentMotorSpeed = (motor[ml] > motor[mr]) ? motor[ml] : motor[mr];
	while (currentMotorSpeed > targetSpeed)
    {
    		currentMotorSpeed -= (currentMotorSpeed >= declOffset) ? declOffset : 1;

        motor[ml] = currentMotorSpeed;
        motor[mr] = currentMotorSpeed;
        wait1Msec(50);
    }

    motor[ml] = targetSpeed;
    motor[mr] = targetSpeed;
}
