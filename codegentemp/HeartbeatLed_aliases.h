/*******************************************************************************
* File Name: HeartbeatLed.h  
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

#if !defined(CY_PINS_HeartbeatLed_ALIASES_H) /* Pins HeartbeatLed_ALIASES_H */
#define CY_PINS_HeartbeatLed_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HeartbeatLed_0			(HeartbeatLed__0__PC)
#define HeartbeatLed_0_PS		(HeartbeatLed__0__PS)
#define HeartbeatLed_0_PC		(HeartbeatLed__0__PC)
#define HeartbeatLed_0_DR		(HeartbeatLed__0__DR)
#define HeartbeatLed_0_SHIFT	(HeartbeatLed__0__SHIFT)
#define HeartbeatLed_0_INTR	((uint16)((uint16)0x0003u << (HeartbeatLed__0__SHIFT*2u)))

#define HeartbeatLed_INTR_ALL	 ((uint16)(HeartbeatLed_0_INTR))


#endif /* End Pins HeartbeatLed_ALIASES_H */


/* [] END OF FILE */
