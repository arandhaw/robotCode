#ifndef ENCODER_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define ENCODER_H
#include <Arduino.h>
#include <DataBuffer.hpp>

#define SPEED_FACTOR 100000    //numerator in speed calculation (micros)
#define TIME_LOWER_BOUND 20000   //time between pulses before speed is declared 0 (micros)

//made as a better version of my original encoder class
class Encoder{
    private:
        int pin1, pin2;
        volatile int count, pos;  
        bool dir;
        DataBuffer<int> times; //holds times to determine speed
        void ISR();

    public:
        Encoder(int pin1, int pin2);
        void reset();  //reset encoder
        int getPos();  //get position (+/-)
        int getCount(); //get total clicks received (distance)
        bool getDir();  //get direction
        float getSpeed(); //calculates speed - can be +/-
        ~Encoder(); //destructor
};
#endif