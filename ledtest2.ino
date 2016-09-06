
int clock = 5; // SCK pin
int latch = 6; // RCK pin
int data = 7;  // DIO pin

#include "led8.h"

Led8 led;
int del = 300;
int start = 0;
int lastmils = 0;
int dir = 1;

void setup()
{
  led.init(data, clock, latch);
  led.clear();

  led.moveToStart();
  led.print(0);
  led.print(1);
  led.print(2);
  led.print(3);
  led.print(4);
  led.print(5);
  led.print(6);
  led.print(7);
}

void loop()
{
  led.tick(0);

  int mils = millis();
  if (mils - lastmils < del)
    return;
  lastmils = mils;

  led.moveToStart();
  for (int i = start; i < 8 + start; i++)
    led.print(i);

  if (dir > 0)
    if (start < 8)
      start++;
    else
      dir = -1;
  else if (start > 0)
    start--;
  else
    dir = 1;
}
