//c++ libraries
#include <cmath>
//self made libraries
#include <OLED.h>
#include <Arduino.h>
#include <Encoders.h>
#include <PID.h>
#include <DataBuffer.hpp>
#include <Sonar.h>
//program files
// #include "sweep.h"
#include "Tasks/tasks.h"
#include "Motion/motion.h"
#include "tapeFollow/tapeFollow.h"
#include "tests/tests.h"

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
DataBuffer<int> sonar_data(5, 100);
PID pid_tape_45(10, 0, 5, 0);

void selfOptimize(){
  float arr[2][6];
  int j = 0; 
  for(int i = 5; i <= 30; i = i + 5){
    PID pid(i, 0, 0, 1000);
    encoder1.reset();
    encoder2.reset();
    motor1.powerMotor(50);
    motor2.powerMotor(50);
    while(goStraight2(pid, 20000, 50, encoder1, encoder2, motor1, motor2)){}
    OLED("total error", pid.totalSquaredError);
    arr[0][j] = i;
    arr[1][j] = pid.totalSquaredError;
    delay(4000);
    j++;
  }

  int min = 0; 
  for(int k = 1; k < 6; k++){
    if(arr[1][k] > arr[1][min]){
      min = k;
    }
  }
  OLED2("Smallest Error:", arr[0][min], arr[1][min]);
}



void setup(){
  setup_OLED(); 
  // move(30);
  // rotate(45, false);
  // move(30);
  // rotate(45, true);
  // while(true);
  // encoder1.reset();
  // encoder2.reset();
  // PID pid1(30, 0, 0, 1000);
  // while(goBack(pid1, cm_to_clicks(300), 40, encoder1, encoder2, motor1, motor2)){}
  // while(true){}
  //OLED("Total error:", pid1.totalSquaredError);
  //2 seconds of delay within this function
  //rotate(false); //true turns right, false turns left
  //delay(500);
  //encoder1.reset();
  //encoder2.reset();
  //selfOptimize();
  // move(50);
  // rotate(180, true);
  // move(50);
  //pwm_start(PB_6, 100, 12, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
  
}

int idol_num = 4; //global variable to keep track of state
int var = 0; 
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
      move(100);
      rotate(90, false);
      move(13);
      rotate(90, false);
      while(goStraight2(pid2, cm_to_clicks(50), 40, encoder1, encoder2, motor1, motor2)){
        if(millis() - sonar_r.lastUse > 60){
          int dist = sonar_r.getDistance();
          if(dist < 25 && dist > 8){
            move(5);
            pickUpRight();
          }
        }
      }
      rotate(90, false);
      move(10);
      rotate(90, false);
      move(50);
      idol_num = 69;
  } else if (idol_num == 4){
    if(encoder1.getPos() < cm_to_clicks(80) && var == 0){
      goStraight2(pid2, cm_to_clicks(300), 40, encoder1, encoder2, motor1, motor2);
    } else {
      if(var == 0){
        stop_robot();
        rotate(45, false);
        move(14);
        rotate(45, true);
        var = 1;
      }
      goStraight2(pid2, cm_to_clicks(200), 40, encoder1, encoder2, motor1, motor2);
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