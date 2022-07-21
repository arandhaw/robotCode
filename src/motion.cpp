#include "motion.h"
// #define KP 5
int factor = 0;
int summedError; 
int total_error = 0; 
#define KP 80
#define KI 50

//speed is an integer between 0 and 25 - an artificial speed scale based on 
//encoder readings
void goSpeed(int speed, Encoder enc, Motor m1){
    float error = speed - enc.getSpeed();
    int power = round( error*KP );
    m1.powerMotor(power, true);
    OLED_manual3(error, enc.getSpeed(), 0);
}

bool goStraight(int kp, int dist, int speed, Encoder enc1, Encoder enc2, Motor m1, Motor m2){

    m1.powerMotor(speed - factor, true);
    m2.powerMotor(speed + factor, true);

    int dist_travelled = enc1.getPos();
    int dDist = enc1.getPos() - enc2.getPos();
    
    factor += dDist*kp/100;
    total_error += dDist*dDist;
    OLED_manual(enc1.getPos(), enc2.getPos(), 0, total_error/100000);
    //safety kill switch
    // if(factor > 20 || factor < 20){
    //     m1.powerMotor(0, true);
    //     m2.powerMotor(0, true);
    // }
    if(dist_travelled > dist){
         stop(m1, m2);
         return true;
    } 
    return false;
}

void stop(Motor m1, Motor m2){
    m1.powerMotor(0, true);
    m2.powerMotor(0, true);
}