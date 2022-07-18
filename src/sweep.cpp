#include "sweep.h"

void sweep(Servo servo1){
    servo1.write(0);
    delay(500);
    servo1.write(90);
    delay(500);
    servo1.write(180);
    delay(500);
}