/***************************************************************************//**
* \file Uart_PowerStart_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_Uart_PowerStart_H)
#define CY_SCB_SPI_UART_PVT_Uart_PowerStart_H

#include "Uart_PowerStart_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (Uart_PowerStart_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  Uart_PowerStart_rxBufferHead;
    extern volatile uint32  Uart_PowerStart_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   Uart_PowerStart_rxBufferOverflow;
    /** @} globals */
#endif /* (Uart_PowerStart_INTERNAL_RX_SW_BUFFER_CONST) */

#if (Uart_PowerStart_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  Uart_PowerStart_txBufferHead;
    extern volatile uint32  Uart_PowerStart_txBufferTail;
#endif /* (Uart_PowerStart_INTERNAL_TX_SW_BUFFER_CONST) */

#if (Uart_PowerStart_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 Uart_PowerStart_rxBufferInternal[Uart_PowerStart_INTERNAL_RX_BUFFER_SIZE];
#endif /* (Uart_PowerStart_INTERNAL_RX_SW_BUFFER) */

#if (Uart_PowerStart_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 Uart_PowerStart_txBufferInternal[Uart_PowerStart_TX_BUFFER_SIZE];
#endif /* (Uart_PowerStart_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void Uart_PowerStart_SpiPostEnable(void);
void Uart_PowerStart_SpiStop(void);

#if (Uart_PowerStart_SCB_MODE_SPI_CONST_CFG)
    void Uart_PowerStart_SpiInit(void);
#endif /* (Uart_PowerStart_SCB_MODE_SPI_CONST_CFG) */

#if (Uart_PowerStart_SPI_WAKE_ENABLE_CONST)
    void Uart_PowerStart_SpiSaveConfig(void);
    void Uart_PowerStart_SpiRestoreConfig(void);
#endif /* (Uart_PowerStart_SPI_WAKE_ENABLE_CONST) */

void Uart_PowerStart_UartPostEnable(void);
void Uart_PowerStart_UartStop(void);

#if (Uart_PowerStart_SCB_MODE_UART_CONST_CFG)
    void Uart_PowerStart_UartInit(void);
#endif /* (Uart_PowerStart_SCB_MODE_UART_CONST_CFG) */

#if (Uart_PowerStart_UART_WAKE_ENABLE_CONST)
    void Uart_PowerStart_UartSaveConfig(void);
    void Uart_PowerStart_UartRestoreConfig(void);
#endif /* (Uart_PowerStart_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in Uart_PowerStart_SetPins() */
#define Uart_PowerStart_UART_RX_PIN_ENABLE    (Uart_PowerStart_UART_RX)
#define Uart_PowerStart_UART_TX_PIN_ENABLE    (Uart_PowerStart_UART_TX)

/* UART RTS and CTS position to be used in  Uart_PowerStart_SetPins() */
#define Uart_PowerStart_UART_RTS_PIN_ENABLE    (0x10u)
#define Uart_PowerStart_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define Uart_PowerStart_SpiUartEnableIntRx(intSourceMask)  Uart_PowerStart_SetRxInterruptMode(intSourceMask)
#define Uart_PowerStart_SpiUartEnableIntTx(intSourceMask)  Uart_PowerStart_SetTxInterruptMode(intSourceMask)
uint32  Uart_PowerStart_SpiUartDisableIntRx(void);
uint32  Uart_PowerStart_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_Uart_PowerStart_H) */


/* [] END OF FILE */
