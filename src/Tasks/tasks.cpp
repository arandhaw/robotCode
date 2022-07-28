#include "tasks.h"

void move(float cm){
  encoder1.reset();
  encoder2.reset();
  PID pid1(30, 0, 0, 1000);
  while(goStraight2(pid1, cm_to_clicks(cm), 40, encoder1, encoder2, motor1, motor2)){}
  //OLED("Total error:", pid1.totalSquaredError);
  stop_robot();
}

void rotate(float angle, bool dir){
  int clicks = round(angle/90*1210); //1210 is a constant - clicks for 90 degree rotation
  PID pid1(30, 0, 0, 1000);
  encoder1.reset();
  encoder2.reset();
  while(spin(pid1, clicks, 40, !dir, encoder1, encoder2, motor1, motor2)){}
  //OLED("Total error:", pid1.totalSquaredError);
  stop_robot();
}

void stop_robot(){
  PID pid2(30, 0, 50, 1000);
  PID pid3(30, 0, 50, 1000);
  int final_pos = encoder1.getPos();
  int final_pos2 = encoder2.getPos();
  int start = millis();
  while(millis() - start < 1000){
     stop(pid2, final_pos, encoder1, motor1);
     stop(pid3, final_pos2, encoder2, motor2);
  }
  motor1.powerMotor(0);
  motor2.powerMotor(0);
}


void pickUpRight() {
  //PA8 is arm 9 is claw
  pwm_start(PB_7, 100, 22, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //open claw
  delay(1000);
  pwm_start(PB_6, 100, 5, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);  //lower arm
  delay(1000);
  pwm_start(PB_7, 100, 15, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //close claw
  delay(1000);
  pwm_start(PB_6, 100, 18, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //raise arm
  delay(1000);
  pwm_start(PB_7, 100, 22, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //open claw
}