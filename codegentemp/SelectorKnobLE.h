/*******************************************************************************
* File Name: SelectorKnobLE.h  
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

#if !defined(CY_PINS_SelectorKnobLE_H) /* Pins SelectorKnobLE_H */
#define CY_PINS_SelectorKnobLE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SelectorKnobLE_aliases.h"


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
} SelectorKnobLE_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SelectorKnobLE_Read(void);
void    SelectorKnobLE_Write(uint8 value);
uint8   SelectorKnobLE_ReadDataReg(void);
#if defined(SelectorKnobLE__PC) || (CY_PSOC4_4200L) 
    void    SelectorKnobLE_SetDriveMode(uint8 mode);
#endif
void    SelectorKnobLE_SetInterruptMode(uint16 position, uint16 mode);
uint8   SelectorKnobLE_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SelectorKnobLE_Sleep(void); 
void SelectorKnobLE_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SelectorKnobLE__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SelectorKnobLE_DRIVE_MODE_BITS        (3)
    #define SelectorKnobLE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SelectorKnobLE_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SelectorKnobLE_SetDriveMode() function.
         *  @{
         */
        #define SelectorKnobLE_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SelectorKnobLE_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SelectorKnobLE_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SelectorKnobLE_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SelectorKnobLE_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SelectorKnobLE_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SelectorKnobLE_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SelectorKnobLE_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SelectorKnobLE_MASK               SelectorKnobLE__MASK
#define SelectorKnobLE_SHIFT              SelectorKnobLE__SHIFT
#define SelectorKnobLE_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SelectorKnobLE_SetInterruptMode() function.
     *  @{
     */
        #define SelectorKnobLE_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SelectorKnobLE_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SelectorKnobLE_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SelectorKnobLE_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SelectorKnobLE__SIO)
    #define SelectorKnobLE_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SelectorKnobLE__PC) && (CY_PSOC4_4200L)
    #define SelectorKnobLE_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SelectorKnobLE_USBIO_DISABLE              ((uint32)(~SelectorKnobLE_USBIO_ENABLE))
    #define SelectorKnobLE_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SelectorKnobLE_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SelectorKnobLE_USBIO_ENTER_SLEEP          ((uint32)((1u << SelectorKnobLE_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SelectorKnobLE_USBIO_SUSPEND_DEL_SHIFT)))
    #define SelectorKnobLE_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SelectorKnobLE_USBIO_SUSPEND_SHIFT)))
    #define SelectorKnobLE_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SelectorKnobLE_USBIO_SUSPEND_DEL_SHIFT)))
    #define SelectorKnobLE_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SelectorKnobLE__PC)
    /* Port Configuration */
    #define SelectorKnobLE_PC                 (* (reg32 *) SelectorKnobLE__PC)
#endif
/* Pin State */
#define SelectorKnobLE_PS                     (* (reg32 *) SelectorKnobLE__PS)
/* Data Register */
#define SelectorKnobLE_DR                     (* (reg32 *) SelectorKnobLE__DR)
/* Input Buffer Disable Override */
#define SelectorKnobLE_INP_DIS                (* (reg32 *) SelectorKnobLE__PC2)

/* Interrupt configuration Registers */
#define SelectorKnobLE_INTCFG                 (* (reg32 *) SelectorKnobLE__INTCFG)
#define SelectorKnobLE_INTSTAT                (* (reg32 *) SelectorKnobLE__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SelectorKnobLE_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SelectorKnobLE__SIO)
    #define SelectorKnobLE_SIO_REG            (* (reg32 *) SelectorKnobLE__SIO)
#endif /* (SelectorKnobLE__SIO_CFG) */

/* USBIO registers */
#if !defined(SelectorKnobLE__PC) && (CY_PSOC4_4200L)
    #define SelectorKnobLE_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SelectorKnobLE_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SelectorKnobLE_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SelectorKnobLE_DRIVE_MODE_SHIFT       (0x00u)
#define SelectorKnobLE_DRIVE_MODE_MASK        (0x07u << SelectorKnobLE_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SelectorKnobLE_H */


/* [] END OF FILE */
