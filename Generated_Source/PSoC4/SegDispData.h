/*******************************************************************************
* File Name: SegDispData.h  
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

#if !defined(CY_PINS_SegDispData_H) /* Pins SegDispData_H */
#define CY_PINS_SegDispData_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SegDispData_aliases.h"


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
} SegDispData_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SegDispData_Read(void);
void    SegDispData_Write(uint8 value);
uint8   SegDispData_ReadDataReg(void);
#if defined(SegDispData__PC) || (CY_PSOC4_4200L) 
    void    SegDispData_SetDriveMode(uint8 mode);
#endif
void    SegDispData_SetInterruptMode(uint16 position, uint16 mode);
uint8   SegDispData_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SegDispData_Sleep(void); 
void SegDispData_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SegDispData__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SegDispData_DRIVE_MODE_BITS        (3)
    #define SegDispData_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SegDispData_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SegDispData_SetDriveMode() function.
         *  @{
         */
        #define SegDispData_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SegDispData_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SegDispData_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SegDispData_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SegDispData_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SegDispData_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SegDispData_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SegDispData_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SegDispData_MASK               SegDispData__MASK
#define SegDispData_SHIFT              SegDispData__SHIFT
#define SegDispData_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SegDispData_SetInterruptMode() function.
     *  @{
     */
        #define SegDispData_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SegDispData_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SegDispData_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SegDispData_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SegDispData__SIO)
    #define SegDispData_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SegDispData__PC) && (CY_PSOC4_4200L)
    #define SegDispData_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SegDispData_USBIO_DISABLE              ((uint32)(~SegDispData_USBIO_ENABLE))
    #define SegDispData_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SegDispData_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SegDispData_USBIO_ENTER_SLEEP          ((uint32)((1u << SegDispData_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SegDispData_USBIO_SUSPEND_DEL_SHIFT)))
    #define SegDispData_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SegDispData_USBIO_SUSPEND_SHIFT)))
    #define SegDispData_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SegDispData_USBIO_SUSPEND_DEL_SHIFT)))
    #define SegDispData_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SegDispData__PC)
    /* Port Configuration */
    #define SegDispData_PC                 (* (reg32 *) SegDispData__PC)
#endif
/* Pin State */
#define SegDispData_PS                     (* (reg32 *) SegDispData__PS)
/* Data Register */
#define SegDispData_DR                     (* (reg32 *) SegDispData__DR)
/* Input Buffer Disable Override */
#define SegDispData_INP_DIS                (* (reg32 *) SegDispData__PC2)

/* Interrupt configuration Registers */
#define SegDispData_INTCFG                 (* (reg32 *) SegDispData__INTCFG)
#define SegDispData_INTSTAT                (* (reg32 *) SegDispData__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SegDispData_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SegDispData__SIO)
    #define SegDispData_SIO_REG            (* (reg32 *) SegDispData__SIO)
#endif /* (SegDispData__SIO_CFG) */

/* USBIO registers */
#if !defined(SegDispData__PC) && (CY_PSOC4_4200L)
    #define SegDispData_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SegDispData_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SegDispData_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SegDispData_DRIVE_MODE_SHIFT       (0x00u)
#define SegDispData_DRIVE_MODE_MASK        (0x07u << SegDispData_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SegDispData_H */


/* [] END OF FILE */
