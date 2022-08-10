//c++ libraries
#include <cmath>
#include <SoftwareSerial.h>
//self made libraries
#include <Zipline.h>
#include <OLED.h>
#include <Arduino.h>
#include <Encoders.h>
#include <PID.h>
#include <DataBuffer.hpp>
#include <Sonar.h>
#include <IRSensor.h>
#include <servo.h>
#include <DigitalSensor.h>
#include <RunOnce.h>
//program files
#include "Tasks/tasks.h"
#include "Motion/motion.h"
#include "tapeFollow/tapeFollow.h"
#include "tests/tests.h"
#include "IRFollow/IRFollow.h"
//SoftwareSerial myserial(PB11, PB10); //PB11 PB10 works best

Zipline zipline(PA10, PA11); //output pin, input pin
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
PID pid_ir(30, 0, 0, 0);

PID pidsonar(5, 0, 0, 0);
PID pidmotion(40, 0, 0, 0);
PID pidIRFind(15, 0,0,0);

RunOnce a;

void setup(){
  setup_OLED();
  delay(250);
}

int idol_num = 0; //global variable to keep track of state
int chickenWire = 0;
int var = 0; 
int state = 0;
RunOnce zip1, zip2, zip3, zip4;
int timer;
PID pid2(30, 0, 0, 1000);

void loop(){
  if(idol_num == 0){
    while(zip1.once()){
      zipline.send();
      while(zipline.receive() == false){}
      timer = millis();
      pwm_start(PB_6, 100, 16, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //raise arm
    }
    if(millis() - timer < 2000){
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
    } else {
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
      if(millis() - sonar_r.lastUse > 45){
        //sonar_data.add(sonar_r.getDistance());
        int dist = sonar_r.getDistance();

        if(dist < 30 && dist > 8){
          move(2);
          //brake(true);
          delay(1000);
          pickUpRight();
          idol_num = 1;
          encoder1.reset();
          encoder2.reset();
          reverse(5);
        }
      }
    }
  } else if (idol_num == 1){

    if( encoder1.getPos() < cm_to_clicks(80) ){
      if (pid_tape_45.error == -100 && chickenWire == 0) {
        chickenWire = 1;
        brake(true);
        delay(1000);
      } 
      if (chickenWire == 1) {
        rotate(8, false);
        move(18);
        findTape(R1, R2, R3);
        chickenWire = 2;
      } else {
        tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
      }
      
    } else {
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
      if(millis() - sonar_r.lastUse > 30){
        
        int dist = sonar_r.getDistance();
        if(dist < 22){ sonar_bool.add(true);
        } else { sonar_bool.add(false); }

        if(dist < 25 && dist > 8){
          move(2);
          pickUpRight();
          encoder1.reset();
          encoder2.reset();
          reverse(4.5);
          while(zip2.once()){
            zipline.send();
            while(zipline.receive() == false){}
          }
          
          idol_num = 2;
          delay(1500);
          motor1.powerMotor(15);
          int start = millis();
          while(millis() - start < 4000){
          //  if(ir1.getValue() > 200 && ir2.getValue() > 200){
          //     brake1(40, motor1, true);
          //     var = 1;
          //     break;
          //  }
          }
          brake1(35, motor1, true);
          delay(1000);
          encoder1.reset();
          encoder2.reset();
          move(20);
          //delay(1000);
          delay(1000);
          rotate(10, false);
          delay(1000);
           move(12);
          delay(1000);
          idol_num = 2;
          var = 0;
          encoder1.reset();
          encoder2.reset();
          }
        }
      }
  } else if (idol_num == 2){
      while(zip3.once()){
        timer = millis();
        zipline.send();
        while(zipline.receive() == false){}
      }
      // while(ir1.getValue() < 500 && ir2.getValue() < 500){
      //   spin(pidmotion, 10, 15, false);
      //   manualBrake(40, 40, true, false);
      // }
       IRFollow(pid_ir, 40);
      if(millis() - timer > 1000){
        if(millis() - sonar_r.lastUse > 60){
          int dist = sonar_r.getDistance();
          if(dist < 25 && dist > 6){
            move(3.5);
            pickUpRight();
            idol_num = 3;
        }
      }
    }  
  } else if (idol_num == 3){
      if(var == 0){
        rotate90(false);
        delay(1000);
        reverse(2.5);
        encoder1.reset();
        encoder2.reset();
        while(spinWide(2300, 40, false)){}
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
            move(4);
            pickUpRight();
            idol_num = 4;
            var = 0;
          }
        }
      }
  } else if (idol_num == 4){
    if(var == 0){
      //rotate(180, false);
      pid_ir.reset();
      encoder1.reset();
      encoder2.reset();
      // while(ir1.getValue() < 600 && ir2.getValue() < 600){
      //   spin(pidmotion, 10000, 15, false);
      // }
      rotate(190, false);
      //manualBrake(40, 40, true, false);
      var = 1;
      encoder1.reset();
      encoder2.reset();
      
    }
    IRFollow(pid_ir, 40);
    if(encoder1.getPos() > cm_to_clicks(80)){
      brake(true);
      encoder1.reset();
      encoder2.reset();
      
      while(goStraight(pidmotion, cm_to_clicks(18), 10)){}


      idol_num = 5;
      var = 0;
    }
  } else if (idol_num == 5) {
      while(zip4.once()){
        zipline.send();
        while(zipline.receive() == false){}
    }
    idol_num = 69;

  }
   else if (idol_num == 69){
    motor1.powerMotor(0);
    motor2.powerMotor(0);
  }

}

