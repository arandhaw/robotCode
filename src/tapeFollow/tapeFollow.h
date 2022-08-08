#ifndef TAPE_FOLLOW_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define TAPE_FOLLOW_H
#include <ReflectSensor.h>
#include <Motor.h>
#include <OLED.h>
#include <PID.h>

extern Motor motor1;
extern Motor motor2;

int getError(ReflectSensor R1, ReflectSensor R2, ReflectSensor R3, int lastError);
void tapeFollow(PID &pid, int speed, ReflectSensor R1, ReflectSensor R2, ReflectSensor R3, Motor leftMotor, Motor rightMotor);
void failure(Motor m1, Motor m2);
void findTape(ReflectSensor R1, ReflectSensor R2, ReflectSensor R3);

#endif