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
#include "helper.h"


//SoftwareSerial myserial(PB11, PB10); //PB11 PB10 works best

// #include "runMotors.h" 
// #include "testMotors.h" 
//Servo myservo;
#define OUTPUT_PIN PA11
#define INPUT_PIN PA10

Motor upMotor(PA2, PA_2, PA3, PA_3); //motor for raising zipline
Motor zipMotor(PA1, PA_1, PA0, PA_0); //motor at the top
Encoder encoder(PB6, PB5, 1);
DigitalSensor topSwitch(PB8);
DigitalSensor bottomSwitch(PB7);
DigitalSensor bluepill(PA10);

bool inputValue;
bool outputValue;

void raiseZipline(int pwm);
void lowerZipline(int pwm);
void setZipline(int time);
void rideZipline(int dist);
void sendMessage();
void raiseTime(int time);
void lowerTime(int time);
void ride();
void doZipline();
//setup function

int state = 7;

void setup(){
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW); //initialize output pin
  inputValue = false;
  delay(1000);
  if(state == 7){
    raiseZipline(50); // remove later
    delay(3000);
  }
  
}


//main loop for program
void loop(){
  if(bluepill.getValue() != inputValue){
    delay(1);
    if(bluepill.getValue() != inputValue){
      state++;
      inputValue = !inputValue;
      delay(10);
      //OLED("I'm seeing something", state);
    }
  }
  
  if(state == 1){
    raiseZipline(50);
    sendMessage();
    state = 2;
  } else if(state == 3){
    lowerZipline(50);
    sendMessage();
    state = 4;
  } else if(state == 5){
    raiseZipline(50);
    sendMessage();
    state++;
  } else if(state == 7){
    lowerTime(2000);
    zipMotor.powerMotor(100);
    delay(2000);
    sendMessage();
    state++;
  } else if (state == 8){
    zipMotor.powerMotor(100);
  } else if(state == 9){
    encoder.reset();
    rideZipline(28);
    zipMotor.powerMotor(0);
    delay(500);
    raiseZipline(50);
    sendMessage();
    state++;
  } else if(state == 11){
    lowerTime(3150);
    sendMessage();
    state++;
  } else if(state == 13){
    raiseZipline(50);
    sendMessage();
    state++;
  } else if(state == 15){
    lowerTime(3500);
    rideZipline(220);
    state++;

  } else {
    upMotor.powerMotor(0);
    zipMotor.powerMotor(0);
  }
  //OLED("messages:", state);

}


void doZipline(){
  lowerTime(2000);
  delay(1000);
  rideZipline(110); 
  delay(1000);
  raiseZipline(50); 
}


void raiseZipline(int pwm){
  int start = millis();
  while(true){
    if(topSwitch.getValue() == true){
      delayMicroseconds(10);
      if(topSwitch.getValue() == true){
        upMotor.powerMotor(0);
        break;
      }
      } else {
        upMotor.powerMotor(pwm);
      } 
    }
    start = millis();
    while(millis() - start < 20){
      upMotor.powerMotor(-100);
    }
    upMotor.powerMotor(0);
}

void raiseTime(int time){
  int start = millis();
  while(millis() - start < time){
    if(topSwitch.getValue() == true){
      delayMicroseconds(10);
      if(topSwitch.getValue() == true){
        upMotor.powerMotor(0);
        break;
      }
      } else {
        upMotor.powerMotor(100);
      } 
    }
    start = millis();
    while(millis() - start < 20){
      upMotor.powerMotor(-100);
    }
    upMotor.powerMotor(0);
}

void lowerTime(int time){
  int start = millis();
  while(millis() - start < time){
    if(bottomSwitch.getValue() == true){
      delayMicroseconds(10);
      if(bottomSwitch.getValue() == true){
        upMotor.powerMotor(0);
        break;
      }
      } else {
        upMotor.powerMotor(-100);
      } 
    }
    start = millis();
    while(millis() - start < 20){
      upMotor.powerMotor(100);
    }
    upMotor.powerMotor(0);
}

void lowerZipline(int pwm){
  
  int start = millis();
  while(true){
    if(bottomSwitch.getValue() == true){
      delayMicroseconds(10);
      if(bottomSwitch.getValue() == true){
        upMotor.powerMotor(0);
        break;
      }
    } else {
      upMotor.powerMotor(-pwm);
    }
  }


}

// void setZipline(int time){
//   lowerZipline();
//   int start = millis();
//   while(millis() - start < time){
//     upMotor.powerMotor(100);
//   }
//   upMotor.powerMotor(0);
// }

void rideZipline(int dist){
  encoder.reset();
  while(encoder.getCount() < cm_to_clicks(dist)){
    zipMotor.powerMotor(100);
  }
  zipMotor.powerMotor(0);
}

void sendMessage(){
  bool value = digitalRead(OUTPUT_PIN);
  digitalWrite(OUTPUT_PIN, !value);
}

