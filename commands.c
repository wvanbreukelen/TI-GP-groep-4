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
  nMotorEncoder[m]=0;
  nMotorEncoderTarget[m]=deg;
  motor[m]=25;

  while(nMotorRunState(m) != runStateIdle){}
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
