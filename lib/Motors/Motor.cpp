#include "Motor.h"

Motor::Motor(int forward_pin, PinName forward_pin_, int reverse_pin, PinName reverse_pin_){
  this->forward_pin  = forward_pin;
      this->reverse_pin = reverse_pin;
      this->forward_pin_  = forward_pin_;
      this->reverse_pin_ = reverse_pin_;
      pinMode(forward_pin, OUTPUT);
      pinMode(reverse_pin, OUTPUT);
      
    }

void Motor::PWM(int dutycycle, PinName pin){
      uint32_t frequency_Hz = 100000; // Maybe change this?
      pwm_start(pin, frequency_Hz, dutycycle,
      TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    }

void Motor::powerMotor(int dutycycle, bool direction){
      if (direction == true){
        PWM(0, reverse_pin_);
        PWM(dutycycle, forward_pin_);
      }
      else{
        PWM(0, forward_pin_);
        PWM(dutycycle, reverse_pin_);
      }
    }