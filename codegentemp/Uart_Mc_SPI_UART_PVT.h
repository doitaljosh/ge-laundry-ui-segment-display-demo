/***************************************************************************//**
* \file Uart_Mc_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_Uart_Mc_H)
#define CY_SCB_SPI_UART_PVT_Uart_Mc_H

#include "Uart_Mc_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (Uart_Mc_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  Uart_Mc_rxBufferHead;
    extern volatile uint32  Uart_Mc_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   Uart_Mc_rxBufferOverflow;
    /** @} globals */
#endif /* (Uart_Mc_INTERNAL_RX_SW_BUFFER_CONST) */

#if (Uart_Mc_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  Uart_Mc_txBufferHead;
    extern volatile uint32  Uart_Mc_txBufferTail;
#endif /* (Uart_Mc_INTERNAL_TX_SW_BUFFER_CONST) */

#if (Uart_Mc_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 Uart_Mc_rxBufferInternal[Uart_Mc_INTERNAL_RX_BUFFER_SIZE];
#endif /* (Uart_Mc_INTERNAL_RX_SW_BUFFER) */

#if (Uart_Mc_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 Uart_Mc_txBufferInternal[Uart_Mc_TX_BUFFER_SIZE];
#endif /* (Uart_Mc_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void Uart_Mc_SpiPostEnable(void);
void Uart_Mc_SpiStop(void);

#if (Uart_Mc_SCB_MODE_SPI_CONST_CFG)
    void Uart_Mc_SpiInit(void);
#endif /* (Uart_Mc_SCB_MODE_SPI_CONST_CFG) */

#if (Uart_Mc_SPI_WAKE_ENABLE_CONST)
    void Uart_Mc_SpiSaveConfig(void);
    void Uart_Mc_SpiRestoreConfig(void);
#endif /* (Uart_Mc_SPI_WAKE_ENABLE_CONST) */

void Uart_Mc_UartPostEnable(void);
void Uart_Mc_UartStop(void);

#if (Uart_Mc_SCB_MODE_UART_CONST_CFG)
    void Uart_Mc_UartInit(void);
#endif /* (Uart_Mc_SCB_MODE_UART_CONST_CFG) */

#if (Uart_Mc_UART_WAKE_ENABLE_CONST)
    void Uart_Mc_UartSaveConfig(void);
    void Uart_Mc_UartRestoreConfig(void);
#endif /* (Uart_Mc_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in Uart_Mc_SetPins() */
#define Uart_Mc_UART_RX_PIN_ENABLE    (Uart_Mc_UART_RX)
#define Uart_Mc_UART_TX_PIN_ENABLE    (Uart_Mc_UART_TX)

/* UART RTS and CTS position to be used in  Uart_Mc_SetPins() */
#define Uart_Mc_UART_RTS_PIN_ENABLE    (0x10u)
#define Uart_Mc_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define Uart_Mc_SpiUartEnableIntRx(intSourceMask)  Uart_Mc_SetRxInterruptMode(intSourceMask)
#define Uart_Mc_SpiUartEnableIntTx(intSourceMask)  Uart_Mc_SetTxInterruptMode(intSourceMask)
uint32  Uart_Mc_SpiUartDisableIntRx(void);
uint32  Uart_Mc_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_Uart_Mc_H) */


/* [] END OF FILE */
