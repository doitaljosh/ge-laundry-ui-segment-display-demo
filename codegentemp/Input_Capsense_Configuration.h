/*******************************************************************************
* \file Input_Capsense_Configuration.h
* \version 7.0
*
* \brief
*   This file provides the customizer parameters definitions.
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

#if !defined(CY_SENSE_Input_Capsense_CONFIGURATION_H)
#define CY_SENSE_Input_Capsense_CONFIGURATION_H

#include <cytypes.h>
#include <cyfitter.h>

/*******************************************************************************
* Customizer-generated defines
*******************************************************************************/
#define Input_Capsense_ENABLE                             (1u)
#define Input_Capsense_DISABLE                            (0u)

#define Input_Capsense_THIRD_GENERATION_BLOCK             (1u)
#define Input_Capsense_FOURTH_GENERATION_BLOCK            (2u)

#define Input_Capsense_GENERATION_BLOCK_VERSION           (2u)

/*******************************************************************************
* HW IP block global defines
*******************************************************************************/

#if (Input_Capsense_GENERATION_BLOCK_VERSION == Input_Capsense_THIRD_GENERATION_BLOCK)
    #define Input_Capsense_CSDV1                          (Input_Capsense_ENABLE)

    #ifdef CYIPBLOCK_m0s8csd_VERSION
        #if (0u == CYIPBLOCK_m0s8csd_VERSION)
            #define Input_Capsense_CSDV1_VER1             (Input_Capsense_ENABLE)
            #define Input_Capsense_CSDV1_VER2             (Input_Capsense_DISABLE)
        #else
            #define Input_Capsense_CSDV1_VER1             (Input_Capsense_DISABLE)
            #define Input_Capsense_CSDV1_VER2             (Input_Capsense_ENABLE)
        #endif
    #else
        #error "HW IP block version is not specified"
    #endif
#else
    #define Input_Capsense_CSDV1                          (Input_Capsense_DISABLE)
    #define Input_Capsense_CSDV1_VER1                     (Input_Capsense_DISABLE)
    #define Input_Capsense_CSDV1_VER2                     (Input_Capsense_DISABLE)
#endif

#if (Input_Capsense_GENERATION_BLOCK_VERSION == Input_Capsense_FOURTH_GENERATION_BLOCK)
    #define Input_Capsense_CSDV2                          (Input_Capsense_ENABLE)

    #ifdef CYIPBLOCK_m0s8csdv2_VERSION
        #if (1u == CYIPBLOCK_m0s8csdv2_VERSION)
            #define Input_Capsense_CSDV2_VER1             (Input_Capsense_ENABLE)
        #else
            #define Input_Capsense_CSDV2_VER1             (Input_Capsense_DISABLE)
        #endif
        #if (2u == CYIPBLOCK_m0s8csdv2_VERSION)
            #define Input_Capsense_CSDV2_VER2             (Input_Capsense_ENABLE)
        #else
            #define Input_Capsense_CSDV2_VER2             (Input_Capsense_DISABLE)
        #endif
    #else
        #error "HW IP block version is not specified"
    #endif
#else
    #define Input_Capsense_CSDV2                          (Input_Capsense_DISABLE)
    #define Input_Capsense_CSDV2_VER1                     (Input_Capsense_DISABLE)
    #define Input_Capsense_CSDV2_VER2                     (Input_Capsense_DISABLE)
#endif

/*******************************************************************************
* Project-global defines
*******************************************************************************/

#define Input_Capsense_2000_MV                            (2000u)

#ifdef CYDEV_VDDA_MV
    #define Input_Capsense_CYDEV_VDDA_MV                  (CYDEV_VDDA_MV)
#else
    #ifdef CYDEV_VDD_MV
        #define Input_Capsense_CYDEV_VDDA_MV              (CYDEV_VDD_MV)
    #endif
#endif

#define Input_Capsense_BAD_CONVERSIONS_NUM                (1u)
#define Input_Capsense_RESAMPLING_CYCLES_MAX_NUMBER       (1u)


/*******************************************************************************
* Enabled Scan Methods
*******************************************************************************/
#define Input_Capsense_CSD_EN                             (1u)
#define Input_Capsense_CSX_EN                             (0u)
#define Input_Capsense_ISX_EN                             (0u)
#define Input_Capsense_CSD_CSX_EN                         (Input_Capsense_CSD_EN && Input_Capsense_CSX_EN)

#define Input_Capsense_MANY_SENSE_MODES_EN                ((Input_Capsense_CSD_EN && Input_Capsense_CSX_EN) || \
                                                             (Input_Capsense_CSD_EN && Input_Capsense_ISX_EN) || \
                                                             (Input_Capsense_CSX_EN && Input_Capsense_ISX_EN) || \
                                                             (Input_Capsense_SELF_TEST_EN))

#define Input_Capsense_MANY_WIDGET_METHODS_EN             ((Input_Capsense_CSD_EN && Input_Capsense_CSX_EN) || \
                                                             (Input_Capsense_CSD_EN && Input_Capsense_ISX_EN) || \
                                                             (Input_Capsense_CSX_EN && Input_Capsense_ISX_EN))

#define Input_Capsense_CSD2X_EN                           (0u)
#define Input_Capsense_CSX2X_EN                           (0u)

/*******************************************************************************
* Definitions for number of widgets and sensors
*******************************************************************************/
#define Input_Capsense_TOTAL_WIDGETS                      (13u)
#define Input_Capsense_TOTAL_CSD_WIDGETS                  (13u)
#define Input_Capsense_TOTAL_CSD_SENSORS                  (13u)
#define Input_Capsense_TOTAL_CSX_WIDGETS                  (0u)
#define Input_Capsense_TOTAL_ISX_WIDGETS                  (0u)
#define Input_Capsense_TOTAL_CSX_NODES                    (0u)
#define Input_Capsense_TOTAL_ISX_NODES                    (0u)

/*******************************************************************************
* Total number of CSD sensors + CSX nodes
*******************************************************************************/
#define Input_Capsense_TOTAL_SENSORS            (Input_Capsense_TOTAL_CSD_SENSORS + \
                                                   Input_Capsense_TOTAL_CSX_NODES+ \
                                                   Input_Capsense_TOTAL_ISX_NODES)

/*******************************************************************************
* Total number of scan slots (used only when dual-channel scan is enabled)
*******************************************************************************/
#define Input_Capsense_TOTAL_SCAN_SLOTS         (13u)

