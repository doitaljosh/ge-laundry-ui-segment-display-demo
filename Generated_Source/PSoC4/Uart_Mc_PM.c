/***************************************************************************//**
* \file Uart_Mc_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Uart_Mc.h"
#include "Uart_Mc_PVT.h"

#if(Uart_Mc_SCB_MODE_I2C_INC)
    #include "Uart_Mc_I2C_PVT.h"
#endif /* (Uart_Mc_SCB_MODE_I2C_INC) */

#if(Uart_Mc_SCB_MODE_EZI2C_INC)
    #include "Uart_Mc_EZI2C_PVT.h"
#endif /* (Uart_Mc_SCB_MODE_EZI2C_INC) */

#if(Uart_Mc_SCB_MODE_SPI_INC || Uart_Mc_SCB_MODE_UART_INC)
    #include "Uart_Mc_SPI_UART_PVT.h"
#endif /* (Uart_Mc_SCB_MODE_SPI_INC || Uart_Mc_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG || \
   (Uart_Mc_SCB_MODE_I2C_CONST_CFG   && (!Uart_Mc_I2C_WAKE_ENABLE_CONST))   || \
   (Uart_Mc_SCB_MODE_EZI2C_CONST_CFG && (!Uart_Mc_EZI2C_WAKE_ENABLE_CONST)) || \
   (Uart_Mc_SCB_MODE_SPI_CONST_CFG   && (!Uart_Mc_SPI_WAKE_ENABLE_CONST))   || \
   (Uart_Mc_SCB_MODE_UART_CONST_CFG  && (!Uart_Mc_UART_WAKE_ENABLE_CONST)))

    Uart_Mc_BACKUP_STRUCT Uart_Mc_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: Uart_Mc_Sleep
****************************************************************************//**
*
*  Prepares the Uart_Mc component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the Uart_Mc_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void Uart_Mc_Sleep(void)
{
#if(Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Uart_Mc_SCB_WAKE_ENABLE_CHECK)
    {
        if(Uart_Mc_SCB_MODE_I2C_RUNTM_CFG)
        {
            Uart_Mc_I2CSaveConfig();
        }
        else if(Uart_Mc_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Uart_Mc_EzI2CSaveConfig();
        }
    #if(!Uart_Mc_CY_SCBIP_V1)
        else if(Uart_Mc_SCB_MODE_SPI_RUNTM_CFG)
        {
            Uart_Mc_SpiSaveConfig();
        }
        else if(Uart_Mc_SCB_MODE_UART_RUNTM_CFG)
        {
            Uart_Mc_UartSaveConfig();
        }
    #endif /* (!Uart_Mc_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        Uart_Mc_backup.enableState = (uint8) Uart_Mc_GET_CTRL_ENABLED;

        if(0u != Uart_Mc_backup.enableState)
        {
            Uart_Mc_Stop();
        }
    }

#else

    #if (Uart_Mc_SCB_MODE_I2C_CONST_CFG && Uart_Mc_I2C_WAKE_ENABLE_CONST)
        Uart_Mc_I2CSaveConfig();

    #elif (Uart_Mc_SCB_MODE_EZI2C_CONST_CFG && Uart_Mc_EZI2C_WAKE_ENABLE_CONST)
        Uart_Mc_EzI2CSaveConfig();

    #elif (Uart_Mc_SCB_MODE_SPI_CONST_CFG && Uart_Mc_SPI_WAKE_ENABLE_CONST)
        Uart_Mc_SpiSaveConfig();

    #elif (Uart_Mc_SCB_MODE_UART_CONST_CFG && Uart_Mc_UART_WAKE_ENABLE_CONST)
        Uart_Mc_UartSaveConfig();

    #else

        Uart_Mc_backup.enableState = (uint8) Uart_Mc_GET_CTRL_ENABLED;

        if(0u != Uart_Mc_backup.enableState)
        {
            Uart_Mc_Stop();
        }

    #endif /* defined (Uart_Mc_SCB_MODE_I2C_CONST_CFG) && (Uart_Mc_I2C_WAKE_ENABLE_CONST) */

#endif /* (Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Uart_Mc_Wakeup
****************************************************************************//**
*
*  Prepares the Uart_Mc component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the Uart_Mc_Wakeup() function without first calling the 
*   Uart_Mc_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void Uart_Mc_Wakeup(void)
{
#if(Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Uart_Mc_SCB_WAKE_ENABLE_CHECK)
    {
        if(Uart_Mc_SCB_MODE_I2C_RUNTM_CFG)
        {
            Uart_Mc_I2CRestoreConfig();
        }
        else if(Uart_Mc_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Uart_Mc_EzI2CRestoreConfig();
        }
    #if(!Uart_Mc_CY_SCBIP_V1)
        else if(Uart_Mc_SCB_MODE_SPI_RUNTM_CFG)
        {
            Uart_Mc_SpiRestoreConfig();
        }
        else if(Uart_Mc_SCB_MODE_UART_RUNTM_CFG)
        {
            Uart_Mc_UartRestoreConfig();
        }
    #endif /* (!Uart_Mc_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != Uart_Mc_backup.enableState)
        {
            Uart_Mc_Enable();
        }
    }

#else

    #if (Uart_Mc_SCB_MODE_I2C_CONST_CFG  && Uart_Mc_I2C_WAKE_ENABLE_CONST)
        Uart_Mc_I2CRestoreConfig();

    #elif (Uart_Mc_SCB_MODE_EZI2C_CONST_CFG && Uart_Mc_EZI2C_WAKE_ENABLE_CONST)
        Uart_Mc_EzI2CRestoreConfig();

    #elif (Uart_Mc_SCB_MODE_SPI_CONST_CFG && Uart_Mc_SPI_WAKE_ENABLE_CONST)
        Uart_Mc_SpiRestoreConfig();

    #elif (Uart_Mc_SCB_MODE_UART_CONST_CFG && Uart_Mc_UART_WAKE_ENABLE_CONST)
        Uart_Mc_UartRestoreConfig();

    #else

        if(0u != Uart_Mc_backup.enableState)
        {
            Uart_Mc_Enable();
        }

    #endif /* (Uart_Mc_I2C_WAKE_ENABLE_CONST) */

#endif /* (Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
