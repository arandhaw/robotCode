#include "tests.h"


void test_servos(){
    pickUpRight();
}

void test_pickup(){
    if(millis() - sonar_r.lastUse > 60){
        int dist = sonar_r.getDistance();
        if(dist < 25 && dist > 8){ 
          pickUpRight();
        }
    }
}

void test_sonar(){
    OLED("Sonar Distance", sonar_r.getDistance());
}
void test_counters(){
    encoder1.testCounters();
}
void test_encoders(){
    OLED_manual(encoder1.getPos(), encoder1.getSpeed(), encoder2.getPos(), encoder2.getSpeed());
}
void test_tapefollowing(){
    tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
}
void test_motors(){
    motor1.powerMotor(40);
    motor2.powerMotor(0);
    delay(1000);
    motor1.powerMotor(0);
    motor2.powerMotor(40);
    delay(1000);
}

void test_IR(){
    int num1 = ir1.getValue();
    delay(1);
    int num2 = ir2.getValue();
    OLED2("IR1, IR2:", num1, num2);
}

int test_sonars(){
    int error = 0;
    if(sonar_r.lastUse - millis() > 60){
        int reading1 = sonar_r.getDistance();
        delay(30);
        int reading2 = sonar_l.getDistance();
        error = reading2 - reading1;
        OLED_manual2(error, reading1, reading2);
    }
    return error;
}

void test_edge(){
    OLED2("Right, left", right.getValue(), left.getValue());
}