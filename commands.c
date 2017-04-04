const int kMaxSizeOfMessage = 30;
const int INBOX = 5;

int readBluetoothData(ubyte* buffer, int nMaxBufferSize)
{
  int sizeOfMessage = cCmdMessageGetSize(INBOX);

  if (sizeOfMessage > nMaxBufferSize)
    sizeOfMessage = nMaxBufferSize;
  if (sizeOfMessage > 0)
    cCmdMessageRead(buffer, sizeOfMessage, INBOX);

  return sizeOfMessage;
}

void robotTurn(short deg, bool inverted = false){
  nSyncedMotors = (inverted) ? synchBC : synchCB;
  nSyncedTurnRatio = -100;

  if (inverted)
  {
  	nMotorEncoder[motorB] = 0;
  	nMotorEncoderTarget[motorB] = deg;
  	motor[motorB] = 25;

  	while (nMotorRunState(motorB) != runStateIdle) {}
  } else {
  	nMotorEncoder[motorC] = 0;
  	nMotorEncoderTarget[motorC] = deg;
  	motor[motorC] = 25;

  	while (nMotorRunState(motorC) != runStateIdle) {}
	}


}

void robotTurnLeft()
{
	robotTurn(180);
}

void robotTurnRight()
{
	robotTurn(180, true);
}

ubyte* waitForInput()
{
	ubyte nRcvBuffer[kMaxSizeOfMessage];

	while (true)
	{
		if (readBluetoothData(nRcvBuffer, kMaxSizeOfMessage) > 0)
		{
			return nRcvBuffer;
		}

		wait1Msec(200);
	}
}

bool handleInput(ubyte* input)
{
	switch (*input)
	{
		case 0x4C:
			// Turn left
			stopTask(startPID);
			stopAllMotors();
			robotTurnLeft();

			break;
		case 0x52:
			// Turn right
			stopTask(startPID);
			robotTurnRight();

			break;
		case 0x46:
			stopAllTasks();
			stopAllMotors();

			break;
		default:
			return false;
			//startTask(soundErrorTask);
	}

	return true;
}

task commandHandlerTask()
{
	ubyte* input = waitForInput();

	if (!handleInput(input))
	{
		// Command not found
		startTask(soundErrorTask);
	}

}

task handleStopCmd()
{
	ubyte nRcvBuffer[kMaxSizeOfMessage];

	while (true)
	{
		if (readBluetoothData(nRcvBuffer, kMaxSizeOfMessage) > 0)
		{
			if (nRcvBuffer == 0x46)
			{
				stopAllTasks();
			}
		}
	}
}

// Some sample code, remove it later @wiebe

/**task main()
{
  ubyte nRcvBuffer[kMaxSizeOfMessage];

  while (true)
  {

    if (readBluetoothData(nRcvBuffer, kMaxSizeOfMessage) > 0)
    {

    	if(nRcvBuffer==0x4c){						//Turn left
    		robotTurn(motorB,355);
    	}
    	else if(nRcvBuffer==0x52){			//Turn right
    		robotTurn(motorC,355);
 			}
  		else if(nRcvBuffer==0x44){			//Turn around
  			nSyncedMotors=synchCB;
    		nSyncedTurnRatio=-100;
  			robotTurn(motorC,355);
  			nSyncedMotors =synchNone;

    	}
  	wait1Msec(100);
		}
	}
  return;
}**/
