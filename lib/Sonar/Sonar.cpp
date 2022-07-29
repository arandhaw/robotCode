#include "Sonar.h"

Sonar::Sonar(int trigPin, int echoPin){
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    lastUse = millis() - 60;
}

int Sonar::getDistance(){
  int duration;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  lastUse = millis();
  return ((duration/2) / 29.1);
}