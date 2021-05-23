/*******************************************************************************
* File Name: BuzzerVol.h  
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

#if !defined(CY_PINS_BuzzerVol_H) /* Pins BuzzerVol_H */
#define CY_PINS_BuzzerVol_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BuzzerVol_aliases.h"


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
} BuzzerVol_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BuzzerVol_Read(void);
void    BuzzerVol_Write(uint8 value);
uint8   BuzzerVol_ReadDataReg(void);
#if defined(BuzzerVol__PC) || (CY_PSOC4_4200L) 
    void    BuzzerVol_SetDriveMode(uint8 mode);
#endif
void    BuzzerVol_SetInterruptMode(uint16 position, uint16 mode);
uint8   BuzzerVol_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BuzzerVol_Sleep(void); 
void BuzzerVol_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BuzzerVol__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BuzzerVol_DRIVE_MODE_BITS        (3)
    #define BuzzerVol_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BuzzerVol_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BuzzerVol_SetDriveMode() function.
         *  @{
         */
        #define BuzzerVol_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BuzzerVol_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BuzzerVol_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BuzzerVol_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BuzzerVol_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BuzzerVol_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BuzzerVol_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BuzzerVol_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BuzzerVol_MASK               BuzzerVol__MASK
#define BuzzerVol_SHIFT              BuzzerVol__SHIFT
#define BuzzerVol_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BuzzerVol_SetInterruptMode() function.
     *  @{
     */
        #define BuzzerVol_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BuzzerVol_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BuzzerVol_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BuzzerVol_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BuzzerVol__SIO)
    #define BuzzerVol_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BuzzerVol__PC) && (CY_PSOC4_4200L)
    #define BuzzerVol_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BuzzerVol_USBIO_DISABLE              ((uint32)(~BuzzerVol_USBIO_ENABLE))
    #define BuzzerVol_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BuzzerVol_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BuzzerVol_USBIO_ENTER_SLEEP          ((uint32)((1u << BuzzerVol_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BuzzerVol_USBIO_SUSPEND_DEL_SHIFT)))
    #define BuzzerVol_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BuzzerVol_USBIO_SUSPEND_SHIFT)))
    #define BuzzerVol_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BuzzerVol_USBIO_SUSPEND_DEL_SHIFT)))
    #define BuzzerVol_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BuzzerVol__PC)
    /* Port Configuration */
    #define BuzzerVol_PC                 (* (reg32 *) BuzzerVol__PC)
#endif
/* Pin State */
#define BuzzerVol_PS                     (* (reg32 *) BuzzerVol__PS)
/* Data Register */
#define BuzzerVol_DR                     (* (reg32 *) BuzzerVol__DR)
/* Input Buffer Disable Override */
#define BuzzerVol_INP_DIS                (* (reg32 *) BuzzerVol__PC2)

/* Interrupt configuration Registers */
#define BuzzerVol_INTCFG                 (* (reg32 *) BuzzerVol__INTCFG)
#define BuzzerVol_INTSTAT                (* (reg32 *) BuzzerVol__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BuzzerVol_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BuzzerVol__SIO)
    #define BuzzerVol_SIO_REG            (* (reg32 *) BuzzerVol__SIO)
#endif /* (BuzzerVol__SIO_CFG) */

/* USBIO registers */
#if !defined(BuzzerVol__PC) && (CY_PSOC4_4200L)
    #define BuzzerVol_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BuzzerVol_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BuzzerVol_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BuzzerVol_DRIVE_MODE_SHIFT       (0x00u)
#define BuzzerVol_DRIVE_MODE_MASK        (0x07u << BuzzerVol_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BuzzerVol_H */


/* [] END OF FILE */
