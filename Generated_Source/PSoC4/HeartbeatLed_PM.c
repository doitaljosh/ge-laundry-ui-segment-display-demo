/*******************************************************************************
* File Name: HeartbeatLed.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "HeartbeatLed.h"

static HeartbeatLed_BACKUP_STRUCT  HeartbeatLed_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: HeartbeatLed_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet HeartbeatLed_SUT.c usage_HeartbeatLed_Sleep_Wakeup
*******************************************************************************/
void HeartbeatLed_Sleep(void)
{
    #if defined(HeartbeatLed__PC)
        HeartbeatLed_backup.pcState = HeartbeatLed_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            HeartbeatLed_backup.usbState = HeartbeatLed_CR1_REG;
            HeartbeatLed_USB_POWER_REG |= HeartbeatLed_USBIO_ENTER_SLEEP;
            HeartbeatLed_CR1_REG &= HeartbeatLed_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(HeartbeatLed__SIO)
        HeartbeatLed_backup.sioState = HeartbeatLed_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        HeartbeatLed_SIO_REG &= (uint32)(~HeartbeatLed_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: HeartbeatLed_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to HeartbeatLed_Sleep() for an example usage.
*******************************************************************************/
void HeartbeatLed_Wakeup(void)
{
    #if defined(HeartbeatLed__PC)
        HeartbeatLed_PC = HeartbeatLed_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            HeartbeatLed_USB_POWER_REG &= HeartbeatLed_USBIO_EXIT_SLEEP_PH1;
            HeartbeatLed_CR1_REG = HeartbeatLed_backup.usbState;
            HeartbeatLed_USB_POWER_REG &= HeartbeatLed_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(HeartbeatLed__SIO)
        HeartbeatLed_SIO_REG = HeartbeatLed_backup.sioState;
    #endif
}


/* [] END OF FILE */
