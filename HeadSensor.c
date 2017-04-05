bool isWall(short minDistCm = 25)
{
	if (SensorValue [sonar] > minDistCm)
	{
		return false;
	} else {
		deceleration(motorB, motorC, 25);
		return true;
	}
}

void robotTurn(short m, short deg){///Must be deleted
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

void goOn(int whereTo, short minDistCm)
{
	short speed = 0;
	bool sensorPart2 = false;
	bool sensor = true;

	while (sensor)
	{
		if (SensorValue [sonar] < minDistCm)
		{
			acceleration(motorB, motorC, 25);
		} else {
			deceleration(motorB, motorC, 0);
			robotTurn(motorC,360);
			acceleration(motorB, motorC, 25);

			wait1Msec(1000);

			sensorPart2 = true;
			sensor = false;

			while (sensorPart2)
			{
				if (SensorValue [sonar] < minDistCm){
					acceleration(motorB, motorC, 25);
				} else {
					deceleration(motorB, motorC, 0);
					robotTurn(motorC,360);
					robotTurn(motorA, whereTo * -1);
					sensorPart2 = false;
				}
			}
		}
	}
}

void avoid(int whereTo, short minDistCm = 25)
{
	if (whereTo < 0)
	{
		nSyncedMotors = synchCB;
		nSyncedTurnRatio = -100;
		robotTurn(motorC, -180);
	}

	if (whereTo > 0){
		nSyncedMotors = synchBC;
		nSyncedTurnRatio = -100;
		robotTurn(motorB, 180);
	}

	robotTurn(motorA, whereTo);
	nSyncedMotors = synchNone;
	goOn(whereTo, minDistCm);
}

task avoidObjectsTask()
{
	while (1)
	{
		if (isWall())
		{
			startTask(soundErrorTask);
			stopTask(startPID);
			stopAllMotors();
			avoid(-90, 15);
			startTask(startPID);
		}
	}
}



/**task main(){
  int way = -90;
  while(1){
  	Acceleration(motorB, motorC, 0);
  	while (!isWall()){}
  	avoid(way);
	}
}**/
