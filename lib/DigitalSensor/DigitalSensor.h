#ifndef DIGITAL_SENSOR_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define DIGITAL_SENSOR_H 

#include <wire.h>

// a class for digital Sensors.

class DigitalSensor {
  private:
    int pin;

  public:
    DigitalSensor(int pin);
    bool getValue();
};

#endif