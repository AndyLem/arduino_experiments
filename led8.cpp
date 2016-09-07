#include "led8.h"

#include "Arduino.h"

String Led8::padLeftAndTrim(String value, int length)
{
  int stringLength = value.length();
  if (stringLength == length) return value;
  if (stringLength > length) return value.substring(0, length-1);
  for (int i=0;i<length-stringLength;i++)
    value = " "+value;
  return value;
}

void Led8::moveRight(int steps)
{
  _cursor += steps;
  if (_cursor >= DISPLAY_LENGTH)
    _cursor = DISPLAY_LENGTH-1;
}

void Led8::update()
{
  outputBinary(0, _buf[0]);
  outputBinary(1, _buf[1]);
  outputBinary(2, _buf[2]);
  outputBinary(3, _buf[3]);
  outputBinary(4, _buf[4]);
  outputBinary(5, _buf[5]);
  outputBinary(6, _buf[6]);
  outputBinary(7, _buf[7]);
}

void Led8::outputBinary(int pos, int binary)
{
  digitalWrite(_latch, LOW);
  shiftOut(_data, _clock, MSBFIRST, 1 << pos);
  shiftOut(_data, _clock, MSBFIRST, binary);
  digitalWrite(_latch, HIGH);
}

char Led8::getBinaryCode(char symbol)
{
  for (int i=0;i<SYMBOLS_COUNT;i++)
    if (_symbols[i].Symbol == symbol) return _symbols[i].Code;
  return _space;
}

void Led8::setBinary(int pos, int binary)
{
  _buf[pos] = binary;
}

void Led8::andBinary(int pos, int binary)
{
  setBinary(pos, binary & _buf[pos]);
}

void Led8::orBinary(int pos, int binary)
{
  setBinary(pos, binary | _buf[pos]);
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
  setBinary(0, _space);
  setBinary(1, _space);
  setBinary(2, _space);
  setBinary(3, _space);
  setBinary(4, _space);
  setBinary(5, _space);
  setBinary(6, _space);
  setBinary(7, _space);
}

void Led8::printBinary(int pos, int binary)
{
  setBinary(pos, binary);
}

void Led8::printBinary(int binary)
{
  setBinary(_cursor, binary);
  moveRight(1);
}

void Led8::putBinary(int binary)
{
  setBinary(_cursor, binary);
}

void Led8::print(int pos, String value)
{
  value.toUpperCase();
  for (int i=0;i<value.length();i++)
  {
    if (pos+i >= DISPLAY_LENGTH) break;
    char symb = value.charAt(i);
    char code = getBinaryCode(symb);
    setBinary(pos+i, code);
  }
}

void Led8::print(int pos, String value, int fieldLength)
{
  print(pos, padLeftAndTrim(value, fieldLength));
}

void Led8::print(int pos, int value, int fieldLength)
{
  print(pos, String(value), fieldLength);
}

void Led8::print(int pos, int value)
{
  print(pos, String(value));
}

void Led8::print(String value)
{
  print(_cursor, value);
  moveRight(value.length());
}

void Led8::print(int value)
{
  print(String(value));
}

void Led8::put(String value)
{
  print(_cursor, value);
}

void Led8::printSpace()
{
  setBinary(_cursor, _space);
  moveRight(1 );
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
