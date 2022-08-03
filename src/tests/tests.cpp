#include "tests.h"

void test_servos(){
    pickUpRight();
}

DataBuffer<int> test_data(5, 100);
void test_pickup(){
    if(millis() - sonar_r.lastUse > 60){
        test_data.add(sonar_r.getDistance());
        if(test_data.runningAvg(3) < 25){ 
          pickUpRight();
          test_data.reset(100);
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