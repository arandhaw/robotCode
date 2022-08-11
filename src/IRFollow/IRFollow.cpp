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

void zigzag(int speed, int p, int time){
    if(right.getValue() == true){
        zigzagTimer = millis();
        dir = false; //go left
    } else if(left.getValue() == true){
        zigzagTimer = millis();
        dir = true; // go right
    } 

    if(millis() - zigzagTimer < time){
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

int lastBounce = -100000;
int direction = 0;

void zigzag2(int speed, int p, int time){
    if(millis() - lastBounce < time){
        if(direction == -1){ //go left
            motor1.powerMotor(speed + p); 
            motor2.powerMotor(speed - p);
            OLED("Go Left", direction);
        } else if(direction == 1){ //go right
            motor1.powerMotor(speed - p);
            motor2.powerMotor(speed + p); 
            OLED("Go Right", direction);
        }
        //go current direction
    } else {

        if(right.getValue() == 1){
            direction = -1; //turn left
            lastBounce = millis();
        } else if(left.getValue() == 1){
            direction = 1; //turn right
            lastBounce = millis();
        } else {
            dir = 0; //go straight
            PID justP(30, 0, 0, 100); // just proportional
            goStraight(justP, 10000, speed);
            OLED("Go Straight", direction);
        }
    }
}

void theChristian(PID &pid, int numOfCorrections, double finalCorAngle, Encoder encoder1, Encoder encoder2) {
    //for (int i = 0; i < numOfCorrections; i++) {        
        while (right.getValue() == 0 && encoder1.getPos() < cm_to_clicks(175)) {
            goStraight(pid, 1000, 35);
        }
        manualBrake(30, 30, true, true);
        while (right.getValue() == 1 && encoder1.getPos() < cm_to_clicks(175)) {
            spinWide2(5, 35, false);
        }
    //} 
}

void zag(){
    return;
}