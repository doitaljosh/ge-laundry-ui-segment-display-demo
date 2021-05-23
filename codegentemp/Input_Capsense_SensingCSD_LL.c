/***************************************************************************//**
* \file Input_Capsense_SensingCSD_LL.c
* \version 7.0
*
* \brief
*   This file defines the data structure global variables and provides
*   implementation for the low-level APIs of the CSD part of
*   the Sensing module. The file contains the APIs used for the CSD block
*   initialization, calibration, and scanning.
*
* \see Input_Capsense v7.0 Datasheet
*
*//*****************************************************************************
* Copyright (2016-2019), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/
#include "Input_Capsense_Structure.h"
#include "Input_Capsense_Configuration.h"
#include "Input_Capsense_SensingCSD_LL.h"
#if (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN)
    #include "Input_Capsense_SelfTest.h"
#endif

#include "cyapicallbacks.h"

#if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)

/***************************************
* API Constants
***************************************/

#if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)

    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_AUTO_ZERO_EN)
        #define Input_Capsense_CSD_AZ_ENABLE_CFG                  (Input_Capsense_CSD_AZ_EN_MASK)
    #else
        #define Input_Capsense_CSD_AZ_ENABLE_CFG                  (0uL)
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_AUTO_ZERO_EN) */

    #if (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG)
        #define Input_Capsense_HSCMP_SCAN_MASK                    (Input_Capsense_HSCMP_EN_MASK | Input_Capsense_CSD_AZ_ENABLE_CFG |\
                                                                     Input_Capsense_HSCMP_INVERT_MASK)
    #else
        #define Input_Capsense_HSCMP_SCAN_MASK                    (Input_Capsense_HSCMP_EN_MASK | Input_Capsense_CSD_AZ_ENABLE_CFG)
    #endif /* (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG) */

    #define Input_Capsense_HSCMP_INIT_MASK                        (Input_Capsense_HSCMP_EN_MASK | Input_Capsense_CSD_AZ_ENABLE_CFG)

    #define Input_Capsense_DEFAULT_SW_SHIELD_SEL                  (0x00000000uL)
    #define Input_Capsense_DEFAULT_CSD_SW_DSI_SEL                 (Input_Capsense_SW_DSI_SEL_CMODPAD | Input_Capsense_SW_DSI_SEL_TANKPAD)
    #define Input_Capsense_DEFAULT_CSD_INTR_SET                   (0x00000000uL)
    #define Input_Capsense_DEFAULT_SW_HS_P_SEL                    (0x00000000uL)
    #define Input_Capsense_DEFAULT_SW_HS_N_SEL                    (0x00000000uL)
    #define Input_Capsense_DEFAULT_CSD_SW_FW_TANK_SEL             (0x00000000uL)
    #define Input_Capsense_DEFAULT_CSD_ADC_CTL                    (0x00000000uL)
    #define Input_Capsense_DEFAULT_HSCMP_CFG                      (0x00000000uL)

    /* CY_ID285392 */
    #define Input_Capsense_FILTER_DELAY_MAX                   (Input_Capsense_CONFIG_FILTER_DELAY_4_CYCLES)
    #define Input_Capsense_EXTRA_COUNTS_MAX                   (Input_Capsense_FILTER_DELAY_MAX + 5u + 20u)

#else

    /* Set IDAC ranges */
    #if (Input_Capsense_IDAC_GAIN_8X == Input_Capsense_CSD_IDAC_GAIN)
        #define Input_Capsense_DEFAULT_IDAC_MOD_RANGE         (Input_Capsense_IDAC_MOD_RANGE_MASK)
        #define Input_Capsense_DEFAULT_IDAC_COMP_RANGE        (Input_Capsense_IDAC_COMP_RANGE_MASK)
    #else
        #define Input_Capsense_DEFAULT_IDAC_MOD_RANGE         (0u)
        #define Input_Capsense_DEFAULT_IDAC_COMP_RANGE        (0u)
    #endif /* (Input_Capsense_IDAC_GAIN_8X == Input_Capsense_CSD_IDAC_GAIN) */

    /* Defining default IDACs configuration according to settings in customizer. */
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
        #define Input_Capsense_DEFAULT_CSD_IDAC_CONFIG        (Input_Capsense_IDAC_MOD_MODE_VARIABLE |\
                                                                 Input_Capsense_IDAC_COMP_MODE_FIXED |\
                                                                 Input_Capsense_DEFAULT_IDAC_MOD_RANGE |\
                                                                 Input_Capsense_DEFAULT_IDAC_COMP_RANGE)
    #else
        #define Input_Capsense_DEFAULT_CSD_IDAC_CONFIG        (Input_Capsense_IDAC_MOD_MODE_VARIABLE |\
                                                                 Input_Capsense_DEFAULT_IDAC_MOD_RANGE)
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) */

#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */


/***************************************
* Variables
***************************************/

#if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
    uint32 Input_Capsense_configCsd = Input_Capsense_DEFAULT_CSD_CONFIG;
#else
    uint32 Input_Capsense_configCsd = Input_Capsense_DEFAULT_CSD_CONFIG | Input_Capsense_DEFAULT_MODULATION_MODE;
    static uint32 Input_Capsense_counterResolution = Input_Capsense_CNT_RESOLUTION_12_BITS;
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */

/* Flag to indicate electrodes that were connected previously */
static uint8 Input_Capsense_eleCsdDisconnectFlag = 0u;
#if ((Input_Capsense_ENABLE == Input_Capsense_CSDV2) && (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN))
    /* Number of re-samplings when the bad conversion occurs */
    uint8 Input_Capsense_badConversionsNum = Input_Capsense_BAD_CONVERSIONS_NUM;
#endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSDV2) && (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN)) */


/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

#if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
    static void Input_Capsense_SsSetShieldDelay(uint32 delay);
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN)
        static void Input_Capsense_SsCSDEnableShieldTank(void);
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN) */
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */

#if ((Input_Capsense_CSD_SS_DIS != Input_Capsense_CSD_AUTOTUNE) || \
     (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTOCAL_EN))
    static cystatus Input_Capsense_SsCSDCalibrateCheck(uint32 widgetId, uint32 target);
    static void Input_Capsense_SsCSDCalibrate(uint32 widgetId, uint32 target);
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
        static void Input_Capsense_SsCSDNormalizeIdac(Input_Capsense_FLASH_WD_STRUCT const *ptrFlashWidget, uint32 target);
    #endif
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTO_GAIN_EN)
        static uint32 Input_Capsense_SsCSDSwitchIdacGain(Input_Capsense_FLASH_WD_STRUCT const *ptrFlashWidget);
    #endif
#endif /* ((Input_Capsense_CSD_SS_DIS != Input_Capsense_CSD_AUTOTUNE) || \
           (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTOCAL_EN))  */

#if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
    static void Input_Capsense_SsCSDSetFilterDelay(void);
#else
    CY_INLINE static void Input_Capsense_SsCSDClockRestart(void);
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
CY_INLINE static void Input_Capsense_SsCSDCmodPrecharge(void);
CY_INLINE static void Input_Capsense_SsCSDTriggerScan(void);
static void Input_Capsense_SsCSDConfigIDACs(void);
static void Input_Capsense_SsCSDSetModeSnsClockDivider(uint32 snsClkSource, uint32 snsClkDivider);

/** \}
* \endcond */


#if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
    /*******************************************************************************
    * Function Name: Input_Capsense_SsSetShieldDelay
    ****************************************************************************//**
    *
    * \brief
    *   This is an internal function that sets a shield delay.
    *
    * \details
    *   The function updates the CSD configuration register bits that define the shield
    *   signal delay relatively to the sense signal.
    *
    * \param delay
    *   Specifies the shield delay value:
    *    PSoC 4100/4200 value interpretation:
    *         0 - no delay
    *         1 - 1 cycle of HFCLK
    *         2 - 2 cycles of HFCLK
    *    Third-generation HW block (except 4100/4200 devices):
    *         0 - no delay
    *         3 - 10ns delay
    *         2 - 50ns delay
    *    Fourth-generation HW block:
    *         0 - no delay
    *         1 - 5ns delay
    *         2 - 10ns delay
    *         3 - 20ns delay
    *
    *******************************************************************************/
    static void Input_Capsense_SsSetShieldDelay(uint32 delay)
    {
        /* Update CSD config register shield delay bits with shield delay value */
        Input_Capsense_configCsd &= (uint32)(~Input_Capsense_CONFIG_SHIELD_DELAY_MASK);
        Input_Capsense_configCsd |= (delay << Input_Capsense_SHIELD_DELAY_SHIFT);
    }

    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN)
        /*******************************************************************************
        * Function Name: Input_Capsense_SsCSDEnableShieldTank
        ****************************************************************************//**
        *
        * \brief
        *   This function configures Csh pin
        *
        * \details
        *   The function updates the CSH_HSIOM register to connect Csh to AMUXBUS-B.
        *   For Third-generation HW block it additionally sets Strong drive mode for Csh
        *   and applies High level to Csh pin when precharge is set to IO buffer.
        *
        *******************************************************************************/
        static void Input_Capsense_SsCSDEnableShieldTank(void)
        {
            /* Update the CSH_HSIOM register to connect Csh to AMUXBUS-B */
            Input_Capsense_WriteBitsSafe(Input_Capsense_CSH_HSIOM_PTR, Input_Capsense_CSH_HSIOM_MASK,
                        (uint32)(Input_Capsense_HSIOM_SEL_AMUXB << Input_Capsense_CSH_HSIOM_SHIFT));

            #if ((Input_Capsense_CSH_PRECHARGE_IO_BUF == Input_Capsense_CSD_CSH_PRECHARGE_SRC) &&\
                 (Input_Capsense_DISABLE == Input_Capsense_CSDV2))
                /* Set Strong drive mode for Csh */
                Input_Capsense_WriteBitsSafe(Input_Capsense_CSH_PC_PTR,
                            (uint32)(Input_Capsense_CSH_PC_MASK << Input_Capsense_CSH_PC_SHIFT),
                            (uint32)(Input_Capsense_CSH_PC_STRONG_MODE << Input_Capsense_CSH_PC_SHIFT));
                /* Appliy High level to Csh pin for Csh */
                Input_Capsense_WriteBitsSafe(Input_Capsense_CSH_DR_PTR, (uint32)(Input_Capsense_DR_MASK << Input_Capsense_CSH_SHIFT), Input_Capsense_CSH_DR_CONFIG);
            #else
                /* Set output port register to 0 to connect to GND */
                Input_Capsense_WriteBitsSafe(Input_Capsense_CSH_DR_PTR, (uint32)(Input_Capsense_DR_MASK << Input_Capsense_CSH_SHIFT), 0u);
            #endif
        }
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN) */

    #if (0u != Input_Capsense_CSD_TOTAL_SHIELD_COUNT)
        /*******************************************************************************
        * Function Name: Input_Capsense_SsCSDEnableShieldElectrodes
        ****************************************************************************//**
        *
        * \brief
        *   This internal function initializes Shield Electrodes.
        *
        * \details
        *   The function sets the bit in the HSIOM register which enables the shield electrode
        *   functionality on the pin. The port and pin configurations are stored in
        *   the Input_Capsense_shieldIoList structure.
        *
        *******************************************************************************/
        void Input_Capsense_SsCSDEnableShieldElectrodes(void)
        {
            Input_Capsense_SsCSDSetShieldElectrodesState(Input_Capsense_SNS_CONNECTION_SHIELD);
        }


        /*******************************************************************************
        * Function Name: Input_Capsense_SsCSDDisableShieldElectrodes
        ****************************************************************************//**
        *
        * \brief
        *   This internal function disables Shield Electrodes.
        *
        * \details
        *   The function resets the bit in the HSIOM register which disables the shield
        *   electrode functionality on the pin. The port and pin configurations are
        *   stored in  the Input_Capsense_shieldIoList structure.
        *
        *******************************************************************************/
        void Input_Capsense_SsCSDDisableShieldElectrodes(void)
        {
            Input_Capsense_SsCSDSetShieldElectrodesState(Input_Capsense_SNS_CONNECTION_GROUND);
        }


        /*******************************************************************************
        * Function Name: Input_Capsense_SsCSDSetShieldElectrodesState
        ****************************************************************************//**
        *
        * \brief
        *   Sets specified shield electrode pin connection state for all dedicated
        *   shield electrodes.
        *
        * \details
        *   The function updates following registers for each shield
        *   electrode:
        *   - port configuration register
        *   - pin data register
        *   - pin HSIOM register
        *   The shield electrodes port and pin configuration registers addresses are
        *   stored in the Input_Capsense_shieldIoList structure.
        *
        * \param state
        *   A new state of the shield electrodes. Available values:
        *   - Input_Capsense_SNS_CONNECTION_GROUND - disconnects electrode from
        *       CSD hardware block and sets it to GPIO mode with Strong Drive
        *   - Input_Capsense_SNS_CONNECTION_HIGHZ - disconnects electrode from
        *       CSD hardware block and sets it to GPIO mode with Analog Hi-Z
        *   - Input_Capsense_SNS_CONNECTION_SHIELD - connects electrode to
        *       CSD hardware block
        *   - Input_Capsense_SNS_CONNECTION_UNDEFINED - sets the same electrode
        *       connection as for Input_Capsense_SNS_CONNECTION_GROUND
        *
        *******************************************************************************/
        void Input_Capsense_SsCSDSetShieldElectrodesState(uint32 state)
        {
            uint8  interruptState;

            uint32 loopIndex;

            uint32 newPinPcVal;
            uint32 newPinHsiomVal;

            uint32 tmpPcDrRegValue;
            uint32 tmpHsiomRegValue;

            Input_Capsense_SHIELD_IO_STRUCT const *shieldIoPtr;

            switch(state)
            {
                case Input_Capsense_SNS_CONNECTION_GROUND:
                    newPinPcVal = CY_SYS_PINS_DM_STRONG;
                    newPinHsiomVal = Input_Capsense_HSIOM_SEL_GPIO;
                    break;
                case Input_Capsense_SNS_CONNECTION_HIGHZ:
                    newPinPcVal = CY_SYS_PINS_DM_ALG_HIZ;
                    newPinHsiomVal = Input_Capsense_HSIOM_SEL_GPIO;
                    break;
                case Input_Capsense_SNS_CONNECTION_SHIELD:
                    newPinPcVal = CY_SYS_PINS_DM_ALG_HIZ;
                    newPinHsiomVal = Input_Capsense_HSIOM_SEL_CSD_SHIELD;
                    break;
                default:
                    newPinPcVal = CY_SYS_PINS_DM_STRONG;
                    newPinHsiomVal = Input_Capsense_HSIOM_SEL_GPIO;
                    break;
            }

            shieldIoPtr = &Input_Capsense_shieldIoList[0u];
            for (loopIndex = 0u; loopIndex < Input_Capsense_CSD_TOTAL_SHIELD_COUNT; loopIndex++)
            {
                interruptState = CyEnterCriticalSection();

                tmpHsiomRegValue = CY_GET_REG32 (shieldIoPtr->hsiomPtr);
                tmpHsiomRegValue &= ~(shieldIoPtr->hsiomMask);
                CY_SET_REG32 (shieldIoPtr->hsiomPtr, tmpHsiomRegValue);

                tmpPcDrRegValue = CY_GET_REG32 (shieldIoPtr->pcPtr);
                tmpPcDrRegValue &= ~(Input_Capsense_GPIO_PC_MASK << shieldIoPtr->shift);
                tmpPcDrRegValue |=  (newPinPcVal << shieldIoPtr->shift);
                CY_SET_REG32 (shieldIoPtr->pcPtr, tmpPcDrRegValue);

                tmpHsiomRegValue |=  (newPinHsiomVal << shieldIoPtr->hsiomShift);
                CY_SET_REG32 (shieldIoPtr->hsiomPtr, tmpHsiomRegValue);

                tmpPcDrRegValue = CY_GET_REG32 (shieldIoPtr->drPtr);
                tmpPcDrRegValue &= ~(1uL << shieldIoPtr->drShift);
                CY_SET_REG32 (shieldIoPtr->drPtr, tmpPcDrRegValue);

                CyExitCriticalSection(interruptState);

                /* Get next electrode */
                shieldIoPtr++;
            }
        }
    #endif /* (0u != Input_Capsense_CSD_TOTAL_SHIELD_COUNT) */
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */


