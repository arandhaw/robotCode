#ifndef IR_Sensor_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define IR_sensor__H 

#include <wire.h>
#define THRESHOLD 250 //Changed to 200

// a class for analog Reflectance Sensors.

class IRSensor {
  private:
    int pin;

  public:
    IRSensor(int pin);

    int getRawValue();
    //returns a digital value (1, 0) based on the threshold
    bool getDigitalValue();
};

#endif