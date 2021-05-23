/***************************************************************************//**
* \file Input_Capsense_SensingCSD_LL.h
* \version 7.0
*
* \brief
*   This file provides the headers of APIs specific to CSD sensing implementation.
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

#if !defined(CY_SENSE_Input_Capsense_SENSINGCSD_LL_H)
#define CY_SENSE_Input_Capsense_SENSINGCSD_LL_H

#include <CyLib.h>
#include <cyfitter.h>
#include <cytypes.h>
#include <cypins.h>
#include "Input_Capsense_Structure.h"
#include "Input_Capsense_Configuration.h"
#include "Input_Capsense_Sensing.h"

/****************************************************************************
* Register and mode mask definition
****************************************************************************/

#if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
    #define Input_Capsense_CSD_CSDCMP_INIT                                (Input_Capsense_CSDCMP_CSDCMP_DISABLED)

    /* SW_HS_P_SEL switches state for Coarse initialization of CMOD (sense path) */
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
        #if (Input_Capsense_CSD__CMOD_PAD == Input_Capsense_CMOD_CONNECTION)
            #define Input_Capsense_CSD_HS_P_SEL_COARSE_CMOD               (Input_Capsense_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #elif (Input_Capsense_CSD__CSHIELD_PAD == Input_Capsense_CMOD_CONNECTION)
            #define Input_Capsense_CSD_HS_P_SEL_COARSE_CMOD               (Input_Capsense_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #else
            #define Input_Capsense_CSD_HS_P_SEL_COARSE_CMOD               (Input_Capsense_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #endif /* (Input_Capsense_CSD__CMOD_PAD == Input_Capsense_CMOD_CONNECTION) */
    #else
        #define Input_Capsense_CSD_HS_P_SEL_COARSE_CMOD                   (0x00000000uL)
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) */

    #if ((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN) && \
        (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN))
        /* SW_HS_P_SEL switches state for Coarse initialization of CTANK (sense path) */
        #if (Input_Capsense_CSD__CSH_TANK_PAD == Input_Capsense_CTANK_CONNECTION)
            #define Input_Capsense_CSD_HS_P_SEL_COARSE_TANK               (Input_Capsense_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #elif (Input_Capsense_CSD__CSHIELD_PAD == Input_Capsense_CTANK_CONNECTION)
            #define Input_Capsense_CSD_HS_P_SEL_COARSE_TANK               (Input_Capsense_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #elif (Input_Capsense_CSD__CMOD_PAD == Input_Capsense_CTANK_CONNECTION)
            #define Input_Capsense_CSD_HS_P_SEL_COARSE_TANK               (Input_Capsense_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #else
            #define Input_Capsense_CSD_HS_P_SEL_COARSE_TANK               (Input_Capsense_SW_HS_P_SEL_SW_HMMA_STATIC_CLOSE)
        #endif /* (Input_Capsense_CSD__CSH_TANK_PAD == Input_Capsense_CTANK_CONNECTION) */
    #else
        #define Input_Capsense_CSD_HS_P_SEL_COARSE_TANK                   (0x00000000uL)
    #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN) && \
               (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)) */

    #define Input_Capsense_CSD_SW_HS_P_SEL_COARSE                         (Input_Capsense_HS_P_SEL_COARSE_CMOD | Input_Capsense_CSD_HS_P_SEL_COARSE_TANK)

    /* C_mod config */
    #if ((Input_Capsense_CSD__CMOD_PAD == Input_Capsense_CMOD_CONNECTION) || (Input_Capsense_CSD__CMOD_PAD == Input_Capsense_CTANK_CONNECTION))
        #define Input_Capsense_CSD_SW_FW_MOD_SEL_INIT             (Input_Capsense_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE |\
                                                                     Input_Capsense_SW_FW_MOD_SEL_SW_F1MA_STATIC_CLOSE |\
                                                                     Input_Capsense_SW_FW_MOD_SEL_SW_F1CA_STATIC_CLOSE)
        #define Input_Capsense_SW_DSI_SEL_CMODPAD                 (Input_Capsense_SW_DSI_CMOD)
    #else
        #define Input_Capsense_CSD_SW_FW_MOD_SEL_INIT             (0x00000000uL)
        #define Input_Capsense_SW_DSI_SEL_CMODPAD                 (0x00000000uL)
    #endif /* (Input_Capsense_CSD__CMOD_PAD == Input_Capsense_CMOD_CONNECTION) */

    /* C_tank config */
    #if ((Input_Capsense_CSD__CSH_TANK_PAD == Input_Capsense_CMOD_CONNECTION) || (Input_Capsense_CSD__CSH_TANK_PAD == Input_Capsense_CTANK_CONNECTION))
        #define Input_Capsense_CSD_SW_FW_TANK_SEL_INIT            (Input_Capsense_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                     Input_Capsense_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE |\
                                                                     Input_Capsense_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE)
        #define Input_Capsense_SW_DSI_SEL_TANKPAD                 (Input_Capsense_SW_DSI_CTANK)
    #else
        #define Input_Capsense_CSD_SW_FW_TANK_SEL_INIT            (0x00000000uL)
        #define Input_Capsense_SW_DSI_SEL_TANKPAD                 (0x00000000uL)
    #endif /* (Input_Capsense_CSD__CSH_TANK_PAD == Input_Capsense_CTANK_CONNECTION) */

    #define Input_Capsense_CSD_SW_SHIELD_SEL_INIT                 (Input_Capsense_SW_SHIELD_SEL_SW_HCAV_HSCMP)

    /* Defining default HW configuration according to settings in customizer. */
    #define Input_Capsense_DEFAULT_CSD_CONFIG                 (Input_Capsense_CONFIG_FILTER_DELAY_12MHZ |\
                                                                 Input_Capsense_CONFIG_SAMPLE_SYNC_MASK)
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_AUTO_ZERO_EN)
        /* Enable CSDCMP */
        #define Input_Capsense_CSD_CSDCMP_SCAN                (Input_Capsense_CSDCMP_CSDCMP_EN_MASK |\
                                                                 Input_Capsense_CSDCMP_AZ_EN_MASK)
    #else
        /* Enable CSDCMP */
        #define Input_Capsense_CSD_CSDCMP_SCAN                (Input_Capsense_CSDCMP_CSDCMP_EN_MASK)
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_AUTO_ZERO_EN) */

    #if ((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN) && \
        (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN))
        /* SW_HS_P_SEL switches state for Coarse initialization of CTANK (sense path) */
        #if (Input_Capsense_CSD__CSH_TANK_PAD == Input_Capsense_CTANK_CONNECTION)
            #define Input_Capsense_CSD_HS_P_SEL_SCAN_TANK                 (Input_Capsense_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #elif (Input_Capsense_CSD__CSHIELD_PAD == Input_Capsense_CTANK_CONNECTION)
            #define Input_Capsense_CSD_HS_P_SEL_SCAN_TANK                 (Input_Capsense_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #elif (Input_Capsense_CSD__CMOD_PAD == Input_Capsense_CTANK_CONNECTION)
            #define Input_Capsense_CSD_HS_P_SEL_SCAN_TANK                 (Input_Capsense_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #else
            #define Input_Capsense_CSD_HS_P_SEL_SCAN_TANK                 (Input_Capsense_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
        #endif /* (Input_Capsense_CSD__CSH_TANK_PAD == Input_Capsense_CTANK_CONNECTION) */
        #define Input_Capsense_CSD_SW_HS_P_SEL_SCAN                       (Input_Capsense_HS_P_SEL_SCAN_TANK)
    #elif(Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
        #define Input_Capsense_CSD_SW_HS_P_SEL_SCAN                       (Input_Capsense_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
    #else
        #define Input_Capsense_CSD_SW_HS_P_SEL_SCAN                       (Input_Capsense_STATIC_OPEN)
    #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN) && \
               (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)) */

    /* SW_FW_MOD_SEL switches state for Coarse initialization of CMOD (sense path) */
    #define Input_Capsense_CSD_SW_FW_MOD_SEL_SCAN                     (0x00000000uL)

    #if((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) && \
        (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN) && \
        (Input_Capsense_CSD__CSH_TANK_PAD == Input_Capsense_CTANK_CONNECTION))
        #define Input_Capsense_CSD_SW_FW_TANK_SEL_SCAN                (Input_Capsense_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE | \
                                                                         Input_Capsense_SW_FW_TANK_SEL_SW_F2CB_STATIC_CLOSE)
    #else
        #define Input_Capsense_CSD_SW_FW_TANK_SEL_SCAN                (0x00000000uL)
    #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) && \
               (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN) && \
               (Input_Capsense_CSD__CSH_TANK_PAD == Input_Capsense_CTANK_CONNECTION)) */

    /* Shield switch default config */
    #if ((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) && \
         (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN))
        #if (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG)
            #define Input_Capsense_CSD_SW_SHIELD_SEL_SCAN             (Input_Capsense_SW_SHIELD_SEL_SW_HCBG_HSCMP)
        #else
            #define Input_Capsense_CSD_SW_SHIELD_SEL_SCAN             (Input_Capsense_SW_SHIELD_SEL_SW_HCBV_HSCMP)
        #endif /* (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG) */
    #elif(Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
        #if (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG)
            #define Input_Capsense_CSD_SW_SHIELD_SEL_SCAN             (Input_Capsense_SW_SHIELD_SEL_SW_HCBV_PHI1 | \
                                                                         Input_Capsense_SW_SHIELD_SEL_SW_HCBG_PHI2_HSCMP)
        #else
            #define Input_Capsense_CSD_SW_SHIELD_SEL_SCAN             (Input_Capsense_SW_SHIELD_SEL_SW_HCBG_PHI1 | \
                                                                         Input_Capsense_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP)
        #endif /* (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG) */
    #else
        #define Input_Capsense_CSD_SW_SHIELD_SEL_SCAN                 (0x00000000uL)
    #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) && \
               (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN)) */

    #define Input_Capsense_CSD_SW_RES_INIT                            (Input_Capsense_CSD_INIT_SWITCH_RES << CYFLD_CSD_RES_HCAV__OFFSET)
    #define Input_Capsense_CSD_SW_RES_SCAN                            ((Input_Capsense_CSD_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBV__OFFSET) |\
                                                                         (Input_Capsense_CSD_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBG__OFFSET))

    #define Input_Capsense_CSD_SHIELD_GPIO_DM                         (Input_Capsense_GPIO_STRGDRV)
    #define Input_Capsense_CSD_SENSOR_HSIOM_SEL                       (Input_Capsense_HSIOM_SEL_CSD_SENSE)
    #define Input_Capsense_CSD_SHIELD_HSIOM_SEL                       (Input_Capsense_HSIOM_SEL_CSD_SHIELD)
    #define Input_Capsense_CSD_CMOD_HSIOM_SEL                         (Input_Capsense_HSIOM_SEL_AMUXA)

    #define Input_Capsense_DEFAULT_IDAC_MOD_BALL_MODE                 ((uint32)Input_Capsense_IDAC_MOD_BALL_MODE_FULL <<\
                                                                         CYFLD_CSD_BAL_MODE__OFFSET)
    #define Input_Capsense_DEFAULT_IDAC_COMP_BALL_MODE                ((uint32)Input_Capsense_IDAC_COMP_BALL_MODE_FULL <<\
                                                                         CYFLD_CSD_BAL_MODE__OFFSET)

    #define Input_Capsense_DEFAULT_SENSE_DUTY_SEL                     (Input_Capsense_SENSE_DUTY_OVERLAP_PHI1_MASK |\
                                                                         Input_Capsense_SENSE_DUTY_OVERLAP_PHI2_MASK)

    #define Input_Capsense_CSD_CAL_MIDDLE_VALUE                       (0x40u)
    #define Input_Capsense_CSD_CAL_IDAC_MAX_VALUE                     (127u)

    #define Input_Capsense_DELAY_EXTRACYCLES_NUM                      (9u)

    /* Clock Source Mode */
    #if (Input_Capsense_CLK_SOURCE_DIRECT == Input_Capsense_CSD_SNS_CLK_SOURCE)
        #define Input_Capsense_DEFAULT_MODULATION_MODE                (Input_Capsense_CLK_SOURCE_DIRECT)
    #elif (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE)
        #define Input_Capsense_DEFAULT_MODULATION_MODE                (Input_Capsense_CLK_SOURCE_SSC2)
    #elif ((Input_Capsense_CLK_SOURCE_PRS8) == Input_Capsense_CSD_SNS_CLK_SOURCE)
        #define Input_Capsense_DEFAULT_MODULATION_MODE                (Input_Capsense_CSD_SNS_CLK_SOURCE)
    #elif ((Input_Capsense_CLK_SOURCE_PRS12) == Input_Capsense_CSD_SNS_CLK_SOURCE)
        #define Input_Capsense_DEFAULT_MODULATION_MODE                (Input_Capsense_CSD_SNS_CLK_SOURCE)
    #else
        #define Input_Capsense_DEFAULT_MODULATION_MODE                (Input_Capsense_CSD_SNS_CLK_SOURCE)
    #endif /* (Input_Capsense_CLK_SOURCE_DIRECT != Input_Capsense_CSD_SNS_CLK_SOURCE) */

    /* IDACs Ranges */
    #if (Input_Capsense_IDAC_GAIN_LOW == Input_Capsense_CSD_IDAC_GAIN)
        #define Input_Capsense_DEFAULT_IDAC_MOD_RANGE                 ((uint32)Input_Capsense_IDAC_MOD_RANGE_IDAC_LO << CYFLD_CSD_RANGE__OFFSET)
        #define Input_Capsense_DEFAULT_IDAC_COMP_RANGE                ((uint32)Input_Capsense_IDAC_COMP_RANGE_IDAC_LO << CYFLD_CSD_RANGE__OFFSET)
    #elif (Input_Capsense_IDAC_GAIN_MEDIUM == Input_Capsense_CSD_IDAC_GAIN)
        #define Input_Capsense_DEFAULT_IDAC_MOD_RANGE                 ((uint32)Input_Capsense_IDAC_MOD_RANGE_IDAC_MED << CYFLD_CSD_RANGE__OFFSET)
        #define Input_Capsense_DEFAULT_IDAC_COMP_RANGE                ((uint32)Input_Capsense_IDAC_COMP_RANGE_IDAC_MED << CYFLD_CSD_RANGE__OFFSET)
    #else
        #define Input_Capsense_DEFAULT_IDAC_MOD_RANGE                 ((uint32)Input_Capsense_IDAC_MOD_RANGE_IDAC_HI << CYFLD_CSD_RANGE__OFFSET)
        #define Input_Capsense_DEFAULT_IDAC_COMP_RANGE                ((uint32)Input_Capsense_IDAC_COMP_RANGE_IDAC_HI << CYFLD_CSD_RANGE__OFFSET)
    #endif

    /* IDACs Polarities */
    #if (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG)
        #define Input_Capsense_DEFAULT_IDAC_MOD_POLARITY              ((uint32)Input_Capsense_IDAC_MOD_POLARITY_VDDA_SNK << CYFLD_CSD_POLARITY__OFFSET)
        #define Input_Capsense_DEFAULT_IDAC_COMP_POLARITY             ((uint32)Input_Capsense_IDAC_COMP_POLARITY_VDDA_SNK << CYFLD_CSD_POLARITY__OFFSET)
    #else
        #define Input_Capsense_DEFAULT_IDAC_MOD_POLARITY              ((uint32)Input_Capsense_IDAC_MOD_POLARITY_VSSA_SRC << CYFLD_CSD_POLARITY__OFFSET)
        #define Input_Capsense_DEFAULT_IDAC_COMP_POLARITY             ((uint32)Input_Capsense_IDAC_COMP_POLARITY_VSSA_SRC << CYFLD_CSD_POLARITY__OFFSET)
    #endif /* (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG) */

    #define Input_Capsense_SW_REFGEN_VREF_SRC                         (Input_Capsense_SW_REFGEN_SEL_SW_SGR_MASK)

    /* IDAC legs configuration */
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
            #define Input_Capsense_DEFAULT_SW_REFGEN_SEL              (Input_Capsense_SW_REFGEN_VREF_SRC | Input_Capsense_SW_REFGEN_SEL_SW_IAIB_MASK)
    #else
            #define Input_Capsense_DEFAULT_SW_REFGEN_SEL              (Input_Capsense_SW_REFGEN_VREF_SRC)
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) */

    /* IDACs register configuration is based on the Component configuration */
    #define Input_Capsense_IDAC_MOD_DEFAULT_CFG                       (Input_Capsense_DEFAULT_IDAC_MOD_RANGE | \
                                                                         Input_Capsense_DEFAULT_IDAC_MOD_POLARITY | \
                                                                         Input_Capsense_DEFAULT_IDAC_MOD_BALL_MODE | \
                                                                        ((uint32)(Input_Capsense_IDAC_MOD_LEG1_MODE_CSD << CYFLD_CSD_LEG1_MODE__OFFSET)) | \
                                                                        ((uint32)(Input_Capsense_IDAC_MOD_LEG2_MODE_CSD << CYFLD_CSD_LEG2_MODE__OFFSET)) | \
                                                                         Input_Capsense_IDAC_MOD_LEG1_EN_MASK)

    #define Input_Capsense_IDAC_COMP_DEFAULT_CFG                      (Input_Capsense_DEFAULT_IDAC_COMP_RANGE | \
                                                                         Input_Capsense_DEFAULT_IDAC_COMP_POLARITY | \
                                                                         Input_Capsense_DEFAULT_IDAC_COMP_BALL_MODE | \
                                                                        ((uint32)(Input_Capsense_IDAC_COMP_LEG1_MODE_CSD_STATIC << CYFLD_CSD_LEG1_MODE__OFFSET)) | \
                                                                        ((uint32)(Input_Capsense_IDAC_COMP_LEG2_MODE_CSD_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET)) | \
                                                                         Input_Capsense_IDAC_COMP_LEG1_EN_MASK)

    #define Input_Capsense_IDAC_MOD_CALIBRATION_CFG                   ((uint32)(Input_Capsense_DEFAULT_IDAC_MOD_RANGE | \
                                                                         Input_Capsense_DEFAULT_IDAC_MOD_POLARITY | \
                                                                         Input_Capsense_DEFAULT_IDAC_MOD_BALL_MODE | \
                                                                        ((uint32)(Input_Capsense_IDAC_MOD_LEG1_MODE_CSD << CYFLD_CSD_LEG1_MODE__OFFSET)) | \
                                                                         Input_Capsense_IDAC_MOD_LEG1_EN_MASK | \
                                                                        ((uint32)((uint32)Input_Capsense_IDAC_MOD_LEG2_MODE_GP_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET))))

    #define Input_Capsense_IDAC_COMP_CALIBRATION_CFG                  ((uint32)(Input_Capsense_DEFAULT_IDAC_COMP_RANGE | \
                                                                         Input_Capsense_DEFAULT_IDAC_COMP_POLARITY | \
                                                                         Input_Capsense_DEFAULT_IDAC_COMP_BALL_MODE | \
                                                                        ((uint32)((uint32)Input_Capsense_IDAC_COMP_LEG1_MODE_GP_STATIC << CYFLD_CSD_LEG1_MODE__OFFSET)) | \
                                                                        ((uint32)((uint32)Input_Capsense_IDAC_COMP_LEG2_MODE_GP_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET))))
