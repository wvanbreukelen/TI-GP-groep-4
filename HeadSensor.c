#include <HeadSensor.h>
#define C_WHEEL 17.593
#define SONAR_DETECT 25

/**
 * Check if a wall is detected
 * @param minDistCm Minimal distance to trigger wall
 * @return Result
 */
bool isWall(short minDistCm)
{
	if (SensorValue [sonar] > minDistCm)
	{
		return false;
	} else {
		deceleration(motorB, motorC, BASE_SPEED);
		return true;
	}
}

/**
 * Evade an object by calculating its radius and following a
 */
void evade()
{
	// Read sensor value
	short startValue = SensorValue[sonar];

	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
	// Turn on motors,
	motor[motorB] = BASE_SPEED;
	motor[motorC] = BASE_SPEED;
	// Until our sensor value is bigger than our start value (implying we passed the object).
	while (SensorValue[sonar] <= startValue + 5) {}
	// Calculate distance travelled since beginning of this function by looking at motor degrees
	short distDegrees = nMotorEncoder[motorB];
	float dist =  (distDegrees / 360.0) * C_WHEEL;
	// If the distance is bigger than 0, we have to correct our angle of entry and adjust accordingly.
	if (dist > 0)
	{
		// The following formula uses SOSCASTOA and pythagoras to calculate the angle we have to turn right in order to keep on track.
		float correctionAngle = radiansToDegrees(atan((dist * dist + (startValue + dist) * (startValue + dist) - (startValue + dist)) / dist));
		// Turn robot ^ degrees
		nSyncedMotors = synchCB;
		nSyncedTurnRatio = -100;
		robotTurn(motorC, correctionAngle);
	}
	// Distance from object to left/right tire
	short rLeft = startValue + 9 + dist;
	short rRight = startValue - 4 + dist;
	// Amount of turns our wheels have to do
	float dLeft = PI * rLeft / C_WHEEL;
	float dRight = PI * rRight / C_WHEEL;
	// Degrees our wheels have to turn
	short turnLeft = dLeft * 360;
	short turnRight = dRight * 360;
	//  Finally, start motors with above values
	nSyncedMotors = synchNone;
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
	nMotorEncoderTarget[motorB] = turnRight;
	nMotorEncoderTarget[motorC] = turnLeft;
	//  Calculate difference in power required on both tires
	float diffMotor = (float) rLeft/rRight;
	//  Adjust speeds of motors accordingly
	motor[motorB] = BASE_SPEED;
	motor[motorC] = BASE_SPEED * diffMotor;

	//  Drive with above speeds until we find a line
	while (SensorValue[BWSensor] > BWOffset && SensorValue[CSensor] > COffset) {}
	//  Turn off motors
	motor[motorB] = 0;
	motor[motorC] = 0;
}
/**
 * Avoid a object
 * @param whereTo Amount of degress needed to turn the ultrasonic sensor
 */
void avoid(int whereTo)
{
	//  Turn robot 90 degrees counterclockwise
	nSyncedMotors = synchCB;
	nSyncedTurnRatio = -100;
	robotTurn(motorC, -180);

	//  Turn the ultrasonic sensor clockwise
	robotTurn(motorA, whereTo);
	nSyncedMotors = synchNone;

	//  Evade object
	evade();
	//  Turn the head back
	robotTurn(motorA, -whereTo);
}

/**
 * This task avoids objects
 */
task avoidObjectsTask()
{
	while (1)
	{
		if (isWall(SONAR_DETECT - 5))
		{
			//  Object is detected, make a sound
			startTask(soundErrorTask);

			//  Stop PID task and motors from running
			stopTask(startPID);
			hogCPU();
			stopAllMotors();
			// If we are in the matrix, turn around 180 degrees.
			if (inMatrixMode)
			{
				robotTurnAround();
				pos->orientation = (pos->orientation == 3) ? 0 : pos->orientation + 1;
        pos->orientation = (pos->orientation == 3) ? 0 : pos->orientation + 1;
        canMove(pos);
			} else {
			// Else, go for evasive maneuvres.
				avoid(-90);
			}

			//  Start the PID task again
			startTask(startPID);
			releaseCPU();
		}
	}
}
