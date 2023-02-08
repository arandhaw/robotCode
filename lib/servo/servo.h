#ifndef MYSERVO_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define MYSERVO_H 


// a class for analog Reflectance Sensors.
#include <Arduino.h>

class servo {
  private:
    PinName pin;

  public:
    int current_pwm;
    servo(PinName pin);
    void move(int pwm);
    void moveSlowly(int pwm, int millis);
};

#endif