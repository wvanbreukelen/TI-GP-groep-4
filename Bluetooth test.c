////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    Bluetooth Sample Program
//
// ROBOTC provides easy send and receive of messages over Bluetooth. This sample program illustrate the
// basic concept. Bluetooth error checking has been removed from the program to make it easier to
// follow the program logic.
//
// There are other sample programs in the ROBOTC distribution that include Bluetooth using error
// checking.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Check to see if a message is available

    /**nSizeOfMessage = cCmdMessageGetSize(INBOX);

    if (nSizeOfMessage > kMaxSizeOfMessage)
      nSizeOfMessage = kMaxSizeOfMessage;
    if (nSizeOfMessage > 0){
      nBTCmdRdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, INBOX);
      stringFromChars(s, (char *) nRcvBuffer);
      long nLastXmitTimeStamp = nPgmTime;
			long nDeltaTime         = 0;

     **/
#pragma platform(NXT)


const int kMaxSizeOfMessage = 30;
const int INBOX = 5;
/**
	buffer = an ubyte array
	nMaxBufferSize = maximum size of the message

	return the hexadecimal code of the message
**/

int readBluetoothData(ubyte* buffer, int nMaxBufferSize)
{
	int sizeOfMessage = cCmdMessageGetSize(INBOX);


    if (sizeOfMessage > nMaxBufferSize)
      sizeOfMessage = nMaxBufferSize;
    if (sizeOfMessage > 0)
      cCmdMessageRead(buffer, sizeOfMessage, INBOX);

     return sizeOfMessage;

}
/**
	m = The motor that it needs to turn

	return void
**/
void robotTurn(short m,short deg){
	nMotorEncoder[m]=0;
  nMotorEncoderTarget[m]=deg;
  motor[m]=25;

  while(nMotorRunState(m) != runStateIdle){}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Receive Messages Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
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
}
