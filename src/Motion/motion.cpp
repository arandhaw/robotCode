#include "motion.h"
// #define KP 5
int factor = 0;
int power = 0; 
#define DEAD_BAND 0

//speed is an integer between 0 and 25 - an artificial speed scale based on 
//encoder readings
void goSpeed(PID &pid, int speed, Encoder enc, Motor m1){
    //updating value of error, sumError, lastError, and total error
    pid.lastError = pid.error;
    pid.error = speed - enc.getSpeed();
    pid.sumError = pid.sumError + pid.error;
    pid.totalSquaredError += pid.error*pid.error;

    power += round(pid.PIDValue());
    m1.powerMotor(power);
    OLED_manual3(enc.getSpeed(), pid.error, power);
}

bool goStraight(int speed, Encoder enc1, Encoder enc2, Motor m1, Motor m2){
    if ((enc2.getPos() - enc1.getPos()) < -DEAD_BAND) {
        // We are pointing too far to the right. Turn right motor on, left motor off.
        m1.powerMotor(speed - 5);
        m2.powerMotor(speed + 5);
    } 
    else if ((enc2.getPos() - enc1.getPos()) > DEAD_BAND){
        // We are pointing too far to the left. Turn left motor on, right motor off.
        m1.powerMotor(speed + 5);
        m2.powerMotor(speed - 5);
    }
    else {
        // Everything seems cool. Continue psuedo-straight.
        m1.powerMotor(speed);
        m2.powerMotor(speed);
    }
    return true;
}

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
    if(dist - abs( enc1.getPos()) < 1000){
         speed = round((  abs(dist) - abs( enc1.getPos()) )/1000*30 + (speed - 30)  );
    }

    pid.lastError = pid.error;
    if(dir = true){
        
    } else {
        pid.error = abs(enc1.getSpeed()) - abs(enc2.getSpeed());
    }

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


  // for(int i = 1; i < 20; i++){
  //   int start = millis();
  //   while(millis() - start < 100){
  //     goSpeed(pid1, i, encoder1, motor1);
  //     goSpeed(pid2, i, encoder2, motor2);
  //   }
  // }

  // goSpeed(pid1, 20, encoder1, motor1);
  // goSpeed(pid2, 20, encoder2, motor2);