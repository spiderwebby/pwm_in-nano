//
// this pulls in 8x PWM signals and spits them out as serial CSV
// it doesn't use pulseIn() because pulseIn sucks hard when you need to use it 8 times
// PWM in on D2-D12
// the arrays are too big, i don't care yet.
// maybe i'll do some digitalRead(i+2) stuff at some point, but that point is not today
//

#include <Arduino.h>

const int maxReadingAge = 5000; // 5ms
volatile bool prev_pinvalue[13];
volatile unsigned int pinmicros[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

byte prev_PINB;
byte prev_PIND;

ISR(PCINT0_vect)
{ // port B isr //D8-D12 port B
  unsigned int isrMicros = micros();
  for (int i = 8; i < 13; i++)
  { // we have to work out which pin changed, and if it's falling or rising
    if (digitalRead(i) != prev_pinvalue[i])
    {
      if (prev_pinvalue[i] == 0)
      { // rising edge
        prev_pinvalue[i] = 1;
        pinmicros[i] = isrMicros;
      }
      else
      { // falling edge
        prev_pinvalue[i] = 0;
        pinmicros[i] = isrMicros - pinmicros[i];
      }
    }
  }
}

ISR(PCINT2_vect)
{ // D2-D7 port D
  unsigned int isrMicros = micros();
  for (int i = 2; i < 8; i++)
  {
    if (digitalRead(i) != prev_pinvalue[i])
    {
      if (prev_pinvalue[i] == 0)
      { // rising edge
        prev_pinvalue[i] = 1;
        pinmicros[i] = isrMicros;
      }
      else
      { // falling edge
        prev_pinvalue[i] = 0;
        pinmicros[i] = isrMicros - pinmicros[i];
      }
    }
  }
}

void setup()
{
  for (int i = 2; i < 13; i++)
  {
    pinMode(i, INPUT);
  }

  PCICR |= B00000101;  // pinchange inturupt port B & D (pins 0-13)
  PCMSK0 |= B00011111; // D12-D8 port B
  PCMSK2 |= B11111100; // D7-D2 port D

  sei(); // turn on le inturrupts

  Serial.begin(115200);
}

void printServos()
{
  Serial.print("$srvo,");
  // we're not actually using all the pins, so we skip a bunch at the start and in the middle
  for (int i = 2; i < 12; i++)
  {
    Serial.print(pinmicros[i]);
    Serial.print(",");
  }
  Serial.println(pinmicros[12]);
}

void expireValues()
{
  unsigned int currentMicros = micros();
  for (int i = 2; i < 13; i++)
  {
    if (pinmicros[i] - maxReadingAge < currentMicros)
      prev_pinvalue[i] = 0;
  }
}

void loop()
{
  printServos();
  expireValues();
}
