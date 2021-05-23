/*******************************************************************************
* File Name: SelectorKnobData.h  
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

#if !defined(CY_PINS_SelectorKnobData_H) /* Pins SelectorKnobData_H */
#define CY_PINS_SelectorKnobData_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SelectorKnobData_aliases.h"


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
} SelectorKnobData_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SelectorKnobData_Read(void);
void    SelectorKnobData_Write(uint8 value);
uint8   SelectorKnobData_ReadDataReg(void);
#if defined(SelectorKnobData__PC) || (CY_PSOC4_4200L) 
    void    SelectorKnobData_SetDriveMode(uint8 mode);
#endif
void    SelectorKnobData_SetInterruptMode(uint16 position, uint16 mode);
uint8   SelectorKnobData_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SelectorKnobData_Sleep(void); 
void SelectorKnobData_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SelectorKnobData__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SelectorKnobData_DRIVE_MODE_BITS        (3)
    #define SelectorKnobData_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SelectorKnobData_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SelectorKnobData_SetDriveMode() function.
         *  @{
         */
        #define SelectorKnobData_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SelectorKnobData_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SelectorKnobData_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SelectorKnobData_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SelectorKnobData_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SelectorKnobData_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SelectorKnobData_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SelectorKnobData_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SelectorKnobData_MASK               SelectorKnobData__MASK
#define SelectorKnobData_SHIFT              SelectorKnobData__SHIFT
#define SelectorKnobData_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SelectorKnobData_SetInterruptMode() function.
     *  @{
     */
        #define SelectorKnobData_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SelectorKnobData_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SelectorKnobData_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SelectorKnobData_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SelectorKnobData__SIO)
    #define SelectorKnobData_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SelectorKnobData__PC) && (CY_PSOC4_4200L)
    #define SelectorKnobData_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SelectorKnobData_USBIO_DISABLE              ((uint32)(~SelectorKnobData_USBIO_ENABLE))
    #define SelectorKnobData_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SelectorKnobData_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SelectorKnobData_USBIO_ENTER_SLEEP          ((uint32)((1u << SelectorKnobData_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SelectorKnobData_USBIO_SUSPEND_DEL_SHIFT)))
    #define SelectorKnobData_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SelectorKnobData_USBIO_SUSPEND_SHIFT)))
    #define SelectorKnobData_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SelectorKnobData_USBIO_SUSPEND_DEL_SHIFT)))
    #define SelectorKnobData_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SelectorKnobData__PC)
    /* Port Configuration */
    #define SelectorKnobData_PC                 (* (reg32 *) SelectorKnobData__PC)
#endif
/* Pin State */
#define SelectorKnobData_PS                     (* (reg32 *) SelectorKnobData__PS)
/* Data Register */
#define SelectorKnobData_DR                     (* (reg32 *) SelectorKnobData__DR)
/* Input Buffer Disable Override */
#define SelectorKnobData_INP_DIS                (* (reg32 *) SelectorKnobData__PC2)

/* Interrupt configuration Registers */
#define SelectorKnobData_INTCFG                 (* (reg32 *) SelectorKnobData__INTCFG)
#define SelectorKnobData_INTSTAT                (* (reg32 *) SelectorKnobData__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SelectorKnobData_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SelectorKnobData__SIO)
    #define SelectorKnobData_SIO_REG            (* (reg32 *) SelectorKnobData__SIO)
#endif /* (SelectorKnobData__SIO_CFG) */

/* USBIO registers */
#if !defined(SelectorKnobData__PC) && (CY_PSOC4_4200L)
    #define SelectorKnobData_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SelectorKnobData_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SelectorKnobData_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SelectorKnobData_DRIVE_MODE_SHIFT       (0x00u)
#define SelectorKnobData_DRIVE_MODE_MASK        (0x07u << SelectorKnobData_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SelectorKnobData_H */


/* [] END OF FILE */
