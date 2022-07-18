#include "tapeFollow.h"
#define KP 10
#define KD 0
#define KI 0
#define KI_MAX 10
#define SPEED 45
#define FAIL_LIMIT 500

int lastError = 0; //error in previous cycle

int lastValue = 0; //last error thats not the same
int secondLastValue; //second last error thats not the same

int lastTime = 0; 
int secondLastTime = 0;

int summedError = 0; //error for integral
int totalSquaredError = 0; //a metric for debugging and nothing else
int failSafe = 0; // not currently being used - a failsafe counter

int getError(ReflectSensor R1, ReflectSensor R2, ReflectSensor R3, int lastError){
    bool a = R1.getDigitalValue();
    bool b = R2.getDigitalValue();
    bool c = R3.getDigitalValue();
    
    int val = a*4 + b*2 + c; //convert 3 booleans into number
    if(val == 2){
        return 0;
    } else if(val == 6){
        return -1; 
    } else if(val == 4){
        return -2; //previously -2
    } else if(val == 3){
        return 1; 
    } else if(val == 1){
        return 2; //previously 2
    } else if(val == 0){
        if(lastError > 0)
            return 3; //previously 3
        if(lastError < 0)
            return -3; //previously -3
    }
    return -100;
}

void PID(ReflectSensor R1, ReflectSensor R2, ReflectSensor R3, Motor leftMotor, Motor rightMotor){
    int error = getError(R1, R2, R3, lastError);
    if (error == -100){
        OLED("Indeterminate State", -100); 
        leftMotor.powerMotor(SPEED, true); //make the motors go straight if
        rightMotor.powerMotor(SPEED, true); //error is indeterminate
        //failSafe++;
        //if(failSafe > FAIL_LIMIT){  failure(leftMotor, rightMotor);  }
        return; //early return statement
    } else { failSafe = 0; }

    //updating state variables
    if(error != lastError){
        secondLastTime = lastTime;
        lastTime = micros();
        lastValue = lastError;
    }
    summedError += error;

    //integration error
    int iError = summedError*KI;
    if(iError > KI_MAX)
        iError = KI_MAX;
    if(summedError*KI < KI_MAX)
        iError = -KI_MAX;

    //derivative error
    int dError = round((  (float)(error - lastValue)/(micros() - secondLastTime)   )*KD*1000 );

    int adjustment = error*KP + iError + dError;
    leftMotor.powerMotor(SPEED + adjustment, true);
    rightMotor.powerMotor(SPEED - adjustment, true);

    OLED("Detected error:", error);

    //updating more state variables
    lastError = error;
    totalSquaredError += error*error;
}

void failure(Motor m1, Motor m2){
    m1.powerMotor(0, true);
    m2.powerMotor(0, true);
    while(true){
        OLED("Total squared error:", totalSquaredError);
    }
}

//int round(float num){
  //  return (int)(num < 0 ? (num - 0.5) : (num + 0.5));
//}
