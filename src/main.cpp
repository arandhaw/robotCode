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
DigitalSensor left(PB5);
DigitalSensor right(PB4);
Motor motor1(PA0, PA_0, PA1, PA_1); //right motor (slower motor)
Motor motor2(PA2, PA_2, PA3, PA_3); //left motor
Encoder encoder2(PB15, PB14, 2);
Encoder encoder1(PB12, PB13, 1);
Sonar sonar_r(PB3, PA15);
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
RunOnce a;

void setup(){
  setup_OLED();
  delay(250);

}

int idol_num = 0; //global variable to keep track of state
int chickenWire = 0;
int var = 0; 
int state = 0;
RunOnce zip1, zip2, zip3, zip4, zip5, zip6;
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
         // delay(1000);
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
        //delay(1000);
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
          reverse(4.8);
          while(zip2.once()){
            zipline.send();
            while(zipline.receive() == false){}
          }
          
          idol_num = 2;
         // delay(1500);
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
          //delay(1000);
          encoder1.reset();
          encoder2.reset();
          move(20);
          //delay(1000);
         // delay(1000);
          rotate(10, false);
         // delay(1000);
           move(12);
         // delay(1000);
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
        //while(zipline.receive() == false){}
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
            move(4);
            pickUpRight();
            idol_num = 3;
        }
      }
    }  
  } else if (idol_num == 3){
      if(var == 0){
        rotate90(false);
       // delay(1000);
        reverse(1.5);
        encoder1.reset();
        encoder2.reset();
        while(spinWide(2350, 40, false)){}
        brake1(80, motor1, true);
       // delay(1000);
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
        //Do double wheel spin turn
        //do edge bounce manouver
        //wait for some encoder distance
        //double wheel rotate left
        //detect with sonar
    }
    idol_num = 6;

  }
   else if (idol_num == 69){
    motor1.powerMotor(0);
    motor2.powerMotor(0);

  } else if( idol_num == 6){
    delay(2500);
    while(right.getValue() == 1){  test_edge(); }
    zipline.send();
    while(zipline.receive() == false){}
    idol_num = 7;

  } else if (idol_num == 7){
    reverse(12);
    zipline.send();
    while(zipline.receive() == false){}
    move(7);
    delay(1000);
    while(spinWide(10000, 30, false)){
      // if(millis() - sonar_r.lastUse > 60){
      //     int dist = sonar_r.getDistance();
      //     if(dist < 25 && dist > 8){
      //       rotateWide(15, false);
      //       pickUpRight();
      //       idol_num = 6;
      //       break;
      //     }
      // }
      if(right.getValue() == 1){
        brake1(60, motor1, true);
        delay(1000);
        pickUpRight();
        idol_num = 6;
        break;
      }
    }
    rotateWide2(120, false); //changed from 120 t0 125
  } else if(idol_num == 6){  //going up the bridge
    encoder1.reset();
    encoder2.reset();
    while(encoder1.getPos() < cm_to_clicks(15)){
      goStraight(pidmotion, 1000, 30);
    }
    while (encoder1.getPos() < cm_to_clicks(130)) {
      zigzag(28, 11, 1250);
    }
    while(encoder1.getPos() < cm_to_clicks(165)){
      zigzag2(28, 11, 1000);
    }
    brake(true);
    delay(1000);
    move(20); //originally 15
    // rotate(5, true);
    // delay(1000);
    // move(25);
    //while(goStraight(pidmotion, 180, 30)){}
    //brake(true);
    idol_num = 7;
  } else if(idol_num == 7) { 
    rotateWide(30, false);
    delay(1000);
    while(spinWide(5000, 20, false)) {
      if(millis() - sonar_r.lastUse > 60){
        int dist = sonar_r.getDistance();
          if(dist < 17 && dist > 8){
            rotateWide(10, false);
            pickUpGold();
            break;
          }
      }
    }
    delay(1000);
    //reverse(5); //changed from 3 to 5
    //delay(1000);
    //rotate(30, false);
    //delay(1000);
    //reverse(10);
    //delay(1000);
    //rotate(150, false);
    rotate(90, true);
    delay(500);
    move(7);
    delay(500);
    rotate(90, true);
    delay(1000);
    reverse(18);
    delay(1500);
    zipline.send();
    while(zipline.receive() == false){}
    //while(goStraight(pidmotion, cm_to_clicks(4), 10)){}
    int start = millis();
    while (millis() - start < 2000) {
        motor1.powerMotor(15);
        motor2.powerMotor(15);
    }
    motor1.powerMotor(0);
    motor2.powerMotor(0);
    //manualBrake(30, 30, false, false);
    zipline.send();
    idol_num = 69;
  }

  //end of course
}

