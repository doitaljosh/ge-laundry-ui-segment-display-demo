/***************************************************************************//**
* \file Uart_Mc_SPI_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Uart_Mc_PVT.h"
#include "Uart_Mc_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(Uart_Mc_INTERNAL_RX_SW_BUFFER_CONST)
    /* Start index to put data into the software receive buffer.*/
    volatile uint32 Uart_Mc_rxBufferHead;
    /* Start index to get data from the software receive buffer.*/
    volatile uint32 Uart_Mc_rxBufferTail;
    /**
    * \addtogroup group_globals
    * \{
    */
    /** Sets when internal software receive buffer overflow
    *  was occurred.
    */
    volatile uint8  Uart_Mc_rxBufferOverflow;
    /** \} globals */
#endif /* (Uart_Mc_INTERNAL_RX_SW_BUFFER_CONST) */

#if(Uart_Mc_INTERNAL_TX_SW_BUFFER_CONST)
    /* Start index to put data into the software transmit buffer.*/
    volatile uint32 Uart_Mc_txBufferHead;
    /* Start index to get data from the software transmit buffer.*/
    volatile uint32 Uart_Mc_txBufferTail;
#endif /* (Uart_Mc_INTERNAL_TX_SW_BUFFER_CONST) */

#if(Uart_Mc_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 Uart_Mc_rxBufferInternal[Uart_Mc_INTERNAL_RX_BUFFER_SIZE];
#endif /* (Uart_Mc_INTERNAL_RX_SW_BUFFER) */

#if(Uart_Mc_INTERNAL_TX_SW_BUFFER)
    volatile uint8 Uart_Mc_txBufferInternal[Uart_Mc_TX_BUFFER_SIZE];
#endif /* (Uart_Mc_INTERNAL_TX_SW_BUFFER) */


