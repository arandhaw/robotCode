//c++ libraries
#include <cmath>
//self made libraries
#include <OLED.h>
#include <Motor.h>
#include <Arduino.h>
#include <Encoders.h>
#include <PID.h>
#include <ReflectSensor.h>
#include <DataBuffer.hpp>
#include <Sonar.h>
#include <IRSensor.h>
#include <servo.h>
#include <DigitalSensor.h>
//program files
// #include "sweep.h"


//SoftwareSerial myserial(PB11, PB10); //PB11 PB10 works best

// #include "runMotors.h" 
// #include "testMotors.h" 
//Servo myservo;
#define OUTPUT_PIN PA10

Motor upMotor(PA2, PA_2, PA3, PA_3); //right motor (slower motor)
Motor zipMotor(PA0, PA_0, PA1, PA_1); //left motor
//Encoder encoder(PB15, PB14, 2);
DigitalSensor topSwitch(PB8);
DigitalSensor bottomSwitch(PB7);
DigitalSensor bluepill(PA9);

int state;
bool inputValue;
bool outputValue;

void raiseZipline();
void lowerZipline();
void setZipline(int time);
void sendMessage();
void ride();

//setup function
void setup(){
  //delay(4000);
  //digitalWrite(OUTPUT_PIN, false); //initialize output pin
  inputValue = false;
  state = 0;
  lowerZipline();
  while(true){
    
    delay(1000);
  // delay(2000);
  // lowerZipline();
  // delay(2000);
  }
}

//main loop for program
void loop(){
  if(bluepill.getValue() != inputValue){
    state++;
    inputValue = bluepill.getValue();
  }

}


void raiseZipline(){
  upMotor.powerMotor(100);
  int start = millis();
  while(true){
    if(topSwitch.getValue() == true){
      upMotor.powerMotor(0);
      break;
    }
  }
}


void lowerZipline(){
  upMotor.powerMotor(-100);
  int start = millis();
  while(true){
    if(bottomSwitch.getValue() == true){
      upMotor.powerMotor(0);
      break;
    }
  }
}

void setZipline(int time){
  lowerZipline();
  int start = millis();
  while(millis() - start < time){
    upMotor.powerMotor(100);
  }
  upMotor.powerMotor(0);
}

void ride(){
  zipMotor.powerMotor(100);
}

void sendMessage(){
  bool value = digitalRead(OUTPUT_PIN);
  digitalWrite(OUTPUT_PIN, !value);
}

