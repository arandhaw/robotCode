#ifndef ENCODERS_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define ENCODERS_H
#include <Arduino.h>

void handle_interrupt1();
void handle_interrupt2();

void handle_interrupt3();
void handle_interrupt4();


class Encoder{
    private:
        int pin1, pin2;
        int num;
        void calibrate();
        
    public:
        Encoder(int pin1, int pin2, int num);
        int getAvgSpeed();
        float getSpeed();
        int getPos();
        int getCount();
        void reset();
        void testCounters();
};
#endif