//
// Created by wiebe on 12-4-2017.
//

#ifndef PID_H
#define PID_H

//Initialise global variables
short BWBlack = 35;
short BWWhite = 60;
short BWOffset = -1;
float BWMax;

// Default calibration values
short CBlack = 22;
short CWhite = 63;
short COffset = -1;
float CMax;

short BWValue, CValue;

bool stopForCrossRoads = true;

void initPID(Calibration* cal, bool fullPID = true);
short errorAmountPID (short BWError, short CError);
bool onCrossRoads(short BW, short C);
void moveLeftPID();
void moveRightPID();
task startPID();
task handleCrossroads();
#endif //PID_H
