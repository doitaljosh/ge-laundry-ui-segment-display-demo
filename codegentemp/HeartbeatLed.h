/*******************************************************************************
* File Name: HeartbeatLed.h  
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

#if !defined(CY_PINS_HeartbeatLed_H) /* Pins HeartbeatLed_H */
#define CY_PINS_HeartbeatLed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HeartbeatLed_aliases.h"


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
} HeartbeatLed_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   HeartbeatLed_Read(void);
void    HeartbeatLed_Write(uint8 value);
uint8   HeartbeatLed_ReadDataReg(void);
#if defined(HeartbeatLed__PC) || (CY_PSOC4_4200L) 
    void    HeartbeatLed_SetDriveMode(uint8 mode);
#endif
void    HeartbeatLed_SetInterruptMode(uint16 position, uint16 mode);
uint8   HeartbeatLed_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void HeartbeatLed_Sleep(void); 
void HeartbeatLed_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(HeartbeatLed__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define HeartbeatLed_DRIVE_MODE_BITS        (3)
    #define HeartbeatLed_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HeartbeatLed_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the HeartbeatLed_SetDriveMode() function.
         *  @{
         */
        #define HeartbeatLed_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define HeartbeatLed_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define HeartbeatLed_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define HeartbeatLed_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define HeartbeatLed_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define HeartbeatLed_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define HeartbeatLed_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define HeartbeatLed_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define HeartbeatLed_MASK               HeartbeatLed__MASK
#define HeartbeatLed_SHIFT              HeartbeatLed__SHIFT
#define HeartbeatLed_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HeartbeatLed_SetInterruptMode() function.
     *  @{
     */
        #define HeartbeatLed_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define HeartbeatLed_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define HeartbeatLed_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define HeartbeatLed_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(HeartbeatLed__SIO)
    #define HeartbeatLed_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(HeartbeatLed__PC) && (CY_PSOC4_4200L)
    #define HeartbeatLed_USBIO_ENABLE               ((uint32)0x80000000u)
    #define HeartbeatLed_USBIO_DISABLE              ((uint32)(~HeartbeatLed_USBIO_ENABLE))
    #define HeartbeatLed_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define HeartbeatLed_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define HeartbeatLed_USBIO_ENTER_SLEEP          ((uint32)((1u << HeartbeatLed_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << HeartbeatLed_USBIO_SUSPEND_DEL_SHIFT)))
    #define HeartbeatLed_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << HeartbeatLed_USBIO_SUSPEND_SHIFT)))
    #define HeartbeatLed_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << HeartbeatLed_USBIO_SUSPEND_DEL_SHIFT)))
    #define HeartbeatLed_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(HeartbeatLed__PC)
    /* Port Configuration */
    #define HeartbeatLed_PC                 (* (reg32 *) HeartbeatLed__PC)
#endif
/* Pin State */
#define HeartbeatLed_PS                     (* (reg32 *) HeartbeatLed__PS)
/* Data Register */
#define HeartbeatLed_DR                     (* (reg32 *) HeartbeatLed__DR)
/* Input Buffer Disable Override */
#define HeartbeatLed_INP_DIS                (* (reg32 *) HeartbeatLed__PC2)

/* Interrupt configuration Registers */
#define HeartbeatLed_INTCFG                 (* (reg32 *) HeartbeatLed__INTCFG)
#define HeartbeatLed_INTSTAT                (* (reg32 *) HeartbeatLed__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define HeartbeatLed_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(HeartbeatLed__SIO)
    #define HeartbeatLed_SIO_REG            (* (reg32 *) HeartbeatLed__SIO)
#endif /* (HeartbeatLed__SIO_CFG) */

/* USBIO registers */
#if !defined(HeartbeatLed__PC) && (CY_PSOC4_4200L)
    #define HeartbeatLed_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define HeartbeatLed_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define HeartbeatLed_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define HeartbeatLed_DRIVE_MODE_SHIFT       (0x00u)
#define HeartbeatLed_DRIVE_MODE_MASK        (0x07u << HeartbeatLed_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins HeartbeatLed_H */


/* [] END OF FILE */
