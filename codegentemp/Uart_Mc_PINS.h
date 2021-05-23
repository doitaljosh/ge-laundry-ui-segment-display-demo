/***************************************************************************//**
* \file Uart_Mc_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
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

#if !defined(CY_SCB_PINS_Uart_Mc_H)
#define CY_SCB_PINS_Uart_Mc_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define Uart_Mc_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define Uart_Mc_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define Uart_Mc_REMOVE_TX_SDA_MISO_PIN      (1u)
#define Uart_Mc_REMOVE_CTS_SCLK_PIN      (1u)
#define Uart_Mc_REMOVE_RTS_SS0_PIN      (1u)
#define Uart_Mc_REMOVE_SS1_PIN                 (1u)
#define Uart_Mc_REMOVE_SS2_PIN                 (1u)
#define Uart_Mc_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define Uart_Mc_REMOVE_I2C_PINS                (1u)
#define Uart_Mc_REMOVE_SPI_MASTER_PINS         (1u)
#define Uart_Mc_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define Uart_Mc_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define Uart_Mc_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define Uart_Mc_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define Uart_Mc_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define Uart_Mc_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define Uart_Mc_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define Uart_Mc_REMOVE_SPI_SLAVE_PINS          (1u)
#define Uart_Mc_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define Uart_Mc_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define Uart_Mc_REMOVE_UART_TX_PIN             (0u)
#define Uart_Mc_REMOVE_UART_RX_TX_PIN          (1u)
#define Uart_Mc_REMOVE_UART_RX_PIN             (0u)
#define Uart_Mc_REMOVE_UART_RX_WAKE_PIN        (1u)
#define Uart_Mc_REMOVE_UART_RTS_PIN            (1u)
#define Uart_Mc_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define Uart_Mc_RX_WAKE_SCL_MOSI_PIN (0u == Uart_Mc_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define Uart_Mc_RX_SCL_MOSI_PIN     (0u == Uart_Mc_REMOVE_RX_SCL_MOSI_PIN)
#define Uart_Mc_TX_SDA_MISO_PIN     (0u == Uart_Mc_REMOVE_TX_SDA_MISO_PIN)
#define Uart_Mc_CTS_SCLK_PIN     (0u == Uart_Mc_REMOVE_CTS_SCLK_PIN)
#define Uart_Mc_RTS_SS0_PIN     (0u == Uart_Mc_REMOVE_RTS_SS0_PIN)
#define Uart_Mc_SS1_PIN                (0u == Uart_Mc_REMOVE_SS1_PIN)
#define Uart_Mc_SS2_PIN                (0u == Uart_Mc_REMOVE_SS2_PIN)
#define Uart_Mc_SS3_PIN                (0u == Uart_Mc_REMOVE_SS3_PIN)

/* Mode defined pins */
#define Uart_Mc_I2C_PINS               (0u == Uart_Mc_REMOVE_I2C_PINS)
#define Uart_Mc_SPI_MASTER_PINS        (0u == Uart_Mc_REMOVE_SPI_MASTER_PINS)
#define Uart_Mc_SPI_MASTER_SCLK_PIN    (0u == Uart_Mc_REMOVE_SPI_MASTER_SCLK_PIN)
#define Uart_Mc_SPI_MASTER_MOSI_PIN    (0u == Uart_Mc_REMOVE_SPI_MASTER_MOSI_PIN)
#define Uart_Mc_SPI_MASTER_MISO_PIN    (0u == Uart_Mc_REMOVE_SPI_MASTER_MISO_PIN)
#define Uart_Mc_SPI_MASTER_SS0_PIN     (0u == Uart_Mc_REMOVE_SPI_MASTER_SS0_PIN)
#define Uart_Mc_SPI_MASTER_SS1_PIN     (0u == Uart_Mc_REMOVE_SPI_MASTER_SS1_PIN)
#define Uart_Mc_SPI_MASTER_SS2_PIN     (0u == Uart_Mc_REMOVE_SPI_MASTER_SS2_PIN)
#define Uart_Mc_SPI_MASTER_SS3_PIN     (0u == Uart_Mc_REMOVE_SPI_MASTER_SS3_PIN)
#define Uart_Mc_SPI_SLAVE_PINS         (0u == Uart_Mc_REMOVE_SPI_SLAVE_PINS)
#define Uart_Mc_SPI_SLAVE_MOSI_PIN     (0u == Uart_Mc_REMOVE_SPI_SLAVE_MOSI_PIN)
#define Uart_Mc_SPI_SLAVE_MISO_PIN     (0u == Uart_Mc_REMOVE_SPI_SLAVE_MISO_PIN)
#define Uart_Mc_UART_TX_PIN            (0u == Uart_Mc_REMOVE_UART_TX_PIN)
#define Uart_Mc_UART_RX_TX_PIN         (0u == Uart_Mc_REMOVE_UART_RX_TX_PIN)
#define Uart_Mc_UART_RX_PIN            (0u == Uart_Mc_REMOVE_UART_RX_PIN)
#define Uart_Mc_UART_RX_WAKE_PIN       (0u == Uart_Mc_REMOVE_UART_RX_WAKE_PIN)
#define Uart_Mc_UART_RTS_PIN           (0u == Uart_Mc_REMOVE_UART_RTS_PIN)
#define Uart_Mc_UART_CTS_PIN           (0u == Uart_Mc_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (Uart_Mc_RX_WAKE_SCL_MOSI_PIN)
    #include "Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (Uart_Mc_RX_SCL_MOSI) */

#if (Uart_Mc_RX_SCL_MOSI_PIN)
    #include "Uart_Mc_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (Uart_Mc_RX_SCL_MOSI) */

#if (Uart_Mc_TX_SDA_MISO_PIN)
    #include "Uart_Mc_uart_tx_i2c_sda_spi_miso.h"
#endif /* (Uart_Mc_TX_SDA_MISO) */

#if (Uart_Mc_CTS_SCLK_PIN)
    #include "Uart_Mc_uart_cts_spi_sclk.h"
#endif /* (Uart_Mc_CTS_SCLK) */

#if (Uart_Mc_RTS_SS0_PIN)
    #include "Uart_Mc_uart_rts_spi_ss0.h"
#endif /* (Uart_Mc_RTS_SS0_PIN) */

#if (Uart_Mc_SS1_PIN)
    #include "Uart_Mc_spi_ss1.h"