/*******************************************************************************
* Function Name: Input_Capsense_SsCSDSetModeSnsClockDivider
****************************************************************************//**
*
* \brief
*   Sets sense source and Sense Clock Divider
*
* \details
*   For Fourth-generation HW block: Updates Input_Capsense_SENSE_PERIOD register with
*   sense source and Sense Clock Divider.
*   For Third-generation HW block: Updates Input_Capsense_configCsd variable with
*   sense source and sets sense clock divider.
*
* \param
*   snsClkSource The sense source for the sense clock.
* \param
*   snsClkDivider The divider value for the sense clock.
*
*******************************************************************************/
static void Input_Capsense_SsCSDSetModeSnsClockDivider(uint32 snsClkSource, uint32 snsClkDivider)
{
    #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
        /* Update reg value with divider and configuration */
        CY_SET_REG32(Input_Capsense_SENSE_PERIOD_PTR, snsClkSource | (snsClkDivider - 1u));
    #else
        /* Set configuration */
        Input_Capsense_configCsd &= ~(Input_Capsense_CONFIG_PRS_SELECT_MASK | Input_Capsense_CSD_PRS_12_BIT);
        Input_Capsense_configCsd |= snsClkSource;

        /* Set sense clock divider */
        Input_Capsense_SsSetSnsClockDivider(snsClkDivider);
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
}


#if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
    /*******************************************************************************
    * Function Name: Input_Capsense_SsCSDSetFilterDelay
    ****************************************************************************//**
    *
    * \brief
    *   Sets the filter delay for Fourth-generation HW block.
    *
    * \details
    *   This function updates Fourth-generation HW block configuration
    *   variable Input_Capsense_configCsd
    *   with the filter delay which depends on the sample clock frequency.
    *   This variable is written into register during enabling
    *   Fourth-generation HW block .
    *
    *******************************************************************************/
    static void Input_Capsense_SsCSDSetFilterDelay(void)
    {
        #if (Input_Capsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ)
            uint32 sampleClkFreqHz;
        #endif /* (Input_Capsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) */

        Input_Capsense_configCsd &= ~Input_Capsense_CONFIG_FILTER_DELAY_MASK;

        #if (Input_Capsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ)
            sampleClkFreqHz = CYDEV_BCLK__HFCLK__HZ / (uint32)Input_Capsense_dsRam.modCsdClk;
            if(sampleClkFreqHz <= Input_Capsense_MOD_CSD_CLK_12MHZ)
            {
                Input_Capsense_configCsd |= Input_Capsense_CONFIG_FILTER_DELAY_12MHZ;
            }
            else if(sampleClkFreqHz <= Input_Capsense_MOD_CSD_CLK_24MHZ)
            {
                Input_Capsense_configCsd |= Input_Capsense_CONFIG_FILTER_DELAY_24MHZ;
            }
            else
            {
                Input_Capsense_configCsd |= Input_Capsense_CONFIG_FILTER_DELAY_48MHZ;
            }
        #else
            Input_Capsense_configCsd |= Input_Capsense_CONFIG_FILTER_DELAY_12MHZ;
        #endif /* (Input_Capsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) */
    }
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)  */


/*******************************************************************************
* Function Name: Input_Capsense_SsCSDConfigIDACs
****************************************************************************//**
*
* \brief
*   Configures the mode for IDAC registers
*
* \details
*   This function configures the IDAC modes depend on Compensation IDAC
*   enabled or disabled.
*
*******************************************************************************/
static void Input_Capsense_SsCSDConfigIDACs(void)
{
    #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
        CY_SET_REG32(Input_Capsense_CSD_IDACA_PTR, Input_Capsense_IDAC_MOD_DEFAULT_CFG);
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
            CY_SET_REG32(Input_Capsense_CSD_IDACB_PTR, Input_Capsense_IDAC_COMP_DEFAULT_CFG);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) */
    #else
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
            CY_SET_REG32(Input_Capsense_IDAC_PTR, Input_Capsense_DEFAULT_CSD_IDAC_CONFIG);
        #else
            CY_SET_REG32(Input_Capsense_IDAC_PTR, CY_GET_REG32(Input_Capsense_IDAC_PTR) &
                                                                ~(Input_Capsense_IDAC_MOD_MODE_MASK |
                                                                  Input_Capsense_IDAC_MOD_MASK));
            CY_SET_REG32(Input_Capsense_IDAC_PTR, CY_GET_REG32(Input_Capsense_IDAC_PTR) |
                                                                 Input_Capsense_DEFAULT_CSD_IDAC_CONFIG);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) */
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
}


/*******************************************************************************
* Function Name: Input_Capsense_SsCSDInitialize
****************************************************************************//**
*
* \brief
*   This API initializes the CSD module.
*
* \details
*   The function performs the following steps for Fourth-generation HW block:
*   1) Sets GPIO output to "0" for all sensor pins;
*   2) Connects CMOD to AMUXBUS-A and to CSDBUS-A;
*   3) Connects CMOD to (sense path) to CSDCOMP;
*   4) Connects Csh_tank to AMUXBUS-B and to CSDBUS-B;
*   5) Connects VREF to REFGEN;
*   6) Configures REFGEN and sets the reference voltage;
*   7) Connects VREF to CSDCOMP and HSCOMP;
*   8) Configures IDAC and connect to CSDBUS-A (to drive CMOD);
*   9) Configures ModClk;
*   10) Configure SnsClk source;
*   11) Sets other CSD configurations (Csd Auto Zero time,
*       Sample Init period, interrupts,
*       CMOD and Csh_tank/shield initialization switch resistance).
*
*   The function performs the following steps for Third-generation HW block:
*   1) Sets all the sensors to the inactive state;
*   2) Enables Shield Electrodes;
*   3) Configures the CSD block and IDACs;
*   4) Connects Cmod to AMUXBUS-A;
*   5) Enables the clocks;
*   6) Sets the shield delay;
*   7) Enables the CSD block; connects Vref Buffer to the AMUX bus.
*
*******************************************************************************/
void Input_Capsense_SsCSDInitialize(void)
{
    #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
        uint32 newRegValue;
    #endif

    /* Set all the sensors to inactive state */
    if(Input_Capsense_dsRam.scanCurrentISC != Input_Capsense_dsRam.scanCsdISC)
    {
        Input_Capsense_SsSetAllIOsState((uint32)Input_Capsense_dsRam.scanCsdISC);
        Input_Capsense_dsRam.scanCurrentISC = Input_Capsense_dsRam.scanCsdISC;
    }

    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
        /* Connect shields to AMUX-B bus (config HSIOM regs) */
        #if (0u != Input_Capsense_CSD_TOTAL_SHIELD_COUNT)
            Input_Capsense_SsCSDEnableShieldElectrodes();
        #endif /* (0u != Input_Capsense_CSD_TOTAL_SHIELD_COUNT) */

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN)
            /* Configure Csh */
            Input_Capsense_SsCSDEnableShieldTank();
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN) */
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */

    #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)

        Input_Capsense_DischargeExtCapacitors(Input_Capsense_EXT_CAP_DISCHARGE_TIME);

        /* Initialize the unused CSD registers to defaut state */
        CY_SET_REG32(Input_Capsense_SENSE_DUTY_PTR, Input_Capsense_DEFAULT_SENSE_DUTY_SEL);

        /* Configure VREF */
        newRegValue = CY_GET_REG32(Input_Capsense_SW_REFGEN_SEL_PTR);
        newRegValue |= Input_Capsense_DEFAULT_SW_REFGEN_SEL;

        CY_SET_REG32(Input_Capsense_SW_REFGEN_SEL_PTR, newRegValue);
        CY_SET_REG32(Input_Capsense_INTR_SET_PTR,         Input_Capsense_DEFAULT_CSD_INTR_SET);
        CY_SET_REG32(Input_Capsense_SW_FW_TANK_SEL_PTR,   Input_Capsense_DEFAULT_CSD_SW_FW_TANK_SEL);
        CY_SET_REG32(Input_Capsense_SW_DSI_SEL_PTR,       Input_Capsense_DEFAULT_CSD_SW_DSI_SEL);
        CY_SET_REG32(Input_Capsense_ADC_CTL_PTR,          Input_Capsense_DEFAULT_CSD_ADC_CTL);
        CY_SET_REG32(Input_Capsense_AMBUF_PTR,            Input_Capsense_AMBUF_PWR_MODE_OFF);
        CY_SET_REG32(Input_Capsense_SW_SHIELD_SEL_PTR,    Input_Capsense_DEFAULT_SW_SHIELD_SEL);
        CY_SET_REG32(Input_Capsense_SW_HS_P_SEL_PTR,      Input_Capsense_DEFAULT_SW_HS_P_SEL);
        CY_SET_REG32(Input_Capsense_SW_HS_N_SEL_PTR,      Input_Capsense_DEFAULT_SW_HS_N_SEL);
        CY_SET_REG32(Input_Capsense_HSCMP_PTR,            Input_Capsense_DEFAULT_HSCMP_CFG);

        /* Connect CMOD to AMUXBUS-A */
        Input_Capsense_WriteBitsSafe(Input_Capsense_CMOD_HSIOM_PTR, Input_Capsense_CMOD_HSIOM_MASK,
                    (uint32)(Input_Capsense_HSIOM_SEL_AMUXA << Input_Capsense_CMOD_HSIOM_SHIFT));

        /* Set output port register to 0 to connect to GND */
        Input_Capsense_WriteBitsSafe(Input_Capsense_CMOD_DR_PTR, Input_Capsense_Cmod__0__MASK, 0u);

        /* Connect AMUXBUS-A to CSDBUS-A */
        newRegValue = CY_GET_REG32(Input_Capsense_SW_BYP_SEL_PTR);
        newRegValue |= Input_Capsense_SW_BYP_SEL_SW_BYA_MASK;
        CY_SET_REG32(Input_Capsense_SW_BYP_SEL_PTR, newRegValue);

        /* Connect CMOD to (sense path) to CSDCOMP */
        #if (Input_Capsense_CSD__CMOD_PAD == Input_Capsense_CMOD_CONNECTION)
            CY_SET_REG32(Input_Capsense_SW_CMP_P_SEL_PTR, Input_Capsense_SW_CMP_P_SEL_SW_SFPM_STATIC_CLOSE);
        #elif (Input_Capsense_CSD__CSHIELD_PAD == Input_Capsense_CMOD_CONNECTION)
            CY_SET_REG32(Input_Capsense_SW_CMP_P_SEL_PTR, Input_Capsense_SW_CMP_P_SEL_SW_SFPS_STATIC_CLOSE);
        #else
            CY_SET_REG32(Input_Capsense_SW_CMP_P_SEL_PTR, Input_Capsense_SW_CMP_P_SEL_SW_SFPT_STATIC_CLOSE);
        #endif /* (Input_Capsense_CSD__CMOD_PAD == Input_Capsense_CMOD_CONNECTION) */

        /* Configure shield driving path */
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
            /* Connect AMUXBUS-B to CSDBUS-B (and AMUXBUS-A to CSDBUS-A ) */
            CY_SET_REG32(Input_Capsense_SW_BYP_SEL_PTR, Input_Capsense_SW_BYP_SEL_SW_BYA_MASK | Input_Capsense_SW_BYP_SEL_SW_BYB_MASK);

            /* Connect AMUXBUS-B to HSCMP positive input */
            CY_SET_REG32(Input_Capsense_SW_HS_P_SEL_PTR, 0x00000000uL);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */

        /* Configure VREF */
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
            /* Connect VREF to REFGEN. Connect IDACB to CSDBUSA */
            newRegValue = CY_GET_REG32(Input_Capsense_SW_REFGEN_SEL_PTR);
            newRegValue |= Input_Capsense_SW_REFGEN_SEL_SW_SGR_MASK | Input_Capsense_SW_REFGEN_SEL_SW_IAIB_MASK;
            CY_SET_REG32(Input_Capsense_SW_REFGEN_SEL_PTR, newRegValue);
        #else
            /* Connect VREF to REFGEN (IAIB switch is open) */
            newRegValue = CY_GET_REG32(Input_Capsense_SW_REFGEN_SEL_PTR);
            newRegValue |= Input_Capsense_SW_REFGEN_SEL_SW_SGR_MASK;
            CY_SET_REG32(Input_Capsense_SW_REFGEN_SEL_PTR, newRegValue);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) */

        /* Connect VREFHI (from RefGen) to CSDCOMP when Vdda >= 2 V */
        CY_SET_REG32(Input_Capsense_SW_CMP_N_SEL_PTR, Input_Capsense_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE);

        #if (Input_Capsense_2000_MV > Input_Capsense_CYDEV_VDDA_MV)

            /* Configure REFGEN. Set reference voltage when Vdda < 2 V */
            CY_SET_REG32(Input_Capsense_REFGEN_PTR, Input_Capsense_REFGEN_LV);

            /* Connect Vrefhi to AMUBUF positive input when Vdaa < 2V
             *  Connect AMUBUF to SCDCMP negative input when Vdaa < 2V
             */
            #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
                #if (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG)
                    CY_SET_REG32(Input_Capsense_SW_AMUXBUF_SEL_PTR, Input_Capsense_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE |
                                                                          Input_Capsense_SW_AMUXBUF_SEL_SW_ICB_PHI2);
                #else
                    CY_SET_REG32(Input_Capsense_SW_AMUXBUF_SEL_PTR, Input_Capsense_SW_AMUXBUF_SEL_SW_DEFAULT);
                #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */
                CY_SET_REG32(Input_Capsense_AMBUF_PTR, Input_Capsense_AMBUF_PWR_MODE_NORM);
            #else
                CY_SET_REG32(Input_Capsense_AMBUF_PTR, Input_Capsense_AMBUF_PWR_MODE_OFF);
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */

            /* Connect VREFHI to HSCOMP */
            CY_SET_REG32(Input_Capsense_SW_HS_N_SEL_PTR, Input_Capsense_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE);
        #else

            /* Configure REFGEN. Set reference voltage when Vdda >= 2 V */
            CY_SET_REG32(Input_Capsense_REFGEN_PTR, Input_Capsense_REFGEN_HV);

            #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
                /* Turn on CSD_AMBUF high power level when Vdaa >= 2V */
                CY_SET_REG32(Input_Capsense_AMBUF_PTR, Input_Capsense_AMBUF_PWR_MODE_HI);

                #if (Input_Capsense_IDAC_SINKING != Input_Capsense_CSD_IDAC_CONFIG)
                    CY_SET_REG32(Input_Capsense_SW_AMUXBUF_SEL_PTR, Input_Capsense_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE |
                                                                          Input_Capsense_SW_AMUXBUF_SEL_SW_ICB_PHI2);
                #else
                    CY_SET_REG32(Input_Capsense_SW_AMUXBUF_SEL_PTR, Input_Capsense_SW_AMUXBUF_SEL_SW_DEFAULT);
                #endif /* (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG) */
            #else
                CY_SET_REG32(Input_Capsense_SW_AMUXBUF_SEL_PTR, Input_Capsense_SW_AMUXBUF_SEL_SW_DEFAULT);
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */

            /* Connect VREFHI to HSCOMP */
            CY_SET_REG32(Input_Capsense_SW_HS_N_SEL_PTR, Input_Capsense_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE);
        #endif /* (Input_Capsense_2000_MV > Input_Capsense_CYDEV_VDDA_MV) */

        /* Configure IDACs mode */
        Input_Capsense_SsCSDConfigIDACs();

        /* Configure ModClk */
        Input_Capsense_SsSetModClkClockDivider((uint32)Input_Capsense_dsRam.modCsdClk);

        /* Set other CSD configurations */
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
            Input_Capsense_SsSetShieldDelay(Input_Capsense_CSD_SHIELD_DELAY);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */

        /* Configure HW block filter delay */
        Input_Capsense_SsCSDSetFilterDelay();

        #if (Input_Capsense_DISABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN)
            /* Enable power to sub-blocks */
            CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd |
                                                      Input_Capsense_CONFIG_SENSE_EN_MASK |
                                                      Input_Capsense_CONFIG_ENABLE_MASK);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN) */

        /* Set Csd Auto Zero time (set AZ_TIME bitmask) */
        CY_SET_REG32(Input_Capsense_SEQ_TIME_PTR, Input_Capsense_CSD_AUTO_ZERO_TIME);

        /* Select CMOD and Csh_tank/shield initialization switch resistance */
        CY_SET_REG32(Input_Capsense_SW_RES_PTR, 0x00000000);

        /* Set the number of dummy fine initialization cycles */
        CY_SET_REG32(Input_Capsense_SEQ_INIT_CNT_PTR, Input_Capsense_CSD_FINE_INIT_TIME);

    #else

        /* Configure IDACs mode */
        Input_Capsense_SsCSDConfigIDACs();

        /* Connect Cmod to AMUXBUS-A using HSIOM registers */
        Input_Capsense_WriteBitsSafe(Input_Capsense_CMOD_HSIOM_PTR, Input_Capsense_CMOD_HSIOM_MASK,
                    (uint32)(Input_Capsense_HSIOM_SEL_AMUXA << Input_Capsense_CMOD_HSIOM_SHIFT));

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
            Input_Capsense_SsSetShieldDelay(Input_Capsense_CSD_SHIELD_DELAY);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */

        /* Enable CSD block. Connect Vref Buffer to AMUX bus to make sure that Cmod is charged before scanning in active mode */
        #if (Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN)
            CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd);
        #else
            CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CTANK_PRECHARGE_CONFIG_CSD_EN);
        #endif
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */

    #if ((Input_Capsense_ENABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN) &&\
         (Input_Capsense_CLK_SOURCE_DIRECT == Input_Capsense_CSD_SNS_CLK_SOURCE))
         /* Set clock dividers and clock source mode */
        Input_Capsense_SsCSDConfigClock();
    #endif
}


