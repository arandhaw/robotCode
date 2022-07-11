#ifndef TAPE_FOLLOW_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define TAPE_FOLLOW_H
#include "ReflectSensor.h"
#include "Motor.h"

int getError(ReflectSensor R1, ReflectSensor R2, ReflectSensor R3, int lastError);
void PID();

#endif