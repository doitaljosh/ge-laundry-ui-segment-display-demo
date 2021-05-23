/***************************************************************************//**
* \file Uart_PowerStart_PM.c
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

#include "Uart_PowerStart.h"
#include "Uart_PowerStart_PVT.h"

#if(Uart_PowerStart_SCB_MODE_I2C_INC)
    #include "Uart_PowerStart_I2C_PVT.h"
#endif /* (Uart_PowerStart_SCB_MODE_I2C_INC) */

#if(Uart_PowerStart_SCB_MODE_EZI2C_INC)
    #include "Uart_PowerStart_EZI2C_PVT.h"
#endif /* (Uart_PowerStart_SCB_MODE_EZI2C_INC) */

#if(Uart_PowerStart_SCB_MODE_SPI_INC || Uart_PowerStart_SCB_MODE_UART_INC)
    #include "Uart_PowerStart_SPI_UART_PVT.h"
#endif /* (Uart_PowerStart_SCB_MODE_SPI_INC || Uart_PowerStart_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(Uart_PowerStart_SCB_MODE_UNCONFIG_CONST_CFG || \
   (Uart_PowerStart_SCB_MODE_I2C_CONST_CFG   && (!Uart_PowerStart_I2C_WAKE_ENABLE_CONST))   || \
   (Uart_PowerStart_SCB_MODE_EZI2C_CONST_CFG && (!Uart_PowerStart_EZI2C_WAKE_ENABLE_CONST)) || \
   (Uart_PowerStart_SCB_MODE_SPI_CONST_CFG   && (!Uart_PowerStart_SPI_WAKE_ENABLE_CONST))   || \
   (Uart_PowerStart_SCB_MODE_UART_CONST_CFG  && (!Uart_PowerStart_UART_WAKE_ENABLE_CONST)))

    Uart_PowerStart_BACKUP_STRUCT Uart_PowerStart_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: Uart_PowerStart_Sleep
****************************************************************************//**
*
*  Prepares the Uart_PowerStart component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the Uart_PowerStart_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void Uart_PowerStart_Sleep(void)
{
#if(Uart_PowerStart_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Uart_PowerStart_SCB_WAKE_ENABLE_CHECK)
    {
        if(Uart_PowerStart_SCB_MODE_I2C_RUNTM_CFG)
        {
            Uart_PowerStart_I2CSaveConfig();
        }
        else if(Uart_PowerStart_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Uart_PowerStart_EzI2CSaveConfig();
        }
    #if(!Uart_PowerStart_CY_SCBIP_V1)
        else if(Uart_PowerStart_SCB_MODE_SPI_RUNTM_CFG)
        {
            Uart_PowerStart_SpiSaveConfig();
        }
        else if(Uart_PowerStart_SCB_MODE_UART_RUNTM_CFG)
        {
            Uart_PowerStart_UartSaveConfig();
        }
    #endif /* (!Uart_PowerStart_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        Uart_PowerStart_backup.enableState = (uint8) Uart_PowerStart_GET_CTRL_ENABLED;

        if(0u != Uart_PowerStart_backup.enableState)
        {
            Uart_PowerStart_Stop();
        }
    }

#else

    #if (Uart_PowerStart_SCB_MODE_I2C_CONST_CFG && Uart_PowerStart_I2C_WAKE_ENABLE_CONST)
        Uart_PowerStart_I2CSaveConfig();

    #elif (Uart_PowerStart_SCB_MODE_EZI2C_CONST_CFG && Uart_PowerStart_EZI2C_WAKE_ENABLE_CONST)
        Uart_PowerStart_EzI2CSaveConfig();

    #elif (Uart_PowerStart_SCB_MODE_SPI_CONST_CFG && Uart_PowerStart_SPI_WAKE_ENABLE_CONST)
        Uart_PowerStart_SpiSaveConfig();

    #elif (Uart_PowerStart_SCB_MODE_UART_CONST_CFG && Uart_PowerStart_UART_WAKE_ENABLE_CONST)
        Uart_PowerStart_UartSaveConfig();

    #else

        Uart_PowerStart_backup.enableState = (uint8) Uart_PowerStart_GET_CTRL_ENABLED;

        if(0u != Uart_PowerStart_backup.enableState)
        {
            Uart_PowerStart_Stop();
        }

    #endif /* defined (Uart_PowerStart_SCB_MODE_I2C_CONST_CFG) && (Uart_PowerStart_I2C_WAKE_ENABLE_CONST) */

#endif /* (Uart_PowerStart_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Uart_PowerStart_Wakeup
****************************************************************************//**
*
*  Prepares the Uart_PowerStart component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the Uart_PowerStart_Wakeup() function without first calling the 
*   Uart_PowerStart_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void Uart_PowerStart_Wakeup(void)
{
#if(Uart_PowerStart_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Uart_PowerStart_SCB_WAKE_ENABLE_CHECK)
    {
        if(Uart_PowerStart_SCB_MODE_I2C_RUNTM_CFG)
        {
            Uart_PowerStart_I2CRestoreConfig();
        }
        else if(Uart_PowerStart_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Uart_PowerStart_EzI2CRestoreConfig();
        }
    #if(!Uart_PowerStart_CY_SCBIP_V1)
        else if(Uart_PowerStart_SCB_MODE_SPI_RUNTM_CFG)
        {
            Uart_PowerStart_SpiRestoreConfig();
        }
        else if(Uart_PowerStart_SCB_MODE_UART_RUNTM_CFG)
        {
            Uart_PowerStart_UartRestoreConfig();
        }
    #endif /* (!Uart_PowerStart_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != Uart_PowerStart_backup.enableState)
        {
            Uart_PowerStart_Enable();
        }
    }

#else

    #if (Uart_PowerStart_SCB_MODE_I2C_CONST_CFG  && Uart_PowerStart_I2C_WAKE_ENABLE_CONST)
        Uart_PowerStart_I2CRestoreConfig();

    #elif (Uart_PowerStart_SCB_MODE_EZI2C_CONST_CFG && Uart_PowerStart_EZI2C_WAKE_ENABLE_CONST)
        Uart_PowerStart_EzI2CRestoreConfig();

    #elif (Uart_PowerStart_SCB_MODE_SPI_CONST_CFG && Uart_PowerStart_SPI_WAKE_ENABLE_CONST)
        Uart_PowerStart_SpiRestoreConfig();

    #elif (Uart_PowerStart_SCB_MODE_UART_CONST_CFG && Uart_PowerStart_UART_WAKE_ENABLE_CONST)
        Uart_PowerStart_UartRestoreConfig();

    #else

        if(0u != Uart_PowerStart_backup.enableState)
        {
            Uart_PowerStart_Enable();
        }

    #endif /* (Uart_PowerStart_I2C_WAKE_ENABLE_CONST) */

#endif /* (Uart_PowerStart_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
