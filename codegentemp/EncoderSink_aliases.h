/*******************************************************************************
* File Name: EncoderSink.h  
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

#if !defined(CY_PINS_EncoderSink_ALIASES_H) /* Pins EncoderSink_ALIASES_H */
#define CY_PINS_EncoderSink_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define EncoderSink_0			(EncoderSink__0__PC)
#define EncoderSink_0_PS		(EncoderSink__0__PS)
#define EncoderSink_0_PC		(EncoderSink__0__PC)
#define EncoderSink_0_DR		(EncoderSink__0__DR)
#define EncoderSink_0_SHIFT	(EncoderSink__0__SHIFT)
#define EncoderSink_0_INTR	((uint16)((uint16)0x0003u << (EncoderSink__0__SHIFT*2u)))

#define EncoderSink_INTR_ALL	 ((uint16)(EncoderSink_0_INTR))


#endif /* End Pins EncoderSink_ALIASES_H */


/* [] END OF FILE */