/*******************************************************************************
* Defines widget IDs
*******************************************************************************/
#define Input_Capsense_SW100_WDGT_ID            (0u)
#define Input_Capsense_SW101_WDGT_ID            (1u)
#define Input_Capsense_SW102_WDGT_ID            (2u)
#define Input_Capsense_SW103_WDGT_ID            (3u)
#define Input_Capsense_SW104_WDGT_ID            (4u)
#define Input_Capsense_SW105_WDGT_ID            (5u)
#define Input_Capsense_SW106_WDGT_ID            (6u)
#define Input_Capsense_SW107_WDGT_ID            (7u)
#define Input_Capsense_SW108_WDGT_ID            (8u)
#define Input_Capsense_SW109_WDGT_ID            (9u)
#define Input_Capsense_SW110_WDGT_ID            (10u)
#define Input_Capsense_SW111_WDGT_ID            (11u)
#define Input_Capsense_SW112_WDGT_ID            (12u)

/*******************************************************************************
* Defines sensor IDs
*******************************************************************************/

/* sw100 sensor names */
#define Input_Capsense_SW100_SNS0_ID            (0u)

/* sw101 sensor names */
#define Input_Capsense_SW101_SNS0_ID            (0u)

/* sw102 sensor names */
#define Input_Capsense_SW102_SNS0_ID            (0u)

/* sw103 sensor names */
#define Input_Capsense_SW103_SNS0_ID            (0u)

/* sw104 sensor names */
#define Input_Capsense_SW104_SNS0_ID            (0u)

/* sw105 sensor names */
#define Input_Capsense_SW105_SNS0_ID            (0u)

/* sw106 sensor names */
#define Input_Capsense_SW106_SNS0_ID            (0u)

/* sw107 sensor names */
#define Input_Capsense_SW107_SNS0_ID            (0u)

/* sw108 sensor names */
#define Input_Capsense_SW108_SNS0_ID            (0u)

/* sw109 sensor names */
#define Input_Capsense_SW109_SNS0_ID            (0u)

/* sw110 sensor names */
#define Input_Capsense_SW110_SNS0_ID            (0u)

/* sw111 sensor names */
#define Input_Capsense_SW111_SNS0_ID            (0u)

/* sw112 sensor names */
#define Input_Capsense_SW112_SNS0_ID            (0u)



/*******************************************************************************
* Enabled widget types
*******************************************************************************/
#define Input_Capsense_BUTTON_WIDGET_EN         (1u)
#define Input_Capsense_SLIDER_WIDGET_EN         (0u)
#define Input_Capsense_MATRIX_WIDGET_EN         (0u)
#define Input_Capsense_PROXIMITY_WIDGET_EN      (0u)
#define Input_Capsense_TOUCHPAD_WIDGET_EN       (0u)
#define Input_Capsense_ENCODERDIAL_WIDGET_EN    (0u)

#define Input_Capsense_CSD_MATRIX_WIDGET_EN     (0u)
#define Input_Capsense_CSD_TOUCHPAD_WIDGET_EN   (0u)

#define Input_Capsense_CSX_MATRIX_WIDGET_EN     (0u)
#define Input_Capsense_CSX_TOUCHPAD_WIDGET_EN   (0u)

/*******************************************************************************
* Centroid APIs
*******************************************************************************/
#define Input_Capsense_CENTROID_EN              (0u)
#define Input_Capsense_TOTAL_DIPLEXED_SLIDERS   (0u)
#define Input_Capsense_TOTAL_LINEAR_SLIDERS     (0u)
#define Input_Capsense_TOTAL_RADIAL_SLIDERS     (0u)
#define Input_Capsense_TOTAL_TOUCHPADS          (0u)
#define Input_Capsense_MAX_CENTROID_LENGTH      (0u)
#define Input_Capsense_SLIDER_MULT_METHOD       (0u)
#define Input_Capsense_TOUCHPAD_MULT_METHOD     (0u)

/*******************************************************************************
* Enabled sensor types
*******************************************************************************/
#define Input_Capsense_REGULAR_SENSOR_EN        (1u)
#define Input_Capsense_PROXIMITY_SENSOR_EN      (0u)

/*******************************************************************************
* Sensor ganging
*******************************************************************************/
#define Input_Capsense_GANGED_SNS_EN            (0u)
#define Input_Capsense_CSD_GANGED_SNS_EN        (0u)
#define Input_Capsense_CSX_GANGED_SNS_EN        (0u)

/*******************************************************************************
* Max number of sensors used among all the widgets
*******************************************************************************/
#define Input_Capsense_MAX_SENSORS_PER_WIDGET   (1u)
#define Input_Capsense_MAX_SENSORS_PER_5X5_TOUCHPAD (1u)

/*******************************************************************************
* Total number of all used electrodes (NOT unique)
*******************************************************************************/
#define Input_Capsense_TOTAL_ELECTRODES         (13u)
/* Obsolete */
#define Input_Capsense_TOTAL_SENSOR_IOS         Input_Capsense_TOTAL_ELECTRODES

/*******************************************************************************
* Total number of used physical IOs (unique)
*******************************************************************************/
#define Input_Capsense_TOTAL_IO_CNT             (13u)

/*******************************************************************************
* Array length for widget status registers
*******************************************************************************/
#define Input_Capsense_WDGT_STATUS_WORDS        \
                        (((uint8)((Input_Capsense_TOTAL_WIDGETS - 1u) / 32u)) + 1u)


/*******************************************************************************
* Auto-tuning mode selection
*******************************************************************************/
#define Input_Capsense_CSD_SS_DIS         (0x00ul)
#define Input_Capsense_CSD_SS_HW_EN       (0x01ul)
#define Input_Capsense_CSD_SS_TH_EN       (0x02ul)
#define Input_Capsense_CSD_SS_HWTH_EN     (Input_Capsense_CSD_SS_HW_EN | \
                                             Input_Capsense_CSD_SS_TH_EN)

#define Input_Capsense_CSD_AUTOTUNE       Input_Capsense_CSD_SS_HWTH_EN


/*******************************************************************************
* General settings
*******************************************************************************/

#define Input_Capsense_AUTO_RESET_METHOD_LEGACY (0u)
#define Input_Capsense_AUTO_RESET_METHOD_SAMPLE (1u)

#define Input_Capsense_MULTI_FREQ_SCAN_EN       (0u)
#define Input_Capsense_SENSOR_AUTO_RESET_EN     (0u)
#define Input_Capsense_SENSOR_AUTO_RESET_METHOD (0u)
#define Input_Capsense_NUM_CENTROIDS            (1u)
#define Input_Capsense_4PTS_LOCAL_MAX_EN        (0u)
#define Input_Capsense_OFF_DEBOUNCE_EN          (0u)
#define Input_Capsense_CUSTOM_DS_RAM_SIZE       (0u)

/* Defines power status of HW block after scanning */
#define Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN  (0u)

