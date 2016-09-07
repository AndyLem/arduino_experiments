#ifndef led8_h
#define led8_h

#include "Arduino.h"

struct SYMBOL
{
  char Symbol;
  char Code;
};

class Led8
{
protected:
  int _data;
  int _clock;
  int _latch;

  #define SYMBOLS_COUNT 24
  SYMBOL const _symbols[SYMBOLS_COUNT] = {
      //      76543210
      { '0', B11000000 },
      { '1', B11111001 },  
      { '2', B10100100 },  
      { '3', B10110000 },  
      { '4', B10011001 },  
      { '5', B10010010 },  
      { '6', B10000010 },  
      { '7', B11111000 },  
      { '8', B10000000 },  
      { '9', B10010000 },  
      
      { '-', B10111111 },  

      { 'A', B10001000 },  
      { 'B', B10000011 },  
      { 'C', B11000110 },  
      { 'D', B10100001 },  
      { 'E', B10000110 },  
      { 'F', B10001110 },  

      { 'H', B10001001 },  
      { 'L', B11000111 },  
      { 'O', B11000000 },
      { 'P', B10001100 },  
      { 'S', B10010010 },  
      { 'U', B11000001 },  
      { 'Y', B10010001 },  
    }; 

  int const _space = 0xFF;
  int _buf[8];
  int _cursor = 0;
  #define DISPLAY_LENGTH 8

  void moveRight(int steps);
  void update();
  void outputBinary(int pos, int binary);
  char getBinaryCode(char symbol);
  String padLeftAndTrim(String value, int length);


public:
  void setBinary(int pos, int binary);

  void andBinary(int pos, int binary);

  void orBinary(int pos, int binary);

  void init(int dataPin, int clockPin, int latchPin);

  void clear();

  void printBinary(int pos, int binary);

  void printBinary(int binary);

  void putBinary(int binary);

  void print(int pos, String value);

  void print(int pos, int value);

  void print(int pos, String value, int fieldLength);

  void print(int pos, int value, int fieldLength);

  void print(String value);

  void print(int value);

  void put(String value);

  void printSpace();

  void moveTo(int pos);

  void moveToStart();

  void tick(int millis);
};

#endif
