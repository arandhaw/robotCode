#ifndef SONAR_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define SONAR_H 

#include <wire.h>

// a class for analog Reflectance Sensors

class Sonar {
  private:
    int trigPin;
    int echoPin;
    

  public:
    int lastUse;
    Sonar(int trigPin, int echoPin);
    int getDistance();
    int getAdjustment(int distance);
    
};

#endif