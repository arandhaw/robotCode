#include "Encoders.h"
#include <OLED.h>


int pin1;

volatile int count1 = 0;
volatile int count2 = 0;
volatile int count3 = 0;
volatile int count4 = 0;

volatile int pos1 = 0;
volatile int pos2 = 0;

volatile int lastTime1 = 1000; 
volatile int secondLastTime1 = 0; 
volatile int lastTime2 = 1000; 
volatile int secondLastTime2 = 0; 

volatile bool b1 = false;
volatile bool b2 = false;
volatile bool b3 = false;
volatile bool b4 = false;
volatile bool dir1;
volatile bool dir2;

void handle_interrupt1(){
    count1++;
    if(count1 % 10 == 0){ //count the time every 10 pulses
        secondLastTime1 = lastTime1;
        lastTime1 = micros();
    }

    bool val = digitalRead(PB13);

    if(val == false){
        pos1++;
        dir1 = true;
    } else if(val == true){
        pos1--;
        dir1 = false;
    }
}
void handle_interrupt2(){
    // count2++;
    // b2 = !b2;
}
void handle_interrupt3(){
    count3++;
    if(count3 % 10 == 0){ //count the time every 10 pulses
        secondLastTime2 = lastTime2;
        lastTime2 = micros();
    }

    bool val = digitalRead(PB14);

    if(val == false){
        pos2++;
        dir2 = true;
    } else if(val == true){
        pos2--;
        dir2 = false;
    }
}
void handle_interrupt4(){
    // count4++;
    // b4 = !b4;
}

Encoder::Encoder(int pin1, int pin2, int num) {
    this-> pin1 = pin1;
    this-> pin2 = pin2;
    this-> num = num;

    //declare interrupt pins, define interrupt function
    if(num == 1){
        attachInterrupt(digitalPinToInterrupt(pin1), handle_interrupt1, RISING);
        // attachInterrupt(digitalPinToInterrupt(pin2), handle_interrupt2, CHANGE);
    }

    if(num == 2){
        attachInterrupt(digitalPinToInterrupt(pin1), handle_interrupt3, RISING);
        // attachInterrupt(digitalPinToInterrupt(pin2), handle_interrupt4, CHANGE);
    }
    // calibrate();
    reset();
}

//calibrates encoder
void Encoder::calibrate(){
    if(num == 1){
        int c1, c2;
        do{
            c1 = count2;
            int state = digitalRead(pin2);
            if(state == HIGH){
                b2 = true;
            } else { b2 = false; }
            c2 = count2;
        } while(c1 != c2);
    }

    if(num == 2){
        int c1, c2;
        do{
            c1 = count4;
            int state = digitalRead(pin2);
            if(state == HIGH){
                b4 = true;
            } else { b4 = false; }
            c2 = count4;
        } while(c1 != c2);
    } 
}
void Encoder::reset(){
    count1 = 0;
    count2 = 0;
    count3 = 0;
    count4 = 0;

    pos1 = 0;
    pos2 = 0;

    lastTime1 = 1000; 
    secondLastTime1 = 0; 
    lastTime2 = 0; 
    secondLastTime2 = 1000; 
}

float Encoder::getSpeed(){
    int dt;
    bool direction;
    float timeSinceLastClick;
    if(num == 1){   
        noInterrupts();
        dt = lastTime1 - secondLastTime1; //time between pulses in microseconds
        timeSinceLastClick = lastTime1;
        interrupts();
        direction = dir1;
        
    } if(num == 2){
        noInterrupts();
        dt = lastTime2 - secondLastTime2; //time between pulses in microseconds
        timeSinceLastClick = lastTime2;
        interrupts();
        direction = dir2;
        
    }
    if(micros() - timeSinceLastClick > 50000){
        return 0; 
    }
    float speed = (float) 100000/dt; //speed in clicks per 10 ms
    if(direction == true){
        return speed;
    } else {
        return -speed; //speed in clicks per 10 ms
    }
}

//gives speed of encoder. takes 10 milliseconds to run
int Encoder::getAvgSpeed(){
    int startTime = millis();
    int startPos = getPos();
    int endPos;
    while( millis() - startTime < 10 ){} //pause without delay for 10 milliseconds
    endPos = getPos();
    return (endPos - startPos); //speed = dist/time -> pings per 10 ms
}

int Encoder::getPos(){
    int pos;
    if(num == 1){
        noInterrupts();
        pos = pos1;
        interrupts();
    }
    if(num == 2){
        noInterrupts();
        pos = pos2;
        interrupts();
    }
    return pos;
}

int Encoder::getCount(){
    int count;
    if(num == 1){
        noInterrupts();
        count = count1;
        interrupts();
    }
    if(num == 2){
        noInterrupts();
        count = count3;
        interrupts();
    }
    return count;
}

void Encoder::testCounters(){
    OLED_manual(count1, count2/2, count3, count4/2);
}
