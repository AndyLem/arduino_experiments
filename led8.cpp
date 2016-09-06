#include "led8.h"

#if ARDUINO >= 100 // Arduino 1.0 and 0023 compatible!
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

void Led8::moveRight()
{
  if (_cursor < 7)
    _cursor++;
}

void Led8::update()
{
  outputSymbol(0, _buf[0]);
  outputSymbol(1, _buf[1]);
  outputSymbol(2, _buf[2]);
  outputSymbol(3, _buf[3]);
  outputSymbol(4, _buf[4]);
  outputSymbol(5, _buf[5]);
  outputSymbol(6, _buf[6]);
  outputSymbol(7, _buf[7]);
}

void Led8::outputSymbol(int pos, int symbol)
{
  digitalWrite(_latch, LOW);
  shiftOut(_data, _clock, MSBFIRST, 1 << pos);
  shiftOut(_data, _clock, MSBFIRST, symbol);
  digitalWrite(_latch, HIGH);
}

void Led8::setSymbol(int pos, int symbol)
{
  _buf[pos] = symbol;
}

void Led8::andSymbol(int pos, int symbol)
{
  setSymbol(pos, symbol & _buf[pos]);
}

void Led8::orSymbol(int pos, int symbol)
{
  setSymbol(pos, symbol | _buf[pos]);
}

void Led8::init(int dataPin, int clockPin, int latchPin)
{
  _data = dataPin;
  _clock = clockPin;
  _latch = latchPin;

  pinMode(_clock, OUTPUT);
  pinMode(_latch, OUTPUT);
  pinMode(_data, OUTPUT);
}

void Led8::clear()
{
  setSymbol(0, _space);
  setSymbol(1, _space);
  setSymbol(2, _space);
  setSymbol(3, _space);
  setSymbol(4, _space);
  setSymbol(5, _space);
  setSymbol(6, _space);
  setSymbol(7, _space);
}

void Led8::printSymbol(int pos, int symbol)
{
  setSymbol(pos, symbol);
}

void Led8::printSymbol(int symbol)
{
  setSymbol(_cursor, symbol);
  moveRight();
}

void Led8::putSymbol(int symbol)
{
  setSymbol(_cursor, symbol);
}

void Led8::print(int pos, int value)
{
  setSymbol(pos, _symbols[value]);
}

void Led8::print(int value)
{
  print(_cursor, value);
  moveRight();
}

void Led8::put(int value)
{
  print(_cursor, value);
}

void Led8::printSpace()
{
  setSymbol(_cursor, _space);
  moveRight();
}

void Led8::moveTo(int pos)
{
  _cursor = pos;
}

void Led8::moveToStart()
{
  moveTo(0);
}

void Led8::tick(int millis)
{
  update();
}
