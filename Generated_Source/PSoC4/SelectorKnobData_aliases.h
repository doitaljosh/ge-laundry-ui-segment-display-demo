/*******************************************************************************
* File Name: SelectorKnobData.h  
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

#if !defined(CY_PINS_SelectorKnobData_ALIASES_H) /* Pins SelectorKnobData_ALIASES_H */
#define CY_PINS_SelectorKnobData_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SelectorKnobData_0			(SelectorKnobData__0__PC)
#define SelectorKnobData_0_PS		(SelectorKnobData__0__PS)
#define SelectorKnobData_0_PC		(SelectorKnobData__0__PC)
#define SelectorKnobData_0_DR		(SelectorKnobData__0__DR)
#define SelectorKnobData_0_SHIFT	(SelectorKnobData__0__SHIFT)
#define SelectorKnobData_0_INTR	((uint16)((uint16)0x0003u << (SelectorKnobData__0__SHIFT*2u)))

#define SelectorKnobData_INTR_ALL	 ((uint16)(SelectorKnobData_0_INTR))


#endif /* End Pins SelectorKnobData_ALIASES_H */


/* [] END OF FILE */
