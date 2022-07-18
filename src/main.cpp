//Test new Branch
#include "tapeFollow.h"
#include <OLED.h>
#include <Arduino.h>
#include "sweep.h"
// #include <Encoders.h>
// #include "runMotors.h" 
// #include "testMotors.h" 
volatile int enc = 0;
volatile int enc2 = 0;
volatile int enc3 = 0;
volatile int enc4 = 0;
ReflectSensor R1(PA6); //left
ReflectSensor R2(PA5); //middle
ReflectSensor R3(PA4); //right
Motor motor1(PA0, PA_0, PA1, PA_1); //right motor (slower motor)
Motor motor2(PA2, PA_2, PA3, PA_3); //left motor
// Encoder encoder1(PB8, PB9, 1);
// Encoder encoder2(PB12, PB13, 2);
Servo myservo;

void handle_interrupt(){
  enc++;
}
void handle_interrupt2(){
  enc2++;
}
void handle_interrupt3(){
  enc3++;
}
void handle_interrupt4(){
  enc4++;
}

void setup(){
  attachInterrupt(digitalPinToInterrupt(PB8), handle_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(PB9), handle_interrupt2, RISING);
  attachInterrupt(digitalPinToInterrupt(PB12), handle_interrupt3, RISING);
  attachInterrupt(digitalPinToInterrupt(PB13), handle_interrupt4, RISING);
  setup_OLED(); //4 seconds of delay within this function
  //setup_runMotors();
  //myservo.attach(PA1);
}

void loop(){
  int start = millis();
  //sweep();
  // PID(R1, R2, R3, motor2, motor1); 
  //OLED_manual(encoder1.getPosition(), encoder2.getPosition(), 0);
  OLED_manual(enc, enc2, enc3, enc4);
  // while(millis() - start < 1000){
  //   OLED_manual(enc, enc2, enc3, enc4);
  //   motor1.powerMotor(40, true);
  //   motor2.powerMotor(40, true);
  // }
  // while(millis() - start < 2000){
  //   OLED_manual(enc, enc2, enc3, enc4);
  //motor1.powerMotor(0, true);
  motor2.powerMotor(0, true);
  // }

  //encoder2.getSpeed();
  //OLED_manual2(R1.getRawValue(), R2.getRawValue(), R3.getRawValue());
  
}