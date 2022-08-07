#include "PID.h"

PID::PID(int KP, int KI, int KD, int I_MAX){
    this->KP = KP;
    this->KI = KI;
    this->KD = KD;
    this->I_MAX = I_MAX;
    reset();
}

void PID::reset(){
    error = 0; //variables to contain error values
    sumError = 0;
    lastError = 0; 
    lastTime = -100;
    time = 0;
    totalSquaredError = 0;

    var1 = 0;
    var2 = 0;
    var3 = 0;
    var4 = 0;
}

float PID::iValue(){
    float iError = KI*sumError;
    if(iError > I_MAX){
        iError = I_MAX;
    } else if(iError < -I_MAX){
        iError = -I_MAX;
    }
    return iError;
}

float PID::dValue(){

    return (error - lastError)/(lastTime - time)*KD;
}

float PID::pValue(){
    return KP*error;
}

float PID::PIDValue(){

    return pValue() + iValue() + dValue();
}