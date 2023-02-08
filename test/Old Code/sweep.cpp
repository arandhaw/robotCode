#include "sweep.h"

void sweep(Servo servo, int speed, int final_angle){
    int start = servo.read();
    for(int ang = start; ang < final_angle; ang = ang + speed){
        servo.write(ang);
        delay(5);
    }
    servo.write(final_angle);
}