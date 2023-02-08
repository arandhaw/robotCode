#ifndef CLAW_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define CLAW_H
#include <Encoders.h>
#include <Motor.h>
#include <OLED.h>
#include <Motion/motion.h>
#include <Sonar.h>
#include <PID.h>
#include <servo.h>
#include <DigitalSensor.h>

extern servo claw;
extern servo arm;
extern DigitalSensor hall;

void pickUpRight();
void resetClaw();
void pickUpRightNoHall();
void pickUpGold();
#endif