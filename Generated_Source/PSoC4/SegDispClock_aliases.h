/*******************************************************************************
* File Name: SegDispClock.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SegDispClock_ALIASES_H) /* Pins SegDispClock_ALIASES_H */
#define CY_PINS_SegDispClock_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SegDispClock_0			(SegDispClock__0__PC)
#define SegDispClock_0_PS		(SegDispClock__0__PS)
#define SegDispClock_0_PC		(SegDispClock__0__PC)
#define SegDispClock_0_DR		(SegDispClock__0__DR)
#define SegDispClock_0_SHIFT	(SegDispClock__0__SHIFT)
#define SegDispClock_0_INTR	((uint16)((uint16)0x0003u << (SegDispClock__0__SHIFT*2u)))

#define SegDispClock_INTR_ALL	 ((uint16)(SegDispClock_0_INTR))


#endif /* End Pins SegDispClock_ALIASES_H */


/* [] END OF FILE */
