/***************************************************************************//**
* \file Input_Capsense_Structure.c
* \version 7.0
*
* \brief
*   This file defines the data structure global variables and provides implementation
*   for the high-level and low-level APIs of the Data Structure module.
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

#include <cytypes.h>
#include "CyLib.h"
#include "Input_Capsense_Structure.h"
#include "Input_Capsense_Configuration.h"

#if (0u != Input_Capsense_ADC_EN)
    #include "Input_Capsense_Adc.h"
#endif /* (0u != Input_Capsense_ADC_EN) */

#if (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN)
    #include "Input_Capsense_SelfTest.h"
#endif

#if (Input_Capsense_ENABLE == Input_Capsense_CENTROID_5X5_CSD_EN)
    #include "Input_Capsense_AdvancedCentroid_LL.h"
#endif

#if (Input_Capsense_ENABLE == Input_Capsense_GES_GLOBAL_EN)
    #include "Input_Capsense_Gesture.h"
#endif /* (Input_Capsense_ENABLE == Input_Capsense_GES_GLOBAL_EN) */

/*******************************************************************************
* Defines the RAM Data Structure variables and their init data in flash
*******************************************************************************/
/**
* \cond SECTION_GLOBAL_VARIABLES
* \addtogroup group_global_variables
* \{
*/

/**
* The variable that contains the Input_Capsense configuration, settings and
* scanning results. Input_Capsense_dsRam represents RAM Data Structure.
*/
Input_Capsense_RAM_STRUCT Input_Capsense_dsRam;
/** \}
* \endcond */

/*******************************************************************************
* Declares Widget's De-bounce Counters
*******************************************************************************/
static uint8 Input_Capsense_debouncesw100[Input_Capsense_SW100_NUM_SENSORS];
static uint8 Input_Capsense_debouncesw101[Input_Capsense_SW101_NUM_SENSORS];
static uint8 Input_Capsense_debouncesw102[Input_Capsense_SW102_NUM_SENSORS];
static uint8 Input_Capsense_debouncesw103[Input_Capsense_SW103_NUM_SENSORS];
static uint8 Input_Capsense_debouncesw104[Input_Capsense_SW104_NUM_SENSORS];
static uint8 Input_Capsense_debouncesw105[Input_Capsense_SW105_NUM_SENSORS];
static uint8 Input_Capsense_debouncesw106[Input_Capsense_SW106_NUM_SENSORS];
static uint8 Input_Capsense_debouncesw107[Input_Capsense_SW107_NUM_SENSORS];
static uint8 Input_Capsense_debouncesw108[Input_Capsense_SW108_NUM_SENSORS];
static uint8 Input_Capsense_debouncesw109[Input_Capsense_SW109_NUM_SENSORS];
static uint8 Input_Capsense_debouncesw110[Input_Capsense_SW110_NUM_SENSORS];
static uint8 Input_Capsense_debouncesw111[Input_Capsense_SW111_NUM_SENSORS];
static uint8 Input_Capsense_debouncesw112[Input_Capsense_SW112_NUM_SENSORS];


/***************************************************************************//**
* Declares Noise Envelope data structures
*******************************************************************************/
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw100[Input_Capsense_SW100_NUM_SENSORS];
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw101[Input_Capsense_SW101_NUM_SENSORS];
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw102[Input_Capsense_SW102_NUM_SENSORS];
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw103[Input_Capsense_SW103_NUM_SENSORS];
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw104[Input_Capsense_SW104_NUM_SENSORS];
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw105[Input_Capsense_SW105_NUM_SENSORS];
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw106[Input_Capsense_SW106_NUM_SENSORS];
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw107[Input_Capsense_SW107_NUM_SENSORS];
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw108[Input_Capsense_SW108_NUM_SENSORS];
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw109[Input_Capsense_SW109_NUM_SENSORS];
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw110[Input_Capsense_SW110_NUM_SENSORS];
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw111[Input_Capsense_SW111_NUM_SENSORS];
static SMARTSENSE_CSD_NOISE_ENVELOPE_STRUCT Input_Capsense_noiseEnvlpsw112[Input_Capsense_SW112_NUM_SENSORS];

/*******************************************************************************
* Defines and initializes the Flash Data Structure
*******************************************************************************/



