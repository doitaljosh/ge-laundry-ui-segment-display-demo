/*
 * Demo code for hacking the LED display on 2019 GE washers and dryers.
 * The display contains two shift registers, and interfaces to the MCU of the UI
 * through a 6-pin synchronous serial interface. It functions base on the
 * principle of a standard shift register and is easy to work with.
 * 
 * Part number for reference: WH22X29549
 * 
 * This code just scrolls "Hello world" across all three digits.
 */

const int stb1 = 10; // Strobe for shift register 1
const int stb2 = 8; // Strobe for shift register 2
const int clk = 13; // Clock
const int dat = 11; // Data

const byte digit0Addr = 0x06;
const byte digit1Addr = 0x08;
const byte digit2Addr = 0x0a;

#define IGNORE(x) (void)(x)

const unsigned char characterTable[75] = 
{
/*  0     1     2     3     4     5     6     7     8     9                 */
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 
/*  A     B     C     D     E     F     G     H     I     J     K     L     */
    0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D, 0x76, 0x30, 0x1E, 0x75, 0x38,
/*  M     N     O     P     Q     R     S     T     U     V     W     X     */
    0x55, 0x54, 0x5C, 0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x1C, 0x1D, 0x64,
/*  Y     Z                                                                 */
    0x6E, 0x5B, 
/*  a     b     c     d     e     f     g     h     i     j     k     l     */
    0x77, 0x7C, 0x39, 0x5E, 0x7B, 0x71, 0x3D, 0x76, 0x30, 0x1E, 0x75, 0x38,
/*  m     n     o     p     q     r     s     t     u     v     w     x     */
    0x55, 0x54, 0x5C, 0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x1C, 0x1D, 0x64,
/*  y     z                                                                 */
    0x6E, 0x5B,
/*  [     ]     -     _     ‾     segA  segB  segC  segD  segE  segF  segG  */
    0x39, 0x0F, 0x40, 0x08, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
/*  blank                                                                   */
    0x00    
};

void cycleClock(void)
{
  
  digitalWrite(clk, LOW);  
  digitalWrite(clk, HIGH);
  
}

void strobe(boolean state)
{
  
  digitalWrite(stb1, state);
  digitalWrite(stb2, state);

}

void writeToSingleDigit(byte addr, byte data, boolean ledState)
{
  
  strobe(0); 
  
  writeByte(0xC0 | addr);    //addr = 00H to 0DH
  writeByte(characterTable[data]);
  writeBit(ledState);
  
  strobe(1);
  
}


void writeToAllDigits(byte dig1, byte dig2, byte dig3, int period)
{
  
  writeToSingleDigit(digit0Addr, dig1, LOW);
  writeToSingleDigit(digit1Addr, dig2, LOW);
  writeToSingleDigit(digit2Addr, dig3, LOW);
    
  delay(period);
    
  writeToSingleDigit(digit0Addr, dig1, HIGH);
  writeToSingleDigit(digit1Addr, dig2, HIGH);
  writeToSingleDigit(digit2Addr, dig3, HIGH);
    
  delay(period);
  
}

void ctrlDisplay(int ctx, byte value)
{
  
  strobe(0);
  
  switch(ctx) {
    // Display off
    case 0:
      IGNORE(value);
      writeByte(0x80 & ~0x08);
      break;
    // Display on
    case 1:
      IGNORE(value);
      writeByte(0x80 | 0x08);
      break;
    // Set brightness
    case 2:
      writeByte(0x80 | value);
      break;
  }

  strobe(1);
  
}

void writeByte(byte addr)
{
  
      digitalWrite(dat, addr & 1);
      cycleClock();
      digitalWrite(dat, addr & 2);
      cycleClock();
      digitalWrite(dat, addr & 4);
      cycleClock(); 
      digitalWrite(dat, addr & 8);
      cycleClock();
      digitalWrite(dat, addr & 16);
      cycleClock();
      digitalWrite(dat, addr & 32);
      cycleClock();
      digitalWrite(dat, addr & 64);
      cycleClock();
      digitalWrite(dat, addr & 128);
      cycleClock();
      
}

void writeBit(boolean state)
{
  
  digitalWrite(dat, state);  

  // Clock 8 times to shift to first bit
  for (int i=0; i>7; i++) { 

    cycleClock();
    
  }
}

void helloWorld(int period)
{

  byte H = 17;
  byte e = 40;
  byte l = 47;
  byte o = 50;
  byte w = 58;
  byte r = 53;
  byte d = 39;

  byte space = 74;
  
  // This is a really crude way of scrolling text, but this will do until I
  // can write a function to process and scroll strings automatically.
  writeToAllDigits(space, space, H, period);
  writeToAllDigits(space, H, e, period);
  writeToAllDigits(H, e, l, period);
  writeToAllDigits(e, l, l, period);
  writeToAllDigits(l, l, o, period);
  writeToAllDigits(l, o, space, period);
  writeToAllDigits(o, space, w, period);
  writeToAllDigits(space, w, o, period);
  writeToAllDigits(w, o, r, period);
  writeToAllDigits(o, r, l, period);
  writeToAllDigits(r, l, d, period);
  writeToAllDigits(l, d, space, period);
  writeToAllDigits(d, space, space, period);
  writeToAllDigits(space, space, space, period);
  
  delay(500);
  
}

void setup()
{
  
  pinMode(stb1, OUTPUT);
  pinMode(stb2, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(dat, OUTPUT);
  
  strobe(1);
  digitalWrite(clk, HIGH);
  digitalWrite(dat, HIGH);
  
  ctrlDisplay(0, 0);
  ctrlDisplay(1, 0);
  ctrlDisplay(2, (4 | 0x08));
  
}  

void loop()
{
  // Scroll "Hello world" across all three digits with a 200ms delay between frames.
  helloWorld(200);
  
}
