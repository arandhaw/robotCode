#ifndef IR_FOLLOW_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define IR_FOLLOW_H

#include <Motor.h>
#include <OLED.h>
#include <PID.h>
#include <IRSensor.h>
#include <Arduino.h>

extern Motor motor1;
extern Motor motor2;
extern IRSensor ir1;
extern IRSensor ir2;

void IRFollow(PID &pid, int speed);

#endif