/* Defines number of scan frequencies */
#if (Input_Capsense_DISABLE != Input_Capsense_MULTI_FREQ_SCAN_EN)
    #define Input_Capsense_NUM_SCAN_FREQS       (3u)
#else
    #define Input_Capsense_NUM_SCAN_FREQS       (1u)
#endif /* #if (Input_Capsense_DISABLE != Input_Capsense_MULTI_FREQ_SCAN_EN) */

/* Data size for thresholds / low baseline reset */
#define Input_Capsense_SIZE_8BITS               (8u)
#define Input_Capsense_SIZE_16BITS              (16u)

#define Input_Capsense_THRESHOLD_SIZE           Input_Capsense_SIZE_16BITS
typedef uint16 Input_Capsense_THRESHOLD_TYPE;

#if (Input_Capsense_AUTO_RESET_METHOD_LEGACY == Input_Capsense_SENSOR_AUTO_RESET_METHOD)
    #define Input_Capsense_LOW_BSLN_RST_SIZE        Input_Capsense_SIZE_8BITS
    typedef uint8 Input_Capsense_LOW_BSLN_RST_TYPE;
#else
    #define Input_Capsense_LOW_BSLN_RST_SIZE    (16u)
    typedef uint16 Input_Capsense_LOW_BSLN_RST_TYPE;
#endif /* #if (Input_Capsense_AUTO_RESET_METHOD_LEGACY == Input_Capsense_SENSOR_AUTO_RESET_METHOD) */

/* Coefficient to define touch threshold for proximity sensors */
#define Input_Capsense_PROX_TOUCH_COEFF         (300u)

/*******************************************************************************
* General Filter Constants
*******************************************************************************/

/* Baseline algorithm options */
#define Input_Capsense_IIR_BASELINE                 (0u)
#define Input_Capsense_BUCKET_BASELINE              (1u)

#define Input_Capsense_BASELINE_TYPE                Input_Capsense_IIR_BASELINE

/* IIR baseline filter algorithm for regular sensors*/
#define Input_Capsense_REGULAR_IIR_BL_TYPE          Input_Capsense_IIR_FILTER_PERFORMANCE

/* IIR baseline coefficients for regular sensors */
#define Input_Capsense_REGULAR_IIR_BL_N             (1u)
#define Input_Capsense_REGULAR_IIR_BL_SHIFT         (8u)

/* IIR baseline filter algorithm for proximity sensors*/
#define Input_Capsense_PROX_IIR_BL_TYPE             Input_Capsense_IIR_FILTER_PERFORMANCE

/* IIR baseline coefficients for proximity sensors */
#define Input_Capsense_PROX_IIR_BL_N                (1u)
#define Input_Capsense_PROX_IIR_BL_SHIFT            (8u)


/* IIR filter constants */
#define Input_Capsense_IIR_COEFFICIENT_K            (256u)

/* IIR filter type */
#define Input_Capsense_IIR_FILTER_STANDARD          (1u)
#define Input_Capsense_IIR_FILTER_PERFORMANCE       (2u)
#define Input_Capsense_IIR_FILTER_MEMORY            (3u)

/* Regular sensor raw count filters */
#define Input_Capsense_REGULAR_RC_FILTER_EN         (0u)
#define Input_Capsense_REGULAR_RC_IIR_FILTER_EN     (0u)
#define Input_Capsense_REGULAR_RC_MEDIAN_FILTER_EN  (0u)
#define Input_Capsense_REGULAR_RC_AVERAGE_FILTER_EN (0u)
#define Input_Capsense_REGULAR_RC_CUSTOM_FILTER_EN  (0u)
#define Input_Capsense_REGULAR_RC_ALP_FILTER_EN     (0u)

/* Proximity sensor raw count filters */
#define Input_Capsense_PROX_RC_FILTER_EN            (0u)
#define Input_Capsense_PROX_RC_IIR_FILTER_EN        (0u)
#define Input_Capsense_PROX_RC_MEDIAN_FILTER_EN     (0u)
#define Input_Capsense_PROX_RC_AVERAGE_FILTER_EN    (0u)
#define Input_Capsense_PROX_RC_CUSTOM_FILTER_EN     (0u)
#define Input_Capsense_PROX_RC_ALP_FILTER_EN        (0u)

#define Input_Capsense_ALP_FILTER_EN                (0u)
#define Input_Capsense_REGULAR_RC_ALP_FILTER_COEFF  (2u)
#define Input_Capsense_PROX_RC_ALP_FILTER_COEFF     (2u)

/* Raw count filters */
#define Input_Capsense_RC_FILTER_EN                 (Input_Capsense_REGULAR_RC_FILTER_EN || Input_Capsense_PROX_RC_FILTER_EN)

/* IIR raw count filter algorithm for regular sensors */
#define Input_Capsense_REGULAR_IIR_RC_TYPE          (Input_Capsense_IIR_FILTER_STANDARD)

/* IIR raw count filter coefficients for regular sensors */
#define Input_Capsense_REGULAR_IIR_RC_N             (128u)
#define Input_Capsense_REGULAR_IIR_RC_SHIFT         (0u)

/* IIR raw count filter algorithm for proximity sensors*/
#define Input_Capsense_PROX_IIR_RC_TYPE             (Input_Capsense_IIR_FILTER_STANDARD)

/* IIR raw count filter coefficients for proximity sensors */
#define Input_Capsense_PROX_IIR_RC_N                (128u)
#define Input_Capsense_PROX_IIR_RC_SHIFT            (0u)

/* Median filter constants */

/* Order of regular sensor median filter */
#define Input_Capsense_REGULAR_MEDIAN_LEN           (2u)

/* Order of proximity sensor median filter */
#define Input_Capsense_PROX_MEDIAN_LEN              (2u)

/* Average filter constants*/
#define Input_Capsense_AVERAGE_FILTER_LEN_2         (1u)
#define Input_Capsense_AVERAGE_FILTER_LEN_4         (3u)

/* Order of regular sensor average filter */
#define Input_Capsense_REGULAR_AVERAGE_LEN          (Input_Capsense_AVERAGE_FILTER_LEN_4)

/* Order of proximity sensor average filter */
#define Input_Capsense_PROX_AVERAGE_LEN             (Input_Capsense_AVERAGE_FILTER_LEN_4)

/* Widget baseline coefficient enable */
#define Input_Capsense_WD_BSLN_COEFF_EN             (0u)

