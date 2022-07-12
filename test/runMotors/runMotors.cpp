#include "runMotors.h"
#include <OLED.h>
#include <wire.h>
#include <Motor.h>

#define AOUT_PIN_1 PA1   // analog out pin for PWM
#define AOUT_PIN_1_PWM PA_1 // analog out pin for PWM (same pin but different
                        	// data type - this is confusing!)
#define AOUT_PIN_2 PA2   // analog out pin for PWM
#define AOUT_PIN_2_PWM PA_2 // analog out pin for PWM (same pin but different
                        	// data type - this is confusing!)                          

Motor motor1(PA0, PA_0, PA1, PA_1);
Motor motor2(PA2, PA_2, PA3, PA_3);
bool dir;
int dutycycle = 50;

//setup function - run once
void setup_runMotors(){
  bool dir = true;
  setup_OLED();
}

//loop function - run in master loop
void loop_runMotors(){
  OLED("Dutycycle:", dutycycle);
  motor1.powerMotor(45, dir);
  motor2.powerMotor(45, !dir);
  delay(2000);
  //motor1.powerMotor(50, dir);
  //motor2.powerMotor(50, dir);
  //OLED(50);
  motor1.powerMotor(45, dir);
  motor2.powerMotor(45, !dir);
  delay(2000);
}
