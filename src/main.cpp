#include <Arduino.h>


const int inPin1 = 7;
const int inPin2 = 8;
const int inPin3 = 9;



void setup() {
  PCICR  |= B00000101; //pinchange inturupt port B & D (pins 0-13)
  PCMSK0 |= B00011111; //D12-D8 port B
  PCMSK2 |= B11111100; // D7-D2 port D
}

void loop() {
  // put your main code here, to run repeatedly:
}

ISR (PCINT0_vect)
{
  
}

ISR (PCINT2_vect)
{
  
}

