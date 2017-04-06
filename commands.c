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

void robotTurn(short m, short deg){
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

/**void robotTurn(short deg, bool inverted = false){
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


}**/

void robotTurnLeft()
{
	robotTurn(motorB, 370);
}

void robotTurnRight()
{
	robotTurn(motorC, 370);
}

void robotTurnAround()
{
	nSyncedMotors = synchCB;
	nSyncedTurnRatio = -100;
	robotTurn(motorC, 360);
	nSyncedMotors = synchNone;
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
	startTask(soundCrossingTask);

	clearDisplay();
	displayTextLine(4, "%#X", *input);

	switch (*input)
	{
		case 0x4C:
			// Turn left
			stopAllMotors();
			robotTurnLeft();

			break;
		case 0x52:
			// Turn right
			stopAllMotors();
			robotTurnRight();

			break;
		case 0x55:
			// Go forward
			motor[motorB] = 25;
			motor[motorC] = 25;

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
			break;
		default:
			return false;
	}

	return true;
}

task commandHandlerTask()
{
	//ubyte* input = waitForInput();

	ubyte nRcvBuffer[kMaxSizeOfMessage];

	while (true)
	{
		if (readBluetoothData(nRcvBuffer, kMaxSizeOfMessage) > 0)
		{
			stopTask(handleCrossroads);
			stopTask(startPID);

			if (!handleInput(nRcvBuffer)) startTask(soundErrorTask);

			startTask(startPID);
			startTask(handleCrossroads);
		}

		wait1Msec(200);
	}

		// Stop PID and crossroad tasks
		//stopTask(startPID);
	//stopTask(handleCrossroads);

	//startTask(soundCrossingTask);

	//if (!handleInput(input))
	//{
		// Cannot handle this kind of input, play an error tune
		//startTask(soundErrorTask);
	//}

		// Re-enable PID and crossroad tasks
	//startTask(startPID);
	//startTask(handleCrossroads);

}

/**void handleUserDecision(ubyte* buffer)
{
	switch (*buffer)
	{
		case 0x46:
			// Fire
			stopAllTasks();
			break;
		case 0x4C:
			// Left
			break;
		case 0x52:
			// Right
			break;
		case 0x44:
			// Down
			break;
		default:
			return;
	}
}**/

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