#endif /* (Uart_Mc_SS1_PIN) */

#if (Uart_Mc_SS2_PIN)
    #include "Uart_Mc_spi_ss2.h"
#endif /* (Uart_Mc_SS2_PIN) */

#if (Uart_Mc_SS3_PIN)
    #include "Uart_Mc_spi_ss3.h"
#endif /* (Uart_Mc_SS3_PIN) */

#if (Uart_Mc_I2C_PINS)
    #include "Uart_Mc_scl.h"
    #include "Uart_Mc_sda.h"
#endif /* (Uart_Mc_I2C_PINS) */

#if (Uart_Mc_SPI_MASTER_PINS)
#if (Uart_Mc_SPI_MASTER_SCLK_PIN)
    #include "Uart_Mc_sclk_m.h"
#endif /* (Uart_Mc_SPI_MASTER_SCLK_PIN) */

#if (Uart_Mc_SPI_MASTER_MOSI_PIN)
    #include "Uart_Mc_mosi_m.h"
#endif /* (Uart_Mc_SPI_MASTER_MOSI_PIN) */

#if (Uart_Mc_SPI_MASTER_MISO_PIN)
    #include "Uart_Mc_miso_m.h"
#endif /*(Uart_Mc_SPI_MASTER_MISO_PIN) */
#endif /* (Uart_Mc_SPI_MASTER_PINS) */

#if (Uart_Mc_SPI_SLAVE_PINS)
    #include "Uart_Mc_sclk_s.h"
    #include "Uart_Mc_ss_s.h"

#if (Uart_Mc_SPI_SLAVE_MOSI_PIN)
    #include "Uart_Mc_mosi_s.h"
#endif /* (Uart_Mc_SPI_SLAVE_MOSI_PIN) */

#if (Uart_Mc_SPI_SLAVE_MISO_PIN)
    #include "Uart_Mc_miso_s.h"
#endif /*(Uart_Mc_SPI_SLAVE_MISO_PIN) */
#endif /* (Uart_Mc_SPI_SLAVE_PINS) */

#if (Uart_Mc_SPI_MASTER_SS0_PIN)
    #include "Uart_Mc_ss0_m.h"
#endif /* (Uart_Mc_SPI_MASTER_SS0_PIN) */

#if (Uart_Mc_SPI_MASTER_SS1_PIN)
    #include "Uart_Mc_ss1_m.h"
#endif /* (Uart_Mc_SPI_MASTER_SS1_PIN) */

#if (Uart_Mc_SPI_MASTER_SS2_PIN)
    #include "Uart_Mc_ss2_m.h"
#endif /* (Uart_Mc_SPI_MASTER_SS2_PIN) */

#if (Uart_Mc_SPI_MASTER_SS3_PIN)
    #include "Uart_Mc_ss3_m.h"
#endif /* (Uart_Mc_SPI_MASTER_SS3_PIN) */

#if (Uart_Mc_UART_TX_PIN)
    #include "Uart_Mc_tx.h"
#endif /* (Uart_Mc_UART_TX_PIN) */

#if (Uart_Mc_UART_RX_TX_PIN)
    #include "Uart_Mc_rx_tx.h"
#endif /* (Uart_Mc_UART_RX_TX_PIN) */

#if (Uart_Mc_UART_RX_PIN)
    #include "Uart_Mc_rx.h"
#endif /* (Uart_Mc_UART_RX_PIN) */

#if (Uart_Mc_UART_RX_WAKE_PIN)
    #include "Uart_Mc_rx_wake.h"
#endif /* (Uart_Mc_UART_RX_WAKE_PIN) */

#if (Uart_Mc_UART_RTS_PIN)
    #include "Uart_Mc_rts.h"
#endif /* (Uart_Mc_UART_RTS_PIN) */

#if (Uart_Mc_UART_CTS_PIN)
    #include "Uart_Mc_cts.h"
#endif /* (Uart_Mc_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (Uart_Mc_RX_SCL_MOSI_PIN)
    #define Uart_Mc_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) Uart_Mc_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define Uart_Mc_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) Uart_Mc_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define Uart_Mc_RX_SCL_MOSI_HSIOM_MASK      (Uart_Mc_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define Uart_Mc_RX_SCL_MOSI_HSIOM_POS       (Uart_Mc_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define Uart_Mc_RX_SCL_MOSI_HSIOM_SEL_GPIO  (Uart_Mc_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define Uart_Mc_RX_SCL_MOSI_HSIOM_SEL_I2C   (Uart_Mc_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define Uart_Mc_RX_SCL_MOSI_HSIOM_SEL_SPI   (Uart_Mc_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define Uart_Mc_RX_SCL_MOSI_HSIOM_SEL_UART  (Uart_Mc_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (Uart_Mc_RX_WAKE_SCL_MOSI_PIN)
    #define Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_MASK      (Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_POS       (Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define Uart_Mc_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define Uart_Mc_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define Uart_Mc_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define Uart_Mc_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) Uart_Mc_INTCFG_TYPE_MASK << \
                                                                           Uart_Mc_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins Uart_Mc_RX_SCL_MOSI_PIN or Uart_Mc_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (Uart_Mc_RX_SCL_MOSI_PIN) */

#if (Uart_Mc_TX_SDA_MISO_PIN)
    #define Uart_Mc_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) Uart_Mc_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define Uart_Mc_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) Uart_Mc_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define Uart_Mc_TX_SDA_MISO_HSIOM_MASK      (Uart_Mc_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define Uart_Mc_TX_SDA_MISO_HSIOM_POS       (Uart_Mc_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define Uart_Mc_TX_SDA_MISO_HSIOM_SEL_GPIO  (Uart_Mc_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define Uart_Mc_TX_SDA_MISO_HSIOM_SEL_I2C   (Uart_Mc_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define Uart_Mc_TX_SDA_MISO_HSIOM_SEL_SPI   (Uart_Mc_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define Uart_Mc_TX_SDA_MISO_HSIOM_SEL_UART  (Uart_Mc_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (Uart_Mc_TX_SDA_MISO_PIN) */

