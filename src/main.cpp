//Test new Branch
#include "tapeFollow.h"
#include <OLED.h>
// #include "runMotors.h" 
// #include "testMotors.h" 

ReflectSensor R1(PA6); //left
ReflectSensor R2(PA5); //middle
ReflectSensor R3(PA4); //right
Motor motor1(PA0, PA_0, PA1, PA_1); //right motor (slower motor)
Motor motor2(PA2, PA_2, PA3, PA_3); //left motor

void setup(){
  setup_OLED(); //4 seconds of delay within this function
  //setup_runMotors();
}

void loop(){
  PID(R1, R2, R3, motor2, motor1); 
  //OLED_manual2(R1.getRawValue(), R2.getRawValue(), R3.getRawValue());
  
}