/*******************************************************************************
* Function Name: Input_Capsense_SsCSDElectrodeCheck
****************************************************************************//**
*
* \brief
*   Checks if electrodes were previously connected using
 * Input_Capsense_CSDSetupWidgetExt() API and if yes disconnects them.
*
* \details
*   This function checks if Input_Capsense_eleCsdDisconnectFlag is set.
*   If it set, the function disconnects the previously connected electrode.
*   The previous IO is contained in Input_Capsense_curSnsIOPtr and
*   Input_Capsense_curFlashSnsPtr contains the previous data for Ganged
*   sensors.
*
*******************************************************************************/
void Input_Capsense_SsCSDElectrodeCheck(void)
{
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
        uint32 tempVal;
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN) */

    if (Input_Capsense_ENABLE == Input_Capsense_eleCsdDisconnectFlag)
    {
        /* Disconnect if electrodes were previous connected by CSDSetupWidgetExt() API */
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
            /* Check ganged sns flag  */
            if (Input_Capsense_GANGED_SNS_MASK == (Input_Capsense_curFlashWdgtPtr->staticConfig & Input_Capsense_GANGED_SNS_MASK))
            {
                /* Get number of ganged pins */
                tempVal = Input_Capsense_curFlashSnsPtr->numPins;

                /* Get IO pointer  */
                Input_Capsense_curSnsIOPtr = &Input_Capsense_ioList[Input_Capsense_curFlashSnsPtr->firstPinId];

                /* Disconnect all ganged sensors */
                do
                {
                    Input_Capsense_CSDDisconnectSns(Input_Capsense_curSnsIOPtr);
                    Input_Capsense_curSnsIOPtr++;
                    tempVal--;
                } while (0u != tempVal);
            }
            else
            {
                /* Disconnect ganged sensor */
                Input_Capsense_CSDDisconnectSns(Input_Capsense_curSnsIOPtr);
            }
        #else
            /* Disable sensor */
            Input_Capsense_CSDDisconnectSns(Input_Capsense_curSnsIOPtr);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)  */

        Input_Capsense_eleCsdDisconnectFlag = 0u;
    }
}


/*******************************************************************************
* Function Name: Input_Capsense_SsCSDSetUpIdacs
****************************************************************************//**
*
* \brief
*  This internal function changes the IDACs values.
*
* \details
*  If Compensation IDAC is enabled, it updates two IDACs.
*  The Modulator IDAC is common for all the sensors of the widget.
*  The Compensation IDAC is updated for the sensor of the widget which
*  is available in the RAM_SNS_STRUCT structure.
*  If the Compensation IDAC is disabled, the function updates the Modulator IDAC
*  value only in the RAM_WD_BASE_STRUCT structure.
*
* \param
*  ptrWdgt The pointer to the RAM_WD_BASE_STRUCT structure.
*
*******************************************************************************/
void Input_Capsense_SsCSDSetUpIdacs(Input_Capsense_RAM_WD_BASE_STRUCT const *ptrWdgt)
{
    uint8 interruptState;
    uint32 idacGain;

    /* Getting IDAC gain */
    idacGain = Input_Capsense_idacGainTable[ptrWdgt->idacGainIndex].gainReg;

    #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
        uint32 idacARegValue;
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
            uint32 idacBRegValue;
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) */

        interruptState = CyEnterCriticalSection();

        /* Get IDACA Value */
        idacARegValue = CY_GET_REG32(Input_Capsense_CSD_IDACA_PTR);

        /* Clear IDACA value and gain */
        idacARegValue &= ~(Input_Capsense_IDAC_MOD_VAL_MASK | Input_Capsense_IDAC_GAIN_MASK);

        /* Set IDACA value gain */
        #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
            if (Input_Capsense_dsFlash.wdgtArray[(Input_Capsense_widgetIndex)].numCols <= Input_Capsense_sensorIndex)
            {
                idacARegValue |= (uint32)ptrWdgt->rowIdacMod[Input_Capsense_scanFreqIndex];
            }
            else
            {
                idacARegValue |= (uint32)ptrWdgt->idacMod[Input_Capsense_scanFreqIndex];
            }
        #else
            idacARegValue |= (uint32)ptrWdgt->idacMod[Input_Capsense_scanFreqIndex];
        #endif /* (Input_Capsense_CSD_MATRIX_WIDGET_EN | Input_Capsense_CSD_TOUCHPAD_WIDGET_EN) */
        idacARegValue |= idacGain;

        /* Update IDACA register with new value */
        CY_SET_REG32(Input_Capsense_CSD_IDACA_PTR, idacARegValue);
        CyExitCriticalSection(interruptState);

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
            interruptState = CyEnterCriticalSection();
            /* Get IDACB Value */
            idacBRegValue = CY_GET_REG32(Input_Capsense_CSD_IDACB_PTR);

            /* Clear IDACB value and gain */
            idacBRegValue &= ~(Input_Capsense_IDAC_COMP_VAL_MASK | Input_Capsense_IDAC_GAIN_MASK);

            /* Set IDACB value and gain */
            idacBRegValue |= (uint32)Input_Capsense_curRamSnsPtr->idacComp[Input_Capsense_scanFreqIndex];
            idacBRegValue |= idacGain;

            /* Update IDACA register with new value */
            CY_SET_REG32(Input_Capsense_CSD_IDACB_PTR, idacBRegValue);
            CyExitCriticalSection(interruptState);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) */

    #else

        uint32 newRegValue;
        uint8 const *ptrIdacMod = ptrWdgt->idacMod;

        #if (Input_Capsense_CSD_MATRIX_WIDGET_EN  | Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
            if (Input_Capsense_dsFlash.wdgtArray[(Input_Capsense_widgetIndex)].numCols <= Input_Capsense_sensorIndex)
            {
                ptrIdacMod = &ptrWdgt->rowIdacMod[0u];
            }
        #endif /* (Input_Capsense_CSD_MATRIX_WIDGET_EN  | Input_Capsense_CSD_TOUCHPAD_WIDGET_EN) */

        interruptState = CyEnterCriticalSection();

        /* Get Idac Value */
        newRegValue = CY_GET_REG32(Input_Capsense_IDAC_PTR);

        /* Clear Idac value and gain */
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
            newRegValue &= ~(Input_Capsense_IDAC_MOD_MASK | Input_Capsense_IDAC_COMP_MASK |
                Input_Capsense_IDAC_GAIN_MASK | (Input_Capsense_IDAC_GAIN_MASK << Input_Capsense_IDAC_COMP_DATA_OFFSET));
        #else
            newRegValue &= ~(Input_Capsense_IDAC_MOD_MASK | Input_Capsense_IDAC_GAIN_MASK);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) */

        /* Set Idac value and gain */
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
            newRegValue |= (ptrIdacMod[Input_Capsense_scanFreqIndex] |
                           (uint32)((uint32)Input_Capsense_curRamSnsPtr->idacComp[Input_Capsense_scanFreqIndex] <<
                           Input_Capsense_IDAC_COMP_DATA_OFFSET));
            newRegValue |= idacGain;
            newRegValue |= (idacGain << Input_Capsense_IDAC_COMP_DATA_OFFSET);
        #else
            newRegValue |= ptrIdacMod[Input_Capsense_scanFreqIndex];
            newRegValue |= idacGain;
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) */
        CY_SET_REG32(Input_Capsense_IDAC_PTR, newRegValue);

        CyExitCriticalSection(interruptState);

    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
}


#if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
    /*******************************************************************************
    * Function Name: Input_Capsense_SsCSDGetNumberOfConversions
    ****************************************************************************//**
    *
    * \brief
    *  This function gets Number of conversions.
    *
    * \details
    *  This function gets Number of conversions using foll.owing equation:
    *   conversionsNum = (2^resolution - 1) / snsClkDivider.
    *
    * \param
    *  snsClkDivider The divider value for the sense clock.
    *  resolution The widget resolution.
    *  snsClkSrc The current Sense Clock Source.
    *
    * \return Returns the Number of conversions.
    *
    *******************************************************************************/
    uint32 Input_Capsense_SsCSDGetNumberOfConversions(uint32 snsClkDivider, uint32 resolution, uint32 snsClkSrc)
    {
        uint32 conversionsNum;
        #if ((Input_Capsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) && (Input_Capsense_ENABLE != Input_Capsense_CSDV2_REF9P6UA_EN))
            uint32 sampleClkFreqHz;
        #endif /* ((Input_Capsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) && (Input_Capsense_ENABLE != Input_Capsense_CSDV2_REF9P6UA_EN)) */

        /* Calculate scanning resolution value in register */
        conversionsNum = (uint32)(1uL << resolution);

        #if(Input_Capsense_ENABLE != Input_Capsense_CSDV2_REF9P6UA_EN)
            /* Apply correction to oveflow for 16 bit resolution */
            if (Input_Capsense_RES16BIT == resolution)
            {
                conversionsNum -= ((snsClkDivider + 1u) >> 1u);

                #if (Input_Capsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ)
                    sampleClkFreqHz = CYDEV_BCLK__HFCLK__HZ / (uint32)Input_Capsense_dsRam.modCsdClk;

                    if (sampleClkFreqHz <= Input_Capsense_MOD_CSD_CLK_12MHZ)
                    {
                        conversionsNum -= Input_Capsense_CONFIG_FILTER_DELAY_2_CYCLES;
                    }
                    else if (sampleClkFreqHz <= Input_Capsense_MOD_CSD_CLK_24MHZ)
                    {
                        conversionsNum -= Input_Capsense_CONFIG_FILTER_DELAY_3_CYCLES;
                    }
                    else
                    {
                        conversionsNum -= Input_Capsense_CONFIG_FILTER_DELAY_4_CYCLES;
                    }
                #else
                    conversionsNum -= Input_Capsense_CONFIG_FILTER_DELAY_2_CYCLES;
                #endif /* (INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) */
            }
        #else
            /* CY_ID285392: Apply correction to oveflow for 16 bit resolution */
            if (Input_Capsense_RES16BIT == resolution)
            {
                conversionsNum -= Input_Capsense_EXTRA_COUNTS_MAX;
            }
        #endif

        if (0u < snsClkDivider)
        {
            conversionsNum /= snsClkDivider;
        }

    #if((Input_Capsense_CLK_SOURCE_PRS8  == Input_Capsense_CSD_SNS_CLK_SOURCE) ||\
        (Input_Capsense_CLK_SOURCE_PRS12 == Input_Capsense_CSD_SNS_CLK_SOURCE) ||\
        (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE))
        switch (snsClkSrc)
        {
            case Input_Capsense_CLK_SOURCE_PRS8:
            case Input_Capsense_CLK_SOURCE_PRS12:
                /* Divide by 2 for PRS8/PRS12 mode */
                conversionsNum >>= 1u;
                break;

            default:
                break;
        }
    #else
        (void)snsClkSrc;
    #endif

    return((conversionsNum > 0uL) ? (conversionsNum) : 1uL);
    }
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */


