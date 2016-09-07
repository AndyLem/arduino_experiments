
int clock = 5; // SCK pin
int latch = 6; // RCK pin
int data = 7;  // DIO pin

/*
looking at the edge with contacts, having the sensor pointing to the front, the pins are from left to right: Ground, Signal, +5V
*/
int motionPin = 3;
int lightPin = A0;
int speakerPin = 11;

#include "led8.h"

Led8 led;
int del = 300;
int start = 0;
int lastmils = 0;
int dir = 1;

void setup()
{
  pinMode(motionPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  
  led.init(data, clock, latch);
  led.clear();

  led.moveToStart();
  led.clear();
  led.print(0, "A");
  led.print(4, "L");
}

void loop()
{
  int m = digitalRead(motionPin);
  int l = map(analogRead(lightPin), -1023, 1023, -99, 99);
  
  led.print(1, m, 2);
  led.print(5, l, 3);

  if (l > 60)
  {
    if (m == HIGH)
    {
      digitalWrite(speakerPin, HIGH);
      delay(1);
      digitalWrite(speakerPin, LOW);
      delay(1);
    }
  }

  for (int i=0;i<100;i++)
  {
    led.tick(0);
    delay(1);
  }
}
