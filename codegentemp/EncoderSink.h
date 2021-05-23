/*******************************************************************************
* File Name: EncoderSink.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_EncoderSink_H) /* Pins EncoderSink_H */
#define CY_PINS_EncoderSink_H

#include "cytypes.h"
#include "cyfitter.h"
#include "EncoderSink_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} EncoderSink_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   EncoderSink_Read(void);
void    EncoderSink_Write(uint8 value);
uint8   EncoderSink_ReadDataReg(void);
#if defined(EncoderSink__PC) || (CY_PSOC4_4200L) 
    void    EncoderSink_SetDriveMode(uint8 mode);
#endif
void    EncoderSink_SetInterruptMode(uint16 position, uint16 mode);
uint8   EncoderSink_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void EncoderSink_Sleep(void); 
void EncoderSink_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(EncoderSink__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define EncoderSink_DRIVE_MODE_BITS        (3)
    #define EncoderSink_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - EncoderSink_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the EncoderSink_SetDriveMode() function.
         *  @{
         */
        #define EncoderSink_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define EncoderSink_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define EncoderSink_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define EncoderSink_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define EncoderSink_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define EncoderSink_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define EncoderSink_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define EncoderSink_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define EncoderSink_MASK               EncoderSink__MASK
#define EncoderSink_SHIFT              EncoderSink__SHIFT
#define EncoderSink_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in EncoderSink_SetInterruptMode() function.
     *  @{
     */
        #define EncoderSink_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define EncoderSink_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define EncoderSink_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define EncoderSink_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(EncoderSink__SIO)
    #define EncoderSink_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(EncoderSink__PC) && (CY_PSOC4_4200L)
    #define EncoderSink_USBIO_ENABLE               ((uint32)0x80000000u)
    #define EncoderSink_USBIO_DISABLE              ((uint32)(~EncoderSink_USBIO_ENABLE))
    #define EncoderSink_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define EncoderSink_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define EncoderSink_USBIO_ENTER_SLEEP          ((uint32)((1u << EncoderSink_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << EncoderSink_USBIO_SUSPEND_DEL_SHIFT)))
    #define EncoderSink_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << EncoderSink_USBIO_SUSPEND_SHIFT)))
    #define EncoderSink_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << EncoderSink_USBIO_SUSPEND_DEL_SHIFT)))
    #define EncoderSink_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(EncoderSink__PC)
    /* Port Configuration */
    #define EncoderSink_PC                 (* (reg32 *) EncoderSink__PC)
#endif
/* Pin State */
#define EncoderSink_PS                     (* (reg32 *) EncoderSink__PS)
/* Data Register */
#define EncoderSink_DR                     (* (reg32 *) EncoderSink__DR)
/* Input Buffer Disable Override */
#define EncoderSink_INP_DIS                (* (reg32 *) EncoderSink__PC2)

/* Interrupt configuration Registers */
#define EncoderSink_INTCFG                 (* (reg32 *) EncoderSink__INTCFG)
#define EncoderSink_INTSTAT                (* (reg32 *) EncoderSink__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define EncoderSink_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(EncoderSink__SIO)
    #define EncoderSink_SIO_REG            (* (reg32 *) EncoderSink__SIO)
#endif /* (EncoderSink__SIO_CFG) */

/* USBIO registers */
#if !defined(EncoderSink__PC) && (CY_PSOC4_4200L)
    #define EncoderSink_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define EncoderSink_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define EncoderSink_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define EncoderSink_DRIVE_MODE_SHIFT       (0x00u)
#define EncoderSink_DRIVE_MODE_MASK        (0x07u << EncoderSink_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins EncoderSink_H */


/* [] END OF FILE */
