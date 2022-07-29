#ifndef PID_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define PID_H

#include <wire.h>

// a class for holding the variables for a PID algorithm
class PID{
    public:
        float error; //variables to contain error values
        float sumError;
        float lastError; 
        int lastTime;
        int time;
        float totalSquaredError;

        float var1, var2, var3, var4; //4 extra variables to use as you see fit

        int KP; //constants - specified once
        int KI;
        int KD;
        int I_MAX;

        PID(int KP, int KI, int KD, int I_MAX);
        void reset();
        float iValue();
        float dValue();
        float pValue();
        float PIDValue();
};

#endif