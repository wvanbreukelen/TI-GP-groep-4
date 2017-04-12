//
// Created by trvan on 12-4-2017.
//

#ifndef REGULATION_H
#define REGULATION_H

void acceleration(short ml, short mr, short targetSpeed, short alcOffset = 1);
void deceleration(short ml, short mr, short targetSpeed, short declOffset = 1);

#endif //REGULATION_H