/* Centroid position filters */
#define Input_Capsense_POSITION_FILTER_EN           (0u)
#define Input_Capsense_POS_MEDIAN_FILTER_EN         (0u)
#define Input_Capsense_POS_IIR_FILTER_EN            (0u)
#define Input_Capsense_POS_ADAPTIVE_IIR_FILTER_EN   (0u)
#define Input_Capsense_POS_AVERAGE_FILTER_EN        (0u)
#define Input_Capsense_POS_JITTER_FILTER_EN         (0u)
#define Input_Capsense_BALLISTIC_MULTIPLIER_EN      (0u)
#define Input_Capsense_CENTROID_3X3_CSD_EN          (0u)
#define Input_Capsense_CENTROID_5X5_CSD_EN          (0u)
#define Input_Capsense_CSD_5X5_MAX_FINGERS          (1u)

#define Input_Capsense_POS_IIR_COEFF                (128u)
#define Input_Capsense_POS_IIR_RESET_RADIAL_SLIDER  (35u)

#define Input_Capsense_CSX_TOUCHPAD_UNDEFINED       (40u)

/* IDAC options */

/* Third-generation HW block IDAC gain */
#define Input_Capsense_IDAC_GAIN_4X                 (4u)
#define Input_Capsense_IDAC_GAIN_8X                 (8u)

/* Fourth-generation HW block IDAC gain */
#define Input_Capsense_IDAC_GAIN_LOW                (0uL)
#define Input_Capsense_IDAC_GAIN_MEDIUM             (1uL)
#define Input_Capsense_IDAC_GAIN_HIGH               (2uL)

#define Input_Capsense_IDAC_SOURCING                (0u)
#define Input_Capsense_IDAC_SINKING                 (1u)

/* Shield tank capacitor precharge source */
#define Input_Capsense_CSH_PRECHARGE_VREF           (0u)
#define Input_Capsense_CSH_PRECHARGE_IO_BUF         (1u)

/* Shield electrode delay */
#define Input_Capsense_NO_DELAY                     (0u)

#if(Input_Capsense_ENABLE == Input_Capsense_CSDV2)
    #define Input_Capsense_SH_DELAY_5NS             (1u)
    #define Input_Capsense_SH_DELAY_10NS            (2u)
    #define Input_Capsense_SH_DELAY_20NS            (3u)
#else
    #if(Input_Capsense_ENABLE == Input_Capsense_CSDV1_VER2)
        #define Input_Capsense_SH_DELAY_10NS        (3u)
        #define Input_Capsense_SH_DELAY_50NS        (2u)
    #else
        #define Input_Capsense_SH_DELAY_1CYCLES     (1u)
        #define Input_Capsense_SH_DELAY_2CYCLES     (2u)
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV1_VER2) */
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */

/* Inactive sensor connection options */
#define Input_Capsense_SNS_CONNECTION_GROUND        (0x00000000u)
#define Input_Capsense_SNS_CONNECTION_HIGHZ         (0x00000001u)
#define Input_Capsense_SNS_CONNECTION_SHIELD        (0x00000002u)
#define Input_Capsense_SNS_CONNECTION_UNDEFINED     (0x00000003u)

/* Sense clock selection options */
#if defined(Input_Capsense_TAPEOUT_STAR_USED)
    #define Input_Capsense_CSDV2_REF9P6UA_EN            (0u)
#else
    #define Input_Capsense_CSDV2_REF9P6UA_EN            (1u)
#endif /* defined(Input_Capsense_TAPEOUT_STAR_USED) */

#define Input_Capsense_CLK_SOURCE_DIRECT            (0x00000000Lu)

#define Input_Capsense_CLK_SOURCE_SSC1              (0x01u)
#define Input_Capsense_CLK_SOURCE_SSC2              (0x02u)
#define Input_Capsense_CLK_SOURCE_SSC3              (0x03u)
#define Input_Capsense_CLK_SOURCE_SSC4              (0x04u)

#define Input_Capsense_CLK_SOURCE_PRS8              (0x05u)
#define Input_Capsense_CLK_SOURCE_PRS12             (0x06u)
#define Input_Capsense_CLK_SOURCE_PRSAUTO           (0xFFu)

#define Input_Capsense_MFS_IMO                      (0u)
#define Input_Capsense_MFS_SNS_CLK                  (1u)

/* Defines scan resolutions */
#define Input_Capsense_RES6BIT                      (6u)
#define Input_Capsense_RES7BIT                      (7u)
#define Input_Capsense_RES8BIT                      (8u)
#define Input_Capsense_RES9BIT                      (9u)
#define Input_Capsense_RES10BIT                     (10u)
#define Input_Capsense_RES11BIT                     (11u)
#define Input_Capsense_RES12BIT                     (12u)
#define Input_Capsense_RES13BIT                     (13u)
#define Input_Capsense_RES14BIT                     (14u)
#define Input_Capsense_RES15BIT                     (15u)
#define Input_Capsense_RES16BIT                     (16u)

/* Fourth-generation HW block: Initialization switch resistance */
#define Input_Capsense_INIT_SW_RES_LOW              (0x00000000Lu)
#define Input_Capsense_INIT_SW_RES_MEDIUM           (0x00000001Lu)
#define Input_Capsense_INIT_SW_RES_HIGH             (0x00000002Lu)

/* Fourth-generation HW block: Initialization switch resistance */
#define Input_Capsense_SCAN_SW_RES_LOW              (0x00000000Lu)
#define Input_Capsense_SCAN_SW_RES_MEDIUM           (0x00000001Lu)
#define Input_Capsense_SCAN_SW_RES_HIGH             (0x00000002Lu)

/* Fourth-generation HW block: CSD shield switch resistance */
#define Input_Capsense_SHIELD_SW_RES_LOW            (0x00000000Lu)
#define Input_Capsense_SHIELD_SW_RES_MEDIUM         (0x00000001Lu)
#define Input_Capsense_SHIELD_SW_RES_HIGH           (0x00000002Lu)
#define Input_Capsense_SHIELD_SW_RES_LOW_EMI        (0x00000003Lu)

/* Fourth-generation HW block: CSD shield switch resistance */
#define Input_Capsense_INIT_SHIELD_SW_RES_LOW       (0x00000000Lu)
#define Input_Capsense_INIT_SHIELD_SW_RES_MEDIUM    (0x00000001Lu)
#define Input_Capsense_INIT_SHIELD_SW_RES_HIGH      (0x00000002Lu)
#define Input_Capsense_INIT_SHIELD_SW_RES_LOW_EMI   (0x00000003Lu)

/* Fourth-generation HW block: CSD shield switch resistance */
#define Input_Capsense_SCAN_SHIELD_SW_RES_LOW       (0x00000000Lu)
#define Input_Capsense_SCAN_SHIELD_SW_RES_MEDIUM    (0x00000001Lu)
#define Input_Capsense_SCAN_SHIELD_SW_RES_HIGH      (0x00000002Lu)
#define Input_Capsense_SCAN_SHIELD_SW_RES_LOW_EMI   (0x00000003Lu)

