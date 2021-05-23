/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <stdint.h>
#include "SsdCharacterTable.h"

const uint8_t characterTable[75] = 
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

/* [] END OF FILE */