#if (Uart_Mc_CTS_SCLK_PIN)
    #define Uart_Mc_CTS_SCLK_HSIOM_REG   (*(reg32 *) Uart_Mc_uart_cts_spi_sclk__0__HSIOM)
    #define Uart_Mc_CTS_SCLK_HSIOM_PTR   ( (reg32 *) Uart_Mc_uart_cts_spi_sclk__0__HSIOM)
    
    #define Uart_Mc_CTS_SCLK_HSIOM_MASK      (Uart_Mc_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define Uart_Mc_CTS_SCLK_HSIOM_POS       (Uart_Mc_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define Uart_Mc_CTS_SCLK_HSIOM_SEL_GPIO  (Uart_Mc_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define Uart_Mc_CTS_SCLK_HSIOM_SEL_I2C   (Uart_Mc_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define Uart_Mc_CTS_SCLK_HSIOM_SEL_SPI   (Uart_Mc_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define Uart_Mc_CTS_SCLK_HSIOM_SEL_UART  (Uart_Mc_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (Uart_Mc_CTS_SCLK_PIN) */

#if (Uart_Mc_RTS_SS0_PIN)
    #define Uart_Mc_RTS_SS0_HSIOM_REG   (*(reg32 *) Uart_Mc_uart_rts_spi_ss0__0__HSIOM)
    #define Uart_Mc_RTS_SS0_HSIOM_PTR   ( (reg32 *) Uart_Mc_uart_rts_spi_ss0__0__HSIOM)
    
    #define Uart_Mc_RTS_SS0_HSIOM_MASK      (Uart_Mc_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define Uart_Mc_RTS_SS0_HSIOM_POS       (Uart_Mc_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define Uart_Mc_RTS_SS0_HSIOM_SEL_GPIO  (Uart_Mc_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define Uart_Mc_RTS_SS0_HSIOM_SEL_I2C   (Uart_Mc_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define Uart_Mc_RTS_SS0_HSIOM_SEL_SPI   (Uart_Mc_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(Uart_Mc_CY_SCBIP_V0 || Uart_Mc_CY_SCBIP_V1)
    #define Uart_Mc_RTS_SS0_HSIOM_SEL_UART  (Uart_Mc_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(Uart_Mc_CY_SCBIP_V0 || Uart_Mc_CY_SCBIP_V1) */
#endif /* (Uart_Mc_RTS_SS0_PIN) */

#if (Uart_Mc_SS1_PIN)
    #define Uart_Mc_SS1_HSIOM_REG  (*(reg32 *) Uart_Mc_spi_ss1__0__HSIOM)
    #define Uart_Mc_SS1_HSIOM_PTR  ( (reg32 *) Uart_Mc_spi_ss1__0__HSIOM)
    
    #define Uart_Mc_SS1_HSIOM_MASK     (Uart_Mc_spi_ss1__0__HSIOM_MASK)
    #define Uart_Mc_SS1_HSIOM_POS      (Uart_Mc_spi_ss1__0__HSIOM_SHIFT)
    #define Uart_Mc_SS1_HSIOM_SEL_GPIO (Uart_Mc_spi_ss1__0__HSIOM_GPIO)
    #define Uart_Mc_SS1_HSIOM_SEL_I2C  (Uart_Mc_spi_ss1__0__HSIOM_I2C)
    #define Uart_Mc_SS1_HSIOM_SEL_SPI  (Uart_Mc_spi_ss1__0__HSIOM_SPI)
#endif /* (Uart_Mc_SS1_PIN) */

#if (Uart_Mc_SS2_PIN)
    #define Uart_Mc_SS2_HSIOM_REG     (*(reg32 *) Uart_Mc_spi_ss2__0__HSIOM)
    #define Uart_Mc_SS2_HSIOM_PTR     ( (reg32 *) Uart_Mc_spi_ss2__0__HSIOM)
    
    #define Uart_Mc_SS2_HSIOM_MASK     (Uart_Mc_spi_ss2__0__HSIOM_MASK)
    #define Uart_Mc_SS2_HSIOM_POS      (Uart_Mc_spi_ss2__0__HSIOM_SHIFT)
    #define Uart_Mc_SS2_HSIOM_SEL_GPIO (Uart_Mc_spi_ss2__0__HSIOM_GPIO)
    #define Uart_Mc_SS2_HSIOM_SEL_I2C  (Uart_Mc_spi_ss2__0__HSIOM_I2C)
    #define Uart_Mc_SS2_HSIOM_SEL_SPI  (Uart_Mc_spi_ss2__0__HSIOM_SPI)
#endif /* (Uart_Mc_SS2_PIN) */

#if (Uart_Mc_SS3_PIN)
    #define Uart_Mc_SS3_HSIOM_REG     (*(reg32 *) Uart_Mc_spi_ss3__0__HSIOM)
    #define Uart_Mc_SS3_HSIOM_PTR     ( (reg32 *) Uart_Mc_spi_ss3__0__HSIOM)
    
    #define Uart_Mc_SS3_HSIOM_MASK     (Uart_Mc_spi_ss3__0__HSIOM_MASK)
    #define Uart_Mc_SS3_HSIOM_POS      (Uart_Mc_spi_ss3__0__HSIOM_SHIFT)
    #define Uart_Mc_SS3_HSIOM_SEL_GPIO (Uart_Mc_spi_ss3__0__HSIOM_GPIO)
    #define Uart_Mc_SS3_HSIOM_SEL_I2C  (Uart_Mc_spi_ss3__0__HSIOM_I2C)
    #define Uart_Mc_SS3_HSIOM_SEL_SPI  (Uart_Mc_spi_ss3__0__HSIOM_SPI)
#endif /* (Uart_Mc_SS3_PIN) */

#if (Uart_Mc_I2C_PINS)
    #define Uart_Mc_SCL_HSIOM_REG  (*(reg32 *) Uart_Mc_scl__0__HSIOM)
    #define Uart_Mc_SCL_HSIOM_PTR  ( (reg32 *) Uart_Mc_scl__0__HSIOM)
    
    #define Uart_Mc_SCL_HSIOM_MASK     (Uart_Mc_scl__0__HSIOM_MASK)
    #define Uart_Mc_SCL_HSIOM_POS      (Uart_Mc_scl__0__HSIOM_SHIFT)
    #define Uart_Mc_SCL_HSIOM_SEL_GPIO (Uart_Mc_sda__0__HSIOM_GPIO)
    #define Uart_Mc_SCL_HSIOM_SEL_I2C  (Uart_Mc_sda__0__HSIOM_I2C)
    
    #define Uart_Mc_SDA_HSIOM_REG  (*(reg32 *) Uart_Mc_sda__0__HSIOM)
    #define Uart_Mc_SDA_HSIOM_PTR  ( (reg32 *) Uart_Mc_sda__0__HSIOM)
    
    #define Uart_Mc_SDA_HSIOM_MASK     (Uart_Mc_sda__0__HSIOM_MASK)
    #define Uart_Mc_SDA_HSIOM_POS      (Uart_Mc_sda__0__HSIOM_SHIFT)
    #define Uart_Mc_SDA_HSIOM_SEL_GPIO (Uart_Mc_sda__0__HSIOM_GPIO)
    #define Uart_Mc_SDA_HSIOM_SEL_I2C  (Uart_Mc_sda__0__HSIOM_I2C)
