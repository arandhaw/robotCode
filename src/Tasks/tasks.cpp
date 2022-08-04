#include "tasks.h"

void sonarPID(PID &pid){
  pid.lastError = pid.error;
  pid.lastTime = pid.time;
  int reading1 = sonar_r.getDistance();
  int reading2 = sonar_l.getDistance();
  pid.error = ((float) reading2 - reading1);
  pid.time = (float) micros()/1000; 
  pid.sumError += pid.error;
  pid.totalSquaredError += pid.error*pid.error;

  int power = round( pid.PIDValue() );
  //capping the max motor speed
  if(power > 20){
    power = 20;
  } else if (power < -20){
    power = -20;
  }
  motor1.powerMotor(power);
  motor2.powerMotor(power);
  OLED_manual2(reading2 - reading1, reading1, reading2);
}

void findIdol(){
  int time = millis();
  PID pid1(8, 0, 0, 100);
  while(millis() - time < 5000){
    sonarPID(pid1);
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
  pwm_start(PB_6, 100, 17, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //raise arm
  delay(1000);
  pwm_start(PB_7, 100, 22, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //open claw
  delay(500);
  pwm_start(PB_6, 100, 16, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //raise arm

}