#include <Arduino.h>
//code to run
#include "tapeFollow.h"
#include "runMotors.h" 
// #include "testMotors.h" 

ReflectSensor R1(PA0);
ReflectSensor R2(PA1);
ReflectSensor R3(PA2);
int lastError = 0;

void setup(){
  setup_OLED();
  //setup_runMotors();
}

void loop(){
  int error = getError(R1, R2, R3, lastError);
  if (error == -100){
    OLED("Robot is lost!", -100);
    lastError = error;
    //stop robot
    return;
  }
  if (error = -10){ 
    OLED("Indeterminate State", -10);
    return; 
  }
  OLED("Detected error:", error);
  lastError = error;
  
}