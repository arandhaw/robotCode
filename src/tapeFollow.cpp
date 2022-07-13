#include "tapeFollow.h"
#define KP 10
#define KD 0
#define KI 0
#define KI_MAX 10
#define SPEED 42
#define FAIL_LIMIT 500

int lastError = 0;
int summedError = 0;
int dError = 0; 
int totalSquaredError = 0;
int failSafe = 0;

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
        return -2;
    } else if(val == 3){
        return 1;
    } else if(val == 1){
        return 2;
    } else if(val == 0){
        if(lastError == 2)
            return 3;
        if(lastError == -2)
            return -3;
        if(lastError == 3)
            return 3;
        if(lastError == -3)
            return -3;
    }
    return -100;
}

void PID(ReflectSensor R1, ReflectSensor R2, ReflectSensor R3, Motor leftMotor, Motor rightMotor){
    int error = getError(R1, R2, R3, lastError);
    // if (error == -100){
    //     OLED("Indeterminate State", -100);
    //     failSafe++;
    //     if(failSafe > FAIL_LIMIT){  failure(leftMotor, rightMotor);  } //Mayvb comment out
    //     return;
    // } else { failSafe = 0; }

    dError = error - lastError;
    summedError += error;
    int iError = summedError*KI;
    if(iError > KI_MAX)
        iError = KI_MAX;
    if(summedError*KI < KI_MAX)
        iError = -KI_MAX;

    int adjustment = error*KP + iError + dError*KD;
    leftMotor.powerMotor(SPEED + adjustment, true); //Switched + and - direction
    rightMotor.powerMotor(SPEED - adjustment, true); //Switched + and - direction

    OLED("Detected error:", error);
    //OLED_manuel(error, adjustment, 0);
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
