#include "motion.h"


bool goStraight2(PID &pid, int dist, int speed, Encoder enc1, Encoder enc2, Motor m1, Motor m2){
    if(dist - enc1.getPos() < 1000){
        speed = round( (dist - enc1.getPos())/1000*30 + (speed - 30)  );
    }
    pid.lastError = pid.error;
    pid.error = enc2.getSpeed() - enc1.getSpeed();
    pid.sumError += pid.error;
    pid.totalSquaredError += pid.error*pid.error;

    m1.powerMotor(speed + pid.PIDValue(), true);
    m2.powerMotor(speed - pid.PIDValue(), true);
    OLED_manual3(enc1.getSpeed(), pid.error, pid.totalSquaredError);
    if(enc1.getPos() <= dist)
        return true;
    else {
        m1.powerMotor(0);
        m2.powerMotor(0);
        return false;
    }
}

//dir gives direction - spin right is ?? spin left is ??
bool spin(PID &pid, int dist, int speed, bool dir, Encoder enc1, Encoder enc2, Motor m1, Motor m2){
    // if(dist - abs( enc1.getPos()) < 1000){
    //      speed = round((  abs(dist) - abs( enc1.getPos()) )/1000*30 + (speed - 30)  );
    // }

    pid.lastError = pid.error;
    pid.error = abs(enc2.getSpeed()) - abs(enc1.getSpeed());
    

    pid.sumError += pid.error;
    pid.totalSquaredError += pid.error*pid.error;

    m1.powerMotor(speed + pid.PIDValue(), dir);
    m2.powerMotor(speed - pid.PIDValue(), !dir);
    OLED_manual3(enc1.getSpeed(), pid.error, 0);
    
    if(abs( enc1.getPos() ) <= dist)
        return true;
    else {
        return false;
    }
}

bool goBack(PID &pid, int dist, int speed, Encoder enc1, Encoder enc2, Motor m1, Motor m2){
    if(dist - abs(enc1.getPos()) < 1000){
        speed = round( (dist - abs( enc1.getPos() ) )/1000*30 + (speed - 30)  );
    }
    pid.lastError = pid.error;
    pid.error = enc1.getSpeed() - enc2.getSpeed();
    pid.sumError += pid.error;
    pid.totalSquaredError += pid.error*pid.error;

    m1.powerMotor(speed + pid.PIDValue(), false);
    m2.powerMotor(speed - pid.PIDValue(), false);
    OLED_manual3(enc1.getSpeed(), pid.error, pid.totalSquaredError);
    if(abs( enc1.getPos() )<= dist)
        return true;
    else {
        m1.powerMotor(0);
        m2.powerMotor(0);
        return false;
    }
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
  while(goStraight2(pid1, cm_to_clicks(cm), 40, encoder1, encoder2, motor1, motor2)){}
  //OLED("Total error:", pid1.totalSquaredError);
  stop_robot();
}

void reverse(float cm){
  encoder1.reset();
  encoder2.reset();
  PID pid1(30, 0, 0, 1000);
  while(goBack(pid1, cm_to_clicks(cm), 40, encoder1, encoder2, motor1, motor2)){}
  //OLED("Total error:", pid1.totalSquaredError);
  stop_robot();
}

void rotate(float angle, bool dir){
  int clicks = round(angle/90*1180); //1210 is a constant - clicks for 90 degree rotation
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
  while(millis() - start < 1500){
     stop(pid2, final_pos, encoder1, motor1);
     stop(pid3, final_pos2, encoder2, motor2);
  }
  motor1.powerMotor(0);
  motor2.powerMotor(0);
}