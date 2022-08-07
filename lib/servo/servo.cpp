#include <servo.h>

servo::servo(PinName pin){
    this-> pin = pin;
    current_pwm = -1;
}

void servo::move(int pwm){
    pwm_start(pin, 100, pwm, TimerCompareFormat_t::RESOLUTION_12B_COMPARE_FORMAT); 
    current_pwm = pwm;
}

void servo::moveSlowly(int pwm, int millis){
    int start_pos = current_pwm;
    if(start_pos == -1){
        move(pwm);
    } else if(pwm < start_pos){
        for(int j = start_pos; j >= pwm; j--){
            move(j);
            delay(millis);
        }
    } else if(pwm > start_pos){
        for(int j = start_pos; j <= pwm; j++){
            move(j);
            delay(millis);
        }
    }
}