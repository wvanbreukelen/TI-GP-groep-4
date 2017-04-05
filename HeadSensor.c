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

void evade(int whereTo)
{
	// Minimal ultrasonic distance for detecting a object
	int minDistCm = 25;

	// While status booleans
	bool sensorPart2 = false;
	bool sensor = true;

	// Front and back of object
	while (sensor)
	{
		if (SensorValue [sonar] < minDistCm)
		{
			acceleration(motorB, motorC, 20);
		} else {
			// Object detected, wait for 500 milliseconds to compensate with 90 degrees turn (overshoot)
			wait1Msec(500);
			deceleration(motorB, motorC, 0);
			// Turn robot
			robotTurn(motorC,360);

			acceleration(motorB, motorC, 20);

			// Keep the motors running at 20% speed until object is seen again
			while (SensorValue[sonar] > minDistCm) {wait1Msec(20);}

			// Little beep to notice user of object
			startTask(soundErrorTask);

			// Some delay to minimize variating readings in the next while loop
			wait1Msec(500);

			// Set while loops status booleans
			sensorPart2 = true;
			sensor = false;

			// Side of object
			while (sensorPart2)
			{
				// When sensor value is bigger than minimal object distance, rotate the robot 90 degress and turn on the motors.
				if (SensorValue [sonar] > minDistCm)
				{
					// Object detected, wait for 500 milliseconds to compensate with 90 degrees turn (overshoot)
					wait1Msec(500);

					deceleration(motorB, motorC, 0);
					robotTurn(motorC, 360);

					// Ultrasone viewing angle to original position (face to front)
					robotTurn(motorA, whereTo * -1);

					// Stop myself (loop)
					sensorPart2 = false;
				}
			}
		}
	}
}

void avoid(int whereTo)
{
	// Turn robot 90 degrees counterclockwise
	nSyncedMotors = synchCB;
	nSyncedTurnRatio = -100;
	robotTurn(motorC, -180);

	// Turn the ultrasonic sensor clockwise
	robotTurn(motorA, whereTo);
	nSyncedMotors = synchNone;

	// Evade object
	evade(whereTo);
}

task avoidObjectsTask()
{
	while (1)
	{
		if (isWall(15))
		{
			// Object is detected, make a sound
			startTask(soundErrorTask);

			// Stop PID task and motors from running
			stopTask(startPID);
			stopAllMotors();

			// Avoid the object
			avoid(-90);

			// Start motors to look for our original line
			acceleration(motorB, motorC, 15);
			while (!onCrossRoads(SensorValue[BWSensor], SensorValue[CSensor])) {}

			// Line detected! Stop the motors!
			deceleration(motorB, motorC, 0);

			// Rotate 90 degrees to get in front of the line
			nSyncedMotors = synchBC;
			nSyncedTurnRatio = -100;
			robotTurn(motorB, 180);

			nSyncedMotors = synchNone;

			// Start the PID task again
			startTask(startPID);
		}
	}
}



/**task main(){
  int way = -90;
  while(1){
  	Acceleration(motorB, motorC, 0);
  	while (!isWall()){}
  	avoid(way, 10);
	}
}**/