#endif /* (Uart_Mc_I2C_PINS) */

#if (Uart_Mc_SPI_SLAVE_PINS)
    #define Uart_Mc_SCLK_S_HSIOM_REG   (*(reg32 *) Uart_Mc_sclk_s__0__HSIOM)
    #define Uart_Mc_SCLK_S_HSIOM_PTR   ( (reg32 *) Uart_Mc_sclk_s__0__HSIOM)
    
    #define Uart_Mc_SCLK_S_HSIOM_MASK      (Uart_Mc_sclk_s__0__HSIOM_MASK)
    #define Uart_Mc_SCLK_S_HSIOM_POS       (Uart_Mc_sclk_s__0__HSIOM_SHIFT)
    #define Uart_Mc_SCLK_S_HSIOM_SEL_GPIO  (Uart_Mc_sclk_s__0__HSIOM_GPIO)
    #define Uart_Mc_SCLK_S_HSIOM_SEL_SPI   (Uart_Mc_sclk_s__0__HSIOM_SPI)
    
    #define Uart_Mc_SS0_S_HSIOM_REG    (*(reg32 *) Uart_Mc_ss0_s__0__HSIOM)
    #define Uart_Mc_SS0_S_HSIOM_PTR    ( (reg32 *) Uart_Mc_ss0_s__0__HSIOM)
    
    #define Uart_Mc_SS0_S_HSIOM_MASK       (Uart_Mc_ss0_s__0__HSIOM_MASK)
    #define Uart_Mc_SS0_S_HSIOM_POS        (Uart_Mc_ss0_s__0__HSIOM_SHIFT)
    #define Uart_Mc_SS0_S_HSIOM_SEL_GPIO   (Uart_Mc_ss0_s__0__HSIOM_GPIO)  
    #define Uart_Mc_SS0_S_HSIOM_SEL_SPI    (Uart_Mc_ss0_s__0__HSIOM_SPI)
#endif /* (Uart_Mc_SPI_SLAVE_PINS) */

#if (Uart_Mc_SPI_SLAVE_MOSI_PIN)
    #define Uart_Mc_MOSI_S_HSIOM_REG   (*(reg32 *) Uart_Mc_mosi_s__0__HSIOM)
    #define Uart_Mc_MOSI_S_HSIOM_PTR   ( (reg32 *) Uart_Mc_mosi_s__0__HSIOM)
    
    #define Uart_Mc_MOSI_S_HSIOM_MASK      (Uart_Mc_mosi_s__0__HSIOM_MASK)
    #define Uart_Mc_MOSI_S_HSIOM_POS       (Uart_Mc_mosi_s__0__HSIOM_SHIFT)
    #define Uart_Mc_MOSI_S_HSIOM_SEL_GPIO  (Uart_Mc_mosi_s__0__HSIOM_GPIO)
    #define Uart_Mc_MOSI_S_HSIOM_SEL_SPI   (Uart_Mc_mosi_s__0__HSIOM_SPI)
#endif /* (Uart_Mc_SPI_SLAVE_MOSI_PIN) */

#if (Uart_Mc_SPI_SLAVE_MISO_PIN)
    #define Uart_Mc_MISO_S_HSIOM_REG   (*(reg32 *) Uart_Mc_miso_s__0__HSIOM)
    #define Uart_Mc_MISO_S_HSIOM_PTR   ( (reg32 *) Uart_Mc_miso_s__0__HSIOM)
    
    #define Uart_Mc_MISO_S_HSIOM_MASK      (Uart_Mc_miso_s__0__HSIOM_MASK)
    #define Uart_Mc_MISO_S_HSIOM_POS       (Uart_Mc_miso_s__0__HSIOM_SHIFT)
    #define Uart_Mc_MISO_S_HSIOM_SEL_GPIO  (Uart_Mc_miso_s__0__HSIOM_GPIO)
    #define Uart_Mc_MISO_S_HSIOM_SEL_SPI   (Uart_Mc_miso_s__0__HSIOM_SPI)
#endif /* (Uart_Mc_SPI_SLAVE_MISO_PIN) */

#if (Uart_Mc_SPI_MASTER_MISO_PIN)
    #define Uart_Mc_MISO_M_HSIOM_REG   (*(reg32 *) Uart_Mc_miso_m__0__HSIOM)
    #define Uart_Mc_MISO_M_HSIOM_PTR   ( (reg32 *) Uart_Mc_miso_m__0__HSIOM)
    
    #define Uart_Mc_MISO_M_HSIOM_MASK      (Uart_Mc_miso_m__0__HSIOM_MASK)
    #define Uart_Mc_MISO_M_HSIOM_POS       (Uart_Mc_miso_m__0__HSIOM_SHIFT)
    #define Uart_Mc_MISO_M_HSIOM_SEL_GPIO  (Uart_Mc_miso_m__0__HSIOM_GPIO)
    #define Uart_Mc_MISO_M_HSIOM_SEL_SPI   (Uart_Mc_miso_m__0__HSIOM_SPI)
#endif /* (Uart_Mc_SPI_MASTER_MISO_PIN) */

#if (Uart_Mc_SPI_MASTER_MOSI_PIN)
    #define Uart_Mc_MOSI_M_HSIOM_REG   (*(reg32 *) Uart_Mc_mosi_m__0__HSIOM)
    #define Uart_Mc_MOSI_M_HSIOM_PTR   ( (reg32 *) Uart_Mc_mosi_m__0__HSIOM)
    
    #define Uart_Mc_MOSI_M_HSIOM_MASK      (Uart_Mc_mosi_m__0__HSIOM_MASK)
    #define Uart_Mc_MOSI_M_HSIOM_POS       (Uart_Mc_mosi_m__0__HSIOM_SHIFT)
    #define Uart_Mc_MOSI_M_HSIOM_SEL_GPIO  (Uart_Mc_mosi_m__0__HSIOM_GPIO)
    #define Uart_Mc_MOSI_M_HSIOM_SEL_SPI   (Uart_Mc_mosi_m__0__HSIOM_SPI)
