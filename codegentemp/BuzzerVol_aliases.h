/*******************************************************************************
* File Name: BuzzerVol.h  
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

#if !defined(CY_PINS_BuzzerVol_ALIASES_H) /* Pins BuzzerVol_ALIASES_H */
#define CY_PINS_BuzzerVol_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BuzzerVol_0			(BuzzerVol__0__PC)
#define BuzzerVol_0_PS		(BuzzerVol__0__PS)
#define BuzzerVol_0_PC		(BuzzerVol__0__PC)
#define BuzzerVol_0_DR		(BuzzerVol__0__DR)
#define BuzzerVol_0_SHIFT	(BuzzerVol__0__SHIFT)
#define BuzzerVol_0_INTR	((uint16)((uint16)0x0003u << (BuzzerVol__0__SHIFT*2u)))

#define BuzzerVol_INTR_ALL	 ((uint16)(BuzzerVol_0_INTR))


#endif /* End Pins BuzzerVol_ALIASES_H */


/* [] END OF FILE */
