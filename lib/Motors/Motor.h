#ifndef MOTOR_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define MOTOR_H

#include <wire.h>

// a class I created for our motors. It has 1 public function (powerMotor) and 
// stores the pins needed to drive the motor

class Motor {
  private:
    int forward_pin;
    int reverse_pin; 
    PinName forward_pin_;
    PinName reverse_pin_;

    //creates PWM wave at specified pin
    void PWM(int dutycycle, PinName pin);
  public:
    //constructor for motor
    Motor(int forward_pin, PinName forward_pin_, int reverse_pin, PinName reverse_pin_);
    //function that drives motor
    void powerMotor(int dutycycle, bool direction);
};

#endif