#else
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
        #define Input_Capsense_CSD_CAL_IDAC_MAX_VALUE                 (127u)
        #define Input_Capsense_CSD_CAL_MIDDLE_VALUE                   (0x40u)
    #else
        #define Input_Capsense_CSD_CAL_IDAC_MAX_VALUE                 (255u)
        #define Input_Capsense_CSD_CAL_MIDDLE_VALUE                   (0x80u)
    #endif

    #define Input_Capsense_IDAC_MOD_CFG_MASK                  (Input_Capsense_IDAC_POLARITY1_MIR_MASK |\
                                                                Input_Capsense_IDAC_MOD_RANGE_MASK |\
                                                                Input_Capsense_IDAC_MOD_MODE_MASK |\
                                                                Input_Capsense_IDAC_MOD_MASK)

    #define Input_Capsense_IDAC_COMP_CFG_MASK                 (Input_Capsense_IDAC_POLARITY2_MIR_MASK |\
                                                                Input_Capsense_IDAC_COMP_RANGE_MASK |\
                                                                Input_Capsense_IDAC_COMP_MODE_MASK |\
                                                                Input_Capsense_IDAC_COMP_MASK)

        #define Input_Capsense_PRS_8_CONFIG                       Input_Capsense_CONFIG_PRS_SELECT_MASK
    #define Input_Capsense_PRS_12_CONFIG                      (Input_Capsense_CONFIG_PRS_12_8_MASK |\
                                                                Input_Capsense_CONFIG_PRS_SELECT_MASK)

    /* Third-generation HW block Initial PRS mode */
    #if (Input_Capsense_CLK_SOURCE_PRS8 == Input_Capsense_CSD_SNS_CLK_SOURCE)
        #define Input_Capsense_DEFAULT_MODULATION_MODE        Input_Capsense_CONFIG_PRS_SELECT_MASK

    #elif (Input_Capsense_CLK_SOURCE_PRS12 == Input_Capsense_CSD_SNS_CLK_SOURCE)
        #define Input_Capsense_DEFAULT_MODULATION_MODE        (Input_Capsense_CONFIG_PRS_12_8_MASK |\
                                                                Input_Capsense_CONFIG_PRS_SELECT_MASK)
    #else
        #define Input_Capsense_DEFAULT_MODULATION_MODE        (0u)
    #endif /* (Input_Capsense_CSD_SNS_CLK_SOURCE == Input_Capsense_PRS_8BITS) */

    /* Defining default CSD configuration according to settings in customizer. */
    #define Input_Capsense_DEFAULT_CSD_CONFIG                 (Input_Capsense_CONFIG_SENSE_COMP_BW_MASK |\
                                                                Input_Capsense_DEFAULT_IDAC_POLARITY |\
                                                                Input_Capsense_CONFIG_SENSE_INSEL_MASK |\
                                                                Input_Capsense_CONFIG_REFBUF_DRV_MASK)

    /* Third-generation HW block Defining mask intended for clearing bits related to pre-charging options. */
    #define Input_Capsense_PRECHARGE_CONFIG_MASK              (Input_Capsense_CONFIG_REFBUF_EN_MASK |\
                                                                Input_Capsense_CONFIG_COMP_MODE_MASK |\
                                                                Input_Capsense_CONFIG_COMP_PIN_MASK  |\
                                                                Input_Capsense_CONFIG_REFBUF_OUTSEL_MASK)

    #define Input_Capsense_CMOD_PRECHARGE_CONFIG              (Input_Capsense_DEFAULT_CSD_CONFIG |\
                                                                Input_Capsense_CONFIG_REFBUF_EN_MASK |\
                                                                Input_Capsense_CONFIG_COMP_PIN_MASK)

    #define Input_Capsense_CMOD_PRECHARGE_CONFIG_CSD_EN       (Input_Capsense_DEFAULT_CSD_CONFIG |\
                                                                Input_Capsense_CSD_ENABLE_MASK |\
                                                                Input_Capsense_CONFIG_REFBUF_EN_MASK |\
                                                                Input_Capsense_CONFIG_COMP_PIN_MASK)


    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
        #if((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN) &&\
            (Input_Capsense_CSH_PRECHARGE_IO_BUF == Input_Capsense_CSD_CSH_PRECHARGE_SRC))
            #define  Input_Capsense_CTANK_PRECHARGE_CONFIG    (Input_Capsense_DEFAULT_CSD_CONFIG |\
                                                                 Input_Capsense_CONFIG_REFBUF_OUTSEL_MASK |\
                                                                 Input_Capsense_CONFIG_REFBUF_EN_MASK |\
                                                                 Input_Capsense_CONFIG_COMP_MODE_MASK |\
                                                                 Input_Capsense_CONFIG_PRS_CLEAR_MASK |\
                                                                 Input_Capsense_CONFIG_COMP_PIN_MASK)
        #else
            #define  Input_Capsense_CTANK_PRECHARGE_CONFIG    (Input_Capsense_DEFAULT_CSD_CONFIG |\
                                                                 Input_Capsense_CONFIG_REFBUF_EN_MASK |\
                                                                 Input_Capsense_CONFIG_PRS_CLEAR_MASK |\
                                                                 Input_Capsense_CONFIG_REFBUF_OUTSEL_MASK)
        #endif
    #else
        #define  Input_Capsense_CTANK_PRECHARGE_CONFIG    (Input_Capsense_DEFAULT_CSD_CONFIG |\
                                                             Input_Capsense_CONFIG_REFBUF_OUTSEL_MASK |\
                                                             Input_Capsense_CONFIG_PRS_CLEAR_MASK)
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */


    #define  Input_Capsense_CTANK_PRECHARGE_CONFIG_CSD_EN     (Input_Capsense_CTANK_PRECHARGE_CONFIG |\
                                                                 Input_Capsense_CONFIG_ENABLE_MASK |\
                                                                 Input_Capsense_CONFIG_SENSE_COMP_EN_MASK)