#endif /* (Uart_Mc_SPI_MASTER_MOSI_PIN) */

#if (Uart_Mc_SPI_MASTER_SCLK_PIN)
    #define Uart_Mc_SCLK_M_HSIOM_REG   (*(reg32 *) Uart_Mc_sclk_m__0__HSIOM)
    #define Uart_Mc_SCLK_M_HSIOM_PTR   ( (reg32 *) Uart_Mc_sclk_m__0__HSIOM)
    
    #define Uart_Mc_SCLK_M_HSIOM_MASK      (Uart_Mc_sclk_m__0__HSIOM_MASK)
    #define Uart_Mc_SCLK_M_HSIOM_POS       (Uart_Mc_sclk_m__0__HSIOM_SHIFT)
    #define Uart_Mc_SCLK_M_HSIOM_SEL_GPIO  (Uart_Mc_sclk_m__0__HSIOM_GPIO)
    #define Uart_Mc_SCLK_M_HSIOM_SEL_SPI   (Uart_Mc_sclk_m__0__HSIOM_SPI)
#endif /* (Uart_Mc_SPI_MASTER_SCLK_PIN) */

#if (Uart_Mc_SPI_MASTER_SS0_PIN)
    #define Uart_Mc_SS0_M_HSIOM_REG    (*(reg32 *) Uart_Mc_ss0_m__0__HSIOM)
    #define Uart_Mc_SS0_M_HSIOM_PTR    ( (reg32 *) Uart_Mc_ss0_m__0__HSIOM)
    
    #define Uart_Mc_SS0_M_HSIOM_MASK       (Uart_Mc_ss0_m__0__HSIOM_MASK)
    #define Uart_Mc_SS0_M_HSIOM_POS        (Uart_Mc_ss0_m__0__HSIOM_SHIFT)
    #define Uart_Mc_SS0_M_HSIOM_SEL_GPIO   (Uart_Mc_ss0_m__0__HSIOM_GPIO)
    #define Uart_Mc_SS0_M_HSIOM_SEL_SPI    (Uart_Mc_ss0_m__0__HSIOM_SPI)
#endif /* (Uart_Mc_SPI_MASTER_SS0_PIN) */

#if (Uart_Mc_SPI_MASTER_SS1_PIN)
    #define Uart_Mc_SS1_M_HSIOM_REG    (*(reg32 *) Uart_Mc_ss1_m__0__HSIOM)
    #define Uart_Mc_SS1_M_HSIOM_PTR    ( (reg32 *) Uart_Mc_ss1_m__0__HSIOM)
    
    #define Uart_Mc_SS1_M_HSIOM_MASK       (Uart_Mc_ss1_m__0__HSIOM_MASK)
    #define Uart_Mc_SS1_M_HSIOM_POS        (Uart_Mc_ss1_m__0__HSIOM_SHIFT)
    #define Uart_Mc_SS1_M_HSIOM_SEL_GPIO   (Uart_Mc_ss1_m__0__HSIOM_GPIO)
    #define Uart_Mc_SS1_M_HSIOM_SEL_SPI    (Uart_Mc_ss1_m__0__HSIOM_SPI)
#endif /* (Uart_Mc_SPI_MASTER_SS1_PIN) */

#if (Uart_Mc_SPI_MASTER_SS2_PIN)
    #define Uart_Mc_SS2_M_HSIOM_REG    (*(reg32 *) Uart_Mc_ss2_m__0__HSIOM)
    #define Uart_Mc_SS2_M_HSIOM_PTR    ( (reg32 *) Uart_Mc_ss2_m__0__HSIOM)
    
    #define Uart_Mc_SS2_M_HSIOM_MASK       (Uart_Mc_ss2_m__0__HSIOM_MASK)
    #define Uart_Mc_SS2_M_HSIOM_POS        (Uart_Mc_ss2_m__0__HSIOM_SHIFT)
    #define Uart_Mc_SS2_M_HSIOM_SEL_GPIO   (Uart_Mc_ss2_m__0__HSIOM_GPIO)
    #define Uart_Mc_SS2_M_HSIOM_SEL_SPI    (Uart_Mc_ss2_m__0__HSIOM_SPI)
#endif /* (Uart_Mc_SPI_MASTER_SS2_PIN) */

#if (Uart_Mc_SPI_MASTER_SS3_PIN)
    #define Uart_Mc_SS3_M_HSIOM_REG    (*(reg32 *) Uart_Mc_ss3_m__0__HSIOM)
    #define Uart_Mc_SS3_M_HSIOM_PTR    ( (reg32 *) Uart_Mc_ss3_m__0__HSIOM)
    
    #define Uart_Mc_SS3_M_HSIOM_MASK      (Uart_Mc_ss3_m__0__HSIOM_MASK)
    #define Uart_Mc_SS3_M_HSIOM_POS       (Uart_Mc_ss3_m__0__HSIOM_SHIFT)
    #define Uart_Mc_SS3_M_HSIOM_SEL_GPIO  (Uart_Mc_ss3_m__0__HSIOM_GPIO)
    #define Uart_Mc_SS3_M_HSIOM_SEL_SPI   (Uart_Mc_ss3_m__0__HSIOM_SPI)
#endif /* (Uart_Mc_SPI_MASTER_SS3_PIN) */

#if (Uart_Mc_UART_RX_PIN)
    #define Uart_Mc_RX_HSIOM_REG   (*(reg32 *) Uart_Mc_rx__0__HSIOM)
    #define Uart_Mc_RX_HSIOM_PTR   ( (reg32 *) Uart_Mc_rx__0__HSIOM)
    
    #define Uart_Mc_RX_HSIOM_MASK      (Uart_Mc_rx__0__HSIOM_MASK)
    #define Uart_Mc_RX_HSIOM_POS       (Uart_Mc_rx__0__HSIOM_SHIFT)
    #define Uart_Mc_RX_HSIOM_SEL_GPIO  (Uart_Mc_rx__0__HSIOM_GPIO)
    #define Uart_Mc_RX_HSIOM_SEL_UART  (Uart_Mc_rx__0__HSIOM_UART)
