#include "Zipline.h"

Zipline::Zipline(int outputPin, int inputPin){
    pinMode(inputPin, INPUT);
    pinMode(outputPin, OUTPUT);
    this-> inputPin = inputPin;
    this-> outputPin = outputPin;
    inputValue = LOW;
    outputValue = LOW;
    
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
    bool read1 = digitalRead(inputPin);
    delay(1);
    bool read2 = digitalRead(inputPin);
    if(read1 != inputValue && read2 != inputValue){
        inputValue = !inputValue;
        return true;
    } else {   
        return false;
    }
    
}