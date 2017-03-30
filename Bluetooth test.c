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

#pragma platform(NXT)

long nLastXmitTimeStamp = nPgmTime;
long nDeltaTime         = 0;

const int kMaxSizeOfMessage = 30;
const int INBOX = 5;





////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Receive Messages Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  TFileIOResult nBTCmdRdErrorStatus;
  int nSizeOfMessage;
  ubyte nRcvBuffer[kMaxSizeOfMessage];

  while (true)
  {
    // Check to see if a message is available

    nSizeOfMessage = cCmdMessageGetSize(INBOX);

    if (nSizeOfMessage > kMaxSizeOfMessage)
      nSizeOfMessage = kMaxSizeOfMessage;
    if (nSizeOfMessage > 0){
      nBTCmdRdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, INBOX);
      nRcvBuffer[nSizeOfMessage] = '\0';

      //stringFromChars(s, (char *) nRcvBuffer);
      displayString(2, "%#X", nRcvBuffer);
      if(nRcvBuffer==0x4c){//left
      nMotorEncoder[motorB]=0;
      nMotorEncoderTarget[motorB]=360;
      motor[motorB]=25;
      wait1Msec(1500);

    }else if(nRcvBuffer==0x52){//right
    nMotorEncoder[motorC]=0;
    nMotorEncoderTarget[motorC]=360;
    motor[motorC]=25;
    wait1Msec(1500);
  }
  else if(nRcvBuffer==0x44){//down
  	nMotorEncoder[motorC]=0;

    nMotorEncoderTarget[motorC]=720;

    motor[motorC]=25;

    wait1Msec(1500);
}
else if(nRcvBuffer==0x46){//fire
			nMotorEncoder[motorC]=0;
			nMotorEncoder[motorB]=0;
      nMotorEncoderTarget[motorC]=360;
      nMotorEncoderTarget[motorC]=360;
      motor[motorB]=100;
      motor[motorC]=100;
      wait1Msec(1500);

}


    }
    wait1Msec(100);

  }
  return;
}
