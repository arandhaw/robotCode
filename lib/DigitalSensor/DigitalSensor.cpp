#include "DigitalSensor.h"

DigitalSensor::DigitalSensor(int pin){
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

bool DigitalSensor::getValue(){
    return digitalRead(pin);
}