/* Sensing method */
#define Input_Capsense_SENSING_LEGACY               (0x00000000Lu)
#define Input_Capsense_SENSING_LOW_EMI              (0x00000001Lu)
#define Input_Capsense_SENSING_FULL_WAVE            (0x00000002Lu)


/*******************************************************************************
* CSD/CSX Common Settings
*******************************************************************************/

#define Input_Capsense_BLOCK_ANALOG_WAKEUP_DELAY_US (0u)

#define Input_Capsense_MFS_METHOD                   (0u)
#define Input_Capsense_IMO_FREQUENCY_OFFSET_F1      (20u)
#define Input_Capsense_IMO_FREQUENCY_OFFSET_F2      (20u)

/*******************************************************************************
* CSD Specific Settings
*******************************************************************************/

/* CSD scan method settings */
#define Input_Capsense_CSD_IDAC_AUTOCAL_EN          (1u)
#define Input_Capsense_CSD_IDAC_GAIN                (Input_Capsense_IDAC_GAIN_HIGH)
#define Input_Capsense_CSD_SHIELD_EN                (0u)
#define Input_Capsense_CSD_SHIELD_TANK_EN           (0u)
#define Input_Capsense_CSD_CSH_PRECHARGE_SRC        (Input_Capsense_CSH_PRECHARGE_VREF)
#define Input_Capsense_CSD_SHIELD_DELAY             (Input_Capsense_NO_DELAY)
#define Input_Capsense_CSD_TOTAL_SHIELD_COUNT       (0u)
#define Input_Capsense_CSD_SCANSPEED_DIVIDER        (1u)
#define Input_Capsense_CSD_COMMON_SNS_CLK_EN        (0u)
#define Input_Capsense_CSD_SNS_CLK_SOURCE           (Input_Capsense_CLK_SOURCE_PRSAUTO)
#define Input_Capsense_CSD_SNS_CLK_DIVIDER          (8u)
#define Input_Capsense_CSD_INACTIVE_SNS_CONNECTION  (Input_Capsense_SNS_CONNECTION_GROUND)
#define Input_Capsense_CSD_IDAC_COMP_EN             (1u)
#define Input_Capsense_CSD_IDAC_CONFIG              (Input_Capsense_IDAC_SOURCING)
#define Input_Capsense_CSD_RAWCOUNT_CAL_LEVEL       (85u)
#define Input_Capsense_CSD_DUALIDAC_LEVEL           (50u)
#define Input_Capsense_CSD_PRESCAN_SETTLING_TIME    (5u)
#define Input_Capsense_CSD_SNSCLK_R_CONST           (1000u)
#define Input_Capsense_CSD_VREF_MV                  (2021u)

#define Input_Capsense_CSD_CALIBRATION_ERROR        (10u)
#define Input_Capsense_CSD_IDAC_AUTO_GAIN_EN        (1u)
#define Input_Capsense_CSD_IDAC_GAIN_INDEX_DEFAULT  (5u)
#define Input_Capsense_CSD_IDAC_MIN                 (20u)
#define Input_Capsense_CSD_COL_ROW_IDAC_ALIGNMENT_EN      (1u)

/* The macro is obsolete and should not be used */
#define Input_Capsense_CSD_DEDICATED_IDAC_COMP_EN   (1u)
/* CSD settings - Fourth-generation HW block */
#define Input_Capsense_CSD_ANALOG_STARTUP_DELAY_US  (10u)
#define Input_Capsense_CSD_FINE_INIT_TIME           (10u)
#define Input_Capsense_CSD_AUTO_ZERO_EN             (0u)
#define Input_Capsense_CSD_AUTO_ZERO_TIME           (15Lu)
#define Input_Capsense_CSD_NOISE_METRIC_EN          (0u)
#define Input_Capsense_CSD_NOISE_METRIC_TH          (1Lu)
#define Input_Capsense_CSD_INIT_SWITCH_RES          (Input_Capsense_INIT_SW_RES_MEDIUM)
#define Input_Capsense_CSD_SENSING_METHOD           (0)
#define Input_Capsense_CSD_SHIELD_SWITCH_RES        (Input_Capsense_SHIELD_SW_RES_MEDIUM)
#define Input_Capsense_CSD_GAIN                     (18Lu)

#define Input_Capsense_CSD_MFS_DIVIDER_OFFSET_F1    (1u)
#define Input_Capsense_CSD_MFS_DIVIDER_OFFSET_F2    (2u)

/*******************************************************************************
* CSX Specific Settings
*******************************************************************************/

/* CSX scan method settings */
#define Input_Capsense_CSX_SCANSPEED_DIVIDER        (1u)
#define Input_Capsense_CSX_COMMON_TX_CLK_EN         (0u)
#define Input_Capsense_CSX_TX_CLK_SOURCE            (Input_Capsense_CLK_SOURCE_PRSAUTO)
#define Input_Capsense_CSX_TX_CLK_DIVIDER           (80u)
#define Input_Capsense_CSX_INACTIVE_SNS_CONNECTION  (Input_Capsense_SNS_CONNECTION_GROUND)
#define Input_Capsense_CSX_MAX_FINGERS              (1u)
#define Input_Capsense_CSX_MAX_LOCAL_PEAKS          (5u)
#define Input_Capsense_CSX_IDAC_AUTOCAL_EN          (0u)
#define Input_Capsense_CSX_IDAC_BITS_USED           (7u)
#define Input_Capsense_CSX_RAWCOUNT_CAL_LEVEL       (40u)
#define Input_Capsense_CSX_IDAC_GAIN                (Input_Capsense_IDAC_GAIN_MEDIUM)
#define Input_Capsense_CSX_CALIBRATION_ERROR        (20u)
#define Input_Capsense_CSX_SKIP_OVSMPL_SPECIFIC_NODES (0u)
#define Input_Capsense_CSX_MULTIPHASE_TX_EN         (0u)
#define Input_Capsense_CSX_MAX_TX_PHASE_LENGTH      (0u)

/* CSX settings - Fourth-generation HW block */
#define Input_Capsense_CSX_ANALOG_STARTUP_DELAY_US  (10u)
#define Input_Capsense_CSX_AUTO_ZERO_EN             (0u)
#define Input_Capsense_CSX_AUTO_ZERO_TIME           (15u)
#define Input_Capsense_CSX_FINE_INIT_TIME           (4u)
#define Input_Capsense_CSX_NOISE_METRIC_EN          (0u)
#define Input_Capsense_CSX_NOISE_METRIC_TH          (1u)
#define Input_Capsense_CSX_INIT_SWITCH_RES          (Input_Capsense_INIT_SW_RES_MEDIUM)
#define Input_Capsense_CSX_SCAN_SWITCH_RES          (Input_Capsense_SCAN_SW_RES_LOW)
#define Input_Capsense_CSX_INIT_SHIELD_SWITCH_RES   (Input_Capsense_INIT_SHIELD_SW_RES_HIGH)
#define Input_Capsense_CSX_SCAN_SHIELD_SWITCH_RES   (Input_Capsense_SCAN_SHIELD_SW_RES_LOW)