/*******************************************************************************
* Function Name: Input_Capsense_SsCSDConfigClock
****************************************************************************//**
*
* \brief
*  This function configure sense clock for different modes.
*
* \details
*  Function sets the clock divider and configures the mode based on configuration.
*
*******************************************************************************/
void Input_Capsense_SsCSDConfigClock(void)
{
    uint32 snsClkDivider;
    uint32 snsClkSrc;
    uint32 newRegValue;

    Input_Capsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (Input_Capsense_RAM_WD_BASE_STRUCT *)
             Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2WdgtRam;

    /* Get sense divider based on configuration */
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN)
        snsClkDivider = (uint32)Input_Capsense_dsRam.snsCsdClk;
    #else
        #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
            /* Get SnsClck divider for rows or columns */
            if (Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].numCols <= Input_Capsense_sensorIndex)
            {
                snsClkDivider = (uint32)(ptrWdgt->rowSnsClk);
            }
            else
            {
                snsClkDivider = (uint32)(ptrWdgt->snsClk);
            }
        #else
            snsClkDivider = (uint32)(ptrWdgt->snsClk);
        #endif /* (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN) */
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN) */

    /* Get sense clk source calculated in Input_Capsense_SsCSDInitialize() before */
    #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
        /* Get SnsClc Source for rows or columns */
        if (Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].numCols <= Input_Capsense_sensorIndex)
        {
            snsClkSrc = (uint32)ptrWdgt->rowSnsClkSource;
        }
        else
        {
            snsClkSrc = (uint32)ptrWdgt->snsClkSource;
        }
    #else
        snsClkSrc = (uint32)ptrWdgt->snsClkSource;
    #endif /* (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN) */

    #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
        newRegValue = (snsClkSrc << CYFLD_CSD_LFSR_SIZE__OFFSET);

        /* Configuring PRS SEL_BIT */
        if ((Input_Capsense_CLK_SOURCE_PRS8 == snsClkSrc) ||
            (Input_Capsense_CLK_SOURCE_PRS12 == snsClkSrc))
        {
            newRegValue |= Input_Capsense_SENSE_PERIOD_SEL_LFSR_MSB_MASK;
        }
    #else
        newRegValue = snsClkSrc;
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */

    #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
        #if((Input_Capsense_CLK_SOURCE_PRS8  == Input_Capsense_CSD_SNS_CLK_SOURCE) ||\
            (Input_Capsense_CLK_SOURCE_PRS12 == Input_Capsense_CSD_SNS_CLK_SOURCE) ||\
            (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE))
            switch (snsClkSrc)
            {
            case Input_Capsense_CLK_SOURCE_PRS8:
            case Input_Capsense_CLK_SOURCE_PRS12:
                /* Divide by 2 for PRS8/PRS12 mode */
                snsClkDivider >>= 1;
                if (snsClkDivider == 0u)
                {
                    snsClkDivider = 1u;
                }
                break;

            default:
                break;
            }
        #endif /* ((Input_Capsense_CLK_SOURCE_PRS8  == Input_Capsense_CSD_SNS_CLK_SOURCE) ||\
                   (Input_Capsense_CLK_SOURCE_PRS12 == Input_Capsense_CSD_SNS_CLK_SOURCE) ||\
                   (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE)) */
    #endif
    Input_Capsense_SsCSDSetModeSnsClockDivider(newRegValue, snsClkDivider);
}


/*******************************************************************************
* Function Name: Input_Capsense_SsCSDCalculateScanDuration
****************************************************************************//**
*
* \brief
*   Calculates Scan Duration which is defined by scan resolution
*
* \details
*   For Fourth-generation HW block: The function calculates the number of conversions and updates
*   SEQ_NORM_CNT register. The number of conversions depends on resolution and
*   snsClk divider.
*   For Third-generation HW block: The function recalculate the resolution using following equation:
*   2^resolution - 1. The calculated value is contained in
*   Input_Capsense_counterResolution global variable and used in
*   Input_Capsense_SsCSDStartSample() function to trigger the scan process.
*
* \param wdgtIndex
*  ptrWdgt The pointer to the RAM_WD_BASE_STRUCT structure.
*
*******************************************************************************/
void Input_Capsense_SsCSDCalculateScanDuration(Input_Capsense_RAM_WD_BASE_STRUCT const *ptrWdgt)
{
    #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
        uint32 conversionsNum;
        uint32 snsClkDivider;

        /* Get Number Of Conversions */
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN)
            snsClkDivider = Input_Capsense_dsRam.snsCsdClk;
        #else
            #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
                /* Get SnsClck divider for rows or columns */
                if (Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].numCols <= Input_Capsense_sensorIndex)
                {
                    snsClkDivider = (uint32)(ptrWdgt->rowSnsClk);
                }
                else
                {
                    snsClkDivider = (uint32)(ptrWdgt->snsClk);
                }
            #else
                snsClkDivider = (uint32)(ptrWdgt->snsClk);
            #endif /* (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN) */
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN) */

        conversionsNum = Input_Capsense_SsCSDGetNumberOfConversions(snsClkDivider, (uint32)ptrWdgt->resolution, (uint32)ptrWdgt->snsClkSource);

        /* Set Number Of Conversions based on scanning resolution */
        CY_SET_REG32(Input_Capsense_SEQ_NORM_CNT_PTR, (conversionsNum & Input_Capsense_SEQ_NORM_CNT_CONV_CNT_MASK));
    #else
        /* Set up scanning resolution  */
        Input_Capsense_counterResolution = (uint32)((0x00000001Lu << ptrWdgt->resolution) - 1u) << Input_Capsense_RESOLUTION_OFFSET;
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
}


/*******************************************************************************
* Function Name: Input_Capsense_CSDSetupWidget
****************************************************************************//**
*
* \brief
*  Performs hardware and firmware initialization required for scanning sensors
*  in a specific widget using the CSD sensing method. This function requires using
*  the Input_Capsense_CSDScan() function to start scanning.
*
* \details
*  \note This function is obsolete and kept for backward compatibility only.
*  The Input_Capsense_SetupWidget() function should be used instead.
*
*  This function initializes the specific widget common parameters to perform
*  the CSD scanning. The initialization includes setting up a Modulator and
*  Sense clock frequency and scanning resolution.
*
*  This function does not connect any specific sensors to the scanning hardware,
*  neither does it start a scanning process. The Input_Capsense_CSDScan()
*  API must be called after initializing the widget to start scanning.
*
*  This function is called when no scanning is in progress. I.e.
*  Input_Capsense_IsBusy() returns a non-busy status.
*
*  This function is called by the Input_Capsense_SetupWidget() API if the
*  given widget uses the CSD sensing method.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*
* \param  widgetId
*  Specifies the ID number of the widget to perform hardware and firmware
*  initialization required for scanning sensors in the specific widget.
*  A macro for the widget ID can be found in the Input_Capsense Configuration header
*  file defined as Input_Capsense_<WidgetName>_WDGT_ID.
*
*******************************************************************************/
void Input_Capsense_CSDSetupWidget(uint32 widgetId)
{
    Input_Capsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (Input_Capsense_RAM_WD_BASE_STRUCT *)
                                                Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

    /* Save widget Id to have assess to it after scanning  */
    Input_Capsense_widgetIndex = (uint8)widgetId;

    Input_Capsense_SsSwitchSensingMode(Input_Capsense_SENSE_METHOD_CSD_E);

    #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
        /* Reset the frequency scan channel if enabled */
        Input_Capsense_scanFreqIndex = Input_Capsense_FREQ_CHANNEL_0;
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */

    /* Disconnect previous electrode if it has been connected */
    Input_Capsense_SsCSDElectrodeCheck();

    /* Initialize IO Sns electrode structure pointer to current widget */
    Input_Capsense_curSnsIOPtr = (Input_Capsense_FLASH_IO_STRUCT const *)
                                    Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2SnsFlash;

    /* Update status register in Data structure */
    Input_Capsense_dsRam.status &= ~Input_Capsense_STATUS_WDGT0_MASK;
    Input_Capsense_dsRam.status |= Input_Capsense_widgetIndex;

    Input_Capsense_SsCSDCalculateScanDuration(ptrWdgt);
    #if (((Input_Capsense_DISABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN) || \
          (Input_Capsense_CLK_SOURCE_DIRECT != Input_Capsense_CSD_SNS_CLK_SOURCE)) && \
         ((!(Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)) || \
          (Input_Capsense_ENABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN)))
        Input_Capsense_SsCSDConfigClock();
    #endif
}


/*******************************************************************************
* Function Name: Input_Capsense_CSDSetupWidgetExt
****************************************************************************//**
*
* \brief
*  Performs extended initialization for the CSD widget and also performs
*  initialization required for a specific sensor in the widget. This function
*  requires using the Input_Capsense_CSDScanExt() function to initiate a scan.
*
* \details
*  Performs extended initialization for the CSD widget and also performs
*  initialization required for a specific sensor in the widget. This function
*  requires using the Input_Capsense_CSDScanExt() function to initiate a scan.
*
*  \note This function is obsolete and kept for backward compatibility only.
*  The Input_Capsense_SetupWidgetExt() function should be used instead.
*
*  This function does the same as Input_Capsense_CSDSetupWidget() and also
*  does the following tasks:
*    1. Connects the first sensor of the widget.
*    2. Configures the IDAC value.
*    3. Initializes an interrupt callback function to initialize a scan of the
*  next sensors in a widget.
*
*  Once this function is called to initialize a widget and a sensor, the
*  Input_Capsense_CSDScanExt() function is called to scan the sensor.
*
*  This function is called when no scanning is in progress. I.e.
*  Input_Capsense_IsBusy() returns a non-busy status.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*
* \param widgetId
*  Specifies the ID number of the widget to perform hardware and firmware
*  initialization required for scanning the specific sensor in the specific
*  widget.
*  A macro for the widget ID can be found in the Input_Capsense Configuration header
*  file defined as Input_Capsense_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specifies the ID number of the sensor within the widget to perform hardware
*  and firmware initialization required for scanning a specific sensor in a
*  specific widget.
*  A macro for the sensor ID within a specified widget can be found in the
*  Input_Capsense Configuration header file defined as
*  Input_Capsense_<WidgetName>_SNS<SensorNumber>_ID
*
*******************************************************************************/
void Input_Capsense_CSDSetupWidgetExt(uint32 widgetId, uint32 sensorId)
{
    Input_Capsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (Input_Capsense_RAM_WD_BASE_STRUCT *)
                                                    Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

    /* Save widget and sensor Ids to have access to it after scanning  */
    Input_Capsense_sensorIndex = (uint8)sensorId;

    /* Update global pointer to Input_Capsense_RAM_SNS_STRUCT to current sensor  */
    Input_Capsense_curRamSnsPtr = (Input_Capsense_RAM_SNS_STRUCT *)
                                              Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2SnsRam
                                              + Input_Capsense_sensorIndex;

    Input_Capsense_CSDSetupWidget(widgetId);

     /* Setup Idac Value */
    Input_Capsense_SsCSDSetUpIdacs(ptrWdgt);

    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
        /* initialize access pointers for current pointer to widget configuration in Flash */
        Input_Capsense_curFlashWdgtPtr = &Input_Capsense_dsFlash.wdgtArray[widgetId];
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)  */

    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
        Input_Capsense_SsCSDConnectSensorExt(widgetId, sensorId);
    #else
        /* Enable sensor */
        Input_Capsense_curSnsIOPtr += Input_Capsense_sensorIndex;
        Input_Capsense_CSDConnectSns(Input_Capsense_curSnsIOPtr);
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)  */

    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
        /* Save sns pointer */
        Input_Capsense_curFlashSnsPtr = (Input_Capsense_FLASH_SNS_STRUCT const *)
                                           Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2SnsFlash +
                                           Input_Capsense_sensorIndex;
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN) */

    Input_Capsense_eleCsdDisconnectFlag = Input_Capsense_DISCONNECT_IO_FLAG;

    /* Setup ISR handler to single-sensor scan function */
    Input_Capsense_ISR_StartEx(&Input_Capsense_CSDPostSingleScan);
}

/*******************************************************************************
* Function Name: Input_Capsense_SsCSDStartSample
****************************************************************************//**
*
* \brief
*   Starts the CSD conversion.
*
* \details
*   This function assumes that the CSD block is already set up using
*   the Input_Capsense_CSDSetupWidget API and the sensor port-pin is connected to the CSD
*   block using Input_Capsense_CSDConnectSns.
*   For Third-generation HW block the function performs the following tasks:
*   1. Disconnects the Vref buffer from AMUX;
*   2. Precharges Cmod;
*   3. Makes the PreSettling delay to have a stable Vref voltage;
*   4. Sets the resolution to the Counter register to start scanning.
*
*******************************************************************************/
void Input_Capsense_SsCSDStartSample(void)
{
    #if (Input_Capsense_ENABLE != Input_Capsense_CSDV2)
        uint8 interruptState;
    #endif

    #ifdef Input_Capsense_START_SAMPLE_CALLBACK
        Input_Capsense_StartSampleCallback(Input_Capsense_widgetIndex, Input_Capsense_sensorIndex);
    #endif /* Input_Capsense_START_SAMPLE_CALLBACK */

    #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
        /* Fourth-generation HW block section */

        /* Disable CSD interrupt to prevent it during coarse initialization */
        CyIntDisable(Input_Capsense_ISR_NUMBER);

        /* Enable power to sub-blocks */
        CY_SET_REG32(Input_Capsense_HSCMP_PTR, Input_Capsense_HSCMP_INIT_MASK);

        #if (Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN)
            CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd |
                                                      Input_Capsense_CONFIG_SENSE_EN_MASK |
                                                      Input_Capsense_CONFIG_ENABLE_MASK);
            #if(Input_Capsense_CSD_ANALOG_STARTUP_DELAY_US > 0uL)
                CyDelayUs(Input_Capsense_CSD_ANALOG_STARTUP_DELAY_US);
            #endif /* (Input_Capsense_CSD_ANALOG_STARTUP_DELAY_US > 0uL) */
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN) */

        /* Precharging Cmod and Csh */
        Input_Capsense_SsCSDCmodPrecharge();

        /* Trigger Scan */
        Input_Capsense_SsCSDTriggerScan();

    #else
        /* Third-generation HW block section */
        interruptState = CyEnterCriticalSection();

        /* Enable CSD block. Disconnect Vref Buffer from AMUX */
        #if ((Input_Capsense_CSH_PRECHARGE_IO_BUF == Input_Capsense_CSD_CSH_PRECHARGE_SRC) &&\
             (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN))
            CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CMOD_PRECHARGE_CONFIG_CSD_EN);
        #else
            CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CTANK_PRECHARGE_CONFIG_CSD_EN);
        #endif

        /* Restart the clocks. Scan one cycle to reset the flip-flop for Direct clock mode */
        Input_Capsense_SsCSDClockRestart();

        /* Precharging Cmod to Vref */
        Input_Capsense_SsCSDCmodPrecharge();

        #if (Input_Capsense_CLK_SOURCE_DIRECT != Input_Capsense_CSD_SNS_CLK_SOURCE)
            /* Set PreSettling delay to skip IDAC glitch before scanning */
            CyDelayCycles(Input_Capsense_GLITCH_ELIMINATION_CYCLES);
        #endif /* (Input_Capsense_CSD_SNS_CLK_SOURCE != Input_Capsense_CLK_SOURCE_DIRECT) */

        /* Trigger Scan */
        Input_Capsense_SsCSDTriggerScan();

        CyExitCriticalSection(interruptState);
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
}


