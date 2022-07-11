/**
 * loop{
 * find error, 
 * determine speed
 * }
 *
 * 
 * powerMotor(speed - adjustment)
 * powerMotor(speed + adjustment)
 **/

//#define KP 3
//#define KD 9
//#define KI 0
#include "tapeFollow.h"

int getError(ReflectSensor R1, ReflectSensor R2, ReflectSensor R3, int lastError){
    bool a = R1.getDigitalValue();
    bool b = R2.getDigitalValue();
    bool c = R3.getDigitalValue();
    int val = a*4 + b*2 + c; //convert 3 booleans into number
    if(val == 2){
        return 0;
    } else if(val == 6){
        return -1;
    } else if(val == 4){
        return -2;
    } else if(val == 3){
        return 1;
    } else if(val == 1){
        return 2;
    } else if(val == 0){
        if(lastError == -100 || lastError == -10 || lastError == 0)
            return -100;
        if(lastError > 0)
            return 3;
        if(lastError < 0)
            return -3;
    } else 
        return -10;
}
//

//void PID(int speed, Motor motor1, Motor motor2){
    //errpr = calculateError();
    //adjustment = error*KD + summedError*KI + derivError*KD;
    //motor1.powerMotor(speed - adjustment, true);
    //motor2.powerMotor(speed + adjustment, true);
//