#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */

#define Input_Capsense_CSD_AVG_CYCLES_PER_LOOP                   (5u)
#define Input_Capsense_CSD_MEASURE_MAX_TIME_US                   (200000u)
#define Input_Capsense_CSD_PRECHARGE_MAX_TIME_US                 (50u)
#define Input_Capsense_CSD_ONE_CLOCK_MAX_TIME_US                 (50u)
#define Input_Capsense_WIDGET_MAX_SCAN_TIME_US                   (5u * 1000000u)

#define Input_Capsense_CSD_CALIBR_WATCHDOG_CYCLES_NUM            (((CYDEV_BCLK__SYSCLK__MHZ) * (Input_Capsense_CSD_MEASURE_MAX_TIME_US)) /\
                                                                    (Input_Capsense_CSD_AVG_CYCLES_PER_LOOP))
#define Input_Capsense_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM         (((CYDEV_BCLK__SYSCLK__MHZ) * (Input_Capsense_CSD_PRECHARGE_MAX_TIME_US)) /\
                                                                    (Input_Capsense_CSD_AVG_CYCLES_PER_LOOP))
#define Input_Capsense_ONE_CLOCK_WATCHDOG_CYCLES_NUM             (((CYDEV_BCLK__SYSCLK__MHZ) * (Input_Capsense_CSD_ONE_CLOCK_MAX_TIME_US)) /\
                                                                    (Input_Capsense_CSD_AVG_CYCLES_PER_LOOP))
