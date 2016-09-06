#ifndef led8_h
#define led8_h

#if ARDUINO >= 100 // Arduino 1.0 and 0023 compatible!
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Led8
{
protected:
  int _data;
  int _clock;
  int _latch;
  char _symbols[16] = {
      //   76543210
      B11000000,  // 0
      B11111001,  // 1
      B10100100,  // 2
      B10110000,  // 3
      B10011001,  // 4
      B10010010,  // 5
      B10000010,  // 6
      B11111000,  // 7
      B10000000,  // 8
      B10010000,  // 9
      B10001000,  // A
      B10000011,  // B
      B11000110,  // C
      B10100001,  // D
      B10000110,  // E
      B10001110}; // F

  int const _space = 0xFF;
  int _buf[8];
  int _cursor = 0;

  void moveRight();
  void update();
  void outputSymbol(int pos, int symbol);

public:
  void setSymbol(int pos, int symbol);

  void andSymbol(int pos, int symbol);

  void orSymbol(int pos, int symbol);

  void init(int dataPin, int clockPin, int latchPin);

  void clear();

  void printSymbol(int pos, int symbol);

  void printSymbol(int symbol);

  void putSymbol(int symbol);

  void print(int pos, int value);

  void print(int value);

  void put(int value);

  void printSpace();

  void moveTo(int pos);

  void moveToStart();

  void tick(int millis);
};

#endif
