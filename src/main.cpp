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
#include <servo.h>
#include <DigitalSensor.h>
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
Sonar sonar_l(PB5, PB4); 
IRSensor ir1(PB0, PA8);
IRSensor ir2(PB1, PA8);
servo arm(PB_6);
servo claw(PB_7);
DigitalSensor hall(PA12); //change
DataBuffer<bool> sonar_bool(50, 0);
DataBuffer<int> sonar_data(5, 100);
PID pid_tape_45(10, 0, 5, 0);
PID pid_ir(20, 0, 0, 0);
PID pidsonar(5, 0, 0, 0);
PID pidmotion(40, 0, 0, 0);

void setup(){
  setup_OLED();
  // while(true){
  //   //OLED("Hall effect:", hall.getValue());
  //   test_sonar();
  // } 
  
}

int idol_num = 0; //global variable to keep track of state
int var = 0; 
int state = 0;
PID pid2(30, 0, 0, 1000);

void loop(){
  if(idol_num == 0){
    if( encoder1.getPos() < cm_to_clicks(180)){
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
    } else {
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
      if(millis() - sonar_r.lastUse > 30){
        //sonar_data.add(sonar_r.getDistance());
        int dist = sonar_r.getDistance();
        if(dist < 22 && dist > 8){ sonar_bool.add(true);
        } else { sonar_bool.add(false); }

        if(dist < 25 && dist > 8){
          brake(true);
          delay(1000);
          pickUpRight();
          idol_num = 1;
          reverse(7);
        }
      }
    }
  } else if (idol_num == 1){
    if( encoder1.getPos() < cm_to_clicks(80) ){
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
    } else {
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
      if(millis() - sonar_r.lastUse > 30){
        
        int dist = sonar_r.getDistance();
        if(dist < 22){ sonar_bool.add(true);
        } else { sonar_bool.add(false); }

        if(dist < 25 && dist > 8){
          brake(true);
          pickUpRight();
          idol_num = 2;
          delay(1000);
          motor1.powerMotor(15);
          int start = millis();
          while(millis() - start < 3000){
            if(ir1.getValue() > 200 && ir2.getValue() > 200){
              brake1(40, motor1, true);
              var = 1;
              break;
            }
          }
          if(var != 1){
            brake1(10, motor1, true);
          }
          
          delay(1000);
          move(20);
          //delay(1000);
          //rotate(20, false);
          delay(1000);
          idol_num = 2;
          var = 0;
          encoder1.reset();
          encoder2.reset();
          }
        }
      }
  } else if (idol_num == 2){
      IRFollow(pid_ir, 40);
      if(encoder1.getPos() > cm_to_clicks(100)){
        if(millis() - sonar_r.lastUse > 60){
          int dist = sonar_r.getDistance();
          if(dist < 22 && dist > 8){
            move(2);
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
            var = 0;
          }
        }
      }
  } else if (idol_num == 4){
    if(var == 0){
      rotateWide(90, false);
      rotate90(false);
      pid_ir.reset();
      var = 1;
      encoder1.reset();
      encoder2.reset();
    }
    IRFollow(pid_ir, 40);
    if(encoder1.getPos() > cm_to_clicks(100)){
      brake(true);
      idol_num = 69;
      var = 0;
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




// reverse(23);
// encoder1.reset();
// encoder2.reset();
// pid_tape_45.KP = 13;
// while(encoder1.getPos() < cm_to_clicks(30)){
// tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
// }
// brake(true);
// rotateWide(30, false);
// move(10);
// }