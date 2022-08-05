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

//four functions that must be called continuously
bool goStraight(PID &pid, int dist, int speed);
bool goBackwards(PID &pid, int dist, int speed);
bool spin(PID &pid, int dist, int speed, bool dir);
bool spinWide(int dist, int speed, bool dir);

//braking functions
void brake(bool dir);
void brake1(int duration, Motor mot, bool dir);
void brakeSpin(bool dir);

//conversion functions
int cm_to_clicks(float cm);
int clicks_to_cm(float cm);

//functions that are called once
void move(float cm);
void moveB(float cm);
void reverse(float cm);
void reverseB(float cm);
void rotate(float angle, bool dir);
void rotate90(bool dir);
void rotateWide(int angle, bool dir);

//these functions suck
void stop_robot();
void stop(PID &pid, int final_pos, Encoder enc, Motor motor);

#endif