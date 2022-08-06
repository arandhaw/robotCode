#include "tasks.h"

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
  
  // arm.move(15);
  // OLED("PWM before motion", arm.current_pwm);
  // delay(5000);
  // arm.moveSlowly(5, 100);
  // OLED("PWM after motion", arm.current_pwm);
  // delay(1000);
  
  arm.move(620);
  delay(1000);
  claw.move(150); //close claw
  delay(1000);
  arm.move(500);
  for(int pwm = 500; pwm >= 348; pwm--){
    arm.move(pwm);
    int start = millis();
    while(millis() - start < 12){
      if(hall.getValue() == LOW){
        delay(1000);
        resetClaw();
        return;
      }
    }
  }
  delay(1000);
  for(int pwm = 287; pwm <= 573; pwm++){ //slowly open claw
    claw.move(pwm);
    int start = millis();
    while(millis() - start < 8){
      if(hall.getValue() == LOW){
        delay(1000);
        resetClaw();
        return;
      }
    }
  }
  delay(1000);
  arm.move(205);
  delay(1000);
  claw.move(174); //close claw
  delay(1000);
  arm.move(680); //raise arm
  delay(1000);
  claw.move(287); //open claw in box
  delay(1000);
  arm.move(620); //reset position of claw
  delay(1000);
  claw.move(573); //open claw fully

}


void resetClaw(){
  claw.move(573); //open claw
  delay(1000);
  arm.move(620);
}
