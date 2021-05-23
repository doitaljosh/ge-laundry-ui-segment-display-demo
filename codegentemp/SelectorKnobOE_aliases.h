/*******************************************************************************
* File Name: SelectorKnobOE.h  
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

#if !defined(CY_PINS_SelectorKnobOE_ALIASES_H) /* Pins SelectorKnobOE_ALIASES_H */
#define CY_PINS_SelectorKnobOE_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SelectorKnobOE_0			(SelectorKnobOE__0__PC)
#define SelectorKnobOE_0_PS		(SelectorKnobOE__0__PS)
#define SelectorKnobOE_0_PC		(SelectorKnobOE__0__PC)
#define SelectorKnobOE_0_DR		(SelectorKnobOE__0__DR)
#define SelectorKnobOE_0_SHIFT	(SelectorKnobOE__0__SHIFT)
#define SelectorKnobOE_0_INTR	((uint16)((uint16)0x0003u << (SelectorKnobOE__0__SHIFT*2u)))

#define SelectorKnobOE_INTR_ALL	 ((uint16)(SelectorKnobOE_0_INTR))


#endif /* End Pins SelectorKnobOE_ALIASES_H */


/* [] END OF FILE */
