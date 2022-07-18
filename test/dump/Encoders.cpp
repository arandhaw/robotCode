#include "Encoders.h"

volatile int position1 = 0;
volatile int position2 = 0;
volatile int position3 = 0;
volatile int position4 = 0;
volatile int i = 0;

void handle_interrupt1(){
    position1++;
    i++;
}
void handle_interrupt2(){
    position2++;
    i++;
}
void handle_interrupt3(){
    position3++;
    i++;
}
void handle_interrupt4(){
    position4++;
    i++;
}

Encoder::Encoder(int pin1, int pin2, int num) {
    this-> pin1 = pin1;
    this-> pin2 = pin2;
    this-> num = num;

    //declare interrupt pins, define interrupt function
    if(num == 1){
        attachInterrupt(digitalPinToInterrupt(pin1), handle_interrupt1, RISING);
        attachInterrupt(digitalPinToInterrupt(pin2), handle_interrupt2, RISING);
    }

    if(num == 2){
        attachInterrupt(digitalPinToInterrupt(pin1), handle_interrupt3, RISING);
        attachInterrupt(digitalPinToInterrupt(pin2), handle_interrupt4, RISING);
    }
}
int Encoder::getSpeed(){
    int startTime = millis();
    int startPos = getPosition();
    int endPos;
    while( millis() - startTime < 10 ){} //pause without delay for 10 milliseconds
    endPos = getPosition();
    return (endPos - startPos)*100; //speed = dist/time -> pings/second
}
int Encoder::getPosition(){
    if(num == 1)
        return position1;
    if(num == 2)
        return position3;
    return 0;
}