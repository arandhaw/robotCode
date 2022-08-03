#ifndef IR_SENSOR_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define IR_SENSOR_H 

#include <Arduino.h>

// a class for analog Reflectance Sensors.

class IRSensor {
  private:
    int pin;
    int resetpin;
  public:
    IRSensor(int pin, int resetpin);
    int getValue();
};

#endif