/*******************************************************************************
* Function Name: Input_Capsense_CSDScanExt
****************************************************************************//**
*
* \brief
*  Starts the CSD conversion on the preconfigured sensor. This function requires
*  using the Input_Capsense_CSDSetupWidgetExt() function to set up the a
*  widget.
*
* \details
*  Starts the CSD conversion on the preconfigured sensor. This function requires
*  using the Input_Capsense_CSDSetupWidgetExt() function to set up the a
*  widget.
*
*  \note This function is obsolete and kept for backward compatibility only.
*  The Input_Capsense_ScanExt() function should be used instead.
*
*  This function performs single scanning of one sensor in the widget configured
*  by the Input_Capsense_CSDSetupWidgetExt() function. It does the following
*  tasks:
*    1. Sets the busy flag in the Input_Capsense_dsRam structure.
*    2. Performs the clock-phase alignment of the sense and modulator clocks.
*    3. Performs the Cmod pre-charging.
*    4. Starts single scanning.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*  This function is called when no scanning is in progress. I.e.
*  Input_Capsense_IsBusy() returns a non-busy status.
*
*  The sensor must be preconfigured by using the
*  Input_Capsense_CSDSetupWidgetExt() API prior to calling this function.
*  The sensor remains ready for a next scan if a previous scan was triggered
*  by using the Input_Capsense_CSDScanExt() function. In this case, calling
*  Input_Capsense_CSDSetupWidgetExt() is not required every time before the
*  Input_Capsense_CSDScanExt() function. If a previous scan was triggered in
*  any other way - Input_Capsense_Scan(), Input_Capsense_ScanAllWidgets() or
*  Input_Capsense_RunTuner() - (see the Input_Capsense_RunTuner() function
*  description for more details), the sensor must be preconfigured again by
*  using the Input_Capsense_CSDSetupWidgetExt() API prior to calling the
*  Input_Capsense_CSDScanExt() function.
*
*  If disconnection of the sensors is required after calling
*  Input_Capsense_CSDScanExt(), the Input_Capsense_CSDDisconnectSns()
*  function can be used.
*
*******************************************************************************/
void Input_Capsense_CSDScanExt(void)
{
    #if ((Input_Capsense_DISABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN) && \
         (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN))
        Input_Capsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (Input_Capsense_RAM_WD_BASE_STRUCT *)
                                                        Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2WdgtRam;

        Input_Capsense_SsCSDCalculateScanDuration(ptrWdgt);
        Input_Capsense_SsCSDConfigClock();
    #endif

    /* Set Start of sensor scan flag */
    Input_Capsense_dsRam.status |= (Input_Capsense_SW_STS_BUSY | Input_Capsense_WDGT_SW_STS_BUSY);

    #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
        /* Reset the frequency scan channel if enabled */
        Input_Capsense_scanFreqIndex = Input_Capsense_FREQ_CHANNEL_0;
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */

    #if (Input_Capsense_ENABLE != Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN) &&\
        (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
        #if(Input_Capsense_CSD_ANALOG_STARTUP_DELAY_US > 0uL)
            CyDelayUs(Input_Capsense_CSD_ANALOG_STARTUP_DELAY_US);
        #endif /* (Input_Capsense_CSD_ANALOG_STARTUP_DELAY_US > 0uL) */
    #endif /* (Input_Capsense_ENABLE != Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN) &&\
              (Input_Capsense_ENABLE == Input_Capsense_CSDV2)*/

    Input_Capsense_SsCSDStartSample();
}


/*******************************************************************************
* Function Name: Input_Capsense_CSDScan
****************************************************************************//**
*
* \brief
*  This function initiates a scan for the sensors of the widget initialized by the
*  Input_Capsense_CSDSetupWidget() function.
*
* \details
*  This function initiates a scan for the sensors of the widget initialized by the
*  Input_Capsense_CSDSetupWidget() function.
*
*  \note This function is obsolete and kept for backward compatibility only.
*  The Input_Capsense_Scan() function should be used instead.
*
*  This function performs scanning of all the sensors in the widget configured by
*  the Input_Capsense_CSDSetupWidget() function. It does the following tasks:
*    1. Connects the first sensor of the widget.
*    2. Configures the IDAC value.
*    3. Initializes the interrupt callback function to initialize a scan of
*       the next sensors in a widget.
*    4. Starts scanning for the first sensor in the widget.
*
*  This function is called by the Input_Capsense_Scan() API if the given
*  widget uses the CSD sensing method.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*
*  This function is called when no scanning is in progress. I.e.
*  Input_Capsense_IsBusy() returns a non-busy status. The widget must be
*  preconfigured by the Input_Capsense_CSDSetupWidget() function if any other
*  widget was previously scanned or any other type of the scan functions was used.
*
*******************************************************************************/
void Input_Capsense_CSDScan(void)
{
    Input_Capsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (Input_Capsense_RAM_WD_BASE_STRUCT *)
                                                    Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2WdgtRam;

    /* Set all the sensors to inactive state */
    if(Input_Capsense_dsRam.scanCurrentISC != Input_Capsense_dsRam.scanCsdISC)
    {
        Input_Capsense_SsSetAllIOsState((uint32)Input_Capsense_dsRam.scanCsdISC);
        Input_Capsense_dsRam.scanCurrentISC = Input_Capsense_dsRam.scanCsdISC;
    }

     /*
      * Update Input_Capsense_sensorIndex with the first sensor in
      * widget to use it in ISR handler to configure the next sensor
      */
    Input_Capsense_sensorIndex = 0u;

    /* Update global pointer to Input_Capsense_RAM_SNS_STRUCT to current sensor  */
    Input_Capsense_curRamSnsPtr = (Input_Capsense_RAM_SNS_STRUCT *)
                                              Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2SnsRam
                                              + Input_Capsense_sensorIndex;

    #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
        /* Reset the frequency scan channel if enabled */
        Input_Capsense_scanFreqIndex = Input_Capsense_FREQ_CHANNEL_0;
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */

    /* Setup Idac Value */
   Input_Capsense_SsCSDSetUpIdacs(ptrWdgt);

    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
        /* Check ganged sns flag  */
        if (Input_Capsense_GANGED_SNS_MASK == (Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].staticConfig &
            Input_Capsense_GANGED_SNS_MASK))
        {
            /* Setup ISR handler to multiple-sensor scan function with ganged sensors */
            Input_Capsense_ISR_StartEx(&Input_Capsense_CSDPostMultiScanGanged);
        }
        else
        {
            /* Set up ISR handler to multiple-sensor scan function without ganged sensors */
            Input_Capsense_ISR_StartEx(&Input_Capsense_CSDPostMultiScan);
        }

        Input_Capsense_SsCSDConnectSensorExt((uint32)Input_Capsense_widgetIndex, (uint32)Input_Capsense_sensorIndex);
    #else
        /* initialize ptr to sensor IO structure to appropriate address */
        Input_Capsense_curSnsIOPtr = (Input_Capsense_FLASH_IO_STRUCT const *)
                                        Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2SnsFlash
                                        + Input_Capsense_sensorIndex;

        /* Enable sensor */
        Input_Capsense_CSDConnectSns(Input_Capsense_curSnsIOPtr);

        /* Set-up ISR handler to multiple-sensor scan function without ganged sensors */
        Input_Capsense_ISR_StartEx(&Input_Capsense_CSDPostMultiScan);
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)  */

    /* Start scanning */
    Input_Capsense_CSDScanExt();
}


/*******************************************************************************
* Function Name: Input_Capsense_SsCSDConnectSensorExt
****************************************************************************//**
*
* \brief
*  Connects a ganged sensor port-pin to the sensing HW block via the AMUX bus.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and
*   masks from the FLASH_IO_STRUCT object. Basing on this data, it updates the HSIOM and
*   PC registers.
*
* \param widgetId
*  Specifies ID of the widget.
*
* \param sensorId
*  Specifies ID of the sensor in the widget.
*
*******************************************************************************/
void Input_Capsense_SsCSDConnectSensorExt(uint32 widgetId, uint32 sensorId)
{
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
        uint32 tempVal;
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN) */

    /* initialize ptr to sensor IO structure to appropriate address */
    Input_Capsense_curSnsIOPtr = (Input_Capsense_FLASH_IO_STRUCT const *)
                                                      Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2SnsFlash
                                                      + sensorId;

    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
        /* Check ganged sns flag  */
        if (Input_Capsense_GANGED_SNS_MASK ==
           (Input_Capsense_dsFlash.wdgtArray[widgetId].staticConfig &
            Input_Capsense_GANGED_SNS_MASK))
        {
            /* Get sns pointer */
            Input_Capsense_curFlashSnsPtr = (Input_Capsense_FLASH_SNS_STRUCT const *)
                                               Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2SnsFlash +
                                               sensorId;

            /* Get number of ganged pins */
            tempVal = Input_Capsense_curFlashSnsPtr->numPins;

            /* Get IO pointer  */
            Input_Capsense_curSnsIOPtr = &Input_Capsense_ioList[Input_Capsense_curFlashSnsPtr->firstPinId];

            /* Connect all ganged sensors  */
            do
            {
                Input_Capsense_CSDConnectSns(Input_Capsense_curSnsIOPtr);
                Input_Capsense_curSnsIOPtr++;
                tempVal--;
            } while (0u != tempVal);
        }
        else
        {
            /* Connect sensor */
            Input_Capsense_CSDConnectSns(Input_Capsense_curSnsIOPtr);
        }
    #else
        /* Connect sensor */
        Input_Capsense_CSDConnectSns(Input_Capsense_curSnsIOPtr);
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN) */
}


/*******************************************************************************
* Function Name: Input_Capsense_SsCSDDisconnectSnsExt
****************************************************************************//**
*
* \brief
*  Disconnects a ganged sensor port-pin from the sensing HW block and AMUX bus.
*  Sets the default state of the un-scanned sensor.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and
*   masks from the FLASH_IO_STRUCT object. Basing on this data and Inactive sensor
*   connection parameter, it updates the HSIOM, PC and DR registers.
*   The HSIOM register is updated only when the Inactive sensor connection parameter
*   is set to Shield.
*
* \param widgetId
*  Specifies ID of the widget.
*
* \param sensorId
*  Specifies ID of the sensor in the widget.
*
*******************************************************************************/
void Input_Capsense_SsCSDDisconnectSnsExt(uint32 widgetId, uint32 sensorId)
{
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
        uint32 tempVal;
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN) */

    /* initialize ptr to sensor IO structure to appropriate address        */
    Input_Capsense_curSnsIOPtr = (Input_Capsense_FLASH_IO_STRUCT const *)
                                                      Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2SnsFlash
                                                      + sensorId;

    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
        /* Check ganged sns flag  */
        if ((Input_Capsense_dsFlash.wdgtArray[widgetId].staticConfig &
            Input_Capsense_GANGED_SNS_MASK) == Input_Capsense_GANGED_SNS_MASK)
        {
            /* Get sns pointer */
            Input_Capsense_curFlashSnsPtr = (Input_Capsense_FLASH_SNS_STRUCT const *)
                                               Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2SnsFlash +
                                               sensorId;

            /* Get number of ganged pins */
            tempVal = Input_Capsense_curFlashSnsPtr->numPins;

            /* Get IO pointer  */
            Input_Capsense_curSnsIOPtr = &Input_Capsense_ioList[Input_Capsense_curFlashSnsPtr->firstPinId];

            /* Disconnect all ganged sensors */
            do
            {
                Input_Capsense_CSDDisconnectSns(Input_Capsense_curSnsIOPtr);
                Input_Capsense_curSnsIOPtr++;
                tempVal--;
            } while (0u != tempVal);
        }
        else
        {
            /* Disconnect ganged sensor */
            Input_Capsense_CSDDisconnectSns(Input_Capsense_curSnsIOPtr);
        }
    #else
        /* Disconnect ganged sensor */
        Input_Capsense_CSDDisconnectSns(Input_Capsense_curSnsIOPtr);
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN) */
}


