#include <helper.h>

int cm_to_clicks(float cm){
  return round( 140*cm );
}

float clicks_to_cm(int clicks){
  return (float) clicks/140 ;
}