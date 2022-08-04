#ifndef TASKS_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define TASKS_H
#include <Encoders.h>
#include <Motor.h>
#include <OLED.h>
#include <Motion/motion.h>
#include <Sonar.h>
#include <PID.h>
#include "SoftwareSerial.h"


extern Sonar sonar_r;
extern Sonar sonar_l;
extern Motor motor1;
extern Motor motor2;

void sonarPID(PID &pid);
void findIdol();
void pickUpRight();

#endif