/*******************************************************************************
* Function Name: Input_Capsense_CSDConnectSns
****************************************************************************//**
*
* \brief
*  Connects a port pin used by the sensor to the AMUX bus of the sensing HW block.
*
* \details
*  Connects a port pin used by the sensor to the AMUX bus of the sensing HW block
*  while a sensor is being scanned. The function ignores the fact if
*  the sensor is a ganged sensor and connects only a specified pin.
*
*  Scanning should be completed before calling this API.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases. Functions that perform a setup and scan of a sensor/widget,
*  automatically set the required pin states and perform the sensor connection.
*  They do not take into account changes in the design made by the
*  Input_Capsense_CSDConnectSns() function.
*
* \param  snsAddrPtr
*  Specifies the pointer to the FLASH_IO_STRUCT object belonging to a sensor
*  which to be connected to the sensing HW block.
*
*******************************************************************************/
void Input_Capsense_CSDConnectSns(Input_Capsense_FLASH_IO_STRUCT const *snsAddrPtr)
{
    uint32 newRegisterValue;
    uint8  interruptState;
    uint32 pinModeShift;
    uint32 pinHSIOMShift;

    /* Get offsets for sensor */
    pinModeShift = (uint32)snsAddrPtr->shift;
    pinHSIOMShift = (uint32)snsAddrPtr->hsiomShift;

    interruptState = CyEnterCriticalSection();

    /* Use temporary variable to update registers without multiple writings to them */
    newRegisterValue = CY_GET_REG32(snsAddrPtr->hsiomPtr);
    newRegisterValue &= ~(Input_Capsense_HSIOM_SEL_MASK << pinHSIOMShift);
    newRegisterValue |= (uint32)((uint32)Input_Capsense_HSIOM_SEL_CSD_SENSE << pinHSIOMShift);

    /* Update port configuration register (drive mode) for sensor */
    CY_SET_REG32(snsAddrPtr->pcPtr, CY_GET_REG32(snsAddrPtr->pcPtr) & (uint32)~((uint32)Input_Capsense_GPIO_PC_MASK << pinModeShift));

    /* Update HSIOM register for sensor */
    CY_SET_REG32(snsAddrPtr->hsiomPtr, newRegisterValue);

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Input_Capsense_CSDDisconnectSns
****************************************************************************//**
*
* \brief
*  Disconnects a sensor port pin from the sensing HW block and the AMUX bus. Sets
*  the default state of the un-scanned sensor.
*
* \details
*  This function works identically to Input_Capsense_CSDConnectSns() except
*  it disconnects the specified port-pin used by the sensor.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases. Functions that perform a setup and scan of sensor/widget
*  automatically set the required pin states and perform the sensor connection.
*  They ignore changes in the design made by the
*  Input_Capsense_CSDDisconnectSns() function.
*
* \param  snsAddrPtr
*  Specifies the pointer to the FLASH_IO_STRUCT object belonging to a sensor
*  which should be disconnected from the sensing HW block.
*
*******************************************************************************/
void Input_Capsense_CSDDisconnectSns(Input_Capsense_FLASH_IO_STRUCT const *snsAddrPtr)
{
    uint8  interruptState;
    uint32 pinHSIOMShift;
    uint32 pinModeShift;
    uint32 newPcRegValue;
    uint32 newHsiomRegValue;

    pinHSIOMShift = (uint32)snsAddrPtr->hsiomShift;
    pinModeShift = (uint32)snsAddrPtr->shift;

    interruptState = CyEnterCriticalSection();

    newPcRegValue  = CY_GET_REG32(snsAddrPtr->pcPtr);
    newPcRegValue &= ~(Input_Capsense_GPIO_PC_MASK << pinModeShift);

    newHsiomRegValue  = CY_GET_REG32(snsAddrPtr->hsiomPtr);
    newHsiomRegValue &= ~(Input_Capsense_HSIOM_SEL_MASK << pinHSIOMShift);
    CY_SET_REG32(snsAddrPtr->hsiomPtr, newHsiomRegValue);

    if(Input_Capsense_SNS_CONNECTION_GROUND == Input_Capsense_dsRam.scanCurrentISC)
    {
        newPcRegValue |= (CY_SYS_PINS_DM_STRONG << pinModeShift);
        CY_SET_REG32(snsAddrPtr->pcPtr, newPcRegValue);
    }
    else
    {
        newPcRegValue |= (CY_SYS_PINS_DM_ALG_HIZ << pinModeShift);
        if(Input_Capsense_SNS_CONNECTION_SHIELD == Input_Capsense_dsRam.scanCurrentISC)
        {
            /* Connect to Shield */
            newHsiomRegValue |= (Input_Capsense_HSIOM_SEL_CSD_SHIELD << pinHSIOMShift);
            CY_SET_REG32(snsAddrPtr->pcPtr, newPcRegValue);
            CY_SET_REG32(snsAddrPtr->hsiomPtr, newHsiomRegValue);
        }
    }
    /* Set logic 0 to port data register */
    CY_SET_REG32(snsAddrPtr->drPtr, CY_GET_REG32(snsAddrPtr->drPtr) & (uint32)~(uint32)((uint32)1u << snsAddrPtr->drShift));

    CyExitCriticalSection(interruptState);
}

#if ((Input_Capsense_CSD_SS_DIS != Input_Capsense_CSD_AUTOTUNE) || \
     (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTOCAL_EN))
    /*******************************************************************************
    * Function Name: Input_Capsense_SsCSDCalibrateCheck
    ****************************************************************************//**
    *
    * \brief
    *  This internal function checks if the calibration is performed successfully.
    *
    * \details
    *  The function verifies that raw counts are within acceptable range
    *  defined by target and calibration error parameters.
    *
    * \param widgetId
    *  The desired widget ID.
    *
    * \param target
    *  Raw count target in percentage.
    *
    * \return Returns the status of the operation:
    *   - Zero     - All the sensors in the widget are calibrated successfully.
    *   - Non-Zero - Calibration failed for any sensor in the widget.
    *
    *******************************************************************************/
    static cystatus Input_Capsense_SsCSDCalibrateCheck(uint32 widgetId, uint32 target)
    {
        cystatus calibrateStatus = CYRET_SUCCESS;
        uint32 rawcount;
        uint32 snsIndex;
        uint32 freqChannel;
        uint32 upperLimit;
        uint32 lowerLimit;

        Input_Capsense_FLASH_WD_STRUCT const *ptrFlashWidget = &Input_Capsense_dsFlash.wdgtArray[widgetId];
        Input_Capsense_RAM_WD_BASE_STRUCT *ptrRamWidget = (Input_Capsense_RAM_WD_BASE_STRUCT *)ptrFlashWidget->ptr2WdgtRam;
        Input_Capsense_RAM_SNS_STRUCT *ptrRamSensor = ptrFlashWidget->ptr2SnsRam;

        /* Calculate acceptable raw count range based on the resolution, target and error */
        rawcount = (0x00000001Lu << ptrRamWidget->resolution) - 1u;
        lowerLimit = 0u;
        if (target > Input_Capsense_CSD_CALIBRATION_ERROR)
        {
            lowerLimit = target - Input_Capsense_CSD_CALIBRATION_ERROR;
        }
        upperLimit = target + Input_Capsense_CSD_CALIBRATION_ERROR;
        if (upperLimit > Input_Capsense_PERCENTAGE_100)
        {
            upperLimit = Input_Capsense_PERCENTAGE_100;
        }
        lowerLimit = (rawcount * lowerLimit) / Input_Capsense_PERCENTAGE_100;
        upperLimit = (rawcount * upperLimit) / Input_Capsense_PERCENTAGE_100;

        /* Check if raw count is in the defined range */
        for(snsIndex = 0u; snsIndex < ptrFlashWidget->totalNumSns; snsIndex++)
        {
            for(freqChannel = Input_Capsense_NUM_SCAN_FREQS; freqChannel-- > 0u;)
            {
                rawcount = ptrRamSensor->raw[freqChannel];
                if ((rawcount < lowerLimit) || (rawcount > upperLimit))
                {
                    calibrateStatus = CYRET_BAD_DATA;
                    break;
                }
            }
            ptrRamSensor++;
        }
        return (calibrateStatus);
    }


    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTO_GAIN_EN)
        /*******************************************************************************
        * Function Name: Input_Capsense_SsCSDSwitchIdacGain
        ****************************************************************************//**
        *
        * \brief
        *  This internal function switches to the lower IDAC gain is possible.
        *
        * \details
        *  This internal function switches to the lower IDAC gain is possible.
        *  Conditions of switching to the lower IDAC gains:
        *  1. The current IDAC gain is not the lowest one.
        *  2. The maximum IDAC at gain switching will not be out of range.
        *  3. The minimum IDAC is still below the acceptable range.
        *
        * \param ptrFlashWidget
        *  Specifies the pointer to a widget.
        *
        * \return Returns the status of the operation:
        *   - Zero     - Gain switching is not needed.
        *   - Non-Zero - Gain was switched to the lower one.
        *
        *******************************************************************************/
        static uint32 Input_Capsense_SsCSDSwitchIdacGain(Input_Capsense_FLASH_WD_STRUCT const *ptrFlashWidget)
        {
            uint32 ratio;
            uint32 maxIdac;
            uint32 minIdac;
            uint32 status = 0u;
            uint32 freqChannel;
            uint32 gainIndex;

            Input_Capsense_RAM_WD_BASE_STRUCT *ptrRamWidget = (Input_Capsense_RAM_WD_BASE_STRUCT *)ptrFlashWidget->ptr2WdgtRam;
            #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
                uint32 snsIndex;
                Input_Capsense_RAM_SNS_STRUCT *ptrRamSensor = ptrFlashWidget->ptr2SnsRam;
            #endif

            gainIndex = ptrRamWidget->idacGainIndex;

            /* Find maximum and minimum IDACs */
            maxIdac = 0u;
            minIdac = Input_Capsense_CSD_CAL_IDAC_MAX_VALUE;
            for(freqChannel = Input_Capsense_NUM_SCAN_FREQS; freqChannel-- > 0u;)
            {
                if (maxIdac < ptrRamWidget->idacMod[freqChannel])
                {
                    maxIdac = ptrRamWidget->idacMod[freqChannel];
                }
                if (minIdac > ptrRamWidget->idacMod[freqChannel])
                {
                    minIdac = ptrRamWidget->idacMod[freqChannel];
                }
                #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
                    if ((Input_Capsense_WD_TOUCHPAD_E == Input_Capsense_GET_WIDGET_TYPE(ptrFlashWidget)) ||
                        (Input_Capsense_WD_MATRIX_BUTTON_E == Input_Capsense_GET_WIDGET_TYPE(ptrFlashWidget)))
                    {
                        if (maxIdac < ptrRamWidget->rowIdacMod[freqChannel])
                        {
                            maxIdac = ptrRamWidget->rowIdacMod[freqChannel];
                        }
                        if (minIdac > ptrRamWidget->rowIdacMod[freqChannel])
                        {
                            minIdac = ptrRamWidget->rowIdacMod[freqChannel];
                        }
                    }
                #endif
            }
            #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
                for(snsIndex = 0u; snsIndex < ptrFlashWidget->totalNumSns; snsIndex++)
                {
                    for(freqChannel = Input_Capsense_NUM_SCAN_FREQS; freqChannel-- > 0u;)
                    {
                        if (minIdac > ptrRamSensor->idacComp[freqChannel])
                        {
                            minIdac = ptrRamSensor->idacComp[freqChannel];
                        }
                    }
                    ptrRamSensor++;
                }
            #endif

            /* Check gain switch conditions */
            if (gainIndex != 0u)
            {
                if (minIdac < Input_Capsense_CSD_IDAC_MIN)
                {
                    ratio = Input_Capsense_idacGainTable[gainIndex].gainValue /
                            Input_Capsense_idacGainTable[gainIndex - 1u].gainValue;
                    if ((maxIdac * ratio) < Input_Capsense_CSD_CAL_IDAC_MAX_VALUE)
                    {
                        /* Switch to lower idac gain */
                        ptrRamWidget->idacGainIndex--;
                        status = 1u;
                    }
                }
            }

            return (status);
        }
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTO_GAIN_EN) */


    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
        /*******************************************************************************
        * Function Name: Input_Capsense_SsCSDNormalizeIdac
        ****************************************************************************//**
        *
        * \brief
        *  This function normalizes compensation IDAC.
        *
        * \details
        *  This function normalizes compensation IDAC.
        *
        * \param ptrFlashWidget
        *  Specifies the pointer to a widget.
        *
        * \param target
        *  Raw count target in percentage.
        *
        *******************************************************************************/
        static void Input_Capsense_SsCSDNormalizeIdac(Input_Capsense_FLASH_WD_STRUCT const *ptrFlashWidget, uint32 target)
        {
            uint32 snsIndex;
            uint32 freqChannel;
            uint32 maxIdac;
            uint32 minIdac;
            uint32 minRaw;
            uint32 maxRawLevel;
            uint32 rawLevel;
            uint32 iMod;

            Input_Capsense_RAM_WD_BASE_STRUCT *ptrRamWidget = (Input_Capsense_RAM_WD_BASE_STRUCT *)ptrFlashWidget->ptr2WdgtRam;
            Input_Capsense_RAM_SNS_STRUCT *ptrRamSensor;

            /* Calculate raw count level based on resolution and target */
            maxRawLevel = (0x00000001Lu << ptrRamWidget->resolution) - 1u;

            /*
            * IDAC Normalization is performed separately for each multi-frequency channel
            * and separately for row and column
            */
            for(freqChannel = Input_Capsense_NUM_SCAN_FREQS; freqChannel-- > 0u;)
            {
                /* Find maximum and minimum IDACs */
                maxIdac = ptrRamWidget->idacMod[freqChannel];
                minIdac = ptrRamWidget->idacMod[freqChannel];
                ptrRamSensor = ptrFlashWidget->ptr2SnsRam;
                minRaw = ptrRamSensor->raw[freqChannel];
                for(snsIndex = 0u; snsIndex < ptrFlashWidget->numCols; snsIndex++)
                {
                    if (minIdac > ptrRamSensor->idacComp[freqChannel])
                    {
                        minIdac = ptrRamSensor->idacComp[freqChannel];
                        minRaw = ptrRamSensor->raw[freqChannel];
                    }
                    ptrRamSensor++;
                }

                /* Define new modulator IDAC */
                rawLevel = ((minRaw * Input_Capsense_PERCENTAGE_100) / maxRawLevel) + Input_Capsense_PERCENTAGE_100;
                iMod = (rawLevel * minIdac) / target;

                if (iMod > maxIdac)
                {
                    iMod = maxIdac;
                }
                ptrRamWidget->idacMod[freqChannel] = (uint8)iMod;

                /* Re-calculate compensation IDAC */
                ptrRamSensor = ptrFlashWidget->ptr2SnsRam;
                for(snsIndex = 0u; snsIndex < ptrFlashWidget->numCols; snsIndex++)
                {
                    rawLevel = (((ptrRamSensor->raw[freqChannel] * Input_Capsense_PERCENTAGE_100) / maxRawLevel) +
                        Input_Capsense_PERCENTAGE_100) * ptrRamSensor->idacComp[freqChannel];
                    if (rawLevel < (iMod * target))
                    {
                        ptrRamSensor->idacComp[freqChannel] = 0u;
                    }
                    else
                    {
                        ptrRamSensor->idacComp[freqChannel] = (uint8)(((rawLevel - (iMod * target)) +
                            (Input_Capsense_PERCENTAGE_100 >> 1u)) / Input_Capsense_PERCENTAGE_100);
                    }
                    ptrRamSensor++;
                }

                #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
                    if ((Input_Capsense_WD_TOUCHPAD_E == Input_Capsense_GET_WIDGET_TYPE(ptrFlashWidget)) ||
                        (Input_Capsense_WD_MATRIX_BUTTON_E == Input_Capsense_GET_WIDGET_TYPE(ptrFlashWidget)))
                    {
                        /* Find maximum and minimum IDACs */
                        maxIdac = ptrRamWidget->rowIdacMod[freqChannel];
                        minIdac = ptrRamWidget->rowIdacMod[freqChannel];
                        ptrRamSensor = &(ptrFlashWidget->ptr2SnsRam[ptrFlashWidget->numCols]);
                        minRaw = ptrRamSensor->raw[freqChannel];
                        for(snsIndex = ptrFlashWidget->numCols; snsIndex < ptrFlashWidget->totalNumSns; snsIndex++)
                        {
                            if (minIdac > ptrRamSensor->idacComp[freqChannel])
                            {
                                minIdac = ptrRamSensor->idacComp[freqChannel];
                                minRaw = ptrRamSensor->raw[freqChannel];
                            }
                            ptrRamSensor++;
                        }

                        /* Define new modulator IDAC */
                        rawLevel = ((minRaw * Input_Capsense_PERCENTAGE_100) / maxRawLevel) + Input_Capsense_PERCENTAGE_100;
                        iMod = (rawLevel * minIdac) / target;

                        if (iMod > maxIdac)
                        {
                            iMod = maxIdac;
                        }
                        ptrRamWidget->rowIdacMod[freqChannel] = (uint8)iMod;

                        /* Re-calculate compensation IDAC */
                        ptrRamSensor = &(ptrFlashWidget->ptr2SnsRam[ptrFlashWidget->numCols]);
                        for(snsIndex = 0u; snsIndex < ptrFlashWidget->numRows; snsIndex++)
                        {
                            rawLevel = (((ptrRamSensor->raw[freqChannel] * Input_Capsense_PERCENTAGE_100) / maxRawLevel) +
                                Input_Capsense_PERCENTAGE_100) * ptrRamSensor->idacComp[freqChannel];
                            if (rawLevel < (iMod * target))
                            {
                                ptrRamSensor->idacComp[freqChannel] = 0u;
                            }
                            else
                            {
                                ptrRamSensor->idacComp[freqChannel] = (uint8)(((rawLevel - (iMod * target)) +
                                    (Input_Capsense_PERCENTAGE_100 >> 1u)) / Input_Capsense_PERCENTAGE_100);
                            }
                            ptrRamSensor++;
                        }
                    }
                #endif
            }
        }
    #endif


    /*******************************************************************************
    * Function Name: Input_Capsense_SsCSDCalibrate
    ****************************************************************************//**
    *
    * \brief
    *  Implements IDAC calibration for a desired widget using successive
    *  approximation algorithm.
    *
    * \details
    *  Implements IDAC calibration for a desired widget using successive
    *  approximation algorithm. It supports any type of CSD widgets, and works
    *  with multi-frequency scan and compensation IDAC features enabled.
    *
    *  As result of function operation, the modulator IDAC that corresponds to the
    *  sensor with the highest capacitance (the biggest modulator IDAC) is stored
    *  into widget data structure. If it is dual-axis widget type (touchpad or matrix
    *  buttons) or if multi-frequency scan feature is enabled then the maximum
    *  modulator IDAC found separately for each multi-frequency channel and for
    *  rows/columns.
    *
    *  If compensation IDAC is enabled, then it preserves IDAC value of
    *  single-sensor calibration. In dual IDAC mode each sensor was calibrated with
    *  equal values of modulator and compensation IDAC.
    *
    *  After IDACs were found each sensor scanned again to get real raw count stored
    *  in sensor structure.
    *
    * \param widgetId
    *  Specifies the ID number of the CSD widget to calibrate its raw count.
    *  A macro for the widget ID can be found in the
    *  Input_Capsense Configuration header file defined as
    *  Input_Capsense_<WidgetName>_WDGT_ID.
    *
    * \param target
    *  Specifies the calibration target in percentages of the maximum raw count.
    *
    *******************************************************************************/
    static void Input_Capsense_SsCSDCalibrate(uint32 widgetId, uint32 target)
    {
        uint32 snsIndex;
        uint32 freqChannel;
        uint32 calMask;
        uint32 temp;
        uint32 watchdogCounter;

        uint8 *ptrIdacMod;
        uint8 *ptrMaxIdac;

        uint8 maxIdac[Input_Capsense_NUM_SCAN_FREQS];

        #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
            uint8 maxRowIdac[Input_Capsense_NUM_SCAN_FREQS];
            uint32 dualWidgetType = 0u;
        #endif

        Input_Capsense_RAM_SNS_STRUCT *ptrRamSensor;
        Input_Capsense_FLASH_WD_STRUCT const *ptrFlashWidget = &Input_Capsense_dsFlash.wdgtArray[widgetId];
        Input_Capsense_RAM_WD_BASE_STRUCT *ptrRamWidget = (Input_Capsense_RAM_WD_BASE_STRUCT *)ptrFlashWidget->ptr2WdgtRam;

        ptrIdacMod = &ptrRamWidget->idacMod[0u];
        ptrMaxIdac = &maxIdac[0u];

        for(freqChannel = Input_Capsense_NUM_SCAN_FREQS; freqChannel-- > 0u;)
        {
            maxIdac[freqChannel] = 0u;
            #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
                maxRowIdac[freqChannel] = 0u;
            #endif
        }

        /* Calculate raw count level based on resolution and target */
        temp = (((0x00000001Lu << ptrRamWidget->resolution) - 1u) * target) / Input_Capsense_PERCENTAGE_100;

        #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
            if ((Input_Capsense_WD_TOUCHPAD_E == Input_Capsense_GET_WIDGET_TYPE(ptrFlashWidget)) ||
                (Input_Capsense_WD_MATRIX_BUTTON_E == Input_Capsense_GET_WIDGET_TYPE(ptrFlashWidget)))
            {
                dualWidgetType = 1u;
            }
        #endif

        /* Loop through the widget sensors */
        for(snsIndex = 0u; snsIndex < ptrFlashWidget->totalNumSns; snsIndex++)
        {
            #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
                if (snsIndex == ptrFlashWidget->numCols)
                {
                    if (0u != dualWidgetType)
                    {
                        ptrIdacMod = &ptrRamWidget->rowIdacMod[0u];
                        ptrMaxIdac = &maxRowIdac[0u];
                    }
                }
            #endif

            ptrRamSensor = &((ptrFlashWidget->ptr2SnsRam)[snsIndex]);

            /* Set default IDAC code */
            calMask = Input_Capsense_CSD_CAL_MIDDLE_VALUE;
            for(freqChannel = Input_Capsense_NUM_SCAN_FREQS; freqChannel-- > 0u;)
            {
                ptrIdacMod[freqChannel] = Input_Capsense_CSD_CAL_MIDDLE_VALUE;
                #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
                    ptrRamSensor->idacComp[freqChannel] = ptrIdacMod[freqChannel];
                #endif
            }

            /* Loop through IDAC code */
            do
            {
                /* Need to configure HW block with each IDAC change */
                Input_Capsense_CSDSetupWidgetExt(widgetId, snsIndex);

                #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
                    Input_Capsense_DischargeExtCapacitors(Input_Capsense_EXT_CAP_DISCHARGE_TIME);
                #endif

                /* Scan sensor */
                Input_Capsense_CSDScanExt();

                watchdogCounter = Input_Capsense_CSD_CALIBR_WATCHDOG_CYCLES_NUM;
                while (((Input_Capsense_dsRam.status & Input_Capsense_SW_STS_BUSY) != 0u) && (0uL != watchdogCounter))
                {
                    watchdogCounter--;
                }

                /* Update IDAC based on scan result */
                for(freqChannel = Input_Capsense_NUM_SCAN_FREQS; freqChannel-- > 0u;)
                {
                    if (ptrRamSensor->raw[freqChannel] < temp)
                    {
                        ptrIdacMod[freqChannel] &= (uint8)(~calMask);
                    }
                }

                /* Switch to the lower IDAC mask */
                calMask >>= 1u;
                for(freqChannel = Input_Capsense_NUM_SCAN_FREQS; freqChannel-- > 0u;)
                {
                    ptrIdacMod[freqChannel] |= (uint8)calMask;
                    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
                        ptrRamSensor->idacComp[freqChannel] = ptrIdacMod[freqChannel];
                    #endif
                    if (0u == calMask)
                    {
                        if (0u == ptrIdacMod[freqChannel])
                        {
                            ptrIdacMod[freqChannel] = 1u;
                            #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
                                ptrRamSensor->idacComp[freqChannel] = ptrIdacMod[freqChannel];
                            #endif
                        }
                    }
                }
            }
            while (calMask != 0u);

            for(freqChannel = Input_Capsense_NUM_SCAN_FREQS; freqChannel-- > 0u;)
            {
                if (ptrMaxIdac[freqChannel] < ptrIdacMod[freqChannel])
                {
                    ptrMaxIdac[freqChannel] = ptrIdacMod[freqChannel];
                }
            }

            /* Perform scan again to get real raw count if IDAC was changed at the last iteration */
            Input_Capsense_CSDSetupWidgetExt(widgetId, snsIndex);
            Input_Capsense_CSDScanExt();

            watchdogCounter = Input_Capsense_CSD_CALIBR_WATCHDOG_CYCLES_NUM;
            while (((Input_Capsense_dsRam.status & Input_Capsense_SW_STS_BUSY) != 0u) && (0uL != watchdogCounter))
            {
                watchdogCounter--;
            }
        }

        for(freqChannel = Input_Capsense_NUM_SCAN_FREQS; freqChannel-- > 0u;)
        {
            ptrRamWidget->idacMod[freqChannel] = maxIdac[freqChannel];
            #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
                if (0u != dualWidgetType)
                {
                    ptrRamWidget->rowIdacMod[freqChannel] = maxRowIdac[freqChannel];

                    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_COL_ROW_IDAC_ALIGNMENT_EN)
                        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN)
                            if (ptrRamWidget->idacMod[freqChannel] < ptrRamWidget->rowIdacMod[freqChannel])
                            {
                                temp = ptrRamWidget->rowIdacMod[freqChannel];
                                if (temp > Input_Capsense_CSD_CAL_IDAC_MAX_VALUE)
                                {
                                    temp = Input_Capsense_CSD_CAL_IDAC_MAX_VALUE;
                                }
                                ptrRamWidget->idacMod[freqChannel] = (uint8)temp;
                            }
                            else
                            {
                                temp = ptrRamWidget->idacMod[freqChannel];
                                if (temp > Input_Capsense_CSD_CAL_IDAC_MAX_VALUE)
                                {
                                    temp = Input_Capsense_CSD_CAL_IDAC_MAX_VALUE;
                                }
                                ptrRamWidget->rowIdacMod[freqChannel] = (uint8)temp;
                            }
                        #else
                            if (((uint32)ptrRamWidget->idacMod[freqChannel] * ptrRamWidget->snsClk) <
                                ((uint32)ptrRamWidget->rowIdacMod[freqChannel] * ptrRamWidget->rowSnsClk))
                            {
                                temp = ((uint32)ptrRamWidget->rowIdacMod[freqChannel] *
                                                ptrRamWidget->rowSnsClk) / ptrRamWidget->snsClk;
                                if (temp > Input_Capsense_CSD_CAL_IDAC_MAX_VALUE)
                                {
                                    temp = Input_Capsense_CSD_CAL_IDAC_MAX_VALUE;
                                }
                                ptrRamWidget->idacMod[freqChannel] = (uint8)temp;
                            }
                            else
                            {
                                temp = ((uint32)ptrRamWidget->idacMod[freqChannel] *
                                                ptrRamWidget->snsClk) / ptrRamWidget->rowSnsClk;
                                if (temp > Input_Capsense_CSD_CAL_IDAC_MAX_VALUE)
                                {
                                    temp = Input_Capsense_CSD_CAL_IDAC_MAX_VALUE;
                                }
                                ptrRamWidget->rowIdacMod[freqChannel] = (uint8)temp;
                            }
                        #endif
                    #endif
                }
            #endif
        }
    }


    /*******************************************************************************
    * Function Name: Input_Capsense_CSDCalibrateWidget
    ****************************************************************************//**
    *
    * \brief
    *  Executes the IDAC calibration for all the sensors in the widget specified in
    *  the input.
    *
    * \details
    *  Executes the IDAC calibration for all the sensors in the widget specified in
    *  the input.
    *
    *  \note This function is obsolete and kept for backward compatibility only.
    *  The Input_Capsense_CalibrateWidget() function should be used instead.
    *
    *  Performs a successive approximation search algorithm to find appropriate
    *  IDAC values for sensors in the specified widget that provides the raw
    *  count to the level specified by the target parameter.
    *
    *  Calibration fails if the achieved raw count is outside of the range specified
    *  by the target and acceptable calibration deviation.
    *
    *  This function is available when the CSD Enable IDAC auto-calibration
    *  parameter is enabled or the  SmartSense auto-tuning mode is configured.
    *
    * \param widgetId
    *  Specifies the ID number of the CSD widget to calibrate its raw count.
    *  A macro for the widget ID can be found in the
    *  Input_Capsense Configuration header file defined as
    *  Input_Capsense_<WidgetName>_WDGT_ID.
    *
    * \param target
    *  Specifies the calibration target in percentages of the maximum raw count.
    *
    * \return
    *  Returns the status of the specified widget calibration:
    *    - CYRET_SUCCESS - The operation is successfully completed.
    *    - CYRET_BAD_PARAM - The input parameter is invalid.
    *    - CYRET_BAD_DATA - The calibration failed and the Component may not operate
    *      as expected.
    *    - CYRET_TIMEOUT - The calibration failed due to timeout.
    *    - CYRET_INVALID_STATE - The previous scanning is not completed and the
    *      hardware block is busy.
    *
    *******************************************************************************/
    cystatus Input_Capsense_CSDCalibrateWidget(uint32 widgetId, uint32 target)
    {
        cystatus calibrateStatus = CYRET_SUCCESS;
        uint32 watchdogCounter;

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTO_GAIN_EN)
            uint32 gainSwitch;
        #endif

        Input_Capsense_FLASH_WD_STRUCT const *ptrFlashWidget = &Input_Capsense_dsFlash.wdgtArray[widgetId];

        if (Input_Capsense_WDGT_SW_STS_BUSY == (Input_Capsense_dsRam.status & Input_Capsense_WDGT_SW_STS_BUSY))
        {
            /* Previous widget is being scanned, return error */
            calibrateStatus = CYRET_INVALID_STATE;
        }
        else
        {
            /* Set default IDAC gain */
            ((Input_Capsense_RAM_WD_BASE_STRUCT *)ptrFlashWidget->ptr2WdgtRam)->idacGainIndex =
                Input_Capsense_CSD_IDAC_GAIN_INDEX_DEFAULT;

            /* Perform calibration */
            #if (Input_Capsense_ENABLE != Input_Capsense_CSD_IDAC_AUTO_GAIN_EN)
                Input_Capsense_SsCSDCalibrate(widgetId, target);
            #else
                do
                {
                    Input_Capsense_SsCSDCalibrate(widgetId, target);
                    gainSwitch = Input_Capsense_SsCSDSwitchIdacGain(ptrFlashWidget);
                } while(0u != gainSwitch);
            #endif

            #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
                /* IDAC Normalization in Dual IDAC mode */
                Input_Capsense_SsCSDNormalizeIdac(ptrFlashWidget, target);
            #endif

            /* Perform specified widget scan to check calibration result */
            Input_Capsense_CSDSetupWidget(widgetId);
            Input_Capsense_CSDScan();

            watchdogCounter = Input_Capsense_WIDGET_MAX_SCAN_TIME;
            while (((Input_Capsense_dsRam.status & Input_Capsense_SW_STS_BUSY) != 0u) && (0uL != watchdogCounter))
            {
                watchdogCounter--;
            }

            /* Verification of calibration result */
            if (0u == watchdogCounter)
            {
                calibrateStatus = CYRET_TIMEOUT;
            }
            else
            {
                calibrateStatus = Input_Capsense_SsCSDCalibrateCheck(widgetId, target);
            }

             /* Update CRC */
            #if (Input_Capsense_ENABLE ==Input_Capsense_TST_WDGT_CRC_EN)
                Input_Capsense_DsUpdateWidgetCrc(widgetId);
            #endif
        }

        return calibrateStatus;
    }
