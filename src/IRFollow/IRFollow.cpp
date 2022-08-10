#include "IRFollow.h"

void IRFollow(PID &pid, int speed) {
    
    pid.lastError = pid.error;
    pid.lastTime = pid.time;
    int reading1 = ir1.getValue();
    int reading2 = ir2.getValue();
    pid.error = ((float) reading2 - reading1)/100;
    pid.time = (float) micros()/1000; 
    pid.sumError += pid.error;
    pid.totalSquaredError += pid.error*pid.error;

    int adjustment = round( pid.PIDValue() );
    motor1.powerMotor(speed + adjustment, true);
    motor2.powerMotor(speed - adjustment, true);
    OLED2("IR1, IR2", reading1, reading2);

}

void IRrotate(PID &pid) {
    
    pid.lastError = pid.error;
    pid.lastTime = pid.time;
    int reading1 = ir1.getValue();
    int reading2 = ir2.getValue();
    pid.error = ((float) reading2 - reading1)/100;
    pid.time = (float) micros()/1000; 
    pid.sumError += pid.error;
    pid.totalSquaredError += pid.error*pid.error;

    int adjustment = round( pid.PIDValue() );
    motor1.powerMotor(adjustment);
    motor2.powerMotor(-adjustment);
    OLED2("IR1, IR2", reading1, reading2);

}

int zigzagTimer = -10000;
bool dir = true;

void zigzag(int speed, int p){
    if(right.getValue() == true){
        zigzagTimer = millis();
        dir = false; //go left
    } else if(left.getValue() == true){
        zigzagTimer = millis();
        dir = true; // go right
    } 

    if(millis() - zigzagTimer < 1500){
        if(dir == false){
            motor1.powerMotor(speed + p);
            motor2.powerMotor(speed - p);
            OLED("Go left", 0);
        } else if(dir == true){
            motor1.powerMotor(speed - p);
            motor2.powerMotor(speed + p);
            OLED("Go Right", 0);
        }
    } else {
        OLED("Go straight", 0);
        PID justP(30, 0, 0, 100); // just proportional
        goStraight(justP, 10000, speed);
    }
    
}