#define Input_Capsense_CSX_MFS_DIVIDER_OFFSET_F1    (1u)
#define Input_Capsense_CSX_MFS_DIVIDER_OFFSET_F2    (2u)

/* Gesture parameters */
#define Input_Capsense_GES_GLOBAL_EN                (0u)

/*******************************************************************************
* ISX Specific Settings
*******************************************************************************/

/* ISX scan method settings */
#define Input_Capsense_ISX_SCANSPEED_DIVIDER        (1u)
#define Input_Capsense_ISX_LX_CLK_DIVIDER           (80u)
#define Input_Capsense_ISX_IDAC_AUTOCAL_EN          (0u)
#define Input_Capsense_ISX_IDAC_BITS_USED           (7u)
#define Input_Capsense_ISX_RAWCOUNT_CAL_LEVEL       (30u)
#define Input_Capsense_ISX_IDAC_GAIN                (Input_Capsense_IDAC_GAIN_MEDIUM)
#define Input_Capsense_ISX_SKIP_OVSMPL_SPECIFIC_NODES (0u)
#define Input_Capsense_ISX_MAX_TX_PHASE_LENGTH      (0u)
#define Input_Capsense_ISX_PIN_COUNT_LX             (u)
/* ISX settings - Fourth-generation HW block */
#define Input_Capsense_ISX_AUTO_ZERO_EN             (0u)
#define Input_Capsense_ISX_AUTO_ZERO_TIME           (15u)
#define Input_Capsense_ISX_FINE_INIT_TIME           (20u)
#define Input_Capsense_ISX_NOISE_METRIC_EN          (0u)
#define Input_Capsense_ISX_NOISE_METRIC_TH          (1u)
#define Input_Capsense_ISX_INIT_SWITCH_RES          (Input_Capsense_INIT_SW_RES_MEDIUM)
#define Input_Capsense_ISX_SCAN_SWITCH_RES          (Input_Capsense_SCAN_SW_RES_LOW)
#define Input_Capsense_ISX_INIT_SHIELD_SWITCH_RES   (Input_Capsense_INIT_SHIELD_SW_RES_HIGH)
#define Input_Capsense_ISX_SCAN_SHIELD_SWITCH_RES   (Input_Capsense_SCAN_SHIELD_SW_RES_LOW)
#define Input_Capsense_ISX_SAMPLE_PHASE_DEG         (30u)

/*******************************************************************************
* Global Parameter Definitions
*******************************************************************************/

/* Compound section definitions */
#define Input_Capsense_ANY_NONSS_AUTOCAL ((0u != Input_Capsense_CSX_IDAC_AUTOCAL_EN) || \
                                       (0u != Input_Capsense_ISX_IDAC_AUTOCAL_EN) || \
                                      ((Input_Capsense_CSD_AUTOTUNE == Input_Capsense_CSD_SS_DIS) && (0u != Input_Capsense_CSD_IDAC_AUTOCAL_EN)))
#define Input_Capsense_ANYMODE_AUTOCAL (((0u != Input_Capsense_CSX_IDAC_AUTOCAL_EN) \
                                       || (0u != Input_Capsense_ISX_IDAC_AUTOCAL_EN)) \
                                       || (0u != Input_Capsense_CSD_IDAC_AUTOCAL_EN))
/* RAM Global Parameters Definitions */
#define Input_Capsense_CONFIG_ID                (0xA9E2u)
#define Input_Capsense_DEVICE_ID                (0x0100u)
#define Input_Capsense_HW_CLOCK                 (0x0BB8u)
#define Input_Capsense_CSD0_CONFIG              (0x0008u)

