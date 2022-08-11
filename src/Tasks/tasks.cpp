#include "tasks.h"
#include <DataBuffer.hpp>
#include "SoftwareSerial.h"

//DataBuffer<int> sonar_pid_data(3, 10);
//SoftwareSerial* serialll = nullptr;

bool bombfound = false;

void pickUpRight() {
  
  if(bombfound == true){
    pickUpRightNoHall();
    return;
  }
  int start; 
  arm.move(620); //raised position
  claw.move(150); //close claw
  delay(500);
  //arm.move(1000);
  // for(int pwm = 500; pwm >= 348; pwm--){
  //   arm.move(pwm);
  //   int start = millis();
  //   while(millis() - start < 12){
  //     if(hall.getValue() == LOW){
  //       delay(1000);
  //       resetClaw();
  //       return;
  //     }
  //   }
  // }
  arm.move(348);
  start = millis();
  while(millis() - start < 1000){
    if(hall.getValue() == LOW){
         delay(500);
         resetClaw();
         bombfound = true;
         return;
       }
  }
  // for(int pwm = 287; pwm <= 573; pwm++){ //slowly open claw
  //   claw.move(pwm);
  //   int start = millis();
  //   while(millis() - start < 8){
  //     if(hall.getValue() == LOW){
  //       delay(1000);
  //       resetClaw();
  //       return;
  //     }
  //   }
  // }
  claw.move(573);
  start = millis();
  while(millis() - start < 1000){
    if(hall.getValue() == LOW){
         delay(500);
         resetClaw();
         bombfound = true;
         return;
       }
  }
  arm.move(205);
  delay(500);
  claw.move(174); //close claw
  start = millis();
  while(millis() - start < 1000){
    if(hall.getValue() == LOW){
         delay(500);
         resetClaw();
         bombfound = true;
         return;
       }
  }
  pwm_start(PB_6, 100, 17, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //raise arm
  delay(750);
  claw.move(287); //open claw in box
  delay(1000);
  resetClaw();
}

void pickUpRightNoHall(){
  
  int start; 
  arm.move(205);
  delay(500);
  claw.move(174); //close claw
  delay(1000);
  pwm_start(PB_6, 100, 17, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //raise arm
  delay(1000);
  claw.move(287); //open claw in box
  delay(1000);
  resetClaw();

}

void pickUpGold(){
  
  int start; 
  arm.move(620); //raised position
  delay(500);
  claw.move(573); //open claw
  delay(500);
  arm.move(205);
  delay(500);
  claw.move(174); //close claw
  delay(1000);
  arm.move(600); 
}


void resetClaw(){
  claw.move(573); //open claw
  arm.move(620);
}


