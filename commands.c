
#include <commands.h>

/**
 * Read bluetooth message buffer
 * @param buffer Buffer array pointer
 * @param nMaxBufferSize Maximum size of message
 * @return Size of read message
 */
int readBluetoothData(ubyte* buffer, int nMaxBufferSize)
{
    //  Get size of latest message
    int sizeOfMessage = cCmdMessageGetSize(inboxSize);

    if (sizeOfMessage > nMaxBufferSize)
        //  Message size is above max buffer size, set the new buffer size
        sizeOfMessage = nMaxBufferSize;
    if (sizeOfMessage > 0)
        //  Place the message into out predefined ubyte buffer using a pointer
        cCmdMessageRead(buffer, sizeOfMessage, inboxSize);

    return sizeOfMessage;
}

/**
 * Move the robot 90 degrees counter clockwise
 */
void robotTurnLeft()
{
    moveLeftPID();
}

/**
 * Move the robot 90 degrees clockwise
 */
void robotTurnRight()
{
    moveRightPID();
}

/**
 * Turn the robot around
 */
void robotTurnAround()
{
    nSyncedMotors = synchCB;
    nSyncedTurnRatio = -100;
    robotTurn(motorC, 360);
    nSyncedMotors = synchNone;
}

bool handleInput(ubyte input)
{
	return handleInput(&input);
}

/**
 * Handle a bluetooth message input
 * @param input Hexadecimal message buffer
 * @return Execution successfull
 */
bool handleInput(ubyte* input)
{
    // Play command received bleep
    startTask(soundCrossingTask);

    switch (*input)
    {
        case 0x4C:
            //  Turn left

      if (inMatrixMode)
      {
        // Change our orientation. If it's north, change to west. Else decrement orientation.
        pos->orientation = (pos->orientation == 0) ? 3 : pos->orientation - 1;

        // Check if the robot has the right to move in the desired direction
        if (!canMove(pos)) {
          pos->orientation = (pos->orientation == 3) ? 0 : pos->orientation + 1;
          return false;
        }
      }

      stopAllMotors();
      robotTurnLeft();

      break;
    case 0x52:
      // Turn right

      if (inMatrixMode)
      {
        pos->orientation = (pos->orientation == 3) ? 0 : pos->orientation + 1;

        // Check if the robot has the right to move in the desired direction
        if (!canMove(pos))
        {
          pos->orientation = (pos->orientation == 0) ? 3 : pos->orientation - 1;
          return false;
        }
      }

      stopAllMotors();
      robotTurnRight();

      break;
    case 0x55:
      // Move up

      if (inMatrixMode)
      {
        if (!canMove(pos)) return false;
      }

      // Go forward
      // motor[motorB] = 25;
      // motor[motorC] = 25;

      acceleration(motorB, motorC, 10);

       // Wait until the robot has passed the crossroad
      while (onCrossRoads(SensorValue[BWSensor], SensorValue[CSensor])) {}
     	break;
    case 0x46:
      if (isActive)
  		{
      	stopAllMotors();
			}

			// Toggle
			isActive = !isActive;

      break;
		case 0x44:
      // Turn around
      stopAllMotors();
      robotTurnAround();

      if (inMatrixMode)
      {
        pos->orientation = (pos->orientation == 3) ? 0 : pos->orientation + 1;
        pos->orientation = (pos->orientation == 3) ? 0 : pos->orientation + 1;

        // Check if the robot has the right to move in the desired direction
        if (!canMove(pos)) return false;
      }

      break;
    case 0x41:
      // Reset robot subtasks
      stopAllMotors();
      stopTask(startPID);
      stopTask(avoidObjectsTask);
      stopTask(handleCrossroads);

      initPID(calibrate(), true);

      initPosition(pos, MATRIX_SIZE_X, MATRIX_SIZE_Y);

      if (DETECT_CROSSROADS) startTask(avoidObjectsTask);
      startTask(startPID);
      if (AVOID_OBJECTS) startTask(handleCrossroads);

      break;

    case 0x42:
           //  Matrix modus
            inMatrixMode = true;
            break;

        case 0x43:
            //  Basic/line following modus
            inMatrixMode = false;
            break;

        default:
            //  If none of the above cases matches with the command, return false
            return false;
    }

    //  Display the current position of the robot
    displayPosition(pos);

    return true;
}

/**
 * Handles off incoming bluetooth commands
 */
task commandHandlerTask()
{
    init_queue(&q);

    ubyte nRcvBuffer[kMaxSizeOfMessage];

    while (true)
    {
        if (readBluetoothData(nRcvBuffer, kMaxSizeOfMessage) > 0)
        {
        		if (nRcvBuffer == 0x4C || nRcvBuffer == 0x52 || nRcvBuffer == 0x55 || nRcvBuffer == 0x44)
        		{
        			// Add to queue
            	enqueue(&q, (ubyte) nRcvBuffer);
        		} else {
        			if (handleInput(nRcvBuffer))
            	{
                if (isActive)
                {
                	startTask(startPID);
                	startTask(handleCrossroads);
                	if (DETECT_CROSSROADS) startTask(avoidObjectsTask);
                }
            	} else {
                // Something went wrong, sound an error
                startTask(soundErrorTask);
            	}
        		}
        }

        wait1Msec(200);
    }
}

/**
 * Detects and handlers crossroads
 */
task handleCrossroads()
{
	while (1)
	{
		//If we set the PID system to stop at crossroads, check for crossroads and break on detection.
		if (stopForCrossRoads && onCrossRoads(BWValue, CValue))
		{
			stopTask(startPID);

			//
			//show(q);


			if (q.count == 0)
			{
				// Stop drive motors
				motor[motorB] = 0;
				motor[motorC] = 0;
			} else {
				ubyte data = dequeue(&q);

				handleInput(data);
				startTask(startPID);
			}


			//deceleration(motorB, motorC, 0, 4);
		}

		wait1Msec(50);
	}
}
