#ifndef MOTION_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define MOTION_H
#include <Encoders.h>
#include <PID.h>
#include <OLED.h>
#include <Motor.h>

void goSpeed(PID &pid, int speed, Encoder enc, Motor m1);
bool goStraight(int speed, Encoder enc1, Encoder enc2, Motor m1, Motor m2);
bool goStraight2(PID &pid, int dist, int speed, Encoder enc1, Encoder enc2, Motor m1, Motor m2);
void stop(PID &pid, int final_pos, Encoder enc, Motor motor);
bool spin(PID &pid, int dist, int speed, bool dir, Encoder enc1, Encoder enc2, Motor m1, Motor m2);
int cm_to_clicks(float cm);

#endif