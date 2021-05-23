/*******************************************************************************
* File Name: SegDispClock.h  
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

#if !defined(CY_PINS_SegDispClock_H) /* Pins SegDispClock_H */
#define CY_PINS_SegDispClock_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SegDispClock_aliases.h"


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
} SegDispClock_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SegDispClock_Read(void);
void    SegDispClock_Write(uint8 value);
uint8   SegDispClock_ReadDataReg(void);
#if defined(SegDispClock__PC) || (CY_PSOC4_4200L) 
    void    SegDispClock_SetDriveMode(uint8 mode);
#endif
void    SegDispClock_SetInterruptMode(uint16 position, uint16 mode);
uint8   SegDispClock_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SegDispClock_Sleep(void); 
void SegDispClock_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SegDispClock__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SegDispClock_DRIVE_MODE_BITS        (3)
    #define SegDispClock_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SegDispClock_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SegDispClock_SetDriveMode() function.
         *  @{
         */
        #define SegDispClock_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SegDispClock_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SegDispClock_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SegDispClock_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SegDispClock_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SegDispClock_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SegDispClock_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SegDispClock_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SegDispClock_MASK               SegDispClock__MASK
#define SegDispClock_SHIFT              SegDispClock__SHIFT
#define SegDispClock_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SegDispClock_SetInterruptMode() function.
     *  @{
     */
        #define SegDispClock_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SegDispClock_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SegDispClock_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SegDispClock_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SegDispClock__SIO)
    #define SegDispClock_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SegDispClock__PC) && (CY_PSOC4_4200L)
    #define SegDispClock_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SegDispClock_USBIO_DISABLE              ((uint32)(~SegDispClock_USBIO_ENABLE))
    #define SegDispClock_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SegDispClock_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SegDispClock_USBIO_ENTER_SLEEP          ((uint32)((1u << SegDispClock_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SegDispClock_USBIO_SUSPEND_DEL_SHIFT)))
    #define SegDispClock_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SegDispClock_USBIO_SUSPEND_SHIFT)))
    #define SegDispClock_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SegDispClock_USBIO_SUSPEND_DEL_SHIFT)))
    #define SegDispClock_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SegDispClock__PC)
    /* Port Configuration */
    #define SegDispClock_PC                 (* (reg32 *) SegDispClock__PC)
#endif
/* Pin State */
#define SegDispClock_PS                     (* (reg32 *) SegDispClock__PS)
/* Data Register */
#define SegDispClock_DR                     (* (reg32 *) SegDispClock__DR)
/* Input Buffer Disable Override */
#define SegDispClock_INP_DIS                (* (reg32 *) SegDispClock__PC2)

/* Interrupt configuration Registers */
#define SegDispClock_INTCFG                 (* (reg32 *) SegDispClock__INTCFG)
#define SegDispClock_INTSTAT                (* (reg32 *) SegDispClock__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SegDispClock_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SegDispClock__SIO)
    #define SegDispClock_SIO_REG            (* (reg32 *) SegDispClock__SIO)
#endif /* (SegDispClock__SIO_CFG) */

/* USBIO registers */
#if !defined(SegDispClock__PC) && (CY_PSOC4_4200L)
    #define SegDispClock_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SegDispClock_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SegDispClock_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SegDispClock_DRIVE_MODE_SHIFT       (0x00u)
#define SegDispClock_DRIVE_MODE_MASK        (0x07u << SegDispClock_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SegDispClock_H */


/* [] END OF FILE */
