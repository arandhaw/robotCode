#ifndef ZIPLINE_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define ZIPLINE_H 


// a class for analog Reflectance Sensors.
#include <wire.h>

class Zipline {
  private:
    int inputPin;
    int outputPin;

  public:
    Zipline(int inputPin, int outputPin);
    void send();
    void receive();
};

#endif