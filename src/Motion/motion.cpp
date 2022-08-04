#include "motion.h"


bool goStraight(PID &pid, int dist, int speed){

    pid.lastError = pid.error;
    pid.error = encoder2.getSpeed() - encoder1.getSpeed();
    pid.sumError += pid.error;
    pid.totalSquaredError += pid.error*pid.error;

    motor1.powerMotor(speed + round( pid.PIDValue() ) + 10, true);
    motor2.powerMotor(speed - round( pid.PIDValue() ), true);
    OLED_manual3(encoder1.getSpeed(), pid.error, pid.totalSquaredError);
    if(encoder1.getPos() <= dist)
        return true;
    else {
        motor1.powerMotor(0);
        motor2.powerMotor(0);
        return false;
    }
}

//dir gives direction - spin right is ?? spin left is ??
bool spin(PID &pid, int dist, int speed, bool dir){

    pid.lastError = pid.error;
    pid.error = abs(encoder2.getSpeed()) - abs(encoder1.getSpeed());
    

    pid.sumError += pid.error;
    pid.totalSquaredError += pid.error*pid.error;

    motor1.powerMotor(speed + round(pid.PIDValue()), !dir);
    motor2.powerMotor(speed - round(pid.PIDValue()), dir);
    OLED_manual3(encoder1.getSpeed(), pid.error, 0);
    
    if(abs( encoder1.getPos() ) <= dist)
        return true;
    else {
        return false;
    }
}

bool spinWide(int dist, int speed, bool dir){
    
    if(dir == false){
      motor1.powerMotor(speed, true);
      OLED_manual3(encoder1.getSpeed(), 0, 0);
      if(abs( encoder1.getPos() ) <= dist){
        return true;
      } else { return false; }

    } else {
      motor2.powerMotor(speed, true);
      OLED_manual3(encoder2.getSpeed(), 0, 0);
      if(abs( encoder2.getPos() ) <= dist){
        return true;
      } else { return false; }

    }
}

bool goBackwards(PID &pid, int dist, int speed){
    
    pid.lastError = pid.error;
    pid.error = encoder1.getSpeed() - encoder2.getSpeed();
    pid.sumError += pid.error;
    pid.totalSquaredError += pid.error*pid.error;

    motor1.powerMotor(speed + round( pid.PIDValue() ), false);
    motor2.powerMotor(speed - round( pid.PIDValue() ), false);
    OLED_manual3(encoder1.getSpeed(), pid.error, pid.totalSquaredError);
    if(abs( encoder1.getPos() )<= dist)
        return true;
    else {
        motor1.powerMotor(0);
        motor2.powerMotor(0);
        return false;
    }
}

void brake(bool dir){
  motor1.powerMotor(100, !dir);
  motor2.powerMotor(100, !dir);
  delay(60);
  motor1.powerMotor(0);
  motor2.powerMotor(0);
}

void brake1(int duration, Motor mot, bool dir){
  mot.powerMotor(100, !dir);
  delay(duration);
  mot.powerMotor(0);
}

void brakeSpin(bool dir){
  motor1.powerMotor(100, !dir);
  motor2.powerMotor(100, dir);
  delay(60);
  motor1.powerMotor(0);
  motor2.powerMotor(0);
}

void stop(PID &pid, int final_pos, Encoder enc, Motor motor){
    pid.lastError = pid.error;
    pid.lastTime = pid.time;
    pid.error = ((float) (final_pos - enc.getPos()))/100;
    pid.time = micros();
    pid.sumError += pid.error;
    float dValue = (pid.error - pid.lastError)/(pid.time - pid.lastTime)*1000000;
    pid.totalSquaredError += pid.error*pid.error;

    int pwm = pid.pValue() + pid.iValue() + dValue;
    motor.powerMotor( pwm );
    OLED_manual3(enc.getPos(), pid.error, dValue);
}

int cm_to_clicks(float cm){
  return round( 70*cm );
}

float clicks_to_cm(int clicks){
  return (float) clicks/70 ;
}

void move(float cm){
  encoder1.reset();
  encoder2.reset();
  PID pid1(30, 0, 0, 1000);
  while(goStraight(pid1, cm_to_clicks(cm), 40)){}
  //OLED("Total error:", pid1.totalSquaredError);
  brake(true);
}

void reverse(float cm){
  encoder1.reset();
  encoder2.reset();
  PID pid1(30, 0, 0, 1000);
  while(goBackwards(pid1, cm_to_clicks(cm), 40)){}
  //OLED("Total error:", pid1.totalSquaredError);
  brake(false);
}
void stop_robot(){
  PID pid2(30, 0, 50, 1000);
  PID pid3(30, 0, 50, 1000);
  int final_pos = encoder1.getPos();
  int final_pos2 = encoder2.getPos();
  int start = millis();
  while(millis() - start < 1500){
     stop(pid2, final_pos, encoder1, motor1);
     stop(pid3, final_pos2, encoder2, motor2);
  }
  motor1.powerMotor(0);
  motor2.powerMotor(0);
}

void rotate(float angle, bool dir){
  int clicks = round(angle/90*1180); //1210 is a constant - clicks for 90 degree rotation
  PID pid1(30, 0, 0, 1000);
  encoder1.reset();
  encoder2.reset();
  while(spin(pid1, clicks, 40, dir)){}
  //OLED("Total error:", pid1.totalSquaredError);
  brake1(60, motor1, !dir);
  brake1(60, motor2, dir);
}

void rotate90(bool dir){
  encoder1.reset();
  encoder2.reset();
  PID pidx(50, 0, 0, 1000);
  while(spin(pidx, 1100, 20, dir)){}
  brake1(60, motor1, !dir);
  brake1(60, motor2, dir);
}

void rotateWide(int angle, bool dir){
  int clicks = round( (float) angle/2400*90 );
  encoder1.reset();
  encoder2.reset();
  if (dir == false){
    while(spinWide(clicks, 40, false)){}
    brake1(80, motor1, true);
  } else {
    while(spinWide(clicks, 40, true)){}
    brake1(80, motor2, true);
  }
}