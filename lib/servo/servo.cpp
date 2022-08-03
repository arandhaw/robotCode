#include <servo.h>

servo::servo(PinName pin){
    this-> pin = pin;
    current_pwm = -1;
}

void servo::move(int pwm){
    pwm_start(pin, 100, pwm, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); 
    current_pwm = pwm;
}

void servo::moveSlowly(int pwm, int speed){
    if(current_pwm = -1){
        move(pwm);
    } else if(pwm < current_pwm){
        for(int i = pwm; i >= pwm; i--){
            move(i);
            delay(speed);
        }
    } else if(pwm > current_pwm){
        for(int i = pwm; i <= pwm; i++){
            move(i);
            delay(speed);
        }
    }
}