#if(Uart_Mc_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: Uart_Mc_SpiUartReadRxData
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * \return
    *  Next data element from the receive buffer. 
    *  The amount of data bits to be received depends on RX data bits selection 
    *  (the data bit counting starts from LSB of return value).
    *
    * \globalvars
    *  Uart_Mc_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  Uart_Mc_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 Uart_Mc_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (Uart_Mc_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (Uart_Mc_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (Uart_Mc_CHECK_RX_SW_BUFFER)
        {
            if (Uart_Mc_rxBufferHead != Uart_Mc_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (Uart_Mc_rxBufferTail + 1u);

                if (Uart_Mc_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = Uart_Mc_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                Uart_Mc_rxBufferTail = locTail;

                #if (Uart_Mc_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (Uart_Mc_INTR_RX_MASK_REG & Uart_Mc_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        Uart_Mc_INTR_RX_MASK_REG |= Uart_Mc_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = Uart_Mc_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: Uart_Mc_SpiUartGetRxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * \return
    *  Number of received data elements.
    *
    * \globalvars
    *  Uart_Mc_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  Uart_Mc_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 Uart_Mc_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (Uart_Mc_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (Uart_Mc_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (Uart_Mc_CHECK_RX_SW_BUFFER)
        {
            locHead = Uart_Mc_rxBufferHead;

            if(locHead >= Uart_Mc_rxBufferTail)
            {
                size = (locHead - Uart_Mc_rxBufferTail);
            }
            else
            {
                size = (locHead + (Uart_Mc_INTERNAL_RX_BUFFER_SIZE - Uart_Mc_rxBufferTail));
            }
        }
        #else
        {
            size = Uart_Mc_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: Uart_Mc_SpiUartClearRxBuffer
    ****************************************************************************//**
    *
    *  Clears the receive buffer and RX FIFO.
    *
    * \globalvars
    *  Uart_Mc_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  Uart_Mc_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    void Uart_Mc_SpiUartClearRxBuffer(void)
    {
        #if (Uart_Mc_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            Uart_Mc_DisableInt();

            /* Flush RX software buffer */
            Uart_Mc_rxBufferHead = Uart_Mc_rxBufferTail;
            Uart_Mc_rxBufferOverflow = 0u;

            Uart_Mc_CLEAR_RX_FIFO;
            Uart_Mc_ClearRxInterruptSource(Uart_Mc_INTR_RX_ALL);

            #if (Uart_Mc_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                Uart_Mc_INTR_RX_MASK_REG |= Uart_Mc_INTR_RX_NOT_EMPTY;
            }
            #endif
            
            /* Release lock */
            Uart_Mc_EnableInt();
        }
        #else
        {
            Uart_Mc_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (Uart_Mc_RX_DIRECTION) */


#if(Uart_Mc_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: Uart_Mc_SpiUartWriteTxData
    ****************************************************************************//**
    *
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *   The amount of data bits to be transmitted depends on TX data bits selection 
    *   (the data bit counting starts from LSB of txDataByte).
    *
    * \globalvars
    *  Uart_Mc_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  Uart_Mc_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void Uart_Mc_SpiUartWriteTxData(uint32 txData)
    {
    #if (Uart_Mc_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (Uart_Mc_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (Uart_Mc_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((Uart_Mc_txBufferHead == Uart_Mc_txBufferTail) &&
                (Uart_Mc_SPI_UART_FIFO_SIZE != Uart_Mc_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                Uart_Mc_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (Uart_Mc_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (Uart_Mc_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == Uart_Mc_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                Uart_Mc_ClearTxInterruptSource(Uart_Mc_INTR_TX_NOT_FULL);

                Uart_Mc_PutWordInTxBuffer(locHead, txData);

                Uart_Mc_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (Uart_Mc_INTR_TX_MASK_REG & Uart_Mc_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    Uart_Mc_INTR_TX_MASK_REG |= (uint32) Uart_Mc_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (Uart_Mc_SPI_UART_FIFO_SIZE == Uart_Mc_GET_TX_FIFO_ENTRIES)
            {
            }

            Uart_Mc_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: Uart_Mc_SpiUartPutArray
    ****************************************************************************//**
    *
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * \param wrBuf: pointer to an array of data to be placed in transmit buffer. 
    *  The width of the data to be transmitted depends on TX data width selection 
    *  (the data bit counting starts from LSB for each array element).
    * \param count: number of data elements to be placed in the transmit buffer.
    *
    * \globalvars
    *  Uart_Mc_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  Uart_Mc_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void Uart_Mc_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            Uart_Mc_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: Uart_Mc_SpiUartGetTxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of elements currently in the transmit buffer.
    *   - TX software buffer is disabled: returns the number of used entries in
    *     TX FIFO.
    *   - TX software buffer is enabled: returns the number of elements currently
    *     used in the transmit buffer. This number does not include used entries in
    *     the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *     not full.
    *
    * \return
    *  Number of data elements ready to transmit.
    *
    * \globalvars
    *  Uart_Mc_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  Uart_Mc_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    uint32 Uart_Mc_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (Uart_Mc_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (Uart_Mc_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (Uart_Mc_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = Uart_Mc_txBufferTail;

            if (Uart_Mc_txBufferHead >= locTail)
            {
                size = (Uart_Mc_txBufferHead - locTail);
            }
            else
            {
                size = (Uart_Mc_txBufferHead + (Uart_Mc_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = Uart_Mc_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: Uart_Mc_SpiUartClearTxBuffer
    ****************************************************************************//**
    *
    *  Clears the transmit buffer and TX FIFO.
    *
    * \globalvars
    *  Uart_Mc_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  Uart_Mc_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void Uart_Mc_SpiUartClearTxBuffer(void)
    {
        #if (Uart_Mc_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            Uart_Mc_DisableInt();

            /* Flush TX software buffer */
            Uart_Mc_txBufferHead = Uart_Mc_txBufferTail;

            Uart_Mc_INTR_TX_MASK_REG &= (uint32) ~Uart_Mc_INTR_TX_NOT_FULL;
            Uart_Mc_CLEAR_TX_FIFO;
            Uart_Mc_ClearTxInterruptSource(Uart_Mc_INTR_TX_ALL);

            /* Release lock */
            Uart_Mc_EnableInt();
        }
        #else
        {
            Uart_Mc_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (Uart_Mc_TX_DIRECTION) */


/*******************************************************************************
* Function Name: Uart_Mc_SpiUartDisableIntRx
****************************************************************************//**
*
*  Disables the RX interrupt sources.
*
*  \return
*   Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 Uart_Mc_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = Uart_Mc_GetRxInterruptMode();

    Uart_Mc_SetRxInterruptMode(Uart_Mc_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: Uart_Mc_SpiUartDisableIntTx
****************************************************************************//**
*
*  Disables TX interrupt sources.
*
*  \return
*   Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 Uart_Mc_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = Uart_Mc_GetTxInterruptMode();

    Uart_Mc_SetTxInterruptMode(Uart_Mc_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: Uart_Mc_PutWordInRxBuffer
    ****************************************************************************//**
    *
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param index:      index to store data byte/word in the RX buffer.
    *  \param rxDataByte: byte/word to store.
    *
    *******************************************************************************/
    void Uart_Mc_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (Uart_Mc_ONE_BYTE_WIDTH == Uart_Mc_rxDataBits)
        {
            Uart_Mc_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            Uart_Mc_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            Uart_Mc_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: Uart_Mc_GetWordFromRxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \return
    *   Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 Uart_Mc_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (Uart_Mc_ONE_BYTE_WIDTH == Uart_Mc_rxDataBits)
        {
            value = Uart_Mc_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) Uart_Mc_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)Uart_Mc_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: Uart_Mc_PutWordInTxBuffer
    ****************************************************************************//**
    *
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx:        index to store data byte/word in the TX buffer.
    *  \param txDataByte: byte/word to store.
    *
    *******************************************************************************/
    void Uart_Mc_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (Uart_Mc_ONE_BYTE_WIDTH == Uart_Mc_txDataBits)
        {
            Uart_Mc_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            Uart_Mc_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            Uart_Mc_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: Uart_Mc_GetWordFromTxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx: index to get data byte/word from the TX buffer.
    *
    *  \return
    *   Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 Uart_Mc_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (Uart_Mc_ONE_BYTE_WIDTH == Uart_Mc_txDataBits)
        {
            value = (uint32) Uart_Mc_txBuffer[idx];
        }
        else
        {
            value  = (uint32) Uart_Mc_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) Uart_Mc_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
