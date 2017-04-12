//
// Created by wiebe on 12-4-2017.
//

#ifndef COMMANDS_H
#define COMMANDS_H

/**
 * Maximum size of single bluetooth message
 */
const int kMaxSizeOfMessage = 30;

/**
 * Maximum size of message inbox
 */
const int inboxSize = 5;

int readBluetoothData(ubyte* buffer, int nMaxBufferSize);
void robotTurnLeft();
void robotTurnRight();
void robotTurnAround();
bool handleInput(ubyte* input);
task commandHandlerTask();

#endif //TI_GP_GROEP_4_COMMANDS_H
