/*******************************************************************************
* File Name: SelectorKnobClock.h  
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

#if !defined(CY_PINS_SelectorKnobClock_ALIASES_H) /* Pins SelectorKnobClock_ALIASES_H */
#define CY_PINS_SelectorKnobClock_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SelectorKnobClock_0			(SelectorKnobClock__0__PC)
#define SelectorKnobClock_0_PS		(SelectorKnobClock__0__PS)
#define SelectorKnobClock_0_PC		(SelectorKnobClock__0__PC)
#define SelectorKnobClock_0_DR		(SelectorKnobClock__0__DR)
#define SelectorKnobClock_0_SHIFT	(SelectorKnobClock__0__SHIFT)
#define SelectorKnobClock_0_INTR	((uint16)((uint16)0x0003u << (SelectorKnobClock__0__SHIFT*2u)))

#define SelectorKnobClock_INTR_ALL	 ((uint16)(SelectorKnobClock_0_INTR))


#endif /* End Pins SelectorKnobClock_ALIASES_H */


/* [] END OF FILE */
