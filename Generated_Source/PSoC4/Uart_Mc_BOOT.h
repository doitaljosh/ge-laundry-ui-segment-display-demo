/***************************************************************************//**
* \file Uart_Mc_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_Uart_Mc_H)
#define CY_SCB_BOOT_Uart_Mc_H

#include "Uart_Mc_PVT.h"

#if (Uart_Mc_SCB_MODE_I2C_INC)
    #include "Uart_Mc_I2C.h"
#endif /* (Uart_Mc_SCB_MODE_I2C_INC) */

#if (Uart_Mc_SCB_MODE_EZI2C_INC)
    #include "Uart_Mc_EZI2C.h"
#endif /* (Uart_Mc_SCB_MODE_EZI2C_INC) */

#if (Uart_Mc_SCB_MODE_SPI_INC || Uart_Mc_SCB_MODE_UART_INC)
    #include "Uart_Mc_SPI_UART.h"
#endif /* (Uart_Mc_SCB_MODE_SPI_INC || Uart_Mc_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define Uart_Mc_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Uart_Mc) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (Uart_Mc_SCB_MODE_I2C_INC)
    #define Uart_Mc_I2C_BTLDR_COMM_ENABLED     (Uart_Mc_BTLDR_COMM_ENABLED && \
                                                            (Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             Uart_Mc_I2C_SLAVE_CONST))
#else
     #define Uart_Mc_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (Uart_Mc_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (Uart_Mc_SCB_MODE_EZI2C_INC)
    #define Uart_Mc_EZI2C_BTLDR_COMM_ENABLED   (Uart_Mc_BTLDR_COMM_ENABLED && \
                                                         Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define Uart_Mc_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (Uart_Mc_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (Uart_Mc_SCB_MODE_SPI_INC)
    #define Uart_Mc_SPI_BTLDR_COMM_ENABLED     (Uart_Mc_BTLDR_COMM_ENABLED && \
                                                            (Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             Uart_Mc_SPI_SLAVE_CONST))
#else
        #define Uart_Mc_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (Uart_Mc_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (Uart_Mc_SCB_MODE_UART_INC)
       #define Uart_Mc_UART_BTLDR_COMM_ENABLED    (Uart_Mc_BTLDR_COMM_ENABLED && \
                                                            (Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (Uart_Mc_UART_RX_DIRECTION && \
                                                              Uart_Mc_UART_TX_DIRECTION)))
