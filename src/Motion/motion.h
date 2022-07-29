#ifndef MOTION_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define MOTION_H
#include <Encoders.h>
#include <PID.h>
#include <OLED.h>
#include <Motor.h>

extern Encoder encoder1;
extern Encoder encoder2;
extern Motor motor1;
extern Motor motor2;

bool goStraight2(PID &pid, int dist, int speed, Encoder enc1, Encoder enc2, Motor m1, Motor m2);
bool goBack(PID &pid, int dist, int speed, Encoder enc1, Encoder enc2, Motor m1, Motor m2);
void stop(PID &pid, int final_pos, Encoder enc, Motor motor);
bool spin(PID &pid, int dist, int speed, bool dir, Encoder enc1, Encoder enc2, Motor m1, Motor m2);
int cm_to_clicks(float cm);
int clicks_to_cm(float cm);

void rotate(float angle, bool dir);
void move(float cm);
void stop_robot();
void reverse(float cm);

#endif