//C++ libraries
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
#include "Claw/Claw.h"
#include "Motion/motion.h"
#include "TapeFollow/tapeFollow.h"
#include "Tests/tests.h"
#include "IRFollow/IRFollow.h"
//SoftwareSerial myserial(PB11, PB10); //to communicate with bluepill

Zipline zipline(PA10, PA11); //output pin, input pin
ReflectSensor R1(PA7); //left
ReflectSensor R2(PA6); //middle
ReflectSensor R3(PA5); //right
DigitalSensor left(PB5);
DigitalSensor right(PB4);
Motor motor1(PA0, PA_0, PA1, PA_1); //right motor
Motor motor2(PA2, PA_2, PA3, PA_3); //left motor
Encoder encoder2(PB15, PB14);
Encoder encoder1(PB12, PB13);
Sonar sonar_r(PB3, PA15);
IRSensor ir1(PB0, PA8);
IRSensor ir2(PB1, PA8);
servo arm(PB_6);
servo claw(PB_7);
DigitalSensor hall(PA12); //change
DataBuffer<bool> sonar_bool(50, 0);
DataBuffer<int> sonar_data(5, 100);
PID pid_tape_45(10, 0, 5, 0); //set parameters for PID algorithms
PID pid_ir(30, 0, 0, 0);
PID pidmotion(40, 0, 0, 0);
PID pid2(30, 0, 0, 1000);

void setup(){
  setup_OLED();
  delay(250);
}

int state = 0; //decides state of robot
int timer; //to store time variables
//for blocks of code that must run only once
RunOnce zip1, zip2, zip3, zip4, zip5, zip6, var1, var2, chicken;

void loop(){

  //raise zipline then start tapefollowing up hill, pick up first idol
  if(state == 0){
    while(zip1.once()){
      zipline.send();
      while(zipline.receive() == false){}
      arm.move(620); //raise arm
      timer = millis();
    }
    if(millis() - timer < 2000){
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
    } else {
      tapeFollow(pid_tape_45, 45, R1, R2, R3, motor1, motor2);
      if(millis() - sonar_r.lastUse > 45){
        int dist = sonar_r.getDistance();

        if(dist < 30 && dist > 8){
          move(2);
          pickUpRight();
          state = 1;
          encoder1.reset();
          encoder2.reset();
          reverse(5);
        }
      }
    }

  //cross chickenwire bridge, pick up 2nd idol, go under arch
  } else if (state == 1){
    if( encoder1.getPos() < cm_to_clicks(80) ){
      if (pid_tape_45.error == -100 && chicken.once() == true) {
        rotate(8, false);
        move(18);
        findTape(R1, R2, R3);
        
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
          }
          motor1.powerMotor(15);
          int start = millis();
          while(millis() - start < 4000){}
          brake1(35, motor1, true);
          while(zipline.receive() == false){}
          encoder1.reset();
          encoder2.reset();
          move(20);
          rotate(10, false);
          move(12);
          state = 2;
          encoder1.reset();
          encoder2.reset();
          }
        }
      }

  //begin following Infrared beacon - raise zipline arm
  } else if (state == 2){
      while(zip3.once()){
        timer = millis();
        zipline.send();
      }
       IRFollow(pid_ir, 40);
      if(millis() - timer > 1500){
        if(millis() - sonar_r.lastUse > 60){
          int dist = sonar_r.getDistance();
          if(dist < 25 && dist > 6){
            move(4.5);
            pickUpRight();
            state = 3;
        }
      }
    }  

  //turn around and move towards 4th idol
  } else if (state == 3){
      if(var1.once()){
        rotate90(false);
        reverse(6);
        encoder1.reset();
        encoder2.reset();
        while(spinWide(2400, 40, false)){}
        brake1(80, motor1, true);
        encoder1.reset();
        encoder2.reset();
      }
      goStraight(pid2, cm_to_clicks(200), 40);
      if(encoder1.getPos() > cm_to_clicks(30)){
        if(millis() - sonar_r.lastUse > 60){
          int dist = sonar_r.getDistance();
          if(dist < 25 && dist > 8){
            move(4);
            pickUpRight();
            state = 4;
          }
        }
      }

  //turn around and head toward zipline
  } else if (state == 4){
    if(var2.once()){
      pid_ir.reset();
      encoder1.reset();
      encoder2.reset();
      rotate(190, false);
      encoder1.reset();
      encoder2.reset(); 
    }
    IRFollow(pid_ir, 40);
    if(encoder1.getPos() > cm_to_clicks(80)){
      brake(true);
      encoder1.reset();
      encoder2.reset();
      
      while(goStraight(pidmotion, cm_to_clicks(25), 10)){}
      state = 5;
    }

  //ascend zipline
  } else if (state == 5) {
      while(zip4.once()){
        zipline.send();
        while(zipline.receive() == false){}
    }
    state = 6;
  //send zipline message once edge is seen
  } else if( state == 6){
    delay(1000);
    while(right.getValue() == 1){  test_edge(); }
    zipline.send();
    while(zipline.receive() == false){}
    state = 7;
  
  //dismount from zipline, begin manouvers for 5th idol
  } else if (state == 7){
    reverse(12);
    zipline.send();
    while(zipline.receive() == false){}
    move(7);
    delay(500);
    while(spinWide(10000, 30, false)){
      if(right.getValue() == 1){
        brake1(60, motor1, true);
        delay(500);
        pickUpRight();
        state = 8;
        break;
      }
    }
    rotateWide2(120, false);

  //going up the bridge with edge detection
  } else if(state == 8){  
    encoder1.reset();
    encoder2.reset();
    while (encoder1.getPos() < cm_to_clicks(177)) {
      theChristian(pidmotion, 3, 0, encoder1, encoder2);
    }
    brake(true);
    delay(500);
    state = 9;

  //pick up the golden idol and mount second zipline
  } else if(state == 9) { 
    rotateWide(30, false);
    delay(500);
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
    rotate(90, true);
    delay(250);
    move(7);
    delay(250);
    rotate(90, true);
    delay(250);
    reverse(18.5);
    delay(750);
    zipline.send();
    while(zipline.receive() == false){}
    int start = millis();
    while (millis() - start < 2000) {
        motor1.powerMotor(15);
        motor2.powerMotor(15);
    }
    motor1.powerMotor(0);
    motor2.powerMotor(0);
    zipline.send();
    state = 99;
  }

  //end of course
  else if (state == 99){
    motor1.powerMotor(0);
    motor2.powerMotor(0);
  }
}