#endif /* ((Input_Capsense_CSD_SS_DIS != Input_Capsense_CSD_AUTOTUNE)) || \
            (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTOCAL_EN)) */


#if (Input_Capsense_DISABLE == Input_Capsense_CSDV2)
    /*******************************************************************************
    * Function Name: Input_Capsense_SsCSDClockRestart
    ****************************************************************************//**
    *
    * \brief
    *  This function restarts the clocks.
    *
    * \details
    *  The function performs following:
    *  1) Stops, sets dividers and starts ModClk clock;
    *  2) Stops and starts SnsClk clock;
    *  3) Scan one cycle to reset the flip-flop for Direct clock mode.
    *
    *******************************************************************************/
    CY_INLINE static void Input_Capsense_SsCSDClockRestart(void)
    {
        #if (Input_Capsense_CLK_SOURCE_DIRECT == Input_Capsense_CSD_SNS_CLK_SOURCE)
            uint32 watchdogCounter;
        #endif /* (Input_Capsense_CLK_SOURCE_DIRECT == Input_Capsense_CSD_SNS_CLK_SOURCE) */

        /* Stop clocks, set dividers, and start clock to align clock phase */
        Input_Capsense_SsSetModClkClockDivider((uint32)Input_Capsense_dsRam.modCsdClk);

        #if (Input_Capsense_ENABLE == Input_Capsense_IS_M0S8PERI_BLOCK)
            /* Stop sense clock clock   */
            CY_SET_REG32(Input_Capsense_SNSCLK_CMD_PTR,
                         ((uint32)Input_Capsense_SnsClk__DIV_ID <<
                         Input_Capsense_SNSCLK_CMD_DIV_SHIFT)|
                         ((uint32)Input_Capsense_SNSCLK_CMD_DISABLE_MASK));

            /* Check whether previous sense clock start command has finished. */
            while(0u != (CY_GET_REG32(Input_Capsense_SNSCLK_CMD_PTR) & Input_Capsense_SNSCLK_CMD_ENABLE_MASK))
            {
                /* Wait until previous sense clock start command has finished. */
            }

            /* Start sense clock aligned to previously started modulator clock. */
            CY_SET_REG32(Input_Capsense_SNSCLK_CMD_PTR,
                         (uint32)(((uint32)Input_Capsense_SnsClk__DIV_ID << Input_Capsense_SNSCLK_CMD_DIV_SHIFT) |
                          ((uint32)Input_Capsense_ModClk__PA_DIV_ID << Input_Capsense_SNSCLK_CMD_PA_DIV_SHIFT) |
                          Input_Capsense_SNSCLK_CMD_ENABLE_MASK));
        #else
            /* Clear bit to disable SnsClk clock. */
            CY_SET_REG32(Input_Capsense_SNSCLK_CMD_PTR,
                         CY_GET_REG32(Input_Capsense_SNSCLK_CMD_PTR) &
                         (uint32)(~(uint32)Input_Capsense_SnsClk__ENABLE_MASK));

            /* Set bit to enable SnsClk clock. */
            CY_SET_REG32(Input_Capsense_SNSCLK_CMD_PTR,
                         CY_GET_REG32(Input_Capsense_SNSCLK_CMD_PTR) |
                        Input_Capsense_SnsClk__ENABLE_MASK);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_IS_M0S8PERI_BLOCK) */

        #if (Input_Capsense_CLK_SOURCE_DIRECT == Input_Capsense_CSD_SNS_CLK_SOURCE)
            /* Scan one cycle to reset the flip-flop for Direct clock mode */
            CyIntDisable(Input_Capsense_ISR_NUMBER);
            CY_SET_REG32(Input_Capsense_COUNTER_PTR, Input_Capsense_ONE_CYCLE);

            watchdogCounter = Input_Capsense_ONE_CLOCK_WATCHDOG_CYCLES_NUM;
            while((0u != (CY_GET_REG32(Input_Capsense_COUNTER_PTR) & Input_Capsense_RESOLUTION_16_BITS)) && (0uL != watchdogCounter))
            {
                watchdogCounter--;
            }
            CY_SET_REG32(Input_Capsense_INTR_PTR, Input_Capsense_INTR_SET_MASK);
            CyIntClearPending(Input_Capsense_ISR_NUMBER);
        #endif /* (Input_Capsense_CLK_SOURCE_DIRECT == Input_Capsense_CSD_SNS_CLK_SOURCE) */
    }