#define Input_Capsense_WIDGET_MAX_SCAN_TIME                      (((CYDEV_BCLK__SYSCLK__MHZ) * (Input_Capsense_WIDGET_MAX_SCAN_TIME_US)) /\
                                                                    (Input_Capsense_CSD_AVG_CYCLES_PER_LOOP))

/***************************************
* Global software variables
***************************************/

extern uint32 Input_Capsense_configCsd;

#if (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN)
    extern uint8 Input_Capsense_badConversionsNum;
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN) */


/***************************************
* Function Prototypes
**************************************/

/**
* \cond SECTION_C_LOW_LEVEL
* \addtogroup group_c_low_level
* \{
*/

void Input_Capsense_CSDSetupWidget(uint32 widgetId);
void Input_Capsense_CSDSetupWidgetExt(uint32 widgetId, uint32 sensorId);
void Input_Capsense_CSDScan(void);
void Input_Capsense_CSDScanExt(void);
#if ((Input_Capsense_CSD_SS_DIS != Input_Capsense_CSD_AUTOTUNE) || \
     (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTOCAL_EN))
    cystatus Input_Capsense_CSDCalibrateWidget(uint32 widgetId, uint32 target);
#endif /* ((Input_Capsense_CSD_SS_DIS != Input_Capsense_CSD_AUTOTUNE) || \
           (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTOCAL_EN))  */
