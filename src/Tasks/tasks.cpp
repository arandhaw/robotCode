#include "tasks.h"




void pickUpRight() {
  //PA8 is arm 9 is claw
  pwm_start(PB_7, 100, 22, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //open claw
  delay(1000);
  pwm_start(PB_6, 100, 5, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);  //lower arm
  delay(1000);
  pwm_start(PB_7, 100, 15, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //close claw
  delay(1000);
  pwm_start(PB_6, 100, 16, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //raise arm
  delay(1000);
  pwm_start(PB_7, 100, 22, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT); //open claw
}