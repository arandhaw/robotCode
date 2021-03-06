//c++ libraries
#include <cmath>
//self made libraries
#include <OLED.h>
#include <Arduino.h>
#include <Encoders.h>
#include <PID.h>
#include <DataBuffer.hpp>
#include <Sonar.h>
#include <IRSensor.h>
//program files
// #include "sweep.h"
#include "Tasks/tasks.h"
#include "Motion/motion.h"
#include "tapeFollow/tapeFollow.h"
#include "tests/tests.h"
#include "IRFollow/IRFollow.h"

// #include "runMotors.h" 
// #include "testMotors.h" 

//Servo myservo;

ReflectSensor R1(PA7); //left
ReflectSensor R2(PA6); //middle
ReflectSensor R3(PA5); //right
Motor motor1(PA0, PA_0, PA1, PA_1); //right motor (slower motor)
Motor motor2(PA2, PA_2, PA3, PA_3); //left motor
Encoder encoder2(PB15, PB14, 2);
Encoder encoder1(PB12, PB13, 1);
Sonar sonar_r(PB3, PA15);
IRSensor ir1(PB0, PA8);
IRSensor ir2(PB1, PA8);
DataBuffer<int> sonar_data(5, 100);
PID pid_tape_45(10, 0, 5, 0);
PID pid_ir(20, 0, 0, 0);

void setup(){
  setup_OLED(); 
  // PID pidx(50, 0, 0, 1000);
  // while(spin(pidx, 1100, 20, false)){}
  // brake1(60, motor1, false);
  // brake1(60, motor2, true);
  // while(true);
  // while(spin(pidx, 1160, 40, true)){}
  // brake1(75, motor1, true);
  // brake1(75, motor2, false);
  // while(true){
  // }
  
}

int idol_num = 2; //global variable to keep track of state
int var = 0; 
int state = 0;
PID pid2(30, 0, 0, 1000);

void loop(){
  if(idol_num == 0){
    if( encoder1.getPos() < cm_to_clicks(180)){
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
    } else {
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
      if(millis() - sonar_r.lastUse > 60){
        sonar_data.add(sonar_r.getDistance());
        int dist = sonar_data.get(0);
        if(dist < 20 && dist > 8){
          move(5);
          pickUpRight();
          idol_num = 1;
          reverse(8);
        }
      }
    }
  } else if (idol_num == 1){
    if( encoder1.getPos() < cm_to_clicks(60) ){
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
    } else {
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
      if(millis() - sonar_r.lastUse > 60){
        int dist = sonar_r.getDistance();
        if(dist < 25 && dist > 8){
          move(5);
          pickUpRight();
          idol_num = 69;
          reverse(9);
          }
        }
      }
  } else if (idol_num == 2){
      IRFollow(pid_ir, 40);
      if(encoder1.getPos() > cm_to_clicks(100)){
        if(millis() - sonar_r.lastUse > 60){
          int dist = sonar_r.getDistance();
          if(dist < 22 && dist > 8){
            move(7);
            pickUpRight();
            idol_num = 3;
        }
      }
    }  
  } else if (idol_num == 3){
      if(var == 0){
        rotate90(false);
        delay(1000);
        move(10);
        delay(1000);
        encoder1.reset();
        encoder2.reset();
        while(spinWide(2200, 40, false)){}
        brake1(80, motor1, true);
        delay(1000);
        encoder1.reset();
        encoder2.reset();
        var++;
      }
      goStraight(pid2, cm_to_clicks(200), 40);
      if(encoder1.getPos() > cm_to_clicks(30)){
        if(millis() - sonar_r.lastUse > 60){
          int dist = sonar_r.getDistance();
          if(dist < 25 && dist > 8){
            move(5);
            pickUpRight();
            idol_num = 69;
          }
        }
      }
  } else if (idol_num == 4){
    if(encoder1.getPos() < cm_to_clicks(80) && var == 0){
      goStraight(pid2, cm_to_clicks(300), 40);
    } else {
      if(var == 0){
        stop_robot();
        rotate(45, false);
        move(14);
        rotate(45, true);
        var = 1;
      }
      goStraight(pid2, cm_to_clicks(200), 40);
      if(millis() - sonar_r.lastUse > 60){
        int dist = sonar_r.getDistance();
        if(dist < 25 && dist > 8){
          move(5);
          pickUpRight();
          idol_num = 69;
          }
        }
    }
  } else if (idol_num == 69){
    motor1.powerMotor(0);
    motor2.powerMotor(0);
  }

  // if(idol_num == 10){
  //   PID pid_1(30, 0, 0, 1000);
  //   goStraight2(pid_1, cm_to_clicks(100), 10, encoder1, encoder2, motor1, motor2);

  //   if(R1.getDigitalValue() == 1){
  //     PID pid(30, 0, 0, 1000);
  //     int d;
  //     int L = 2;
  //     encoder1.reset();
  //     encoder2.reset();
  //     while(goStraight2(pid, cm_to_clicks(10000), 10, encoder1, encoder2, motor1, motor2)){
  //       if(R3.getDigitalValue() == 1){
  //         d = encoder1.getPos();
  //         stop_robot();
  //         break;
  //       }
  //     }
      
  //     float angle = 180/PI*std::atan((float) d/L);
  //     rotate(angle, false);
  //     encoder1.reset();
  //     encoder2.reset();
  //     pid_1.reset();
  //   }
  // }
  // motor1.powerMotor(50);
  // motor2.powerMotor(50);
  //OLED_manual(encoder1.getSpeed(), 0, encoder2.getSpeed(), 0);
  //encoder1.testCounters();

}



// } else if (idol_num == 2){
//     
//     }