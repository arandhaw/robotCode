#ifndef MOTION_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define MOTION_H
#include <Encoders.h>
#include <OLED.h>
#include <Motor.h>

void goSpeed(int speed, Encoder enc, Motor m1);
bool goStraight(int kp, int dist, int speed, Encoder enc1, Encoder enc2, Motor m1, Motor m2);
void stop(Motor m1, Motor m2);
void spin(int dist, int speed);
bool goSpeed();
int getError();


#endif