/*******************************************************************************
* sw100 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW100_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW100_NUM_SENSORS        (1u)

/*******************************************************************************
* sw100 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW100_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW100_FINGER_TH          (100u)
#define Input_Capsense_SW100_NOISE_TH           (40u)
#define Input_Capsense_SW100_NNOISE_TH          (40u)
#define Input_Capsense_SW100_HYSTERESIS         (10u)
#define Input_Capsense_SW100_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW100_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW100_IDAC_MOD0          (32u)
#define Input_Capsense_SW100_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW100_SNS_CLK            (4u)
#define Input_Capsense_SW100_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW100_FINGER_CAP         (160u)
#define Input_Capsense_SW100_SIGPFC             (0u)

/*******************************************************************************
* sw101 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW101_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW101_NUM_SENSORS        (1u)

/*******************************************************************************
* sw101 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW101_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW101_FINGER_TH          (100u)
#define Input_Capsense_SW101_NOISE_TH           (40u)
#define Input_Capsense_SW101_NNOISE_TH          (40u)
#define Input_Capsense_SW101_HYSTERESIS         (10u)
#define Input_Capsense_SW101_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW101_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW101_IDAC_MOD0          (32u)
#define Input_Capsense_SW101_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW101_SNS_CLK            (4u)
#define Input_Capsense_SW101_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW101_FINGER_CAP         (160u)
#define Input_Capsense_SW101_SIGPFC             (0u)

/*******************************************************************************
* sw102 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW102_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW102_NUM_SENSORS        (1u)

/*******************************************************************************
* sw102 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW102_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW102_FINGER_TH          (100u)
#define Input_Capsense_SW102_NOISE_TH           (40u)
#define Input_Capsense_SW102_NNOISE_TH          (40u)
#define Input_Capsense_SW102_HYSTERESIS         (10u)
#define Input_Capsense_SW102_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW102_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW102_IDAC_MOD0          (32u)
#define Input_Capsense_SW102_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW102_SNS_CLK            (4u)
#define Input_Capsense_SW102_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW102_FINGER_CAP         (160u)
#define Input_Capsense_SW102_SIGPFC             (0u)

/*******************************************************************************
* sw103 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW103_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW103_NUM_SENSORS        (1u)

/*******************************************************************************
* sw103 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW103_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW103_FINGER_TH          (100u)
#define Input_Capsense_SW103_NOISE_TH           (40u)
#define Input_Capsense_SW103_NNOISE_TH          (40u)
#define Input_Capsense_SW103_HYSTERESIS         (10u)
#define Input_Capsense_SW103_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW103_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW103_IDAC_MOD0          (32u)
#define Input_Capsense_SW103_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW103_SNS_CLK            (4u)
#define Input_Capsense_SW103_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW103_FINGER_CAP         (160u)
#define Input_Capsense_SW103_SIGPFC             (0u)

/*******************************************************************************
* sw104 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW104_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW104_NUM_SENSORS        (1u)

/*******************************************************************************
* sw104 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW104_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW104_FINGER_TH          (100u)
#define Input_Capsense_SW104_NOISE_TH           (40u)
#define Input_Capsense_SW104_NNOISE_TH          (40u)
#define Input_Capsense_SW104_HYSTERESIS         (10u)
#define Input_Capsense_SW104_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW104_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW104_IDAC_MOD0          (32u)
#define Input_Capsense_SW104_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW104_SNS_CLK            (4u)
#define Input_Capsense_SW104_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW104_FINGER_CAP         (160u)
#define Input_Capsense_SW104_SIGPFC             (0u)

/*******************************************************************************
* sw105 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW105_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW105_NUM_SENSORS        (1u)

/*******************************************************************************
* sw105 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW105_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW105_FINGER_TH          (100u)
#define Input_Capsense_SW105_NOISE_TH           (40u)
#define Input_Capsense_SW105_NNOISE_TH          (40u)
#define Input_Capsense_SW105_HYSTERESIS         (10u)
#define Input_Capsense_SW105_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW105_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW105_IDAC_MOD0          (32u)
#define Input_Capsense_SW105_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW105_SNS_CLK            (4u)
#define Input_Capsense_SW105_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW105_FINGER_CAP         (160u)
#define Input_Capsense_SW105_SIGPFC             (0u)

/*******************************************************************************
* sw106 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW106_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW106_NUM_SENSORS        (1u)

/*******************************************************************************
* sw106 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW106_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW106_FINGER_TH          (100u)
#define Input_Capsense_SW106_NOISE_TH           (40u)
#define Input_Capsense_SW106_NNOISE_TH          (40u)
#define Input_Capsense_SW106_HYSTERESIS         (10u)
#define Input_Capsense_SW106_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW106_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW106_IDAC_MOD0          (32u)
#define Input_Capsense_SW106_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW106_SNS_CLK            (4u)
#define Input_Capsense_SW106_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW106_FINGER_CAP         (160u)
#define Input_Capsense_SW106_SIGPFC             (0u)

/*******************************************************************************
* sw107 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW107_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW107_NUM_SENSORS        (1u)

/*******************************************************************************
* sw107 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW107_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW107_FINGER_TH          (100u)
#define Input_Capsense_SW107_NOISE_TH           (40u)
#define Input_Capsense_SW107_NNOISE_TH          (40u)
#define Input_Capsense_SW107_HYSTERESIS         (10u)
#define Input_Capsense_SW107_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW107_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW107_IDAC_MOD0          (32u)
#define Input_Capsense_SW107_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW107_SNS_CLK            (4u)
#define Input_Capsense_SW107_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW107_FINGER_CAP         (160u)
#define Input_Capsense_SW107_SIGPFC             (0u)

/*******************************************************************************
* sw108 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW108_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW108_NUM_SENSORS        (1u)

/*******************************************************************************
* sw108 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW108_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW108_FINGER_TH          (100u)
#define Input_Capsense_SW108_NOISE_TH           (40u)
#define Input_Capsense_SW108_NNOISE_TH          (40u)
#define Input_Capsense_SW108_HYSTERESIS         (10u)
#define Input_Capsense_SW108_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW108_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW108_IDAC_MOD0          (32u)
#define Input_Capsense_SW108_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW108_SNS_CLK            (4u)
#define Input_Capsense_SW108_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW108_FINGER_CAP         (160u)
#define Input_Capsense_SW108_SIGPFC             (0u)

/*******************************************************************************
* sw109 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW109_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW109_NUM_SENSORS        (1u)

/*******************************************************************************
* sw109 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW109_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW109_FINGER_TH          (100u)
#define Input_Capsense_SW109_NOISE_TH           (40u)
#define Input_Capsense_SW109_NNOISE_TH          (40u)
#define Input_Capsense_SW109_HYSTERESIS         (10u)
#define Input_Capsense_SW109_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW109_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW109_IDAC_MOD0          (32u)
#define Input_Capsense_SW109_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW109_SNS_CLK            (4u)
#define Input_Capsense_SW109_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW109_FINGER_CAP         (160u)
#define Input_Capsense_SW109_SIGPFC             (0u)

/*******************************************************************************
* sw110 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW110_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW110_NUM_SENSORS        (1u)

/*******************************************************************************
* sw110 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW110_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW110_FINGER_TH          (100u)
#define Input_Capsense_SW110_NOISE_TH           (40u)
#define Input_Capsense_SW110_NNOISE_TH          (40u)
#define Input_Capsense_SW110_HYSTERESIS         (10u)
#define Input_Capsense_SW110_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW110_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW110_IDAC_MOD0          (32u)
#define Input_Capsense_SW110_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW110_SNS_CLK            (4u)
#define Input_Capsense_SW110_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW110_FINGER_CAP         (160u)
#define Input_Capsense_SW110_SIGPFC             (0u)

/*******************************************************************************
* sw111 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW111_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW111_NUM_SENSORS        (1u)

/*******************************************************************************
* sw111 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW111_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW111_FINGER_TH          (100u)
#define Input_Capsense_SW111_NOISE_TH           (40u)
#define Input_Capsense_SW111_NNOISE_TH          (40u)
#define Input_Capsense_SW111_HYSTERESIS         (10u)
#define Input_Capsense_SW111_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW111_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW111_IDAC_MOD0          (32u)
#define Input_Capsense_SW111_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW111_SNS_CLK            (4u)
#define Input_Capsense_SW111_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW111_FINGER_CAP         (160u)
#define Input_Capsense_SW111_SIGPFC             (0u)

/*******************************************************************************
* sw112 initialization values for FLASH data structure
*******************************************************************************/
#define Input_Capsense_SW112_STATIC_CONFIG      (10241u)
#define Input_Capsense_SW112_NUM_SENSORS        (1u)

/*******************************************************************************
* sw112 initialization values for RAM data structure
*******************************************************************************/
#define Input_Capsense_SW112_RESOLUTION         (Input_Capsense_RES12BIT)
#define Input_Capsense_SW112_FINGER_TH          (100u)
#define Input_Capsense_SW112_NOISE_TH           (40u)
#define Input_Capsense_SW112_NNOISE_TH          (40u)
#define Input_Capsense_SW112_HYSTERESIS         (10u)
#define Input_Capsense_SW112_ON_DEBOUNCE        (3u)
#define Input_Capsense_SW112_LOW_BSLN_RST       (30u)
#define Input_Capsense_SW112_IDAC_MOD0          (32u)
#define Input_Capsense_SW112_IDAC_GAIN_INDEX    (5u)
#define Input_Capsense_SW112_SNS_CLK            (4u)
#define Input_Capsense_SW112_SNS_CLK_SOURCE     (0u)
#define Input_Capsense_SW112_FINGER_CAP         (160u)
#define Input_Capsense_SW112_SIGPFC             (0u)

