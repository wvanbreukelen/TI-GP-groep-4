#pragma platform(NXT)

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

task cmdDriveStop()
{
	ubyte nRcvBuffer[kMaxSizeOfMessage];

	while (true)
	{
		if (readBluetoothData(nRcvBuffer, kMaxSizeOfMessage) > 0)
		{
			if (nRcvBuffer == 0x46){
				if (nMotorRunState[motorB] == runStateIdle)
				{
					motor[motorB] = 25;
					motor[motorC] = 25;
				} else {
					motor[motorB] = 0;
					motor[motorC] = 0;
				}
			}
		}
	}
}
