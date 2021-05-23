/* ========================================
 *
 * Display functions
 *
 * ========================================
*/

#include <project.h>
#include "Display.h"

const uint8_t digit0Addr = 0x06;
const uint8_t digit1Addr = 0x08;
const uint8_t digit2Addr = 0x0a;

void cycleClock(void)
{
  
  SegDispClock_Write(LOW);  
  SegDispClock_Write(HIGH); 
  
}

void strobe(bool state)
{
  
  SegDispStb1_Write(state);
  //SegDispStb2_Write(state);

}

void writeByte(uint8_t addr)
{
  
      SegDispData_Write(addr & 1);
      cycleClock();
      SegDispData_Write(addr & 2);
      cycleClock();
      SegDispData_Write(addr & 4);
      cycleClock(); 
      SegDispData_Write(addr & 8);
      cycleClock();
      SegDispData_Write(addr & 16);
      cycleClock();
      SegDispData_Write(addr & 32);
      cycleClock();
      SegDispData_Write(addr & 64);
      cycleClock();
      SegDispData_Write(addr & 128);
      cycleClock();
      
}

void writeBit(bool state)
{
  
  SegDispData_Write(state);  

  // Clock 8 times to shift to first bit
  for (int i=0; i>7; i++) { 

    cycleClock();
    
  }
}

void writeToSingleDigit(uint8_t addr, uint8_t data, bool ledState)
{
  
  strobe(LOW); 
  
  writeByte(0xC0 | addr);    //addr = 00H to 0DH
  writeByte(characterTable[data]);
  writeBit(ledState);
  
  strobe(HIGH);
  
}


void writeToAllDigits(uint8_t dig1, uint8_t dig2, uint8_t dig3, int period)
{
  
  writeToSingleDigit(digit0Addr, dig1, LOW);
  writeToSingleDigit(digit1Addr, dig2, HIGH);
  writeToSingleDigit(digit2Addr, dig3, LOW);
    
  CyDelay(period);
    
  writeToSingleDigit(digit0Addr, dig1, HIGH);
  writeToSingleDigit(digit1Addr, dig2, HIGH);
  writeToSingleDigit(digit2Addr, dig3, HIGH);
    
  CyDelay(period);
  
}

void ctrlDisplay(int ctx, uint8_t value)
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

/* [] END OF FILE */
