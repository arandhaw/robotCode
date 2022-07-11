#include "ReflectSensor.h"

ReflectSensor::ReflectSensor(int pin){
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

int ReflectSensor::getRawValue(){
    return analogRead(pin);
}

//returns a digital value (1, 0) based on the threshold
bool ReflectSensor::getDigitalValue(){
    int value = getRawValue();
    if (value >= THRESHOLD){ return 1; } 
    else { return 0; }
}