/**
* \cond SECTION_API_CONSTANTS
* \addtogroup group_api_constants
* \{
*/
/**
* Constant for the FLASH Data Structure
*/
const Input_Capsense_FLASH_STRUCT Input_Capsense_dsFlash =
{
    /* Flash Widget Initialization Data */
    {
        { /* sw100 */
            &Input_Capsense_ioList[0u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw100,
            Input_Capsense_dsRam.snsList.sw100,
            (void *)0u,
            Input_Capsense_debouncesw100,
            Input_Capsense_SW100_STATIC_CONFIG,
            Input_Capsense_SW100_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW100_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw100,
        },
        { /* sw101 */
            &Input_Capsense_ioList[1u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw101,
            Input_Capsense_dsRam.snsList.sw101,
            (void *)0u,
            Input_Capsense_debouncesw101,
            Input_Capsense_SW101_STATIC_CONFIG,
            Input_Capsense_SW101_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW101_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw101,
        },
        { /* sw102 */
            &Input_Capsense_ioList[2u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw102,
            Input_Capsense_dsRam.snsList.sw102,
            (void *)0u,
            Input_Capsense_debouncesw102,
            Input_Capsense_SW102_STATIC_CONFIG,
            Input_Capsense_SW102_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW102_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw102,
        },
        { /* sw103 */
            &Input_Capsense_ioList[3u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw103,
            Input_Capsense_dsRam.snsList.sw103,
            (void *)0u,
            Input_Capsense_debouncesw103,
            Input_Capsense_SW103_STATIC_CONFIG,
            Input_Capsense_SW103_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW103_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw103,
        },
        { /* sw104 */
            &Input_Capsense_ioList[4u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw104,
            Input_Capsense_dsRam.snsList.sw104,
            (void *)0u,
            Input_Capsense_debouncesw104,
            Input_Capsense_SW104_STATIC_CONFIG,
            Input_Capsense_SW104_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW104_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw104,
        },
        { /* sw105 */
            &Input_Capsense_ioList[5u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw105,
            Input_Capsense_dsRam.snsList.sw105,
            (void *)0u,
            Input_Capsense_debouncesw105,
            Input_Capsense_SW105_STATIC_CONFIG,
            Input_Capsense_SW105_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW105_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw105,
        },
        { /* sw106 */
            &Input_Capsense_ioList[6u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw106,
            Input_Capsense_dsRam.snsList.sw106,
            (void *)0u,
            Input_Capsense_debouncesw106,
            Input_Capsense_SW106_STATIC_CONFIG,
            Input_Capsense_SW106_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW106_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw106,
        },
        { /* sw107 */
            &Input_Capsense_ioList[7u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw107,
            Input_Capsense_dsRam.snsList.sw107,
            (void *)0u,
            Input_Capsense_debouncesw107,
            Input_Capsense_SW107_STATIC_CONFIG,
            Input_Capsense_SW107_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW107_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw107,
        },
        { /* sw108 */
            &Input_Capsense_ioList[8u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw108,
            Input_Capsense_dsRam.snsList.sw108,
            (void *)0u,
            Input_Capsense_debouncesw108,
            Input_Capsense_SW108_STATIC_CONFIG,
            Input_Capsense_SW108_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW108_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw108,
        },
        { /* sw109 */
            &Input_Capsense_ioList[9u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw109,
            Input_Capsense_dsRam.snsList.sw109,
            (void *)0u,
            Input_Capsense_debouncesw109,
            Input_Capsense_SW109_STATIC_CONFIG,
            Input_Capsense_SW109_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW109_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw109,
        },
        { /* sw110 */
            &Input_Capsense_ioList[10u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw110,
            Input_Capsense_dsRam.snsList.sw110,
            (void *)0u,
            Input_Capsense_debouncesw110,
            Input_Capsense_SW110_STATIC_CONFIG,
            Input_Capsense_SW110_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW110_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw110,
        },
        { /* sw111 */
            &Input_Capsense_ioList[11u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw111,
            Input_Capsense_dsRam.snsList.sw111,
            (void *)0u,
            Input_Capsense_debouncesw111,
            Input_Capsense_SW111_STATIC_CONFIG,
            Input_Capsense_SW111_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW111_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw111,
        },
        { /* sw112 */
            &Input_Capsense_ioList[12u],
            (void *)&Input_Capsense_dsRam.wdgtList.sw112,
            Input_Capsense_dsRam.snsList.sw112,
            (void *)0u,
            Input_Capsense_debouncesw112,
            Input_Capsense_SW112_STATIC_CONFIG,
            Input_Capsense_SW112_NUM_SENSORS,
            (uint8)Input_Capsense_WD_BUTTON_E,
            Input_Capsense_SW112_NUM_SENSORS,
            Input_Capsense_noiseEnvlpsw112,
        },
    },
};

/**
* The array of the pointers to the electrode specific register.
*/
const Input_Capsense_FLASH_IO_STRUCT Input_Capsense_ioList[Input_Capsense_TOTAL_ELECTRODES] =
{
    { /* 0: sw100_Sns0 */
        (reg32 *)Input_Capsense_Sns__0__HSIOM,
        (reg32 *)Input_Capsense_Sns__0__PC,
        (reg32 *)Input_Capsense_Sns__0__DR,
        (reg32 *)Input_Capsense_Sns__0__PS,
        Input_Capsense_Sns__0__HSIOM_MASK,
        Input_Capsense_Sns__0__MASK,
        Input_Capsense_Sns__0__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__0__SHIFT,
        (uint8)Input_Capsense_Sns__0__SHIFT * 3u,
    },
    { /* 1: sw101_Sns0 */
        (reg32 *)Input_Capsense_Sns__1__HSIOM,
        (reg32 *)Input_Capsense_Sns__1__PC,
        (reg32 *)Input_Capsense_Sns__1__DR,
        (reg32 *)Input_Capsense_Sns__1__PS,
        Input_Capsense_Sns__1__HSIOM_MASK,
        Input_Capsense_Sns__1__MASK,
        Input_Capsense_Sns__1__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__1__SHIFT,
        (uint8)Input_Capsense_Sns__1__SHIFT * 3u,
    },
    { /* 2: sw102_Sns0 */
        (reg32 *)Input_Capsense_Sns__2__HSIOM,
        (reg32 *)Input_Capsense_Sns__2__PC,
        (reg32 *)Input_Capsense_Sns__2__DR,
        (reg32 *)Input_Capsense_Sns__2__PS,
        Input_Capsense_Sns__2__HSIOM_MASK,
        Input_Capsense_Sns__2__MASK,
        Input_Capsense_Sns__2__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__2__SHIFT,
        (uint8)Input_Capsense_Sns__2__SHIFT * 3u,
    },
    { /* 3: sw103_Sns0 */
        (reg32 *)Input_Capsense_Sns__3__HSIOM,
        (reg32 *)Input_Capsense_Sns__3__PC,
        (reg32 *)Input_Capsense_Sns__3__DR,
        (reg32 *)Input_Capsense_Sns__3__PS,
        Input_Capsense_Sns__3__HSIOM_MASK,
        Input_Capsense_Sns__3__MASK,
        Input_Capsense_Sns__3__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__3__SHIFT,
        (uint8)Input_Capsense_Sns__3__SHIFT * 3u,
    },
    { /* 4: sw104_Sns0 */
        (reg32 *)Input_Capsense_Sns__4__HSIOM,
        (reg32 *)Input_Capsense_Sns__4__PC,
        (reg32 *)Input_Capsense_Sns__4__DR,
        (reg32 *)Input_Capsense_Sns__4__PS,
        Input_Capsense_Sns__4__HSIOM_MASK,
        Input_Capsense_Sns__4__MASK,
        Input_Capsense_Sns__4__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__4__SHIFT,
        (uint8)Input_Capsense_Sns__4__SHIFT * 3u,
    },
    { /* 5: sw105_Sns0 */
        (reg32 *)Input_Capsense_Sns__5__HSIOM,
        (reg32 *)Input_Capsense_Sns__5__PC,
        (reg32 *)Input_Capsense_Sns__5__DR,
        (reg32 *)Input_Capsense_Sns__5__PS,
        Input_Capsense_Sns__5__HSIOM_MASK,
        Input_Capsense_Sns__5__MASK,
        Input_Capsense_Sns__5__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__5__SHIFT,
        (uint8)Input_Capsense_Sns__5__SHIFT * 3u,
    },
    { /* 6: sw106_Sns0 */
        (reg32 *)Input_Capsense_Sns__6__HSIOM,
        (reg32 *)Input_Capsense_Sns__6__PC,
        (reg32 *)Input_Capsense_Sns__6__DR,
        (reg32 *)Input_Capsense_Sns__6__PS,
        Input_Capsense_Sns__6__HSIOM_MASK,
        Input_Capsense_Sns__6__MASK,
        Input_Capsense_Sns__6__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__6__SHIFT,
        (uint8)Input_Capsense_Sns__6__SHIFT * 3u,
    },
    { /* 7: sw107_Sns0 */
        (reg32 *)Input_Capsense_Sns__7__HSIOM,
        (reg32 *)Input_Capsense_Sns__7__PC,
        (reg32 *)Input_Capsense_Sns__7__DR,
        (reg32 *)Input_Capsense_Sns__7__PS,
        Input_Capsense_Sns__7__HSIOM_MASK,
        Input_Capsense_Sns__7__MASK,
        Input_Capsense_Sns__7__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__7__SHIFT,
        (uint8)Input_Capsense_Sns__7__SHIFT * 3u,
    },
    { /* 8: sw108_Sns0 */
        (reg32 *)Input_Capsense_Sns__8__HSIOM,
        (reg32 *)Input_Capsense_Sns__8__PC,
        (reg32 *)Input_Capsense_Sns__8__DR,
        (reg32 *)Input_Capsense_Sns__8__PS,
        Input_Capsense_Sns__8__HSIOM_MASK,
        Input_Capsense_Sns__8__MASK,
        Input_Capsense_Sns__8__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__8__SHIFT,
        (uint8)Input_Capsense_Sns__8__SHIFT * 3u,
    },
    { /* 9: sw109_Sns0 */
        (reg32 *)Input_Capsense_Sns__9__HSIOM,
        (reg32 *)Input_Capsense_Sns__9__PC,
        (reg32 *)Input_Capsense_Sns__9__DR,
        (reg32 *)Input_Capsense_Sns__9__PS,
        Input_Capsense_Sns__9__HSIOM_MASK,
        Input_Capsense_Sns__9__MASK,
        Input_Capsense_Sns__9__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__9__SHIFT,
        (uint8)Input_Capsense_Sns__9__SHIFT * 3u,
    },
    { /* 10: sw110_Sns0 */
        (reg32 *)Input_Capsense_Sns__10__HSIOM,
        (reg32 *)Input_Capsense_Sns__10__PC,
        (reg32 *)Input_Capsense_Sns__10__DR,
        (reg32 *)Input_Capsense_Sns__10__PS,
        Input_Capsense_Sns__10__HSIOM_MASK,
        Input_Capsense_Sns__10__MASK,
        Input_Capsense_Sns__10__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__10__SHIFT,
        (uint8)Input_Capsense_Sns__10__SHIFT * 3u,
    },
    { /* 11: sw111_Sns0 */
        (reg32 *)Input_Capsense_Sns__11__HSIOM,
        (reg32 *)Input_Capsense_Sns__11__PC,
        (reg32 *)Input_Capsense_Sns__11__DR,
        (reg32 *)Input_Capsense_Sns__11__PS,
        Input_Capsense_Sns__11__HSIOM_MASK,
        Input_Capsense_Sns__11__MASK,
        Input_Capsense_Sns__11__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__11__SHIFT,
        (uint8)Input_Capsense_Sns__11__SHIFT * 3u,
    },
    { /* 12: sw112_Sns0 */
        (reg32 *)Input_Capsense_Sns__12__HSIOM,
        (reg32 *)Input_Capsense_Sns__12__PC,
        (reg32 *)Input_Capsense_Sns__12__DR,
        (reg32 *)Input_Capsense_Sns__12__PS,
        Input_Capsense_Sns__12__HSIOM_MASK,
        Input_Capsense_Sns__12__MASK,
        Input_Capsense_Sns__12__HSIOM_SHIFT,
        (uint8)Input_Capsense_Sns__12__SHIFT,
        (uint8)Input_Capsense_Sns__12__SHIFT * 3u,
    },
};



/** \}
* \endcond */

/* Initialization data for RAM widget list */
const Input_Capsense_RAM_WD_LIST_STRUCT Input_Capsense_ramWidgetInit =
{
    { /* sw100 */
        Input_Capsense_SW100_RESOLUTION,
        Input_Capsense_SW100_FINGER_TH,
        Input_Capsense_SW100_NOISE_TH,
        Input_Capsense_SW100_NNOISE_TH,
        Input_Capsense_SW100_HYSTERESIS,
        Input_Capsense_SW100_ON_DEBOUNCE,
        Input_Capsense_SW100_LOW_BSLN_RST,
        {
            Input_Capsense_SW100_IDAC_MOD0,
        },
        Input_Capsense_SW100_IDAC_GAIN_INDEX,
        Input_Capsense_SW100_SNS_CLK,
        Input_Capsense_SW100_SNS_CLK_SOURCE,
        Input_Capsense_SW100_FINGER_CAP,
        Input_Capsense_SW100_SIGPFC,
    },
    { /* sw101 */
        Input_Capsense_SW101_RESOLUTION,
        Input_Capsense_SW101_FINGER_TH,
        Input_Capsense_SW101_NOISE_TH,
        Input_Capsense_SW101_NNOISE_TH,
        Input_Capsense_SW101_HYSTERESIS,
        Input_Capsense_SW101_ON_DEBOUNCE,
        Input_Capsense_SW101_LOW_BSLN_RST,
        {
            Input_Capsense_SW101_IDAC_MOD0,
        },
        Input_Capsense_SW101_IDAC_GAIN_INDEX,
        Input_Capsense_SW101_SNS_CLK,
        Input_Capsense_SW101_SNS_CLK_SOURCE,
        Input_Capsense_SW101_FINGER_CAP,
        Input_Capsense_SW101_SIGPFC,
    },
    { /* sw102 */
        Input_Capsense_SW102_RESOLUTION,
        Input_Capsense_SW102_FINGER_TH,
        Input_Capsense_SW102_NOISE_TH,
        Input_Capsense_SW102_NNOISE_TH,
        Input_Capsense_SW102_HYSTERESIS,
        Input_Capsense_SW102_ON_DEBOUNCE,
        Input_Capsense_SW102_LOW_BSLN_RST,
        {
            Input_Capsense_SW102_IDAC_MOD0,
        },
        Input_Capsense_SW102_IDAC_GAIN_INDEX,
        Input_Capsense_SW102_SNS_CLK,
        Input_Capsense_SW102_SNS_CLK_SOURCE,
        Input_Capsense_SW102_FINGER_CAP,
        Input_Capsense_SW102_SIGPFC,
    },
    { /* sw103 */
        Input_Capsense_SW103_RESOLUTION,
        Input_Capsense_SW103_FINGER_TH,
        Input_Capsense_SW103_NOISE_TH,
        Input_Capsense_SW103_NNOISE_TH,
        Input_Capsense_SW103_HYSTERESIS,
        Input_Capsense_SW103_ON_DEBOUNCE,
        Input_Capsense_SW103_LOW_BSLN_RST,
        {
            Input_Capsense_SW103_IDAC_MOD0,
        },
        Input_Capsense_SW103_IDAC_GAIN_INDEX,
        Input_Capsense_SW103_SNS_CLK,
        Input_Capsense_SW103_SNS_CLK_SOURCE,
        Input_Capsense_SW103_FINGER_CAP,
        Input_Capsense_SW103_SIGPFC,
    },
    { /* sw104 */
        Input_Capsense_SW104_RESOLUTION,
        Input_Capsense_SW104_FINGER_TH,
        Input_Capsense_SW104_NOISE_TH,
        Input_Capsense_SW104_NNOISE_TH,
        Input_Capsense_SW104_HYSTERESIS,
        Input_Capsense_SW104_ON_DEBOUNCE,
        Input_Capsense_SW104_LOW_BSLN_RST,
        {
            Input_Capsense_SW104_IDAC_MOD0,
        },
        Input_Capsense_SW104_IDAC_GAIN_INDEX,
        Input_Capsense_SW104_SNS_CLK,
        Input_Capsense_SW104_SNS_CLK_SOURCE,
        Input_Capsense_SW104_FINGER_CAP,
        Input_Capsense_SW104_SIGPFC,
    },
    { /* sw105 */
        Input_Capsense_SW105_RESOLUTION,
        Input_Capsense_SW105_FINGER_TH,
        Input_Capsense_SW105_NOISE_TH,
        Input_Capsense_SW105_NNOISE_TH,
        Input_Capsense_SW105_HYSTERESIS,
        Input_Capsense_SW105_ON_DEBOUNCE,
        Input_Capsense_SW105_LOW_BSLN_RST,
        {
            Input_Capsense_SW105_IDAC_MOD0,
        },
        Input_Capsense_SW105_IDAC_GAIN_INDEX,
        Input_Capsense_SW105_SNS_CLK,
        Input_Capsense_SW105_SNS_CLK_SOURCE,
        Input_Capsense_SW105_FINGER_CAP,
        Input_Capsense_SW105_SIGPFC,
    },
    { /* sw106 */
        Input_Capsense_SW106_RESOLUTION,
        Input_Capsense_SW106_FINGER_TH,
        Input_Capsense_SW106_NOISE_TH,
        Input_Capsense_SW106_NNOISE_TH,
        Input_Capsense_SW106_HYSTERESIS,
        Input_Capsense_SW106_ON_DEBOUNCE,
        Input_Capsense_SW106_LOW_BSLN_RST,
        {
            Input_Capsense_SW106_IDAC_MOD0,
        },
        Input_Capsense_SW106_IDAC_GAIN_INDEX,
        Input_Capsense_SW106_SNS_CLK,
        Input_Capsense_SW106_SNS_CLK_SOURCE,
        Input_Capsense_SW106_FINGER_CAP,
        Input_Capsense_SW106_SIGPFC,
    },
    { /* sw107 */
        Input_Capsense_SW107_RESOLUTION,
        Input_Capsense_SW107_FINGER_TH,
        Input_Capsense_SW107_NOISE_TH,
        Input_Capsense_SW107_NNOISE_TH,
        Input_Capsense_SW107_HYSTERESIS,
        Input_Capsense_SW107_ON_DEBOUNCE,
        Input_Capsense_SW107_LOW_BSLN_RST,
        {
            Input_Capsense_SW107_IDAC_MOD0,
        },
        Input_Capsense_SW107_IDAC_GAIN_INDEX,
        Input_Capsense_SW107_SNS_CLK,
        Input_Capsense_SW107_SNS_CLK_SOURCE,
        Input_Capsense_SW107_FINGER_CAP,
        Input_Capsense_SW107_SIGPFC,
    },
    { /* sw108 */
        Input_Capsense_SW108_RESOLUTION,
        Input_Capsense_SW108_FINGER_TH,
        Input_Capsense_SW108_NOISE_TH,
        Input_Capsense_SW108_NNOISE_TH,
        Input_Capsense_SW108_HYSTERESIS,
        Input_Capsense_SW108_ON_DEBOUNCE,
        Input_Capsense_SW108_LOW_BSLN_RST,
        {
            Input_Capsense_SW108_IDAC_MOD0,
        },
        Input_Capsense_SW108_IDAC_GAIN_INDEX,
        Input_Capsense_SW108_SNS_CLK,
        Input_Capsense_SW108_SNS_CLK_SOURCE,
        Input_Capsense_SW108_FINGER_CAP,
        Input_Capsense_SW108_SIGPFC,
    },
    { /* sw109 */
        Input_Capsense_SW109_RESOLUTION,
        Input_Capsense_SW109_FINGER_TH,
        Input_Capsense_SW109_NOISE_TH,
        Input_Capsense_SW109_NNOISE_TH,
        Input_Capsense_SW109_HYSTERESIS,
        Input_Capsense_SW109_ON_DEBOUNCE,
        Input_Capsense_SW109_LOW_BSLN_RST,
        {
            Input_Capsense_SW109_IDAC_MOD0,
        },
        Input_Capsense_SW109_IDAC_GAIN_INDEX,
        Input_Capsense_SW109_SNS_CLK,
        Input_Capsense_SW109_SNS_CLK_SOURCE,
        Input_Capsense_SW109_FINGER_CAP,
        Input_Capsense_SW109_SIGPFC,
    },
    { /* sw110 */
        Input_Capsense_SW110_RESOLUTION,
        Input_Capsense_SW110_FINGER_TH,
        Input_Capsense_SW110_NOISE_TH,
        Input_Capsense_SW110_NNOISE_TH,
        Input_Capsense_SW110_HYSTERESIS,
        Input_Capsense_SW110_ON_DEBOUNCE,
        Input_Capsense_SW110_LOW_BSLN_RST,
        {
            Input_Capsense_SW110_IDAC_MOD0,
        },
        Input_Capsense_SW110_IDAC_GAIN_INDEX,
        Input_Capsense_SW110_SNS_CLK,
        Input_Capsense_SW110_SNS_CLK_SOURCE,
        Input_Capsense_SW110_FINGER_CAP,
        Input_Capsense_SW110_SIGPFC,
    },
    { /* sw111 */
        Input_Capsense_SW111_RESOLUTION,
        Input_Capsense_SW111_FINGER_TH,
        Input_Capsense_SW111_NOISE_TH,
        Input_Capsense_SW111_NNOISE_TH,
        Input_Capsense_SW111_HYSTERESIS,
        Input_Capsense_SW111_ON_DEBOUNCE,
        Input_Capsense_SW111_LOW_BSLN_RST,
        {
            Input_Capsense_SW111_IDAC_MOD0,
        },
        Input_Capsense_SW111_IDAC_GAIN_INDEX,
        Input_Capsense_SW111_SNS_CLK,
        Input_Capsense_SW111_SNS_CLK_SOURCE,
        Input_Capsense_SW111_FINGER_CAP,
        Input_Capsense_SW111_SIGPFC,
    },
    { /* sw112 */
        Input_Capsense_SW112_RESOLUTION,
        Input_Capsense_SW112_FINGER_TH,
        Input_Capsense_SW112_NOISE_TH,
        Input_Capsense_SW112_NNOISE_TH,
        Input_Capsense_SW112_HYSTERESIS,
        Input_Capsense_SW112_ON_DEBOUNCE,
        Input_Capsense_SW112_LOW_BSLN_RST,
        {
            Input_Capsense_SW112_IDAC_MOD0,
        },
        Input_Capsense_SW112_IDAC_GAIN_INDEX,
        Input_Capsense_SW112_SNS_CLK,
        Input_Capsense_SW112_SNS_CLK_SOURCE,
        Input_Capsense_SW112_FINGER_CAP,
        Input_Capsense_SW112_SIGPFC,
    },
};


/* IDAC Initialization Data */
const uint8 Input_Capsense_ramIdacInit[Input_Capsense_TOTAL_SENSORS] =
{
    /* sw100 */
    Input_Capsense_SW100_SNS0_IDAC_COMP0,

    /* sw101 */
    Input_Capsense_SW101_SNS0_IDAC_COMP0,

    /* sw102 */
    Input_Capsense_SW102_SNS0_IDAC_COMP0,

    /* sw103 */
    Input_Capsense_SW103_SNS0_IDAC_COMP0,

    /* sw104 */
    Input_Capsense_SW104_SNS0_IDAC_COMP0,

    /* sw105 */
    Input_Capsense_SW105_SNS0_IDAC_COMP0,

    /* sw106 */
    Input_Capsense_SW106_SNS0_IDAC_COMP0,

    /* sw107 */
    Input_Capsense_SW107_SNS0_IDAC_COMP0,

    /* sw108 */
    Input_Capsense_SW108_SNS0_IDAC_COMP0,

    /* sw109 */
    Input_Capsense_SW109_SNS0_IDAC_COMP0,

    /* sw110 */
    Input_Capsense_SW110_SNS0_IDAC_COMP0,

    /* sw111 */
    Input_Capsense_SW111_SNS0_IDAC_COMP0,

    /* sw112 */
    Input_Capsense_SW112_SNS0_IDAC_COMP0,
};





/*******************************************************************************
* Defines internal data types and statements
*******************************************************************************/
#define PARAM_TYPE_OFFSET       (30u)
#define PARAM_TYPE_MASK         (3Lu << PARAM_TYPE_OFFSET)
#define PARAM_RWBIT_OFFSET      (29u)
#define PARAM_RWBIT_MASK        (1Lu << PARAM_RWBIT_OFFSET)
#define PARAM_FBIT_OFFSET       (28u)
#define PARAM_FBIT_MASK         (1Lu << PARAM_FBIT_OFFSET)
#define PARAM_UBIT_OFFSET       (23u)
#define PARAM_UBIT_MASK         (1Lu << PARAM_UBIT_OFFSET)
#define PARAM_WDID_OFFSET       (16u)
#define PARAM_WDID_MASK         (0x7FLu << PARAM_WDID_OFFSET)
#define PARAM_CRC_OFFSET        (24u)
#define PARAM_CRC_MASK          (0x0FLu << PARAM_CRC_OFFSET)

/* Defines align masks for uint16 and uint32 */
#define UINT16_ALIGN_MASK       (1Lu)
#define UINT32_ALIGN_MASK       (3Lu)

/* Defines supported parameter types */
#define DS_PARAM_TYPE_UINT8     (0x01u)
#define DS_PARAM_TYPE_UINT16    (0x02u)
#define DS_PARAM_TYPE_UINT32    (0x03u)


/* Defines PARAM_ID structure */
typedef struct
{
    uint16 offset;      /* parameter offset */
    uint8  widgetId;    /* widget Id parameter belongs to */
    uint8  affectsCrc;  /* parameter affects widget CRC */
    uint8  crc;         /* parameter CRC */
    uint8  flash;       /* parameter located in FLASH flag */
    uint8  rw;          /* parameter is read/write flag */
    uint8  type;        /* parameter type: uint8/uint16/uint32 */
} PARAM_ID_STRUCT;


/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/
/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/



static cystatus DsParseParamId(uint32 paramId, PARAM_ID_STRUCT *pData);

/** \}
* \endcond */


/*******************************************************************************
* Function Name: Input_Capsense_DsInitialize
****************************************************************************//**
*
* \brief
*   This function initializes the Data Structure storage.
*
* \details
*   This function copies the default widget configuration parameters
*   from the Flash storage into the RAM Data Structure.
*
*******************************************************************************/
void Input_Capsense_DsInitialize(void)
{
    #if ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || \
         (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) || \
        ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && \
         (Input_Capsense_ENABLE == Input_Capsense_CSX_SKIP_OVSMPL_SPECIFIC_NODES)))
        uint32 snsId;
        uint32 wdgtId;
        Input_Capsense_RAM_SNS_STRUCT * ptrSnsTmp;
        Input_Capsense_FLASH_WD_STRUCT const * ptrFlashWdgt;
    #endif

    #if ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && \
         (Input_Capsense_ENABLE == Input_Capsense_CSX_SKIP_OVSMPL_SPECIFIC_NODES))
        uint16 subConvNumber;
    #endif

    #if ((0u != Input_Capsense_CSX_EN) || (0 != Input_Capsense_CSD_IDAC_COMP_EN))
        uint8 const * ptrIdacInit = Input_Capsense_ramIdacInit;
    #endif

    /* Reset RAM data structure content */
    (void)memset(&Input_Capsense_dsRam, 0, sizeof(Input_Capsense_dsRam));

    /* Initialize configId, deviceId and hwClock registers */
    Input_Capsense_dsRam.configId = Input_Capsense_CONFIG_ID;
    Input_Capsense_dsRam.deviceId = Input_Capsense_DEVICE_ID;
    Input_Capsense_dsRam.hwClock = Input_Capsense_HW_CLOCK;

    /* Initialize global RAM data */
    Input_Capsense_dsRam.csd0Config = Input_Capsense_CSD0_CONFIG;

    Input_Capsense_dsRam.scanCurrentISC = Input_Capsense_SNS_CONNECTION_UNDEFINED;
    #if (0u != Input_Capsense_TOTAL_CSD_WIDGETS)
        Input_Capsense_dsRam.modCsdClk = Input_Capsense_CSD_SCANSPEED_DIVIDER;
        Input_Capsense_dsRam.scanCsdISC = Input_Capsense_CSD_INACTIVE_SNS_CONNECTION;

        #if (0u != Input_Capsense_CSD_COMMON_SNS_CLK_EN)
            Input_Capsense_dsRam.snsCsdClk = Input_Capsense_CSD_SNS_CLK_DIVIDER;
        #endif /* #if (0u != Input_Capsense_CSD_COMMON_SNS_CLK_EN) */
    #endif /* #if (0u != Input_Capsense_TOTAL_CSD_WIDGETS) */

    #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
        Input_Capsense_dsRam.modCsxClk = Input_Capsense_CSX_SCANSPEED_DIVIDER;
        Input_Capsense_dsRam.scanCsxISC = Input_Capsense_CSX_INACTIVE_SNS_CONNECTION;

        #if (0u != Input_Capsense_CSX_COMMON_TX_CLK_EN)
            Input_Capsense_dsRam.snsCsxClk = Input_Capsense_CSX_TX_CLK_DIVIDER;
        #endif /* #if (0u != Input_Capsense_CSX_COMMON_TX_CLK_EN) */
    #endif /* #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN) */

    #if (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
        Input_Capsense_dsRam.modIsxClk = Input_Capsense_ISX_SCANSPEED_DIVIDER;
    #endif /* #if (0u != Input_Capsense_ISX_EN) */

    #if (0u != Input_Capsense_SELF_TEST_EN)

        Input_Capsense_dsRam.glbCrc = Input_Capsense_GLB_CRC;
        Input_Capsense_dsRam.selfTestConfig.fineInitTime = (uint8)Input_Capsense_TST_FINE_INIT_TIME;
        Input_Capsense_dsRam.selfTestConfig.startupDelay = Input_Capsense_TST_ANALOG_STARTUP_DELAY_US;

        #if (0u != Input_Capsense_TST_SNS_SHORT_EN)
            Input_Capsense_dsRam.selfTestConfig.snsShortTimeUs = Input_Capsense_TST_SNS_SHORT_TIME;
        #endif

        #if ((0u != Input_Capsense_TST_SNS_CAP_EN) ||\
             (0u != Input_Capsense_TST_SH_CAP_EN))
            Input_Capsense_dsRam.selfTestConfig.snsCapSnsClkDivider = Input_Capsense_TST_SNS_CAP_SNS_CLK_DIVIDER;
            Input_Capsense_dsRam.selfTestConfig.snsCapSnsClkHz = Input_Capsense_TST_SNS_CAP_SNS_CLK_HZ;
            Input_Capsense_dsRam.selfTestConfig.snsCapResolution = Input_Capsense_TST_SNS_CAP_RESOLUTION;
            Input_Capsense_dsRam.selfTestConfig.snsCapVrefGain = Input_Capsense_TST_SNS_CAP_VREF_GAIN ;
            Input_Capsense_dsRam.selfTestConfig.snsCapVrefVoltage = Input_Capsense_TST_SNS_CAP_VREF_MV;
            Input_Capsense_dsRam.selfTestConfig.snsCapModClkDivider = Input_Capsense_TST_MOD_CLK_DIVIDER ;
            Input_Capsense_dsRam.selfTestConfig.snsCapModClkKHz = Input_Capsense_TST_MOD_CLK_KHZ ;
        #endif /* ((0u != Input_Capsense_TST_SNS_CAP_EN) ||
                   (0u != Input_Capsense_TST_SH_CAP_EN)) */

        #if (0u != Input_Capsense_TST_SNS_CAP_EN)
            #if (0u != Input_Capsense_CSD_EN)
                Input_Capsense_dsRam.selfTestConfig.bistCsdSnsCapISC = Input_Capsense_SNS_CAP_CSD_INACTIVE_CONNECTION;
            #endif /* (0u != Input_Capsense_CSD_EN) */
            #if (0u != Input_Capsense_CSX_EN)
                Input_Capsense_dsRam.selfTestConfig.bistCsxSnsCapISC = Input_Capsense_SNS_CAP_CSX_INACTIVE_CONNECTION;
            #endif /* (0u != Input_Capsense_CSX_EN) */
        #endif /* (0u != Input_Capsense_TST_SNS_CAP_EN) */

        #if (0u != Input_Capsense_TST_SH_CAP_EN)
            #if ((0u != Input_Capsense_CSD_EN) && (0u != Input_Capsense_CSD_SHIELD_EN))
                Input_Capsense_dsRam.selfTestConfig.bistCsdShCapISC = Input_Capsense_SHIELD_CAP_INACTIVE_CONNECTION;
            #endif /* ((0u != Input_Capsense_CSD_EN) && (0u != Input_Capsense_CSD_SHIELD_EN)) */
        #endif /* (0u != Input_Capsense_TST_SH_CAP_EN) */

        #if (0u != Input_Capsense_TST_EXTERNAL_CAP_EN)
            Input_Capsense_dsRam.selfTestConfig.extCapVrefGain = Input_Capsense_TST_EXT_CAP_VREF_GAIN;
            Input_Capsense_dsRam.selfTestConfig.extCapVrefVoltage = Input_Capsense_TST_EXT_CAP_VREF_MV;
        #endif /* #if (0u != Input_Capsense_TST_EXTERNAL_CAP_EN) */

        #if (0u != Input_Capsense_TST_VDDA_EN)
            Input_Capsense_dsRam.selfTestConfig.vddaResolution = Input_Capsense_TST_VDDA_RESOLUTION;
            Input_Capsense_dsRam.selfTestConfig.vddaModClkDivider = Input_Capsense_TST_VDDA_MOD_CLK_DIVIDER;

            Input_Capsense_dsRam.selfTestConfig.vddaVrefGain = Input_Capsense_TST_VDDA_VREF_GAIN;
            Input_Capsense_dsRam.selfTestConfig.vddaVrefVoltage = Input_Capsense_TST_VDDA_VREF_MV;
        #endif /* #if (0u != Input_Capsense_TST_VDDA_EN) */

    #endif /* #if (0u != Input_Capsense_SELF_TEST_EN) */

    /* Initialize RAM widget data */
    Input_Capsense_dsRam.wdgtList = Input_Capsense_ramWidgetInit;

    /* Initialize Gesture configuration structure */
    #if ((0u != Input_Capsense_GES_GLOBAL_EN) || (0u != Input_Capsense_BALLISTIC_MULTIPLIER_EN))
        Input_Capsense_dsRam.timestampInterval = Input_Capsense_TIMESTAMP_INTERVAL;
    #endif /* ((0u != Input_Capsense_GES_GLOBAL_EN) || (0u != Input_Capsense_BALLISTIC_MULTIPLIER_EN)) */

    #if (0u != Input_Capsense_GES_GLOBAL_EN)
        Input_Capsense_dsRam.gestures = Input_Capsense_ramGesturesInit;
    #endif /* (0u != Input_Capsense_GES_GLOBAL_EN) */

    #if (0u != Input_Capsense_BALLISTIC_MULTIPLIER_EN)
        Input_Capsense_dsRam.ballisticConfig = Input_Capsense_ramBallisticInit;
    #endif /* (0u != Input_Capsense_BALLISTIC_MULTIPLIER_EN) */

    #if (0u != Input_Capsense_CSX_EN) || (0 != Input_Capsense_CSD_IDAC_COMP_EN)
        /* Initialize IDAC data */
        ptrFlashWdgt = Input_Capsense_dsFlash.wdgtArray;

        for (wdgtId = Input_Capsense_TOTAL_WIDGETS; wdgtId-- > 0u; )
        {
            ptrSnsTmp = ptrFlashWdgt->ptr2SnsRam;

            for (snsId = Input_Capsense_GET_SNS_CNT_BY_PTR(ptrFlashWdgt); snsId-- > 0u;)
            {
                ptrSnsTmp->idacComp[0u] = *ptrIdacInit;
                ptrIdacInit++;

                #if (0u != Input_Capsense_MULTI_FREQ_SCAN_EN)
                    ptrSnsTmp->idacComp[1u] = *ptrIdacInit;
                    ptrIdacInit++;

                    ptrSnsTmp->idacComp[2u] = *ptrIdacInit;
                    ptrIdacInit++;
                #endif /* #if (0u != Input_Capsense_MULTI_FREQ_SCAN_EN) */

                ptrSnsTmp++;
            }

            ptrFlashWdgt++; /* Move to next widget */
        }
    #endif /*(0u != Input_Capsense_CSX_EN) || (0 != Input_Capsense_CSD_IDAC_COMP_EN)*/

    #if ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && \
         (Input_Capsense_ENABLE == Input_Capsense_CSX_SKIP_OVSMPL_SPECIFIC_NODES))
        /* Initialize Sub-Conversion Number for each node of each CSX widget */
        ptrFlashWdgt = Input_Capsense_dsFlash.wdgtArray;
        for (wdgtId = Input_Capsense_TOTAL_WIDGETS; wdgtId-- > 0u;)
        {
            /* Check for widget sense method */
            if (Input_Capsense_SENSE_METHOD_CSX_E == Input_Capsense_GET_SENSE_METHOD(ptrFlashWdgt))
            {
                /* Take the sub-convesion number of a CSX widget and initialize each node of this widget */
                subConvNumber = ((Input_Capsense_RAM_WD_BASE_STRUCT *)(ptrFlashWdgt->ptr2WdgtRam))->resolution;
                ptrSnsTmp = ptrFlashWdgt->ptr2SnsRam;
                for (snsId = Input_Capsense_GET_SNS_CNT_BY_PTR(ptrFlashWdgt); snsId-- > 0u;)
                {
                    ptrSnsTmp->subConvNum = subConvNumber;
                    ptrSnsTmp++;
                }
            }
            /* Move to the next widget */
            ptrFlashWdgt++;
        }
    #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && \
               (Input_Capsense_ENABLE == Input_Capsense_CSX_SKIP_OVSMPL_SPECIFIC_NODES)) */

    #if (0u != Input_Capsense_ADC_EN)
        Input_Capsense_AdcDsInitialize();
    #endif /* (0u != Input_Capsense_ADC_EN) */
}


#if (0u != Input_Capsense_ADC_EN)
    /*******************************************************************************
    * Function Name: Input_Capsense_AdcDsInitialize
    ****************************************************************************//**
    *
    * \brief
    *   Configures the initial Adc datastructure members.
    *
    *******************************************************************************/
    void Input_Capsense_AdcDsInitialize(void)
    {
        Input_Capsense_dsRam.adcResolution = Input_Capsense_ADC_RESOLUTION;
        Input_Capsense_dsRam.adcIdac = (uint8)(Input_Capsense_ADC_IDAC_DEFAULT);
        Input_Capsense_dsRam.adcActiveCh = Input_Capsense_AdcNO_CHANNEL;
    }
#endif /* (0u != Input_Capsense_ADC_EN) */


/*******************************************************************************
* Function Name: DsParseParamId
****************************************************************************//**
*
* \brief
*   This function parses the parameter ID and checks its correctness.
*
* \details
*   This function checks the parameter CRC if the self-test is enabled,
*   validates the offset value and parameter type.
*
* \param paramId The parameter to parse.
* \param pData   The pointer to the structure that will hold parsed data.
*
* \return CYRET_SUCCESS     If the parameter is valid
*         CYRET_BAD_PARAM   If the parameter is invalid
*
*******************************************************************************/
static cystatus DsParseParamId(uint32 paramId, PARAM_ID_STRUCT *pData)
{
    cystatus result = CYRET_SUCCESS;

    #if (0u != Input_Capsense_SELF_TEST_EN)
        const uint8 crcTable[] =
        {
            0x00u, 0x09u, 0x0Bu, 0x02u, 0x0Fu, 0x06u, 0x04u, 0x0Du,
            0x07u, 0x0Eu, 0x0Cu, 0x05u, 0x08u, 0x01u, 0x03u, 0x0Au
        };

        uint32 i;
        uint32 actualCrc = 0u;
        uint32 crcIndex;
    #endif /* #if (0u != Input_Capsense_SELF_TEST_EN) */

    /* Extract parameter data */
    pData->offset     = LO16(paramId);
    pData->affectsCrc = LO8((paramId & PARAM_UBIT_MASK)  >> PARAM_UBIT_OFFSET);
    pData->widgetId   = LO8((paramId & PARAM_WDID_MASK)  >> PARAM_WDID_OFFSET);
    pData->type       = LO8((paramId & PARAM_TYPE_MASK)  >> PARAM_TYPE_OFFSET);
    pData->flash      = LO8((paramId & PARAM_FBIT_MASK)  >> PARAM_FBIT_OFFSET);
    pData->rw         = LO8((paramId & PARAM_RWBIT_MASK) >> PARAM_RWBIT_OFFSET);
    pData->crc        = LO8((paramId & PARAM_CRC_MASK)   >> PARAM_CRC_OFFSET);

    /* Check parameter CRC if self-test is enabled */
    #if (0u != Input_Capsense_SELF_TEST_EN)

        /* Calculate CRC for bits 0..24.
         * The CRC is calculated using nibbles (4-bits).
         * So for 0..24 bits there are in total 6 nibbles. */
        for (i = 6u; i > 0u; i--)
        {
            crcIndex = actualCrc ^ (paramId & 0x0Fu);
            actualCrc = crcTable[crcIndex];
            paramId >>= 4u;
        }

        /* Add bits 28..32 */
        crcIndex = actualCrc ^ ((paramId >> 4u) & 0x0Fu);
        actualCrc = crcTable[crcIndex];

        /* Add bits 24..28 (CRC) */
        crcIndex = actualCrc ^ (paramId & 0x0Fu);
        actualCrc = crcTable[crcIndex];

        if (0u != actualCrc)
        {
            /* CRC mismatch */
            result = CYRET_BAD_PARAM;
        }

        if ((CYRET_SUCCESS == result) &&
            (0u != pData->affectsCrc) && (pData->widgetId >= Input_Capsense_TOTAL_WIDGETS ))
        {
            /* Wrong widgetId for protected parameter */
            result = CYRET_BAD_PARAM;
        }

        /* Check offset value range */
        if (CYRET_SUCCESS == result)
        {
            if (0u == pData->flash)
            {
                /* Check offset for RAM Data Structure range */
                if (pData->offset >= sizeof(Input_Capsense_dsRam))
                {
                    result = CYRET_BAD_PARAM;
                }
            }
            else
            {
                /* Check offset for Flash Data Structure range */
                if (pData->offset >= sizeof(Input_Capsense_dsFlash))
                {
                    result = CYRET_BAD_PARAM;
                }

                /* Check if it is marked as Read Only */
                if (0u != pData->rw)
                {
                    result = CYRET_BAD_PARAM;
                }
            }
        }
    #else /* #if (0u != Input_Capsense_SELF_TEST_EN) */
        /* Check offset value range */
        if (0u == pData->flash)
        {
            /* Check offset for RAM Data Structure range */
            if (pData->offset >= sizeof(Input_Capsense_dsRam))
            {
                result = CYRET_BAD_PARAM;
            }
        }
        else
        {
            /* Check offset for Flash Data Structure range */
            if (pData->offset >= sizeof(Input_Capsense_dsFlash))
            {
                result = CYRET_BAD_PARAM;
            }

            /* Check if it is marked as Read Only */
            if (0u != pData->rw)
            {
                result = CYRET_BAD_PARAM;
            }
        }
    #endif /* #if (0u != Input_Capsense_SELF_TEST_EN) */

    if (CYRET_SUCCESS == result)
    {
        /* Check parameter type, offset alignment */
        switch (pData->type)
        {
        case DS_PARAM_TYPE_UINT16:
            if (0u != (pData->offset & UINT16_ALIGN_MASK))
            {
                result = CYRET_BAD_PARAM;
            }
            break;

        case DS_PARAM_TYPE_UINT32:
            if (0u != (pData->offset & UINT32_ALIGN_MASK))
            {
                result = CYRET_BAD_PARAM;
            }
            break;

        case DS_PARAM_TYPE_UINT8:
            break;

        default:
            result = CYRET_BAD_PARAM;
            break;
        }
    }

    return result;
}

/*******************************************************************************
* Function Name: Input_Capsense_GetParam
****************************************************************************//**
*
* \brief
*  Gets the specified parameter value from the \ref group_structures.
*
* \details
*  This function gets the value of the specified parameter by the paramId
*  argument. The paramId for each register is available in the
*  Input_Capsense RegisterMap header file as
*  Input_Capsense_<ParameterName>_PARAM_ID. The paramId is a special
*  enumerated value generated by the customizer. The format of paramId is as
*  follows:
*    1. [ byte 3 byte 2 byte 1 byte 0 ]
*    2. [ TTWFCCCC UIIIIIII MMMMMMMM LLLLLLLL ]
*    3. T - encodes the parameter type:
*      - 01b: uint8
*      - 10b: uint16
*      - 11b: uint32
*    4. W - indicates whether the parameter is writable:
*      - 0: ReadOnly
*      - 1: Read/Write
*    5. C - 4 bit CRC (X^3 + 1) of the whole paramId word, the C bits are
*       filled with 0s when the CRC is calculated.
*    6. U - indicates if the parameter affects the RAM Widget Object CRC.
*    7. I - specifies that the widgetId parameter belongs to
*    8. M,L - the parameter offset MSB and LSB accordingly in:
*      - Flash Data Structure if W bit is 0.
*      - RAM Data Structure if W bit is 1.
*
*  Refer to the \ref group_structures section for details of the data structure
*  organization and examples of its register access.
*
* \param paramId
*  Specifies the ID of parameter to get its value.
*  A macro for the parameter ID can be found in the Input_Capsense RegisterMap header
*  file defined as Input_Capsense_<ParameterName>_PARAM_ID.
*
* \param value
*  The pointer to a variable to be updated with the obtained value.
*
* \return
*  Returns the status of the operation:
*    - CYRET_SUCCESS - The operation is successfully completed.
*    - CYRET_BAD_PARAM - The input parameter is invalid.
*
*******************************************************************************/
cystatus Input_Capsense_GetParam(uint32 paramId, uint32 *value)
{
    PARAM_ID_STRUCT pData;
    cystatus result;

    union
    {
        volatile void   const * ptr;
        volatile uint8  const * ptrUint8;
        volatile uint16 const * ptrUint16;
        volatile uint32 const * ptrUint32;
    } ptrData;

    result = DsParseParamId(paramId, &pData);

    /* Parse and validate paramId */
    if (CYRET_SUCCESS == result)
    {
        /* Get base address of parameter */
        if (0u == pData.flash)
        {
            ptrData.ptr = &Input_Capsense_dsRam;
        }
        else
        {
            ptrData.ptr = &Input_Capsense_dsFlash;
        }

        /* Add offset to base address */
        ptrData.ptrUint8 += pData.offset;

        /* Read data */
        if (DS_PARAM_TYPE_UINT8 == pData.type)
        {
            *value = (uint32) (*ptrData.ptrUint8);
        }
        else if (DS_PARAM_TYPE_UINT16 == pData.type)
        {
            *value = (uint32) (*ptrData.ptrUint16);
        }
        else if (DS_PARAM_TYPE_UINT32 == pData.type)
        {
            *value = *ptrData.ptrUint32;
        }
        else
        {
            /* Parameter comes here already validated. */
            CYASSERT(0u);
        }
    }

    return result;
}


/*******************************************************************************
* Function Name: Input_Capsense_SetParam
****************************************************************************//**
*
* \brief
*  Sets a new value for the specified parameter in the \ref group_structures.
*
* \details
*  This function sets the value of the specified parameter by the paramId
*  argument. The paramId for each register is available in the
*  Input_Capsense RegisterMap header file as
*  Input_Capsense_<ParameterName>_PARAM_ID. The paramId is a special
*  enumerated value generated by the customizer. The format of paramId is as
*  follows:
*    1. [ byte 3 byte 2 byte 1 byte 0 ]
*    2. [ TTWFCCCC UIIIIIII MMMMMMMM LLLLLLLL ]
*    3. T - encodes the parameter type:
*      - 01b: uint8
*      - 10b: uint16
*      - 11b: uint32
*    4. W - indicates whether the parameter is writable:
*      - 0: ReadOnly
*      - 1: Read/Write
*    5. C - 4 bit CRC (X^3 + 1) of the whole paramId word, the C bits are
*       filled with 0s when the CRC is calculated.
*    6. U - indicates if the parameter affects the RAM Widget Object CRC.
*    7. I - specifies that the widgetId parameter belongs to
*    8. M,L - the parameter offset MSB and LSB accordingly in:
*      - Flash Data Structure if W bit is 0.
*      - RAM Data Structure if W bit is 1.
*
*  Refer to the \ref group_structures section for details of the data structure
*  organization and examples of its register access.
*
*  This function writes specified value into the desired register without
*  other registers update. It is application layer responsibility to keep all
*  the data structure registers aligned. Repeated call of
*  Input_Capsense_Start() function helps aligning dependent register values.
*
* \param paramId
*  Specifies the ID of parameter to set its value.
*  A macro for the parameter ID can be found in the Input_Capsense RegisterMap header
*  file defined as Input_Capsense_<ParameterName>_PARAM_ID.

* \param value
*  Specifies the new parameter's value.
*
* \return
*  Returns the status of the operation:
*    - CYRET_SUCCESS - The operation is successfully completed.
*    - CYRET_BAD_PARAM - The input parameter is invalid.
*
*******************************************************************************/
cystatus Input_Capsense_SetParam(uint32 paramId, uint32 value)
{
    cystatus result;
    PARAM_ID_STRUCT pData;

    union
    {
        volatile void   * ptr;
        volatile uint8  * ptrUint8;
        volatile uint16 * ptrUint16;
        volatile uint32 * ptrUint32;
    } ptrData;

    result = DsParseParamId(paramId, &pData);

    /* verify if parameter is writable */
    if (CYRET_SUCCESS == result)
    {
        if (0u == pData.rw)
        {
            result = CYRET_BAD_PARAM;
        }
    }

    /* Parse and validate paramId */
    if (CYRET_SUCCESS == result)
    {
        /* Get base address of parameter */
        ptrData.ptr = &Input_Capsense_dsRam;

        /* Add offset to base address */
        ptrData.ptrUint8 += pData.offset;

        /* Write data */
        if (DS_PARAM_TYPE_UINT8 == pData.type)
        {
            *ptrData.ptrUint8 = LO8(value);
        }
        else if (DS_PARAM_TYPE_UINT16 == pData.type)
        {
            *ptrData.ptrUint16 = LO16(value);
        }
        else if (DS_PARAM_TYPE_UINT32 == pData.type)
        {
            *ptrData.ptrUint32 = value;
        }
        else
        {
            /* Parameter comes here already validated. */
            CYASSERT(0u);
        }

        #if (Input_Capsense_ENABLE == (Input_Capsense_TST_WDGT_CRC_EN || Input_Capsense_TST_GLOBAL_CRC_EN))
            /* Update widget or global CRC if self-test is enabled and parameter affects it */
            if (0u != pData.affectsCrc)
            {
                if ((ptrData.ptrUint16 >= &Input_Capsense_dsRam.csd0Config) &&
                    (ptrData.ptrUint16 <  &Input_Capsense_dsRam.glbCrc))
                {

                    #if (Input_Capsense_ENABLE == Input_Capsense_TST_GLOBAL_CRC_EN)
                        Input_Capsense_DsUpdateGlobalCrc();
                    #endif /* (Input_Capsense_ENABLE == Input_Capsense_TST_GLOBAL_CRC_EN) */

                }
                else
                {
                    #if (Input_Capsense_ENABLE == Input_Capsense_TST_WDGT_CRC_EN)
                        Input_Capsense_DsUpdateWidgetCrc((uint32)pData.widgetId);
                    #endif /* (Input_Capsense_ENABLE == Input_Capsense_TST_WDGT_CRC_EN) */
                }
            }
        #endif /* (Input_Capsense_ENABLE == (Input_Capsense_TST_WDGT_CRC_EN || Input_Capsense_TST_GLOBAL_CRC_EN)) */
    }

    return result;
}

/*******************************************************************************
* Function Name: Input_Capsense_IsAnyWidgetActive
****************************************************************************//**
*
* \brief
*  Reports if any widget has detected a touch.
*
* \details
*  This function reports if any widget has detected a touch or not by extracting
*  information from the wdgtStatus registers
*  (Input_Capsense_WDGT_STATUS<X>_VALUE). This function does not process a
*  widget but extracts processed results from the \ref group_structures.
*
* \return
*   Returns the touch detection status of all the widgets:
*     - Zero - No touch is detected in all the widgets or sensors.
*     - Non-zero - At least one widget or sensor detected a touch.
*
*******************************************************************************/
uint32 Input_Capsense_IsAnyWidgetActive(void)
{
    uint32 result = 0Lu;
    uint32 wdWord;

    for (wdWord = Input_Capsense_WDGT_STATUS_WORDS; wdWord-- > 0u;)
    {
        result |= Input_Capsense_dsRam.wdgtStatus[wdWord];
    }

    return result;
}


/*******************************************************************************
* Function Name: Input_Capsense_IsWidgetActive
****************************************************************************//**
*
* \brief
*  Reports if the specified widget detects a touch on any of its sensors.
*
* \details
*  This function reports if the specified widget has detected a touch or not by
*  extracting information from the wdgtStatus registers
*  (Input_Capsense_WDGT_STATUS<X>_VALUE). This function does not process the
*  widget but extracts processed results from the \ref group_structures.
*
* \param widgetId
*  Specifies the ID number of the widget to get its status.
*  A macro for the widget ID can be found in the Input_Capsense Configuration header
*  file defined as Input_Capsense_<WidgetName>_WDGT_ID.
*
* \return
*  Returns the touch detection status of the specified widgets:
*    - Zero - No touch is detected in the specified widget or a wrong widgetId
*      is specified.
*    - Non-zero if at least one sensor of the specified widget is active, i.e.
*      a touch is detected.
*
*******************************************************************************/
uint32 Input_Capsense_IsWidgetActive(uint32 widgetId)
{
    uint32 result = 0Lu;

    if (widgetId < Input_Capsense_TOTAL_WIDGETS)
    {
        result = Input_Capsense_GET_WIDGET_ACTIVE_STATUS(widgetId);
    }
    return result;
}


/*******************************************************************************
* Function Name: Input_Capsense_IsSensorActive
****************************************************************************//**
*
* \brief
*  Reports if the specified sensor in the widget detects a touch.
*
* \details
*  This function reports if the specified sensor in the widget has detected a
*  touch or not by extracting information from the wdgtStatus registers
*  (Input_Capsense_WDGT_STATUS<X>_VALUE). This function does not process the
*  widget or sensor but extracts processed results from the \ref group_structures.
*
*  For proximity sensors, this function returns the proximity detection status. To
*  get the finger touch status of proximity sensors, use the
*  Input_Capsense_IsProximitySensorActive() function.
*
* \param widgetId
*  Specifies the ID number of the widget.
*  A macro for the widget ID can be found in the Input_Capsense Configuration header
*  file defined as Input_Capsense_<WidgetName>_WDGT_ID.

* \param sensorId
*  Specifies the ID number of the sensor within the widget to get its touch
*  detection status.
*  A macro for the sensor ID within the specified widget can be found in the
*  Input_Capsense Configuration header file defined as
*  Input_Capsense_<WidgetName>_SNS<SensorNumber>_ID.
*
* \return
*  Returns the touch detection status of the specified sensor / widget:
*    - Zero if no touch is detected in the specified sensor / widget or a wrong
*      widget ID / sensor ID is specified.
*    - Non-zero if the specified sensor is active i.e. touch is detected. If the
*      specific sensor belongs to a proximity widget, the proximity detection
*      status is returned.
*
*******************************************************************************/
uint32 Input_Capsense_IsSensorActive(uint32 widgetId, uint32 sensorId)
{
    uint32 result = 0Lu;

    if ((widgetId < Input_Capsense_TOTAL_WIDGETS) &&
        (sensorId < Input_Capsense_GET_SENSOR_COUNT(widgetId)))
    {
        #if (Input_Capsense_ENABLE == Input_Capsense_PROXIMITY_WIDGET_EN)
            if (Input_Capsense_WD_PROXIMITY_E ==
                (Input_Capsense_WD_TYPE_ENUM)Input_Capsense_dsFlash.wdgtArray[widgetId].wdgtType)
            {
                sensorId = Input_Capsense_PROX_STS_OFFSET(sensorId);
            }
        #endif /* (Input_Capsense_ENABLE != Input_Capsense_PROXIMITY_WIDGET_EN) */
        result = Input_Capsense_dsRam.snsStatus[widgetId] & (1Lu << sensorId);
    }

    return result;
}

#if (0u != Input_Capsense_MATRIX_WIDGET_EN)
/*******************************************************************************
* Function Name: Input_Capsense_IsMatrixButtonsActive
****************************************************************************//**
*
* \brief
*  Reports the status of the specified matrix button widget.
*
* \details
*  This function reports if the specified matrix widget has detected a touch or
*  not by extracting information from the wdgtStatus registers
*  (Input_Capsense_WDGT_STATUS<X>_VALUE for the CSD widgets and
*  Input_Capsense_SNS_STATUS<WidgetId>_VALUE for CSX widget). In addition, the
*  function provides details of the active sensor including active rows/columns
*  for the CSD widgets. This function is used only with the matrix button
*  widgets. This function does not process the widget but extracts
*  processed results from the \ref group_structures.
*
* \param widgetId
*  Specifies the ID number of the matrix button widget to check the status of its
*  sensors.
*  A macro for the widget ID can be found in the Input_Capsense Configuration header file
*  defined as Input_Capsense_<WidgetName>_WDGT_ID
*
* \return
*  Returns the touch detection status of the sensors in the specified matrix
*  buttons widget. Zero indicates that no touch is detected in the specified
*  widget or a wrong widgetId is specified.
*    1. For the matrix buttons widgets with the CSD sensing mode:
*      - Bit [31] if set, indicates that one or more sensors in the widget
*        detected a touch.
*      - Bits [30..24] are reserved
*      - Bits [23..16] indicate the logical sensor number of the sensor that
*        detected a touch. If more than one sensor detected a touch for the CSD
*        widget, no status is reported because more than one touch is invalid for the
*        CSD matrix buttons widgets.
*      - Bits [15..8] indicate the active row number.
*      - Bits [7..0] indicate the active column number.
*    2. For the matrix buttons widgets with the CSX widgets, each bit (31..0)
*      corresponds to the TX/RX intersection.
*
*******************************************************************************/
uint32 Input_Capsense_IsMatrixButtonsActive(uint32 widgetId)
{
    uint32 result = 0Lu;
    cystatus state = CYRET_SUCCESS;
    Input_Capsense_FLASH_WD_STRUCT const *ptrFlashWdgt = 0u;

    #if (0u != Input_Capsense_CSD_MATRIX_WIDGET_EN)
        Input_Capsense_RAM_WD_CSD_MATRIX_STRUCT *wdCsdMatrix;
    #endif

    if (widgetId >= Input_Capsense_TOTAL_WIDGETS)
    {
        state = CYRET_BAD_PARAM;
    }
    else
    {
        ptrFlashWdgt = &Input_Capsense_dsFlash.wdgtArray[widgetId];

        if ((Input_Capsense_WD_TYPE_ENUM)ptrFlashWdgt->wdgtType != Input_Capsense_WD_MATRIX_BUTTON_E)
        {
            state = CYRET_BAD_PARAM;
        }
        else if (0u == Input_Capsense_GET_WIDGET_ACTIVE_STATUS(widgetId))
        {
            state = CYRET_BAD_PARAM;
        }
        else
        {
            /* input parameters are OK */
        }
    }

    if (CYRET_SUCCESS == state)
    {
        switch(Input_Capsense_GET_SENSE_METHOD(ptrFlashWdgt))
        {
        #if (0u != Input_Capsense_CSD_MATRIX_WIDGET_EN)
            case Input_Capsense_SENSE_METHOD_CSD_E:
                wdCsdMatrix = ptrFlashWdgt->ptr2WdgtRam;

                result = Input_Capsense_MATRIX_BUTTONS_TOUCHED |
                         ((uint32)wdCsdMatrix->posSnsId << 16u)  |
                         ((uint32)wdCsdMatrix->posRow   << 8u)   |
                         (uint32)wdCsdMatrix->posCol;
                break;
        #endif /* #if (0u != Input_Capsense_CSD_MATRIX_WIDGET_EN) */

        #if (0u != Input_Capsense_CSX_MATRIX_WIDGET_EN)
            case Input_Capsense_SENSE_METHOD_CSX_E:
                result = Input_Capsense_dsRam.snsStatus[widgetId];
                break;
        #endif /* #if (0u != Input_Capsense_CSX_MATRIX_WIDGET_EN) */

        default:
            CYASSERT(0u);
            break;
        }
    }

    return result;
}
#endif /* #if (0u != Input_Capsense_MATRIX_WIDGET_EN) */

#if (0u != Input_Capsense_PROXIMITY_WIDGET_EN)
/*******************************************************************************
* Function Name: Input_Capsense_IsProximitySensorActive
****************************************************************************//**
*
* \brief
*  Reports the finger detection status of the specified proximity widget/sensor.
*
* \details
*  This function reports if the specified proximity sensor has detected a touch
*  or not by extracting information from the wdgtStatus registers
*  (Input_Capsense_SNS_STATUS<WidgetId>_VALUE). This function is used
*  only with proximity sensor widgets. This function does not process the
*  widget but extracts processed results from the \ref group_structures.
*
* \param widgetId
*  Specifies the ID number of the proximity widget.
*  A macro for the widget ID can be found in the Input_Capsense Configuration header
*  file defined as Input_Capsense_<WidgetName>_WDGT_ID
*
* \param proxId
*  Specifies the ID number of the proximity sensor within the proximity widget to
*  get its touch detection status.
*  A macro for the proximity ID within a specified widget can be found in the
*  Input_Capsense Configuration header file defined as
*  Input_Capsense_<WidgetName>_SNS<SensorNumber>_ID
*
* \return
*  Returns the status of the specified sensor of the proximity widget. Zero
*  indicates that no touch is detected in the specified sensor / widget or a
*  wrong widgetId / proxId is specified.
*    - Bits [31..2] are reserved.
*    - Bit [1] indicates that a touch is detected.
*    - Bit [0] indicates that a proximity is detected.
*
*******************************************************************************/
uint32 Input_Capsense_IsProximitySensorActive(uint32 widgetId, uint32 proxId)
{
    uint32 result = 0Lu;

    if ((widgetId < Input_Capsense_TOTAL_WIDGETS) && (proxId < Input_Capsense_GET_SENSOR_COUNT(widgetId)) &&
        (Input_Capsense_WD_PROXIMITY_E ==
            (Input_Capsense_WD_TYPE_ENUM)Input_Capsense_dsFlash.wdgtArray[widgetId].wdgtType))
    {
        result = Input_Capsense_dsRam.snsStatus[widgetId];
        result >>= Input_Capsense_PROX_STS_OFFSET(proxId);
        result &=  Input_Capsense_PROX_STS_MASK;
    }

    return result;
}
#endif /* #if (0u != Input_Capsense_PROXIMITY_WIDGET_EN) */


#if (0u != Input_Capsense_SLIDER_WIDGET_EN)
/*******************************************************************************
* Function Name: Input_Capsense_GetCentroidPos
****************************************************************************//**
*
* \brief
*  Reports the centroid position for the specified slider widget.
*
* \details
*  This function reports the centroid value of a specified radial or linear
*  slider widget by extracting information from the wdgtStatus registers
*  (Input_Capsense_<WidgetName>_POSITION<X>_VALUE). This function is
*  used only with radial or linear slider widgets. This function does not
*  process the widget but extracts processed results from the \ref group_structures.
*
* \param widgetId
*  Specifies the ID number of a slider widget to get the centroid of the
*  detected touch.
*  A macro for the widget ID can be found in the
*  Input_Capsense Configuration header file defined as
*  Input_Capsense_<WidgetName>_WDGT_ID
*
* \return
*  Returns the centroid position of a specified slider widget:
*    - The centroid position if a touch is detected.
*    - Input_Capsense_SLIDER_NO_TOUCH - No touch is detected or a wrong
*      widgetId is specified.
*
*******************************************************************************/
uint32 Input_Capsense_GetCentroidPos(uint32 widgetId)
{
    uint32 result = Input_Capsense_SLIDER_NO_TOUCH;
    Input_Capsense_RAM_WD_SLIDER_STRUCT *wdSlider;

    if ((widgetId < Input_Capsense_TOTAL_WIDGETS) &&
        ((Input_Capsense_WD_LINEAR_SLIDER_E ==
            (Input_Capsense_WD_TYPE_ENUM)Input_Capsense_dsFlash.wdgtArray[widgetId].wdgtType) ||
         (Input_Capsense_WD_RADIAL_SLIDER_E ==
            (Input_Capsense_WD_TYPE_ENUM)Input_Capsense_dsFlash.wdgtArray[widgetId].wdgtType)))
    {
        wdSlider = Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;
        result = (uint32)wdSlider->position[0u];
    }

    return result;
}
#endif /* #if (0u != Input_Capsense_SLIDER_WIDGET_EN) */


#if (0u != Input_Capsense_TOUCHPAD_WIDGET_EN)
/*******************************************************************************
* Function Name: Input_Capsense_GetXYCoordinates
****************************************************************************//**
*
* \brief
*  Reports the X/Y position detected for the specified touchpad widget.
*
* \details
*  This function reports a touch position (X and Y coordinates) value of a
*  specified touchpad widget by extracting information from the wdgtStatus
*  registers (Input_Capsense_<WidgetName>_POS_Y_VALUE). This function should
*  be used only with the touchpad widgets. This function does not process the
*  widget but extracts processed results from the \ref group_structures.
*
* \param widgetId
*  Specifies the ID number of a touchpad widget to get the X/Y position of a
*  detected touch.
*  A macro for the widget ID can be found in the
*  Input_Capsense Configuration header file defined as
*  Input_Capsense_<WidgetName>_WDGT_ID.
*
* \return
*  Returns the touch position of a specified touchpad widget:
*    1. If a touch is detected:
*      - Bits [31..16] indicate the Y coordinate.
*      - Bits [15..0] indicate the X coordinate.
*    2. If no touch is detected or a wrong widgetId is specified:
*      - Input_Capsense_TOUCHPAD_NO_TOUCH.
*
*******************************************************************************/
uint32 Input_Capsense_GetXYCoordinates(uint32 widgetId)
{
    Input_Capsense_FLASH_WD_STRUCT const *ptrFlashWdgt = NULL;

    #if (0u != Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
        Input_Capsense_RAM_WD_CSD_TOUCHPAD_STRUCT *wdCsdTouchpad;
    #endif /* #if (0u != Input_Capsense_CSD_TOUCHPAD_WIDGET_EN) */

    #if (0u != Input_Capsense_CSX_TOUCHPAD_WIDGET_EN)
        Input_Capsense_RAM_WD_CSX_TOUCHPAD_STRUCT *wdCsxTouchpad;
    #endif /* #if (0u != Input_Capsense_CSX_TOUCHPAD_WIDGET_EN) */

    cystatus state = CYRET_SUCCESS;
    uint32 result = Input_Capsense_TOUCHPAD_NO_TOUCH;

    if (widgetId >= Input_Capsense_TOTAL_WIDGETS)
    {
        state = CYRET_BAD_PARAM;
    }
    else
    {
        ptrFlashWdgt = &Input_Capsense_dsFlash.wdgtArray[widgetId];

        if ((Input_Capsense_WD_TYPE_ENUM)ptrFlashWdgt->wdgtType != Input_Capsense_WD_TOUCHPAD_E)
        {
            state = CYRET_BAD_PARAM;
        }
    }

    if (CYRET_SUCCESS == state)
    {
        switch(Input_Capsense_GET_SENSE_METHOD(ptrFlashWdgt))
        {
        #if (0u != Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
            case Input_Capsense_SENSE_METHOD_CSD_E:
                wdCsdTouchpad = ptrFlashWdgt->ptr2WdgtRam;
                #if (Input_Capsense_ENABLE == Input_Capsense_CENTROID_5X5_CSD_EN)
                    #if (Input_Capsense_ENABLE == Input_Capsense_CENTROID_3X3_CSD_EN)
                        if (0 != (ptrFlashWdgt->staticConfig & Input_Capsense_CENTROID_5X5_MASK))
                        {
                    #endif
                        result = ((uint32)wdCsdTouchpad->position.pos[0u].x) |
                                 ((uint32)wdCsdTouchpad->position.pos[0u].y << 16u);
                    #if (Input_Capsense_ENABLE == Input_Capsense_CENTROID_3X3_CSD_EN)
                        }
                    #endif
                #endif

                #if (Input_Capsense_ENABLE == Input_Capsense_CENTROID_3X3_CSD_EN)
                    #if (Input_Capsense_ENABLE == Input_Capsense_CENTROID_5X5_CSD_EN)
                        if (0 != (ptrFlashWdgt->staticConfig & Input_Capsense_CENTROID_3X3_MASK))
                        {
                    #endif
                        result = ((uint32)wdCsdTouchpad->posX) |
                                 ((uint32)wdCsdTouchpad->posY << 16u);
                    #if (Input_Capsense_ENABLE == Input_Capsense_CENTROID_5X5_CSD_EN)
                        }
                    #endif
                #endif

                break;
        #endif /* #if (0u != Input_Capsense_CSD_TOUCHPAD_WIDGET_EN) */

        #if (0u != Input_Capsense_CSX_TOUCHPAD_WIDGET_EN)
            case Input_Capsense_SENSE_METHOD_CSX_E:
                wdCsxTouchpad = ptrFlashWdgt->ptr2WdgtRam;

                result = ((uint32)wdCsxTouchpad->touch[0u].x) |
                         ((uint32)wdCsxTouchpad->touch[0u].y << 16u);
                break;
        #endif /* #if (0u != Input_Capsense_CSX_TOUCHPAD_WIDGET_EN) */

        default:
            CYASSERT(0u);
            break;
        }
    }

    return result;
}
#endif /* #if (0u != Input_Capsense_TOUCHPAD_WIDGET_EN) */


/* [] END OF FILE */
