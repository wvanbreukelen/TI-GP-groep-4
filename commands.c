/**
 * Maximum size of single bluetooth message
 */
const int kMaxSizeOfMessage = 30;

/**
 * Maximum size of message inbox
 */
const int inboxSize = 5;

/**
 * Read bluetooth message buffer
 * @param buffer Buffer array pointer
 * @param nMaxBufferSize Maximum size of message
 * @return Size of read message
 */
int readBluetoothData(ubyte* buffer, int nMaxBufferSize)
{
  int sizeOfMessage = cCmdMessageGetSize(inboxSize);

  if (sizeOfMessage > nMaxBufferSize)
    sizeOfMessage = nMaxBufferSize;
  if (sizeOfMessage > 0)
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
            // Turn left

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
            motor[motorB] = 25;
            motor[motorC] = 25;

             // Wait until the robot has passed the crossroad
            while (onCrossRoads(SensorValue[BWSensor], SensorValue[CSensor])) {}

            break;
        case 0x46:
            // Fire, stop the robot
            stopAllTasks();
            stopAllMotors();

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
            // Matrix modus
            inMatrixMode = true;
            break;

        case 0x43:
            // Basic/line following modus
            inMatrixMode = false;
            break;

        default:
            // If none of the above cases matches with the command, return false
            return false;
    }

    // Display the current position of the robot
    displayPosition(pos);

    return true;
}

/**
 * Handles off incoming bluetooth commands
 */
task commandHandlerTask()
{
    ubyte nRcvBuffer[kMaxSizeOfMessage];

    while (true)
    {
        if (readBluetoothData(nRcvBuffer, kMaxSizeOfMessage) > 0)
        {
            // Message received, stop tasks that influence the motors
            stopTask(handleCrossroads);
            stopTask(startPID);
            stopTask(avoidObjectsTask);

            // Handle the bluetooth command
            if (handleInput(nRcvBuffer))
            {
                startTask(startPID);
                startTask(handleCrossroads);
                if (DETECT_CROSSROADS) startTask(avoidObjectsTask);
            } else {
                // Something went wrong, sound an error
                startTask(soundErrorTask);
            }
        }

        wait1Msec(200);
    }
}
