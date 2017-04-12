//
// Created by wiebe on 12-4-2017.
//

#ifndef CALIBRATION_H
#define CALIBRATION_H

typedef struct
{
    short CBlack;
    short CWhite;
    short BWBlack;
    short BWWhite;
} Calibration;

void findBoundaries(Calibration* cal);
Calibration* calibrate();


#endif //CALIBRATION_H
