#ifndef REFLECT_SENSOR_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define REFLECT_SENSOR_H 

#include <wire.h>
#define THRESHOLD 500

// a class for analog Reflectance Sensors.

class ReflectSensor {
  private:
    int pin;

  public:
    ReflectSensor(int pin);

    int getRawValue();
    //returns a digital value (1, 0) based on the threshold
    bool getDigitalValue();
};

#endif