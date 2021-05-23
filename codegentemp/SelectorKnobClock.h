/*******************************************************************************
* File Name: SelectorKnobClock.h  
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

#if !defined(CY_PINS_SelectorKnobClock_H) /* Pins SelectorKnobClock_H */
#define CY_PINS_SelectorKnobClock_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SelectorKnobClock_aliases.h"


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
} SelectorKnobClock_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SelectorKnobClock_Read(void);
void    SelectorKnobClock_Write(uint8 value);
uint8   SelectorKnobClock_ReadDataReg(void);
#if defined(SelectorKnobClock__PC) || (CY_PSOC4_4200L) 
    void    SelectorKnobClock_SetDriveMode(uint8 mode);
#endif
void    SelectorKnobClock_SetInterruptMode(uint16 position, uint16 mode);
uint8   SelectorKnobClock_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SelectorKnobClock_Sleep(void); 
void SelectorKnobClock_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SelectorKnobClock__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SelectorKnobClock_DRIVE_MODE_BITS        (3)
    #define SelectorKnobClock_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SelectorKnobClock_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SelectorKnobClock_SetDriveMode() function.
         *  @{
         */
        #define SelectorKnobClock_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SelectorKnobClock_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SelectorKnobClock_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SelectorKnobClock_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SelectorKnobClock_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SelectorKnobClock_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SelectorKnobClock_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SelectorKnobClock_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SelectorKnobClock_MASK               SelectorKnobClock__MASK
#define SelectorKnobClock_SHIFT              SelectorKnobClock__SHIFT
#define SelectorKnobClock_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SelectorKnobClock_SetInterruptMode() function.
     *  @{
     */
        #define SelectorKnobClock_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SelectorKnobClock_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SelectorKnobClock_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SelectorKnobClock_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SelectorKnobClock__SIO)
    #define SelectorKnobClock_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SelectorKnobClock__PC) && (CY_PSOC4_4200L)
    #define SelectorKnobClock_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SelectorKnobClock_USBIO_DISABLE              ((uint32)(~SelectorKnobClock_USBIO_ENABLE))
    #define SelectorKnobClock_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SelectorKnobClock_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SelectorKnobClock_USBIO_ENTER_SLEEP          ((uint32)((1u << SelectorKnobClock_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SelectorKnobClock_USBIO_SUSPEND_DEL_SHIFT)))
    #define SelectorKnobClock_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SelectorKnobClock_USBIO_SUSPEND_SHIFT)))
    #define SelectorKnobClock_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SelectorKnobClock_USBIO_SUSPEND_DEL_SHIFT)))
    #define SelectorKnobClock_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SelectorKnobClock__PC)
    /* Port Configuration */
    #define SelectorKnobClock_PC                 (* (reg32 *) SelectorKnobClock__PC)
#endif
/* Pin State */
#define SelectorKnobClock_PS                     (* (reg32 *) SelectorKnobClock__PS)
/* Data Register */
#define SelectorKnobClock_DR                     (* (reg32 *) SelectorKnobClock__DR)
/* Input Buffer Disable Override */
#define SelectorKnobClock_INP_DIS                (* (reg32 *) SelectorKnobClock__PC2)

/* Interrupt configuration Registers */
#define SelectorKnobClock_INTCFG                 (* (reg32 *) SelectorKnobClock__INTCFG)
#define SelectorKnobClock_INTSTAT                (* (reg32 *) SelectorKnobClock__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SelectorKnobClock_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SelectorKnobClock__SIO)
    #define SelectorKnobClock_SIO_REG            (* (reg32 *) SelectorKnobClock__SIO)
#endif /* (SelectorKnobClock__SIO_CFG) */

/* USBIO registers */
#if !defined(SelectorKnobClock__PC) && (CY_PSOC4_4200L)
    #define SelectorKnobClock_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SelectorKnobClock_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SelectorKnobClock_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SelectorKnobClock_DRIVE_MODE_SHIFT       (0x00u)
#define SelectorKnobClock_DRIVE_MODE_MASK        (0x07u << SelectorKnobClock_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SelectorKnobClock_H */


/* [] END OF FILE */