#else
     #define Uart_Mc_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (Uart_Mc_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define Uart_Mc_BTLDR_COMM_MODE_ENABLED    (Uart_Mc_I2C_BTLDR_COMM_ENABLED   || \
                                                     Uart_Mc_SPI_BTLDR_COMM_ENABLED   || \
                                                     Uart_Mc_EZI2C_BTLDR_COMM_ENABLED || \
                                                     Uart_Mc_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Uart_Mc_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void Uart_Mc_I2CCyBtldrCommStart(void);
    void Uart_Mc_I2CCyBtldrCommStop (void);
    void Uart_Mc_I2CCyBtldrCommReset(void);
    cystatus Uart_Mc_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Uart_Mc_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (Uart_Mc_SCB_MODE_I2C_CONST_CFG)
        #define Uart_Mc_CyBtldrCommStart   Uart_Mc_I2CCyBtldrCommStart
        #define Uart_Mc_CyBtldrCommStop    Uart_Mc_I2CCyBtldrCommStop
        #define Uart_Mc_CyBtldrCommReset   Uart_Mc_I2CCyBtldrCommReset
        #define Uart_Mc_CyBtldrCommRead    Uart_Mc_I2CCyBtldrCommRead
        #define Uart_Mc_CyBtldrCommWrite   Uart_Mc_I2CCyBtldrCommWrite
    #endif /* (Uart_Mc_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Uart_Mc_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Uart_Mc_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void Uart_Mc_EzI2CCyBtldrCommStart(void);
    void Uart_Mc_EzI2CCyBtldrCommStop (void);
    void Uart_Mc_EzI2CCyBtldrCommReset(void);
    cystatus Uart_Mc_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Uart_Mc_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (Uart_Mc_SCB_MODE_EZI2C_CONST_CFG)
        #define Uart_Mc_CyBtldrCommStart   Uart_Mc_EzI2CCyBtldrCommStart
        #define Uart_Mc_CyBtldrCommStop    Uart_Mc_EzI2CCyBtldrCommStop
        #define Uart_Mc_CyBtldrCommReset   Uart_Mc_EzI2CCyBtldrCommReset
        #define Uart_Mc_CyBtldrCommRead    Uart_Mc_EzI2CCyBtldrCommRead
        #define Uart_Mc_CyBtldrCommWrite   Uart_Mc_EzI2CCyBtldrCommWrite
    #endif /* (Uart_Mc_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Uart_Mc_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Uart_Mc_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void Uart_Mc_SpiCyBtldrCommStart(void);
    void Uart_Mc_SpiCyBtldrCommStop (void);
    void Uart_Mc_SpiCyBtldrCommReset(void);
    cystatus Uart_Mc_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Uart_Mc_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (Uart_Mc_SCB_MODE_SPI_CONST_CFG)
        #define Uart_Mc_CyBtldrCommStart   Uart_Mc_SpiCyBtldrCommStart
        #define Uart_Mc_CyBtldrCommStop    Uart_Mc_SpiCyBtldrCommStop
        #define Uart_Mc_CyBtldrCommReset   Uart_Mc_SpiCyBtldrCommReset
        #define Uart_Mc_CyBtldrCommRead    Uart_Mc_SpiCyBtldrCommRead
        #define Uart_Mc_CyBtldrCommWrite   Uart_Mc_SpiCyBtldrCommWrite
    #endif /* (Uart_Mc_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Uart_Mc_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Uart_Mc_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void Uart_Mc_UartCyBtldrCommStart(void);
    void Uart_Mc_UartCyBtldrCommStop (void);
    void Uart_Mc_UartCyBtldrCommReset(void);
    cystatus Uart_Mc_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Uart_Mc_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (Uart_Mc_SCB_MODE_UART_CONST_CFG)
        #define Uart_Mc_CyBtldrCommStart   Uart_Mc_UartCyBtldrCommStart
        #define Uart_Mc_CyBtldrCommStop    Uart_Mc_UartCyBtldrCommStop
        #define Uart_Mc_CyBtldrCommReset   Uart_Mc_UartCyBtldrCommReset
        #define Uart_Mc_CyBtldrCommRead    Uart_Mc_UartCyBtldrCommRead
        #define Uart_Mc_CyBtldrCommWrite   Uart_Mc_UartCyBtldrCommWrite
    #endif /* (Uart_Mc_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Uart_Mc_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Uart_Mc_BTLDR_COMM_ENABLED)
    #if (Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void Uart_Mc_CyBtldrCommStart(void);
        void Uart_Mc_CyBtldrCommStop (void);
        void Uart_Mc_CyBtldrCommReset(void);
        cystatus Uart_Mc_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus Uart_Mc_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (Uart_Mc_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Uart_Mc)
        #define CyBtldrCommStart    Uart_Mc_CyBtldrCommStart
        #define CyBtldrCommStop     Uart_Mc_CyBtldrCommStop
        #define CyBtldrCommReset    Uart_Mc_CyBtldrCommReset
        #define CyBtldrCommWrite    Uart_Mc_CyBtldrCommWrite
        #define CyBtldrCommRead     Uart_Mc_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Uart_Mc) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Uart_Mc_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define Uart_Mc_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define Uart_Mc_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define Uart_Mc_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define Uart_Mc_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef Uart_Mc_SPI_BYTE_TO_BYTE
    #define Uart_Mc_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef Uart_Mc_UART_BYTE_TO_BYTE
    #define Uart_Mc_UART_BYTE_TO_BYTE  (87u)
#endif /* Uart_Mc_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_Uart_Mc_H) */


/* [] END OF FILE */
