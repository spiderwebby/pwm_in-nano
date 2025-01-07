#include <Arduino.h>


const int inPin1 = 7;
const int inPin2 = 8;
const int inPin3 = 9;

byte prev_PINB;
byte prev_PIND;

void setup() {
  PCICR  |= B00000101; //pinchange inturupt port B & D (pins 0-13)
  PCMSK0 |= B00011111; //D12-D8 port B
  PCMSK2 |= B11111100; // D7-D2 port D
}

void loop() {
  // put your main code here, to run repeatedly:
}

ISR (PCINT0_vect) //port B isr
{
  
  switch(PINB)    //PINB is the pin values of port B
  case B00000000:
    break;
  case B00000001:

    break;
  case B00000010:

    break;
  case B00000100:

    break;
  case B00001000:

    break;
  case B00010000:

    break;

}

ISR (PCINT2_vect)
{
  
}

