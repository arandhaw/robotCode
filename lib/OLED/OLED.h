#ifndef OLED_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define OLED_H
#include <Arduino.h>

void setup_OLED();
void OLED(String str, int num);
void OLED_manuel(int a, int b, int c);
void OLED_manual2(int a, int b, int c);
//any functions you want to use in main program

#endif