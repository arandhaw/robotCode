#ifndef TESTS_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define TESTS_H
#include <ReflectSensor.h>
#include <Motor.h>
#include <OLED.h>
#include <PID.h>
#include <Encoders.h>
#include <Motor.h>
#include <Sonar.h>
#include <DataBuffer.hpp>
#include <IRSensor.h>

#include "Tasks/tasks.h"
#include "Motion/motion.h"
#include "tapeFollow/tapeFollow.h"

extern PID pid_tape_45;
extern Encoder encoder1;
extern Encoder encoder2;
extern Motor motor1;
extern Motor motor2;
extern Sonar sonar_r;
extern ReflectSensor R1; //left
extern ReflectSensor R2; //middle
extern ReflectSensor R3; //right
extern DigitalSensor right; //reflectsensor on right
extern DigitalSensor left; //reflectsensor on left
extern IRSensor ir1;
extern IRSensor ir2;


void test_servos();
void test_pickup();
void test_sonar();
void test_counters();
void test_encoders();
void test_tapefollowing();
void test_motors();
void test_IR();
int test_sonars();
void test_edge();
#endif