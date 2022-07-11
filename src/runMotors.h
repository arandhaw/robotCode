#ifndef RUN_MOTORS_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define RUN_MOTORS_H

void loop_runMotors();
void setup_runMotors();
void setup_OLED();
void OLED(String str, int num);
//any functions you want to use in main program

#endif