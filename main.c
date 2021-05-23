/* ========================================
 *
 * Demo code for hacking the LED display on 2019 GE washers and dryers.
 * The display contains two shift registers, and interfaces to the MCU of the UI
 * through a 6-pin synchronous serial interface. It functions base on the
 * principle of a standard shift register and is easy to work with.
 * 
 * Part number for reference: WH22X29549
 * 
 * This code just scrolls "Hello world" across all three digits.
 *
 * This version is ported to run on the captouch UI board itself and can be compiled with PSoC creator.
 *
 * ========================================
*/

#include "Display.h"
#include <project.h>

void helloWorld(int period)
{

  uint8_t H = 17;
  uint8_t e = 40;
  uint8_t l = 47;
  uint8_t o = 50;
  uint8_t w = 58;
  uint8_t r = 53;
  uint8_t d = 39;

  uint8_t space = 74;
  
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
  
  CyDelay(500);
  
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    strobe(HIGH);
    SegDispClock_Write(HIGH);
    SegDispData_Write(HIGH);
    
    ctrlDisplay(0, 0);
    ctrlDisplay(1, 0);
    ctrlDisplay(2, (4 | 0x08));

    for(;;)
    {
        // Scroll "Hello world" across all three digits with a 200ms delay between frames.
        helloWorld(200);
  
    }
}

/* [] END OF FILE */
