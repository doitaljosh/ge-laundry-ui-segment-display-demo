/*******************************************************************************
* File Name: BuzzerFreq.h  
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

#if !defined(CY_PINS_BuzzerFreq_ALIASES_H) /* Pins BuzzerFreq_ALIASES_H */
#define CY_PINS_BuzzerFreq_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BuzzerFreq_0			(BuzzerFreq__0__PC)
#define BuzzerFreq_0_PS		(BuzzerFreq__0__PS)
#define BuzzerFreq_0_PC		(BuzzerFreq__0__PC)
#define BuzzerFreq_0_DR		(BuzzerFreq__0__DR)
#define BuzzerFreq_0_SHIFT	(BuzzerFreq__0__SHIFT)
#define BuzzerFreq_0_INTR	((uint16)((uint16)0x0003u << (BuzzerFreq__0__SHIFT*2u)))

#define BuzzerFreq_INTR_ALL	 ((uint16)(BuzzerFreq_0_INTR))


#endif /* End Pins BuzzerFreq_ALIASES_H */


/* [] END OF FILE */
