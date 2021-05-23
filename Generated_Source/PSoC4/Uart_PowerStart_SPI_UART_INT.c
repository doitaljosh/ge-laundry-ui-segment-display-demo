/***************************************************************************//**
* \file Uart_PowerStart_SPI_UART_INT.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
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

#include "Uart_PowerStart_PVT.h"
#include "Uart_PowerStart_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (Uart_PowerStart_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: Uart_PowerStart_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(Uart_PowerStart_SPI_UART_ISR)
{
#if (Uart_PowerStart_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (Uart_PowerStart_INTERNAL_RX_SW_BUFFER_CONST) */

#if (Uart_PowerStart_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (Uart_PowerStart_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef Uart_PowerStart_SPI_UART_ISR_ENTRY_CALLBACK
    Uart_PowerStart_SPI_UART_ISR_EntryCallback();
#endif /* Uart_PowerStart_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != Uart_PowerStart_customIntrHandler)
    {
        Uart_PowerStart_customIntrHandler();
    }

    #if(Uart_PowerStart_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        Uart_PowerStart_ClearSpiExtClkInterruptSource(Uart_PowerStart_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (Uart_PowerStart_CHECK_RX_SW_BUFFER)
    {
        if (Uart_PowerStart_CHECK_INTR_RX_MASKED(Uart_PowerStart_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (Uart_PowerStart_rxBufferHead + 1u);

                /* Adjust local head index */
                if (Uart_PowerStart_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == Uart_PowerStart_rxBufferTail)
                {
                    #if (Uart_PowerStart_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        Uart_PowerStart_INTR_RX_MASK_REG &= ~Uart_PowerStart_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) Uart_PowerStart_RX_FIFO_RD_REG;
                        Uart_PowerStart_rxBufferOverflow = (uint8) Uart_PowerStart_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    Uart_PowerStart_PutWordInRxBuffer(locHead, Uart_PowerStart_RX_FIFO_RD_REG);

                    /* Move head index */
                    Uart_PowerStart_rxBufferHead = locHead;
                }
            }
            while(0u != Uart_PowerStart_GET_RX_FIFO_ENTRIES);

            Uart_PowerStart_ClearRxInterruptSource(Uart_PowerStart_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (Uart_PowerStart_CHECK_TX_SW_BUFFER)
    {
        if (Uart_PowerStart_CHECK_INTR_TX_MASKED(Uart_PowerStart_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (Uart_PowerStart_txBufferHead != Uart_PowerStart_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (Uart_PowerStart_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (Uart_PowerStart_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    Uart_PowerStart_TX_FIFO_WR_REG = Uart_PowerStart_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    Uart_PowerStart_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    Uart_PowerStart_DISABLE_INTR_TX(Uart_PowerStart_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (Uart_PowerStart_SPI_UART_FIFO_SIZE != Uart_PowerStart_GET_TX_FIFO_ENTRIES);

            Uart_PowerStart_ClearTxInterruptSource(Uart_PowerStart_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef Uart_PowerStart_SPI_UART_ISR_EXIT_CALLBACK
    Uart_PowerStart_SPI_UART_ISR_ExitCallback();
#endif /* Uart_PowerStart_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (Uart_PowerStart_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