void Input_Capsense_CSDConnectSns(Input_Capsense_FLASH_IO_STRUCT const *snsAddrPtr);
void Input_Capsense_CSDDisconnectSns(Input_Capsense_FLASH_IO_STRUCT const *snsAddrPtr);

/** \}
* \endcond */

/*****************************************************
* Function Prototypes - internal Low Level functions
*****************************************************/

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

void Input_Capsense_SsCSDInitialize(void);
void Input_Capsense_SsCSDStartSample(void);
void Input_Capsense_SsCSDSetUpIdacs(Input_Capsense_RAM_WD_BASE_STRUCT const *ptrWdgt);
void Input_Capsense_SsCSDConfigClock(void);
void Input_Capsense_SsCSDElectrodeCheck(void);
#if ((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) && \
     (0u != Input_Capsense_CSD_TOTAL_SHIELD_COUNT))
    void Input_Capsense_SsCSDEnableShieldElectrodes(void);
    void Input_Capsense_SsCSDDisableShieldElectrodes(void);
    void Input_Capsense_SsCSDSetShieldElectrodesState(uint32 state);
#endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) && \
           (0u != Input_Capsense_CSD_TOTAL_SHIELD_COUNT)) */
#if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
    uint32 Input_Capsense_SsCSDGetNumberOfConversions(uint32 snsClkDivider, uint32 resolution, uint32 snsClkSrc);
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
void Input_Capsense_SsCSDCalculateScanDuration(Input_Capsense_RAM_WD_BASE_STRUCT const *ptrWdgt);
void Input_Capsense_SsCSDConnectSensorExt(uint32 widgetId, uint32 sensorId);
void Input_Capsense_SsCSDDisconnectSnsExt(uint32 widgetId, uint32 sensorId);

#if ((Input_Capsense_CSD_SS_DIS != Input_Capsense_CSD_AUTOTUNE) || \
     (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN) || \
     (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTOCAL_EN))
#endif /* ((Input_Capsense_CSD_SS_DIS != Input_Capsense_CSD_AUTOTUNE) || \
           (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN) || \
           (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTOCAL_EN)) */

/** \}
* \endcond */

/***************************************
* Global software variables
***************************************/
extern uint32 Input_Capsense_configCsd;

/* Interrupt handler */
extern CY_ISR_PROTO(Input_Capsense_CSDPostSingleScan);
extern CY_ISR_PROTO(Input_Capsense_CSDPostMultiScan);
#if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
extern CY_ISR_PROTO(Input_Capsense_CSDPostMultiScanGanged);
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN) */
#if (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN)
    extern uint8 Input_Capsense_badConversionsNum;
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN) */

#endif /* End CY_SENSE_Input_Capsense_SENSINGCSD_LL_H */


/* [] END OF FILE */
