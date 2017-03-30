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
      string s = "";
      stringFromChars(s, (char *) nRcvBuffer);
      if(s=="LEFT"){
      motor[motorB]=25;
      motor[motorC]=-25;
      wait1Msec(730);
      motor[motorB]=0;
      motor[motorC]=0;

    }else if(s=="RIGHT"){
    motor[motorB]=-25;
    motor[motorC]=25;
    wait1Msec(730);
    motor[motorB]=0;
    motor[motorC]=0;
  }
  else if(s=="DOWN"){
      motor[motorB]=25;
      motor[motorC]=-25;
  wait1Msec(1460);
      motor[motorB]=0;
      motor[motorC]=0;
}
else if(s=="FIRE"){

      motor[motorB]=100;
      motor[motorC]=100;
      wait1Msec(1000);
      motor[motorB]=0;
      motor[motorC]=0;
}
      displayCenteredBigTextLine(4, s);

    }
    wait1Msec(100);

  }
  return;
}
