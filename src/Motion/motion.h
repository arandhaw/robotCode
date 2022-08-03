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

bool goStraight(PID &pid, int dist, int speed);
bool goBackwards(PID &pid, int dist, int speed);
void stop(PID &pid, int final_pos, Encoder enc, Motor motor);
void brake(bool dir);
void brake1(int duration, Motor mot, bool dir);
void brakeSpin(int speed, bool dir);
bool spin(PID &pid, int dist, int speed, bool dir);
bool spinWide(int dist, int speed, bool dir);
int cm_to_clicks(float cm);
int clicks_to_cm(float cm);

void rotate(float angle, bool dir);
void rotate90(bool dir);
void move(float cm);
void stop_robot();
void reverse(float cm);

#endif