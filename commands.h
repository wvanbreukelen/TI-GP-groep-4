//
// Created by wiebe on 12-4-2017.
//

#ifndef COMMANDS_H
#define COMMANDS_H

int readBluetoothData(ubyte* buffer, int nMaxBufferSize);
void robotTurnLeft();
void robotTurnRight();
void robotTurnAround();
bool handleInput(ubyte* input);
// task commandHandlerTask();

#endif //TI_GP_GROEP_4_COMMANDS_H
