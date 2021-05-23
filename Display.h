/* ========================================
 *
 * Constants and prototypes for interfacing with display functions
 *
 * ========================================
*/

#include "SsdCharacterTable.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define LOW 0
#define HIGH 1

extern const uint8_t digit0Addr;
extern const uint8_t digit1Addr;
extern const uint8_t digit2Addr;

#define IGNORE(x) (void)(x)

void writeToSingleDigit(uint8_t addr, uint8_t data, bool ledState);
void writeToAllDigits(uint8_t dig1, uint8_t dig2, uint8_t dig3, int period);
void ctrlDisplay(int ctx, uint8_t value);
void strobe(bool state);


/* [] END OF FILE */