#endif /* (Uart_Mc_UART_RX_PIN) */

#if (Uart_Mc_UART_RX_WAKE_PIN)
    #define Uart_Mc_RX_WAKE_HSIOM_REG   (*(reg32 *) Uart_Mc_rx_wake__0__HSIOM)
    #define Uart_Mc_RX_WAKE_HSIOM_PTR   ( (reg32 *) Uart_Mc_rx_wake__0__HSIOM)
    
    #define Uart_Mc_RX_WAKE_HSIOM_MASK      (Uart_Mc_rx_wake__0__HSIOM_MASK)
    #define Uart_Mc_RX_WAKE_HSIOM_POS       (Uart_Mc_rx_wake__0__HSIOM_SHIFT)
    #define Uart_Mc_RX_WAKE_HSIOM_SEL_GPIO  (Uart_Mc_rx_wake__0__HSIOM_GPIO)
    #define Uart_Mc_RX_WAKE_HSIOM_SEL_UART  (Uart_Mc_rx_wake__0__HSIOM_UART)
#endif /* (Uart_Mc_UART_WAKE_RX_PIN) */

#if (Uart_Mc_UART_CTS_PIN)
    #define Uart_Mc_CTS_HSIOM_REG   (*(reg32 *) Uart_Mc_cts__0__HSIOM)
    #define Uart_Mc_CTS_HSIOM_PTR   ( (reg32 *) Uart_Mc_cts__0__HSIOM)
    
    #define Uart_Mc_CTS_HSIOM_MASK      (Uart_Mc_cts__0__HSIOM_MASK)
    #define Uart_Mc_CTS_HSIOM_POS       (Uart_Mc_cts__0__HSIOM_SHIFT)
    #define Uart_Mc_CTS_HSIOM_SEL_GPIO  (Uart_Mc_cts__0__HSIOM_GPIO)
    #define Uart_Mc_CTS_HSIOM_SEL_UART  (Uart_Mc_cts__0__HSIOM_UART)
#endif /* (Uart_Mc_UART_CTS_PIN) */

#if (Uart_Mc_UART_TX_PIN)
    #define Uart_Mc_TX_HSIOM_REG   (*(reg32 *) Uart_Mc_tx__0__HSIOM)
    #define Uart_Mc_TX_HSIOM_PTR   ( (reg32 *) Uart_Mc_tx__0__HSIOM)
    
    #define Uart_Mc_TX_HSIOM_MASK      (Uart_Mc_tx__0__HSIOM_MASK)
    #define Uart_Mc_TX_HSIOM_POS       (Uart_Mc_tx__0__HSIOM_SHIFT)
    #define Uart_Mc_TX_HSIOM_SEL_GPIO  (Uart_Mc_tx__0__HSIOM_GPIO)
    #define Uart_Mc_TX_HSIOM_SEL_UART  (Uart_Mc_tx__0__HSIOM_UART)
#endif /* (Uart_Mc_UART_TX_PIN) */

#if (Uart_Mc_UART_RX_TX_PIN)
    #define Uart_Mc_RX_TX_HSIOM_REG   (*(reg32 *) Uart_Mc_rx_tx__0__HSIOM)
    #define Uart_Mc_RX_TX_HSIOM_PTR   ( (reg32 *) Uart_Mc_rx_tx__0__HSIOM)
    
    #define Uart_Mc_RX_TX_HSIOM_MASK      (Uart_Mc_rx_tx__0__HSIOM_MASK)
    #define Uart_Mc_RX_TX_HSIOM_POS       (Uart_Mc_rx_tx__0__HSIOM_SHIFT)
    #define Uart_Mc_RX_TX_HSIOM_SEL_GPIO  (Uart_Mc_rx_tx__0__HSIOM_GPIO)
    #define Uart_Mc_RX_TX_HSIOM_SEL_UART  (Uart_Mc_rx_tx__0__HSIOM_UART)
#endif /* (Uart_Mc_UART_RX_TX_PIN) */

#if (Uart_Mc_UART_RTS_PIN)
    #define Uart_Mc_RTS_HSIOM_REG      (*(reg32 *) Uart_Mc_rts__0__HSIOM)
    #define Uart_Mc_RTS_HSIOM_PTR      ( (reg32 *) Uart_Mc_rts__0__HSIOM)
    
    #define Uart_Mc_RTS_HSIOM_MASK     (Uart_Mc_rts__0__HSIOM_MASK)
    #define Uart_Mc_RTS_HSIOM_POS      (Uart_Mc_rts__0__HSIOM_SHIFT)    
    #define Uart_Mc_RTS_HSIOM_SEL_GPIO (Uart_Mc_rts__0__HSIOM_GPIO)
    #define Uart_Mc_RTS_HSIOM_SEL_UART (Uart_Mc_rts__0__HSIOM_UART)    
#endif /* (Uart_Mc_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define Uart_Mc_HSIOM_DEF_SEL      (0x00u)
#define Uart_Mc_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for Uart_Mc_CY_SCBIP_V0 
* and Uart_Mc_CY_SCBIP_V1. It is not recommended to use them for 
* Uart_Mc_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define Uart_Mc_HSIOM_UART_SEL     (0x09u)
#define Uart_Mc_HSIOM_I2C_SEL      (0x0Eu)
#define Uart_Mc_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define Uart_Mc_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define Uart_Mc_RX_SCL_MOSI_PIN_INDEX       (0u)
#define Uart_Mc_TX_SDA_MISO_PIN_INDEX       (1u)
#define Uart_Mc_CTS_SCLK_PIN_INDEX       (2u)
#define Uart_Mc_RTS_SS0_PIN_INDEX       (3u)
#define Uart_Mc_SS1_PIN_INDEX                  (4u)
#define Uart_Mc_SS2_PIN_INDEX                  (5u)
#define Uart_Mc_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define Uart_Mc_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << Uart_Mc_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define Uart_Mc_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << Uart_Mc_RX_SCL_MOSI_PIN_INDEX)
#define Uart_Mc_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << Uart_Mc_TX_SDA_MISO_PIN_INDEX)
#define Uart_Mc_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << Uart_Mc_CTS_SCLK_PIN_INDEX)
#define Uart_Mc_RTS_SS0_PIN_MASK     ((uint32) 0x01u << Uart_Mc_RTS_SS0_PIN_INDEX)
#define Uart_Mc_SS1_PIN_MASK                ((uint32) 0x01u << Uart_Mc_SS1_PIN_INDEX)
#define Uart_Mc_SS2_PIN_MASK                ((uint32) 0x01u << Uart_Mc_SS2_PIN_INDEX)
#define Uart_Mc_SS3_PIN_MASK                ((uint32) 0x01u << Uart_Mc_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define Uart_Mc_INTCFG_TYPE_MASK           (0x03u)
#define Uart_Mc_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define Uart_Mc_PIN_DM_ALG_HIZ  (0u)
#define Uart_Mc_PIN_DM_DIG_HIZ  (1u)
#define Uart_Mc_PIN_DM_OD_LO    (4u)
#define Uart_Mc_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define Uart_Mc_DM_MASK    (0x7u)
#define Uart_Mc_DM_SIZE    (3u)
#define Uart_Mc_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) Uart_Mc_DM_MASK << (Uart_Mc_DM_SIZE * (pos)))) >> \
                                                              (Uart_Mc_DM_SIZE * (pos)) )

