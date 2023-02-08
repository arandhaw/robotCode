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
    // OLED2("IR1, IR2", reading1, reading2);

}

void theChristian(PID &pid, int numOfCorrections, double finalCorAngle, Encoder encoder1, Encoder encoder2) {
    //for (int i = 0; i < numOfCorrections; i++) {        
        while (right.getValue() == 0 && encoder1.getPos() < cm_to_clicks(177)) {
            goStraight(pid, 1000, 35);
        }
        manualBrake(30, 30, true, true);
        while (right.getValue() == 1 && encoder1.getPos() < cm_to_clicks(177)) {
            spinWide2(5, 35, false);
        }
    //} 
}
