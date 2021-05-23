/*******************************************************************************
* File Name: BuzzerFreq.h  
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

#if !defined(CY_PINS_BuzzerFreq_H) /* Pins BuzzerFreq_H */
#define CY_PINS_BuzzerFreq_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BuzzerFreq_aliases.h"


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
} BuzzerFreq_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BuzzerFreq_Read(void);
void    BuzzerFreq_Write(uint8 value);
uint8   BuzzerFreq_ReadDataReg(void);
#if defined(BuzzerFreq__PC) || (CY_PSOC4_4200L) 
    void    BuzzerFreq_SetDriveMode(uint8 mode);
#endif
void    BuzzerFreq_SetInterruptMode(uint16 position, uint16 mode);
uint8   BuzzerFreq_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BuzzerFreq_Sleep(void); 
void BuzzerFreq_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BuzzerFreq__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BuzzerFreq_DRIVE_MODE_BITS        (3)
    #define BuzzerFreq_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BuzzerFreq_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BuzzerFreq_SetDriveMode() function.
         *  @{
         */
        #define BuzzerFreq_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BuzzerFreq_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BuzzerFreq_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BuzzerFreq_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BuzzerFreq_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BuzzerFreq_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BuzzerFreq_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BuzzerFreq_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BuzzerFreq_MASK               BuzzerFreq__MASK
#define BuzzerFreq_SHIFT              BuzzerFreq__SHIFT
#define BuzzerFreq_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BuzzerFreq_SetInterruptMode() function.
     *  @{
     */
        #define BuzzerFreq_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BuzzerFreq_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BuzzerFreq_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BuzzerFreq_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BuzzerFreq__SIO)
    #define BuzzerFreq_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BuzzerFreq__PC) && (CY_PSOC4_4200L)
    #define BuzzerFreq_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BuzzerFreq_USBIO_DISABLE              ((uint32)(~BuzzerFreq_USBIO_ENABLE))
    #define BuzzerFreq_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BuzzerFreq_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BuzzerFreq_USBIO_ENTER_SLEEP          ((uint32)((1u << BuzzerFreq_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BuzzerFreq_USBIO_SUSPEND_DEL_SHIFT)))
    #define BuzzerFreq_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BuzzerFreq_USBIO_SUSPEND_SHIFT)))
    #define BuzzerFreq_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BuzzerFreq_USBIO_SUSPEND_DEL_SHIFT)))
    #define BuzzerFreq_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BuzzerFreq__PC)
    /* Port Configuration */
    #define BuzzerFreq_PC                 (* (reg32 *) BuzzerFreq__PC)
#endif
/* Pin State */
#define BuzzerFreq_PS                     (* (reg32 *) BuzzerFreq__PS)
/* Data Register */
#define BuzzerFreq_DR                     (* (reg32 *) BuzzerFreq__DR)
/* Input Buffer Disable Override */
#define BuzzerFreq_INP_DIS                (* (reg32 *) BuzzerFreq__PC2)

/* Interrupt configuration Registers */
#define BuzzerFreq_INTCFG                 (* (reg32 *) BuzzerFreq__INTCFG)
#define BuzzerFreq_INTSTAT                (* (reg32 *) BuzzerFreq__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BuzzerFreq_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BuzzerFreq__SIO)
    #define BuzzerFreq_SIO_REG            (* (reg32 *) BuzzerFreq__SIO)
#endif /* (BuzzerFreq__SIO_CFG) */

/* USBIO registers */
#if !defined(BuzzerFreq__PC) && (CY_PSOC4_4200L)
    #define BuzzerFreq_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BuzzerFreq_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BuzzerFreq_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BuzzerFreq_DRIVE_MODE_SHIFT       (0x00u)
#define BuzzerFreq_DRIVE_MODE_MASK        (0x07u << BuzzerFreq_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BuzzerFreq_H */


/* [] END OF FILE */
