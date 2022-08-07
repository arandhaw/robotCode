#include "tapeFollow.h"

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

void tapeFollow(PID &pid, int speed, ReflectSensor R1, ReflectSensor R2, ReflectSensor R3, Motor leftMotor, Motor rightMotor){
    pid.error = getError(R1, R2, R3, pid.lastError);
    if (pid.error == -100){
        OLED("Indeterminate State", -100); 
        leftMotor.powerMotor(speed, true); //make the motors go straight if
        rightMotor.powerMotor(speed, true); //error is indeterminate
        //failSafe++;
        //if(failSafe > FAIL_LIMIT){  failure(leftMotor, rightMotor);  }
        return; //early return statement
    }

    //updating state variables
    if(pid.error != pid.lastError){
        pid.lastTime = pid.time;
        pid.time = micros();
        pid.var1 = pid.lastError;
    }
    pid.sumError += pid.error;

    //derivative error
    int dValue = round((  (float)(pid.error - pid.var1)/(micros() - pid.lastTime)   )*pid.KD*1000 );

    int adjustment = pid.error*pid.KP + pid.iValue() + dValue;
    leftMotor.powerMotor(speed + adjustment, true);
    rightMotor.powerMotor(speed - adjustment, true);

    OLED("Detected error:", pid.error);

    //updating more state variables
    pid.lastError = pid.error;
    pid.totalSquaredError += pid.error*pid.error;
}

void failure(Motor m1, Motor m2){
    m1.powerMotor(0, true);
    m2.powerMotor(0, true);
}


//int round(float num){
  //  return (int)(num < 0 ? (num - 0.5) : (num + 0.5));
//}
