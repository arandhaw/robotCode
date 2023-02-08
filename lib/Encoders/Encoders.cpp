#include "Encoders.h"


Encoder::Encoder(int pin1, int pin2)
    :  times(5, 0) //initialize DataBuffer object
{
    this-> pin1 = pin1;
    this-> pin2 = pin2;
    attachInterrupt(digitalPinToInterrupt(pin1), std::bind(&Encoder::ISR, this), RISING);
    reset();
}

//interrupt service routine
void Encoder::ISR(){ 
    count++;
    times.add(micros());

    if(digitalRead(pin2) == false){
        pos++;
        dir = true;
    } else {
        pos--;
        dir = false;
    }
}

void Encoder::reset(){
    count = 0;
    pos = 0; 
    times.reset(0);
}

int Encoder::getPos(){
    return pos;
}

int Encoder::getCount(){
    return count;
}

bool Encoder::getDir(){
    return dir;
}

float Encoder::getSpeed(){
    int t1, t2;
    bool direction;

    noInterrupts();
    t1 = times.get(0);
    t2 = times.get(4); //time between pulses in microseconds
    direction = dir;
    interrupts();

    int dt = t1 - t2;

    if(micros() - t1 > TIME_LOWER_BOUND || t2 == 0){ //if time since last pulse is large, return 0
        return 0;                         //return zero while t2 is same as initialization
    }
    float speed = (float) SPEED_FACTOR/dt; //default is clicks per 10 ms

    if(direction == true){  return speed;  } 
    else {  return -speed;  }
}

//destructor
Encoder::~Encoder(){
    detachInterrupt(digitalPinToInterrupt(pin1));
}