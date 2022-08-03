#include "IRSensor.h"

IRSensor::IRSensor(int pin, int resetpin){
    this-> pin = pin;
    this-> resetpin = resetpin;
    pinMode(resetpin, OUTPUT);
    pinMode(pin, INPUT_ANALOG);
}

int IRSensor::getValue(){
    digitalWrite(resetpin,HIGH);
    delayMicroseconds(1000);   
    digitalWrite(resetpin, LOW);
    delayMicroseconds(1000); 
    int val = analogRead(pin);
    delay(1);
    return val;
}