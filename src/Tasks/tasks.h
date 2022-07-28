#ifndef TASKS_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define TASKS_H
#include <Encoders.h>
#include <Motor.h>
#include <OLED.h>
#include <Motion/motion.h>

extern Encoder encoder1;
extern Encoder encoder2;
extern Motor motor1;
extern Motor motor2;

void rotate(float angle, bool dir);
void move(float cm);
void stop_robot();
void pickUpRight();

#endif