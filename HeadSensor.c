
#pragma config(Sensor, S2,     sonar,          sensorSONAR)
#pragma config(Motor,  motorA,          headMotor,     tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool isWall()
{
	int distanceInCm = 25;
	if (SensorValue [sonar] > distanceInCm)
	{
		return false;
	} else {
		Deceleration(motorB, motorC, 25);
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

void goOn(int whereTo)
{
	int distanceInCm = 30;
	short speed = 0;
	bool sensorPart2 = false;
	bool sensor = true;

	while (sensor)
	{
		if (SensorValue [sonar] < distanceInCm)
		{
			speed = Acceleration(motorB, motorC, speed);
		} else {
			speed = Deceleration(motorB, motorC, speed);
			robotTurn(motorC,360);
			speed = Acceleration(motorB, motorC, speed);

			wait1Msec(1000);

			sensorPart2 = true;
			sensor = false;

			while (sensorPart2)
			{
				if (SensorValue [sonar] < distanceInCm){
					speed = Acceleration(motorB, motorC, speed);
				} else {
					speed = Deceleration(motorB, motorC, speed);
					robotTurn(motorC,360);
					robotTurn(motorA, whereTo * -1);
					sensorPart2 = false;
				}
			}
		}
	}
}

void avoid(int whereTo)
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
	goOn(whereTo);
}


/**task main(){
  int way = -90;
  while(1){
  	Acceleration(motorB, motorC, 0);
  	while (!isWall()){}
  	avoid(way);
	}
}**/
