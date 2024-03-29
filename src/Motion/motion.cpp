#include "motion.h"


bool goStraight(PID &pid, int dist, int speed){

    pid.lastError = pid.error;
    pid.error = encoder2.getSpeed() - encoder1.getSpeed();
    pid.sumError += pid.error;
    pid.totalSquaredError += pid.error*pid.error;

    float adjustment = pid.KP*pid.error;
    motor1.powerMotor(speed + round( adjustment ), true);
    motor2.powerMotor(speed - round( adjustment ), true);
    // OLED_manual3(encoder1.getSpeed(), pid.error, pid.totalSquaredError);
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

    float adjustment = pid.KP*pid.error;

    motor1.powerMotor(speed + round( adjustment ), !dir);
    motor2.powerMotor(speed - round( adjustment ), dir);
    // OLED_manual2(pid.pValue(), pid.iValue(), pid.dValue());
    //// OLED_manual3(encoder1.getSpeed(), pid.error, 0);
    
    if(abs( encoder1.getPos() ) <= dist)
        return true;
    else {
        motor1.powerMotor(0);
        motor2.powerMotor(0);
        return false;
    }
}

bool spinWide(int dist, int speed, bool dir){
    
    if(dir == false){
      motor1.powerMotor(speed, true);
      // OLED_manual3(encoder1.getSpeed(), 0, 0);
      if(abs( encoder1.getPos() ) <= dist){
        return true;
      } else { return false; }

    } else {
      motor2.powerMotor(speed, true);
      // OLED_manual3(encoder2.getSpeed(), 0, 0);
      if(abs( encoder2.getPos() ) <= dist){
        return true;
      } else { 
        motor1.powerMotor(0);
        motor2.powerMotor(0);
        return false; 
      }

    }
}

bool goBackwards(PID &pid, int dist, int speed){
    
    pid.lastError = pid.error;
    pid.error = encoder1.getSpeed() - encoder2.getSpeed();
    pid.sumError += pid.error;
    pid.totalSquaredError += pid.error*pid.error;

    float adjustment = pid.KP*pid.error;
    motor1.powerMotor(speed + round( adjustment ), false);
    motor2.powerMotor(speed - round( adjustment ), false);
    // OLED_manual3(encoder1.getSpeed(), pid.error, pid.totalSquaredError);
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

void manualBrake(int duration1, int duration2, int dir1, int dir2){
  motor1.powerMotor(100, dir1);
  motor2.powerMotor(100, dir2);
  int start = millis();
  bool stop1 = false;
  bool stop2 = false;
  while(stop1 == false || stop2 == false){
    if(millis() - start > duration1 && stop1 == false){
      motor1.powerMotor(0);
      stop1 = true;
    }
    if(millis() - start > duration2 && stop2 == false){
      motor2.powerMotor(0);
      stop2 = true;
    }
  }
}

void brakeSpin(bool dir){
  motor1.powerMotor(100, dir);
  motor2.powerMotor(100, !dir);
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
    // OLED_manual3(enc.getPos(), pid.error, dValue);
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

//does not brake after motion
void moveB(float cm){
  encoder1.reset();
  encoder2.reset();
  PID pid1(30, 0, 0, 1000);
  while(goStraight(pid1, cm_to_clicks(cm), 40)){}
  //OLED("Total error:", pid1.totalSquaredError);
  motor1.powerMotor(0);
  motor2.powerMotor(0);
}

void reverse(float cm){
  encoder1.reset();
  encoder2.reset();
  PID pid1(30, 0, 0, 1000);
  while(goBackwards(pid1, cm_to_clicks(cm), 40)){}
  //OLED("Total error:", pid1.totalSquaredError);
  brake(false);
}

void reverseB(float cm){
  encoder1.reset();
  encoder2.reset();
  PID pid1(30, 0, 0, 1000);
  while(goBackwards(pid1, cm_to_clicks(cm), 40)){}
  //OLED("Total error:", pid1.totalSquaredError);
  motor1.powerMotor(0);
  motor2.powerMotor(0);
}

void rotate(float angle, bool dir){
  int clicksSuck = (1180.0*angle)/(90.0); //1210 is a constant - clicks for 90 degree rotation
 // OLED("After Clicks Calc", 0);
  PID pid_rotate(30, 0, 0, 1000);
  encoder1.reset();
  encoder2.reset();
  //  OLED("Before Spin", 1);

  while(spin(pid_rotate, clicksSuck, 40, dir)){}
   // OLED("After Spin", 3);

  //OLED("Total error:", pid1.totalSquaredError);
  manualBrake(60, 60, dir, !dir);
}

void rotate90(bool dir){
  encoder1.reset();
  encoder2.reset();
  PID pidx(50, 0, 0, 1000);
  while(spin(pidx, 1100, 20, dir)){}
  manualBrake(60, 60, dir, !dir);
}

void rotateWide(int angle, bool dir){
  int clicks = round( (float) angle*2400/90 );
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

void rotateWide2(int angle, bool dir){
  int clicks = round( (float) angle*2400/90 );
  encoder1.reset();
  encoder2.reset();
  if (dir == false){
    while(spinWide2(clicks, 40, false)){}
    brake1(80, motor2, false);
  } else {
    while(spinWide2(clicks, 40, true)){}
    brake1(80, motor1, false);
  }
}

bool spinWide2(int dist, int speed, bool dir){
    
    if(dir == false){
      motor2.powerMotor(speed, false);
      // OLED_manual3(encoder1.getSpeed(), 0, 0);
      if(abs( encoder2.getPos() ) <= dist){
        return true;
      } else { 
        motor1.powerMotor(0);
        motor2.powerMotor(0);
        return false; }

    } else {
      motor1.powerMotor(speed, false);
      // OLED_manual3(encoder1.getSpeed(), 0, 0);
      if(abs( encoder1.getPos() ) <= dist){
        return true;
      } else { 
        motor1.powerMotor(0);
        motor2.powerMotor(0);
        return false; 
      }

    }
}