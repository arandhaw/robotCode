#include "tasks.h"
#include <DataBuffer.hpp>
#include "SoftwareSerial.h"


//DataBuffer<int> sonar_pid_data(3, 10);


SoftwareSerial* serialll = nullptr;


void sonarPID(PID &pid){
  if(millis() - sonar_r.lastUse < 60){
    return;
  } 
  pid.lastError = pid.error;
  pid.lastTime = pid.time;
  int reading1 = sonar_r.getDistance();

  delay(15);
  int reading2 = sonar_l.getDistance();

  pid.error = ((float) reading2 - reading1);
  if (pid.error > 30 || pid.error < 30) {
      pid.error = pid.lastError;
  }
  //sonar_pid_data.add(pid.error);

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

    // _serial->print(pid.error);
    // _serial->print(", ");
    // _serial->print(reading1);
    // _serial->print(", ");
    // _serial->print(reading2);
    // _serial->print(", ");
    // _serial->print(sonar_pid_data.runningAvg(3));
    // _serial->println(";");

    //return sonar_pid_data.runningAvg(3);
  OLED_manual2(reading2 - reading1, reading1, reading2);

}

void findIdol(){
  int time = millis();
  PID pid1(8, 0, 0, 100);
  while(millis() - time < 5000){
    //sonarPID(pid1);
  }
  motor1.powerMotor(0);
  motor2.powerMotor(0);
}

void pickUpRight() {
  
   pwm_start(PB_7, 100, 14, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //open claw
  delay(1000);
  pwm_start(PB_6, 100, 5, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);  //lower arm
  delay(1000);
  pwm_start(PB_7, 100, 4, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //close claw
  delay(1000);
  pwm_start(PB_6, 100, 16, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //raise arm
  delay(1000);
  pwm_start(PB_7, 100, 7, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);

}

