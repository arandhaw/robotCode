#ifndef HELPER_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define HELPER_H 

#include <wire.h>


// a class for analog Reflectance Sensors.


int cm_to_clicks(float cm);
float clicks_to_cm(int clicks);

#endif
