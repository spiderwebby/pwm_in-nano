#include <Arduino.h>


const int maxReadingAge = 5000; //5ms
volatile bool prev_pinvalue[15];
volatile unsigned int pinmicros[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//volatile unsigned int pin_high_time[15];

byte prev_PINB;
byte prev_PIND;

//! could probably merge the two for()'s by adding an "if(i<7) i=9;" or whatever

//these are defined *elsewhere ooooOOOOooo*
//we have to work out which pin changed, and if it's falling or rising
ISR (PCINT0_vect) //port B isr //D12-D8 port B
{
  unsigned int isrMicros = micros();
  for(int i = 8; i<13;i++)
  {
    if(digitalRead(i) != prev_pinvalue[i])
    {
      if(prev_pinvalue[i]==0) //rising edge
      {
        prev_pinvalue[i] = 1;
        pinmicros[i] = isrMicros;
      }
      else //falling edge
      {
        prev_pinvalue[i] = 0;
        pinmicros[i] = isrMicros - pinmicros[i];
      }
    }
  }
}

ISR (PCINT2_vect)// D7-D2 port D
{
  unsigned int isrMicros = micros();
  for(int i = 2; i<8;i++)
  {
    if(digitalRead(i) != prev_pinvalue[i])
    {
      if(prev_pinvalue[i]==0) //rising edge
      {
        prev_pinvalue[i] = 1;
        pinmicros[i] = isrMicros;
      }
      else //falling edge
      {
        prev_pinvalue[i] = 0;
        pinmicros[i] = isrMicros - pinmicros[i];
      }
    }
  }
}


void setup() {

  for(int i = 2; i<8;i++)  
  {
    pinMode(i,INPUT);
  }
  for(int i = 8; i<12;i++)
  {
    pinMode(i,INPUT);
  }

  PCICR  |= B00000101; //pinchange inturupt port B & D (pins 0-13)
  PCMSK0 |= B00011111; //D12-D8 port B
  PCMSK2 |= B11111100; // D7-D2 port D

  sei();

  Serial.begin(115200);

}

void printServos()
{
    Serial.print("$srvo,");
  //we're not actually using all the pins, so we skip a bunch at the start and in the middle
  for(int i = 2; i<8;i++)  
  {
    Serial.print(pinmicros[i]);
    Serial.print(",");
  }
  for(int i = 8; i<12;i++)
  {
    Serial.print(pinmicros[i]);
    Serial.print(",");
  }
  Serial.println(pinmicros[12]);
}

void expireValues()
{
  unsigned int currentMicros = micros();
  for(int i = 2; i<8;i++)  
  {
    if(pinmicros[i]-maxReadingAge < currentMicros)
      prev_pinvalue[i] = 0;
  }

  for(int i = 8; i<12;i++)
  {
    if(pinmicros[i]-maxReadingAge < currentMicros)
      prev_pinvalue[i] = 0;
  }
}

void loop() 
{
  printServos();
  expireValues();
}