#endif /* (Input_Capsense_DISABLE == Input_Capsense_CSDV2) */


/*******************************************************************************
* Function Name: Input_Capsense_SsCSDCmodPrecharge
****************************************************************************//**
*
* \brief
*  This function initializes the Cmod charging to Vref.
*
* \details
*  For Third-generation HW block:
*  The function initializes the Cmod charging to Vref.
*  Then it waits the even when Cmod is completely charged
*  to Vref to have stable raw counts. Software Watchdog Counter is implemented to
*  prevent the project hanging.
*
*  For Fourth-generation HW block:
*  Coarse initialization for CMOD and Cch.
*  The coarse initialization is performed by HSCOMP.
*  The HSCOMP monitors the Cmod voltage via Cmod sense path
*  and charges the Cmod using HCAV switch via CSDBUS-A, AMUXBUS-A
*  and static connection of Cmod to AMUXBUS-A.
*
*******************************************************************************/
CY_INLINE static void Input_Capsense_SsCSDCmodPrecharge(void)
{
    #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
        uint32 watchdogCounter;
        /* Fourth-generation HW block section */

        CY_SET_REG32(Input_Capsense_CSDCMP_PTR, Input_Capsense_CSD_CSDCMP_INIT);
        CY_SET_REG32(Input_Capsense_SW_FW_MOD_SEL_PTR,  Input_Capsense_CSD_SW_FW_MOD_SEL_INIT);
        CY_SET_REG32(Input_Capsense_SW_FW_TANK_SEL_PTR, Input_Capsense_CSD_SW_FW_TANK_SEL_INIT);
        CY_SET_REG32(Input_Capsense_SW_SHIELD_SEL_PTR,  Input_Capsense_CSD_SW_SHIELD_SEL_INIT);
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
            /*
             * Connect CMOD to (sense path) to HSCOMP: HMPM or HMPS or HMPT switches depend on Cmod connects to certain pad
             * Connect AMUXBUS-B to HSCMP positive input
             */
            CY_SET_REG32(Input_Capsense_SW_HS_P_SEL_PTR, Input_Capsense_SW_HS_P_SEL_COARSE);

            #if(0u != Input_Capsense_CSD_SHIELD_TANK_EN)
                /* Connect CTANK to AMUXBUS-A */
                Input_Capsense_WriteBitsSafe(Input_Capsense_CSH_HSIOM_PTR, Input_Capsense_CSH_HSIOM_MASK,
                    (uint32)(Input_Capsense_HSIOM_SEL_AMUXA << Input_Capsense_CSH_HSIOM_SHIFT));
            #endif /* (0u != Input_Capsense_CSD_SHIELD_TANK_EN) */
        #else
            /* Connect CMOD to (sense path) to HSCOMP: HMPM or HMPS or HMPT switches depend on Cmod connects to certain pad */
            CY_SET_REG32(Input_Capsense_SW_HS_P_SEL_PTR, Input_Capsense_SW_HS_P_SEL_COARSE);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */

        CY_SET_REG32(Input_Capsense_SW_RES_PTR, Input_Capsense_CSD_SW_RES_INIT);

        /* Clear all interrupt pending requests */
        CY_SET_REG32(Input_Capsense_INTR_PTR, Input_Capsense_INTR_ALL_MASK);

        CY_SET_REG32(Input_Capsense_INTR_MASK_PTR, Input_Capsense_CLEAR_MASK);

        /* Start SEQUENCER for coarse initialization for Cmod */
        CY_SET_REG32(Input_Capsense_SEQ_START_PTR, Input_Capsense_SEQ_START_SEQ_MODE_MASK |
                                                         Input_Capsense_SEQ_START_START_MASK);

        /* Init Watchdog Counter to prevent a hang */
        watchdogCounter = Input_Capsense_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM;

        /* Wait for INTR.INIT goes high */
        while((0u == (CY_GET_REG32(Input_Capsense_INTR_PTR) & Input_Capsense_INTR_INIT_MASK)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        if (0u == watchdogCounter)
        {
            /* Set sequencer to idle state if coarse initialization fails */
            CY_SET_REG32(Input_Capsense_SEQ_START_PTR, Input_Capsense_SEQ_START_ABORT_MASK);
        }

    #else

        uint32 tmpRegValue;
        uint32 newRegValue;
        uint32 watchdogCounter;

        /* Save the current IDAC configuration */
        tmpRegValue = CY_GET_REG32(Input_Capsense_IDAC_PTR);

        /* Wait until Cmod discharges below Vref */
        CyDelayCycles(Input_Capsense_CMOD_DISCHARGE_CYCLES);

        newRegValue = Input_Capsense_CSD_IDAC_PRECHARGE_CONFIG | (tmpRegValue & ~Input_Capsense_IDAC_MOD_CFG_MASK);

        /* Set the IDAC configuration for fast Cmod precharge to Vref */
        CY_SET_REG32(Input_Capsense_IDAC_PTR, newRegValue);

        #if (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG)
            CY_SET_REG32(Input_Capsense_CONFIG_PTR, CY_GET_REG32(Input_Capsense_CONFIG_PTR) & ~Input_Capsense_CONFIG_POLARITY_MASK);
        #endif /* (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG) */

        /* Init Watchdog Counter to prevent a hang */
        watchdogCounter = Input_Capsense_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM;

        /* Wait until Cmod reaches to Vref */
        while((0u == (CY_GET_REG32(Input_Capsense_STATUS_PTR) & Input_Capsense_STATUS_SAMPLE)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        #if (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG)
            CY_SET_REG32(Input_Capsense_CONFIG_PTR, CY_GET_REG32(Input_Capsense_CONFIG_PTR) | Input_Capsense_CONFIG_POLARITY_MASK);
        #endif /* (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG) */

        /* Restore the current IDAC configuration */
        CY_SET_REG32(Input_Capsense_IDAC_PTR, tmpRegValue);

        /* Enable the sense modulator output */
        CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CTANK_PRECHARGE_CONFIG_CSD_EN | Input_Capsense_CONFIG_SENSE_EN_MASK);

        CyIntEnable(Input_Capsense_ISR_NUMBER);

    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
}


/*******************************************************************************
* Function Name: Input_Capsense_SsCSDTriggerScan
****************************************************************************//**
*
* \brief
*  This function triggers the scanning.
*
* \details
*  For Third-generation HW block:
*  Writes resolution to start the scanning.
*
*  For Fourth-generation HW block:
*  Trigger the fine initialization (scan some dummy cycles) and start sampling.
*  Fine initialization for CMOD and Start scan.
*  For the fine initialization and sampling, Cmod is static connected to AMUXBUS-A
*  and in every conversion (one cycle of SnsClk), the sensor capacitance is charged
*  from Cmod and discharged to ground using the switches in GPIO cell.
*  The CSDCOMP monitors voltage on Cmod using the sense path and charges Cmod back
*  to Vref using IDACs by connecting IDAC to CSDBUS-A and then the AMUXBUS-A.
*
*******************************************************************************/
CY_INLINE static void Input_Capsense_SsCSDTriggerScan(void)
{
    #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)

        /* Fourth-generation HW block section */

        uint32 watchdogCounter;

        /* Clear previous interrupts */
        CY_SET_REG32(Input_Capsense_INTR_PTR, Input_Capsense_INTR_ALL_MASK);

        /* Clear pending interrupts  */
        CyIntClearPending(Input_Capsense_ISR_NUMBER);

        /* Enable CSD interrupt */
        CyIntEnable(Input_Capsense_ISR_NUMBER);


        CY_SET_REG32(Input_Capsense_SW_HS_P_SEL_PTR, Input_Capsense_CSD_SW_HS_P_SEL_SCAN);

        /* Set scanning configuration for switches */
        CY_SET_REG32(Input_Capsense_SW_FW_MOD_SEL_PTR, Input_Capsense_CSD_SW_FW_MOD_SEL_SCAN);
        CY_SET_REG32(Input_Capsense_SW_FW_TANK_SEL_PTR,Input_Capsense_CSD_SW_FW_TANK_SEL_SCAN);

        CY_SET_REG32(Input_Capsense_SW_SHIELD_SEL_PTR,  Input_Capsense_CSD_SW_SHIELD_SEL_SCAN);

        #if((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) && (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN))
            /* Connect CTANK to AMUXBUS-B */
            Input_Capsense_SsCSDEnableShieldTank();
        #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) && (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN)) */

        CY_SET_REG32(Input_Capsense_SW_RES_PTR, Input_Capsense_CSD_SW_RES_SCAN);
        CY_SET_REG32(Input_Capsense_CSDCMP_PTR, Input_Capsense_CSD_CSDCMP_SCAN);

        #if (Input_Capsense_DISABLE == Input_Capsense_CSD_SHIELD_EN)
            /* Disable HSCOMP during the sampling phase when shield is disabled */
            CY_SET_REG32(Input_Capsense_HSCMP_PTR, 0u);
        #else
            CY_SET_REG32(Input_Capsense_HSCMP_PTR, Input_Capsense_HSCMP_SCAN_MASK);
        #endif /* (Input_Capsense_DISABLE == Input_Capsense_CSD_SHIELD_EN) */

        #if (Input_Capsense_CLK_SOURCE_DIRECT != Input_Capsense_CSD_SNS_CLK_SOURCE)
            /* Force the LFSR to it's initial state (all ones) */
            CY_SET_REG32(Input_Capsense_SENSE_PERIOD_PTR, CY_GET_REG32(Input_Capsense_SENSE_PERIOD_PTR) |
                                                           Input_Capsense_SENSE_PERIOD_LFSR_CLEAR_MASK);
        #endif /* (Input_Capsense_CLK_SOURCE_DIRECT != Input_Capsense_CSD_SNS_CLK_SOURCE) */

        /* Enable SAMPLE interrupt */
        CY_SET_REG32(Input_Capsense_INTR_MASK_PTR, Input_Capsense_INTR_MASK_SAMPLE_MASK);

        /* Init Watchdog Counter to prevent a hang */
        watchdogCounter = Input_Capsense_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM;

        /* Wait for IDLE state of the HW sequencer */
        while((0u != (Input_Capsense_STAT_SEQ_REG & Input_Capsense_STAT_SEQ_SEQ_STATE_MASK)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        /* Start SEQUENCER for fine initialization scan for Cmod and then for normal scan */
        CY_SET_REG32(Input_Capsense_SEQ_START_PTR, Input_Capsense_SEQ_START_AZ0_SKIP_MASK |
                                                     Input_Capsense_SEQ_START_AZ1_SKIP_MASK |
                                                     Input_Capsense_SEQ_START_START_MASK);

    #else

        /* Third-generation HW block section */

        /* Set resolution to Counter register to start scanning */
        CY_SET_REG32(Input_Capsense_COUNTER_PTR, Input_Capsense_counterResolution);

    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
}

#endif  /* (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) */


/* [] END OF FILE */
