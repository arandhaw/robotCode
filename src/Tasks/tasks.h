#ifndef TASKS_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define TASKS_H
#include <Encoders.h>
#include <Motor.h>
#include <OLED.h>
#include <Motion/motion.h>
#include <Sonar.h>
#include <PID.h>

#include <servo.h>
#include <DigitalSensor.h>
extern Sonar sonar_r;
extern Sonar sonar_l;
extern Motor motor1;
extern Motor motor2;
extern servo claw;
extern servo arm;
extern DigitalSensor hall;

void sonarPID(PID &pid);
void findIdol();
void pickUpRight();
void resetClaw();

#endif