/* RAM Sensor Parameters Definitions */
#define Input_Capsense_SW100_SNS0_IDAC_COMP0    (32u)
#define Input_Capsense_SW101_SNS0_IDAC_COMP0    (32u)
#define Input_Capsense_SW102_SNS0_IDAC_COMP0    (32u)
#define Input_Capsense_SW103_SNS0_IDAC_COMP0    (32u)
#define Input_Capsense_SW104_SNS0_IDAC_COMP0    (32u)
#define Input_Capsense_SW105_SNS0_IDAC_COMP0    (32u)
#define Input_Capsense_SW106_SNS0_IDAC_COMP0    (32u)
#define Input_Capsense_SW107_SNS0_IDAC_COMP0    (32u)
#define Input_Capsense_SW108_SNS0_IDAC_COMP0    (32u)
#define Input_Capsense_SW109_SNS0_IDAC_COMP0    (32u)
#define Input_Capsense_SW110_SNS0_IDAC_COMP0    (32u)
#define Input_Capsense_SW111_SNS0_IDAC_COMP0    (32u)
#define Input_Capsense_SW112_SNS0_IDAC_COMP0    (32u)



/*******************************************************************************
* ADC Specific Macros
*******************************************************************************/
#define Input_Capsense_ADC_RES8BIT                  (8u)
#define Input_Capsense_ADC_RES10BIT                 (10u)

#define Input_Capsense_ADC_FULLRANGE_MODE           (0u)
#define Input_Capsense_ADC_VREF_MODE                (1u)

#define Input_Capsense_ADC_MIN_CHANNELS             (1u)
#define Input_Capsense_ADC_EN                       (0u)
#define Input_Capsense_ADC_STANDALONE_EN            (0u)
#define Input_Capsense_ADC_TOTAL_CHANNELS           (1u)
#define Input_Capsense_ADC_RESOLUTION               (Input_Capsense_ADC_RES10BIT)
#define Input_Capsense_ADC_AMUXB_INPUT_EN           (0u)
#define Input_Capsense_ADC_SELECT_AMUXB_CH          (0u)
#define Input_Capsense_ADC_AZ_EN                    (1Lu)
#define Input_Capsense_ADC_AZ_TIME                  (5u)
#define Input_Capsense_ADC_VREF_MV                  (2133u)
#define Input_Capsense_ADC_GAIN                     (17Lu)
#define Input_Capsense_ADC_IDAC_DEFAULT             (19u)
#define Input_Capsense_ADC_MODCLK_DIV_DEFAULT       (1u)
#define Input_Capsense_ADC_MEASURE_MODE             (Input_Capsense_ADC_FULLRANGE_MODE)
#define Input_Capsense_ADC_ANALOG_STARTUP_DELAY_US  (5u)
#define Input_Capsense_ADC_ACQUISITION_TIME_US      (13u)

/*******************************************************************************
* Built-In Self-Test Configuration
*******************************************************************************/
#define Input_Capsense_SELF_TEST_EN                   (0Lu)
#define Input_Capsense_TST_GLOBAL_CRC_EN              (0Lu)
#define Input_Capsense_TST_WDGT_CRC_EN                (0Lu)
#define Input_Capsense_TST_BSLN_DUPLICATION_EN        (0Lu)
#define Input_Capsense_TST_BSLN_RAW_OUT_RANGE_EN      (0Lu)
#define Input_Capsense_TST_SNS_SHORT_EN               (0Lu)
#define Input_Capsense_TST_SNS_CAP_EN                 (0Lu)
#define Input_Capsense_TST_SH_CAP_EN                  (0Lu)
#define Input_Capsense_TST_EXTERNAL_CAP_EN            (0Lu)
#define Input_Capsense_TST_VDDA_EN                    (0Lu)


#define Input_Capsense_GLOBAL_CRC_AREA_START          (0u)
#define Input_Capsense_GLOBAL_CRC_AREA_SIZE           (0u)
#define Input_Capsense_WIDGET_CRC_AREA_START          (0u)
#define Input_Capsense_WIDGET_CRC_AREA_SIZE           (0u)

/* The resolution for sensor capacity measurement */
#define Input_Capsense_TST_SNS_CAP_RESOLUTION         (12u)

/* VDDA measurement test configuration */
/* The resolution for VDDA measurement */
#define Input_Capsense_TST_VDDA_RESOLUTION            (10u)
/* The ModClk divider for external capacitor capacity measurement */
#define Input_Capsense_TST_VDDA_MOD_CLK_DIVIDER       (1u)

#define Input_Capsense_TST_VDDA_VREF_MV               (0u)
#define Input_Capsense_TST_VDDA_VREF_GAIN             (0u)
#define Input_Capsense_TST_VDDA_IDAC_DEFAULT          (0u)

#define Input_Capsense_TST_FINE_INIT_TIME             (10u)
#define Input_Capsense_TST_ANALOG_STARTUP_DELAY_US    (23u)

#define Input_Capsense_TST_IDAC_AUTO_GAIN_EN          (1u)
#define Input_Capsense_TST_SNS_CAP_RAW_ERROR          (10u)
#define Input_Capsense_TST_IDAC_GAIN_INDEX            (0xFFu)
#define Input_Capsense_TST_RAW_TARGET                 (85u)

#define Input_Capsense_TST_SNS_SHORT_TIME             (2u)

#define Input_Capsense_SNS_CAP_CSD_INACTIVE_CONNECTION        (Input_Capsense_SNS_CONNECTION_GROUND)
#define Input_Capsense_SNS_CAP_CSX_INACTIVE_CONNECTION        (Input_Capsense_SNS_CONNECTION_GROUND)
#define Input_Capsense_SHIELD_CAP_INACTIVE_CONNECTION         (Input_Capsense_SNS_CONNECTION_GROUND)


/*******************************************************************************
* Gesture Configuration
*******************************************************************************/
#define Input_Capsense_TIMESTAMP_INTERVAL             (1Lu)
#define Input_Capsense_GESTURE_EN_WIDGET_ID           (0Lu)
#define Input_Capsense_BALLISTIC_EN_WIDGET_ID         (0Lu)


#endif /* CY_SENSE_Input_Capsense_CONFIGURATION_H */


/* [] END OF FILE */