#if (Uart_Mc_TX_SDA_MISO_PIN)
    #define Uart_Mc_CHECK_TX_SDA_MISO_PIN_USED \
                (Uart_Mc_PIN_DM_ALG_HIZ != \
                    Uart_Mc_GET_P4_PIN_DM(Uart_Mc_uart_tx_i2c_sda_spi_miso_PC, \
                                                   Uart_Mc_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (Uart_Mc_TX_SDA_MISO_PIN) */

#if (Uart_Mc_RTS_SS0_PIN)
    #define Uart_Mc_CHECK_RTS_SS0_PIN_USED \
                (Uart_Mc_PIN_DM_ALG_HIZ != \
                    Uart_Mc_GET_P4_PIN_DM(Uart_Mc_uart_rts_spi_ss0_PC, \
                                                   Uart_Mc_uart_rts_spi_ss0_SHIFT))
#endif /* (Uart_Mc_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define Uart_Mc_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define Uart_Mc_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define Uart_Mc_SET_HSIOM_SEL(reg, mask, pos, sel) Uart_Mc_SET_REGISTER_BITS(reg, mask, pos, sel)
#define Uart_Mc_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        Uart_Mc_SET_REGISTER_BITS(reg, mask, pos, intType)
#define Uart_Mc_SET_INP_DIS(reg, mask, val) Uart_Mc_SET_REGISTER_BIT(reg, mask, val)

/* Uart_Mc_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  Uart_Mc_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (Uart_Mc_CY_SCBIP_V0)
#if (Uart_Mc_I2C_PINS)
    #define Uart_Mc_SET_I2C_SCL_DR(val) Uart_Mc_scl_Write(val)

    #define Uart_Mc_SET_I2C_SCL_HSIOM_SEL(sel) \
                          Uart_Mc_SET_HSIOM_SEL(Uart_Mc_SCL_HSIOM_REG,  \
                                                         Uart_Mc_SCL_HSIOM_MASK, \
                                                         Uart_Mc_SCL_HSIOM_POS,  \
                                                         (sel))
    #define Uart_Mc_WAIT_SCL_SET_HIGH  (0u == Uart_Mc_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (Uart_Mc_RX_WAKE_SCL_MOSI_PIN)
    #define Uart_Mc_SET_I2C_SCL_DR(val) \
                            Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define Uart_Mc_SET_I2C_SCL_HSIOM_SEL(sel) \
                    Uart_Mc_SET_HSIOM_SEL(Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define Uart_Mc_WAIT_SCL_SET_HIGH  (0u == Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (Uart_Mc_RX_SCL_MOSI_PIN)
    #define Uart_Mc_SET_I2C_SCL_DR(val) \
                            Uart_Mc_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define Uart_Mc_SET_I2C_SCL_HSIOM_SEL(sel) \
                            Uart_Mc_SET_HSIOM_SEL(Uart_Mc_RX_SCL_MOSI_HSIOM_REG,  \
                                                           Uart_Mc_RX_SCL_MOSI_HSIOM_MASK, \
                                                           Uart_Mc_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define Uart_Mc_WAIT_SCL_SET_HIGH  (0u == Uart_Mc_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define Uart_Mc_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define Uart_Mc_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define Uart_Mc_WAIT_SCL_SET_HIGH  (0u)
#endif /* (Uart_Mc_I2C_PINS) */

/* SCB I2C: sda signal */
#if (Uart_Mc_I2C_PINS)
    #define Uart_Mc_WAIT_SDA_SET_HIGH  (0u == Uart_Mc_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (Uart_Mc_TX_SDA_MISO_PIN)
    #define Uart_Mc_WAIT_SDA_SET_HIGH  (0u == Uart_Mc_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define Uart_Mc_WAIT_SDA_SET_HIGH  (0u)
#endif /* (Uart_Mc_MOSI_SCL_RX_PIN) */
#endif /* (Uart_Mc_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (Uart_Mc_RX_SCL_MOSI_PIN)
    #define Uart_Mc_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (Uart_Mc_RX_WAKE_SCL_MOSI_PIN)
    #define Uart_Mc_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) Uart_Mc_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(Uart_Mc_UART_RX_WAKE_PIN)
    #define Uart_Mc_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) Uart_Mc_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (Uart_Mc_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define Uart_Mc_REMOVE_MOSI_SCL_RX_WAKE_PIN    Uart_Mc_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define Uart_Mc_REMOVE_MOSI_SCL_RX_PIN         Uart_Mc_REMOVE_RX_SCL_MOSI_PIN
#define Uart_Mc_REMOVE_MISO_SDA_TX_PIN         Uart_Mc_REMOVE_TX_SDA_MISO_PIN
#ifndef Uart_Mc_REMOVE_SCLK_PIN
#define Uart_Mc_REMOVE_SCLK_PIN                Uart_Mc_REMOVE_CTS_SCLK_PIN
#endif /* Uart_Mc_REMOVE_SCLK_PIN */
#ifndef Uart_Mc_REMOVE_SS0_PIN
#define Uart_Mc_REMOVE_SS0_PIN                 Uart_Mc_REMOVE_RTS_SS0_PIN
#endif /* Uart_Mc_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define Uart_Mc_MOSI_SCL_RX_WAKE_PIN   Uart_Mc_RX_WAKE_SCL_MOSI_PIN
#define Uart_Mc_MOSI_SCL_RX_PIN        Uart_Mc_RX_SCL_MOSI_PIN
#define Uart_Mc_MISO_SDA_TX_PIN        Uart_Mc_TX_SDA_MISO_PIN
#ifndef Uart_Mc_SCLK_PIN
#define Uart_Mc_SCLK_PIN               Uart_Mc_CTS_SCLK_PIN
#endif /* Uart_Mc_SCLK_PIN */
#ifndef Uart_Mc_SS0_PIN
#define Uart_Mc_SS0_PIN                Uart_Mc_RTS_SS0_PIN
#endif /* Uart_Mc_SS0_PIN */

#if (Uart_Mc_MOSI_SCL_RX_WAKE_PIN)
    #define Uart_Mc_MOSI_SCL_RX_WAKE_HSIOM_REG     Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Uart_Mc_MOSI_SCL_RX_WAKE_HSIOM_PTR     Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Uart_Mc_MOSI_SCL_RX_WAKE_HSIOM_MASK    Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Uart_Mc_MOSI_SCL_RX_WAKE_HSIOM_POS     Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define Uart_Mc_MOSI_SCL_RX_WAKE_INTCFG_REG    Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Uart_Mc_MOSI_SCL_RX_WAKE_INTCFG_PTR    Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define Uart_Mc_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Uart_Mc_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  Uart_Mc_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (Uart_Mc_RX_WAKE_SCL_MOSI_PIN) */

#if (Uart_Mc_MOSI_SCL_RX_PIN)
    #define Uart_Mc_MOSI_SCL_RX_HSIOM_REG      Uart_Mc_RX_SCL_MOSI_HSIOM_REG
    #define Uart_Mc_MOSI_SCL_RX_HSIOM_PTR      Uart_Mc_RX_SCL_MOSI_HSIOM_PTR
    #define Uart_Mc_MOSI_SCL_RX_HSIOM_MASK     Uart_Mc_RX_SCL_MOSI_HSIOM_MASK
    #define Uart_Mc_MOSI_SCL_RX_HSIOM_POS      Uart_Mc_RX_SCL_MOSI_HSIOM_POS
#endif /* (Uart_Mc_MOSI_SCL_RX_PIN) */

#if (Uart_Mc_MISO_SDA_TX_PIN)
    #define Uart_Mc_MISO_SDA_TX_HSIOM_REG      Uart_Mc_TX_SDA_MISO_HSIOM_REG
    #define Uart_Mc_MISO_SDA_TX_HSIOM_PTR      Uart_Mc_TX_SDA_MISO_HSIOM_REG
    #define Uart_Mc_MISO_SDA_TX_HSIOM_MASK     Uart_Mc_TX_SDA_MISO_HSIOM_REG
    #define Uart_Mc_MISO_SDA_TX_HSIOM_POS      Uart_Mc_TX_SDA_MISO_HSIOM_REG
#endif /* (Uart_Mc_MISO_SDA_TX_PIN_PIN) */

#if (Uart_Mc_SCLK_PIN)
    #ifndef Uart_Mc_SCLK_HSIOM_REG
    #define Uart_Mc_SCLK_HSIOM_REG     Uart_Mc_CTS_SCLK_HSIOM_REG
    #define Uart_Mc_SCLK_HSIOM_PTR     Uart_Mc_CTS_SCLK_HSIOM_PTR
    #define Uart_Mc_SCLK_HSIOM_MASK    Uart_Mc_CTS_SCLK_HSIOM_MASK
    #define Uart_Mc_SCLK_HSIOM_POS     Uart_Mc_CTS_SCLK_HSIOM_POS
    #endif /* Uart_Mc_SCLK_HSIOM_REG */
#endif /* (Uart_Mc_SCLK_PIN) */

#if (Uart_Mc_SS0_PIN)
    #ifndef Uart_Mc_SS0_HSIOM_REG
    #define Uart_Mc_SS0_HSIOM_REG      Uart_Mc_RTS_SS0_HSIOM_REG
    #define Uart_Mc_SS0_HSIOM_PTR      Uart_Mc_RTS_SS0_HSIOM_PTR
    #define Uart_Mc_SS0_HSIOM_MASK     Uart_Mc_RTS_SS0_HSIOM_MASK
    #define Uart_Mc_SS0_HSIOM_POS      Uart_Mc_RTS_SS0_HSIOM_POS
    #endif /* Uart_Mc_SS0_HSIOM_REG */
#endif /* (Uart_Mc_SS0_PIN) */

#define Uart_Mc_MOSI_SCL_RX_WAKE_PIN_INDEX Uart_Mc_RX_WAKE_SCL_MOSI_PIN_INDEX
#define Uart_Mc_MOSI_SCL_RX_PIN_INDEX      Uart_Mc_RX_SCL_MOSI_PIN_INDEX
#define Uart_Mc_MISO_SDA_TX_PIN_INDEX      Uart_Mc_TX_SDA_MISO_PIN_INDEX
#ifndef Uart_Mc_SCLK_PIN_INDEX
#define Uart_Mc_SCLK_PIN_INDEX             Uart_Mc_CTS_SCLK_PIN_INDEX
#endif /* Uart_Mc_SCLK_PIN_INDEX */
#ifndef Uart_Mc_SS0_PIN_INDEX
#define Uart_Mc_SS0_PIN_INDEX              Uart_Mc_RTS_SS0_PIN_INDEX
#endif /* Uart_Mc_SS0_PIN_INDEX */

#define Uart_Mc_MOSI_SCL_RX_WAKE_PIN_MASK Uart_Mc_RX_WAKE_SCL_MOSI_PIN_MASK
#define Uart_Mc_MOSI_SCL_RX_PIN_MASK      Uart_Mc_RX_SCL_MOSI_PIN_MASK
#define Uart_Mc_MISO_SDA_TX_PIN_MASK      Uart_Mc_TX_SDA_MISO_PIN_MASK
#ifndef Uart_Mc_SCLK_PIN_MASK
#define Uart_Mc_SCLK_PIN_MASK             Uart_Mc_CTS_SCLK_PIN_MASK
#endif /* Uart_Mc_SCLK_PIN_MASK */
#ifndef Uart_Mc_SS0_PIN_MASK
#define Uart_Mc_SS0_PIN_MASK              Uart_Mc_RTS_SS0_PIN_MASK
#endif /* Uart_Mc_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_Uart_Mc_H) */


/* [] END OF FILE */
