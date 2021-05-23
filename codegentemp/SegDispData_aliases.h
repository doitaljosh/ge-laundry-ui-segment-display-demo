/*******************************************************************************
* File Name: SegDispData.h  
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

#if !defined(CY_PINS_SegDispData_ALIASES_H) /* Pins SegDispData_ALIASES_H */
#define CY_PINS_SegDispData_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SegDispData_0			(SegDispData__0__PC)
#define SegDispData_0_PS		(SegDispData__0__PS)
#define SegDispData_0_PC		(SegDispData__0__PC)
#define SegDispData_0_DR		(SegDispData__0__DR)
#define SegDispData_0_SHIFT	(SegDispData__0__SHIFT)
#define SegDispData_0_INTR	((uint16)((uint16)0x0003u << (SegDispData__0__SHIFT*2u)))

#define SegDispData_INTR_ALL	 ((uint16)(SegDispData_0_INTR))


#endif /* End Pins SegDispData_ALIASES_H */


/* [] END OF FILE */
