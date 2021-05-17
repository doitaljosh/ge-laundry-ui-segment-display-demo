/*
 * Demo code for hacking the LED display on 2019 GE washers and dryers.
 * The display contains two shift registers, and interfaces to the MCU of the UI
 * through a 6-pin synchronous serial interface. It functions base on the
 * principle of a standard shift register and is easy to work with.
 * 
 * Part number for reference: WH22X29549
 * 
 * This code just counts from 0-F in hexadecimal on all three digits.
 */

const int stb1 = 10; // Strobe for shift register 1
const int stb2 = 8; // Strobe for shift register 2
const int clk = 13; // Clock
const int dat = 11; // Data

const byte digit0Addr = 0x06;
const byte digit1Addr = 0x08;
const byte digit2Addr = 0x0a;

const unsigned char characterTable[74] = 
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
    0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D, 0x76, 0x30, 0x1E, 0x75, 0x38,
/*  m     n     o     p     q     r     s     t     u     v     w     x     */
    0x55, 0x54, 0x5C, 0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x1C, 0x1D, 0x64,
/*  y     z                                                                 */
    0x6E, 0x5B,
/*  [     ]     -     _     ‾     segA  segB  segC  segD  segE  segF  segG  */
    0x39, 0x0F, 0x40, 0x08, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40
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

void writeToDisplay(byte addr, byte data, boolean ledState)
{
  
  strobe(0); 
  
  writeByte(0xC0 | addr);    //addr = 00H to 0DH
  writeByte(characterTable[data]);
  writeBit(ledState);
  
  strobe(1);
  
}

void setBrightness(byte intensity)
{
  
  strobe(0);
  
  writeByte(0x80 | intensity);
  
  strobe(1);
  
}  

void displayOn(void)
{
  
  strobe(0);
  
  writeByte(0x80 | 0x08);
  
  strobe(1);
   
}  

void displayOff(void)
{
  
  strobe(0);
  
  writeByte(0x80 & ~0x08);
  
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

void count(byte start, byte end, int period)
{

  byte Digit0 = start;
  byte Digit1 = start;
  byte Digit2 = start;
  
  while (1) {
    
    writeToDisplay(digit0Addr, Digit0, LOW);
    writeToDisplay(digit1Addr, Digit1, LOW);
    writeToDisplay(digit2Addr, Digit2, LOW);
    
    delay(period);
    
    Digit0++;
    Digit1++;
    Digit2++;
    
    writeToDisplay(digit0Addr, Digit0, HIGH);
    writeToDisplay(digit1Addr, Digit1, HIGH);
    writeToDisplay(digit2Addr, Digit2, HIGH);
    
    delay(period);
    
    Digit0++;
    Digit1++;
    Digit2++;
    
    if(Digit0 >= end) {
      
      Digit0 = start;
      Digit1 = start;
      Digit2 = start;
      
    }
  }
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
  
  displayOff();
  displayOn();
  setBrightness(4 | 0x08);
  
}  

void loop()
{
  // Count in hexadecimal from 0-16 on all three digits
  count(0, 16, 1000);
  
}
