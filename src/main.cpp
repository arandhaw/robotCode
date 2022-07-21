//Test new Branch
#include "tapeFollow.h"
#include <OLED.h>
#include <Arduino.h>
#include "sweep.h"
#include <Encoders.h>
#include "motion.h"
// #include "runMotors.h" 
// #include "testMotors.h" 

ReflectSensor R1(PA6); //left
ReflectSensor R2(PA5); //middle
ReflectSensor R3(PA4); //right
Motor motor1(PA0, PA_0, PA1, PA_1); //right motor (slower motor)
Motor motor2(PA2, PA_2, PA3, PA_3); //left motor
Encoder encoder1(PB8, PB9, 1);
Encoder encoder2(PB12, PB13, 2);
Servo myservo;

void setup(){
  setup_OLED(); //4 seconds of delay within this function
  //encoder1.reset();
  //encoder2.reset();
  //while(goStraight(60, 20000, 50, encoder1, encoder2, motor1, motor2) == false){}
}

void loop(){
  goSpeed(20, encoder1, motor1);
  //motor1.powerMotor(10);
}