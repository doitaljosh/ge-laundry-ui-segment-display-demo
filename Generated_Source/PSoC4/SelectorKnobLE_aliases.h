/*******************************************************************************
* File Name: SelectorKnobLE.h  
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

#if !defined(CY_PINS_SelectorKnobLE_ALIASES_H) /* Pins SelectorKnobLE_ALIASES_H */
#define CY_PINS_SelectorKnobLE_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SelectorKnobLE_0			(SelectorKnobLE__0__PC)
#define SelectorKnobLE_0_PS		(SelectorKnobLE__0__PS)
#define SelectorKnobLE_0_PC		(SelectorKnobLE__0__PC)
#define SelectorKnobLE_0_DR		(SelectorKnobLE__0__DR)
#define SelectorKnobLE_0_SHIFT	(SelectorKnobLE__0__SHIFT)
#define SelectorKnobLE_0_INTR	((uint16)((uint16)0x0003u << (SelectorKnobLE__0__SHIFT*2u)))

#define SelectorKnobLE_INTR_ALL	 ((uint16)(SelectorKnobLE_0_INTR))


#endif /* End Pins SelectorKnobLE_ALIASES_H */


/* [] END OF FILE */
