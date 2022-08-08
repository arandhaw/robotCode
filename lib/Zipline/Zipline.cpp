#include "Zipline.h"

Zipline::Zipline(int outputPin, int inputPin){
    pinMode(inputPin, INPUT);
    pinMode(outputPin, OUTPUT);
    this-> inputPin = inputPin;
    this-> outputPin = outputPin;
    inputValue = false;
    outputValue = false;
    
}

void Zipline::send(){
    outputValue = !outputValue;
    if(outputValue == true){
        digitalWrite(outputPin, HIGH);
    } else {
        digitalWrite(outputPin, LOW);
    }
    
}

bool Zipline::receive(){
    if(digitalRead(inputPin) == inputValue){
        return false;
    } else {
        inputValue = !inputValue;
        return true;
    }
    
}