//
// Created by wiebe on 12-4-2017.
//

#ifndef POSITION_H
#define POSITION_H

typedef struct {
    short x, y;
    short orientation; //0 is North, 1 is East, 2 is South, 3 is West.
    short maxX, maxY;
} Position;

void initPosition(Position* pos, short maxX = 4, short maxY = 4, char orientation = 0);
bool canMove(Position* pos);
void robotTurn(short m, short deg);
void displayPosition(Position* pos);

#endif //POSITION_H
