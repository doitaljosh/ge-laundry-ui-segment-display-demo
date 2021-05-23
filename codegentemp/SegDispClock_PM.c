/*******************************************************************************
* File Name: SegDispClock.c  
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
#include "SegDispClock.h"

static SegDispClock_BACKUP_STRUCT  SegDispClock_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: SegDispClock_Sleep
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
*  \snippet SegDispClock_SUT.c usage_SegDispClock_Sleep_Wakeup
*******************************************************************************/
void SegDispClock_Sleep(void)
{
    #if defined(SegDispClock__PC)
        SegDispClock_backup.pcState = SegDispClock_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            SegDispClock_backup.usbState = SegDispClock_CR1_REG;
            SegDispClock_USB_POWER_REG |= SegDispClock_USBIO_ENTER_SLEEP;
            SegDispClock_CR1_REG &= SegDispClock_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SegDispClock__SIO)
        SegDispClock_backup.sioState = SegDispClock_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        SegDispClock_SIO_REG &= (uint32)(~SegDispClock_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: SegDispClock_Wakeup
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
*  Refer to SegDispClock_Sleep() for an example usage.
*******************************************************************************/
void SegDispClock_Wakeup(void)
{
    #if defined(SegDispClock__PC)
        SegDispClock_PC = SegDispClock_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            SegDispClock_USB_POWER_REG &= SegDispClock_USBIO_EXIT_SLEEP_PH1;
            SegDispClock_CR1_REG = SegDispClock_backup.usbState;
            SegDispClock_USB_POWER_REG &= SegDispClock_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SegDispClock__SIO)
        SegDispClock_SIO_REG = SegDispClock_backup.sioState;
    #endif
}


/* [] END OF FILE */
