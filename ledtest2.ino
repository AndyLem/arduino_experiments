
int clock = 5; // SCK pin
int latch = 6; // RCK pin
int data = 7; // DIO pin

class Led8
{
protected:
  int _data;
  int _clock;
  int _latch;  
  int _symbols[16] =  {
//   76543210 
    B11000000,    // 0
    B11111001,    // 1
    B10100100,    // 2
    B10110000,    // 3
    B10011001,    // 4
    B10010010,    // 5
    B10000010,    // 6
    B11111000,    // 7
    B10000000,    // 8
    B10010000,    // 9
    B10001000,    // A
    B10000011,    // B
    B11000110,    // C
    B10100001,    // D
    B10000110,    // E
    B10001110};   // F

  int const _space = 0xFF;
  
  int _buf[8];

  int _cursor = 0;

  void moveRight()
  {
    if (_cursor < 7) _cursor++;
  }

  void update()
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

  void outputSymbol(int pos, int symbol)
  {
    digitalWrite(_latch, LOW);
    shiftOut(_data, _clock, MSBFIRST, 1 << pos);
    shiftOut(_data, _clock, MSBFIRST, symbol);
    digitalWrite(_latch, HIGH); 
  }    
  
public:
  void setSymbol(int pos, int symbol)
  {
    _buf[pos] = symbol;
  }    

  void andSymbol(int pos, int symbol)
  {
    setSymbol(pos, symbol & _buf[pos]);
  }

  void orSymbol(int pos, int symbol)
  {
    setSymbol(pos, symbol | _buf[pos]);
  }
  
  void init(int dataPin, int clockPin, int latchPin)
  {
    _data = dataPin;
    _clock = clockPin;
    _latch = latchPin;

    pinMode(_clock, OUTPUT);  
    pinMode(_latch, OUTPUT);  
    pinMode(_data, OUTPUT);   
  }

  void clear()
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

  void printSymbol(int pos, int symbol)
  {
    setSymbol(pos, symbol);
  }

  void printSymbol(int symbol)
  {
    setSymbol(_cursor, symbol);
    moveRight();
  }

  void putSymbol(int symbol)
  {
    setSymbol(_cursor, symbol);
  }
  
  void print(int pos, int value)
  {
    setSymbol(pos, _symbols[value]);
  }

  void print(int value)
  {
    print(_cursor, value);
    moveRight();
  }

  void put(int value)
  {
    print(_cursor, value);
  }

  void printSpace()
  {
    setSymbol(_cursor, _space);
    moveRight();
  }

  void moveTo(int pos)
  {
    _cursor = pos;
  }

  void moveToStart()
  {
    moveTo(0);
  }

  void tick(int millis)
  {
    update();
  }
};

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
  if (mils - lastmils < del) return;
  lastmils = mils;

  led.moveToStart();
  for (int i=start; i<8+start;i++)
    led.print(i);

  if (dir > 0)
    if (start < 8)
      start++;
    else dir = -1;  
  else if (start > 0)
    start--;
    else dir = 1;

}



