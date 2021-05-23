/***************************************************************************//**
* \file Input_Capsense_RegisterMap.h
* \version 7.0
*
* \brief
*   This file provides the definitions for the Component data structure register.
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

#if !defined(CY_SENSE_Input_Capsense_REGISTER_MAP_H)
#define CY_SENSE_Input_Capsense_REGISTER_MAP_H

#include <cytypes.h>
#include "Input_Capsense_Configuration.h"
#include "Input_Capsense_Structure.h"

/*****************************************************************************/
/* RAM Data structure register definitions                                   */
/*****************************************************************************/
#define Input_Capsense_CONFIG_ID_VALUE                      (Input_Capsense_dsRam.configId)
#define Input_Capsense_CONFIG_ID_OFFSET                     (0u)
#define Input_Capsense_CONFIG_ID_SIZE                       (2u)
#define Input_Capsense_CONFIG_ID_PARAM_ID                   (0x87000000u)

#define Input_Capsense_DEVICE_ID_VALUE                      (Input_Capsense_dsRam.deviceId)
#define Input_Capsense_DEVICE_ID_OFFSET                     (2u)
#define Input_Capsense_DEVICE_ID_SIZE                       (2u)
#define Input_Capsense_DEVICE_ID_PARAM_ID                   (0x8B000002u)

#define Input_Capsense_HW_CLOCK_VALUE                       (Input_Capsense_dsRam.hwClock)
#define Input_Capsense_HW_CLOCK_OFFSET                      (4u)
#define Input_Capsense_HW_CLOCK_SIZE                        (2u)
#define Input_Capsense_HW_CLOCK_PARAM_ID                    (0x86000004u)

#define Input_Capsense_TUNER_CMD_VALUE                      (Input_Capsense_dsRam.tunerCmd)
#define Input_Capsense_TUNER_CMD_OFFSET                     (6u)
#define Input_Capsense_TUNER_CMD_SIZE                       (2u)
#define Input_Capsense_TUNER_CMD_PARAM_ID                   (0xA1000006u)

#define Input_Capsense_SCAN_COUNTER_VALUE                   (Input_Capsense_dsRam.scanCounter)
#define Input_Capsense_SCAN_COUNTER_OFFSET                  (8u)
#define Input_Capsense_SCAN_COUNTER_SIZE                    (2u)
#define Input_Capsense_SCAN_COUNTER_PARAM_ID                (0x85000008u)

#define Input_Capsense_STATUS_VALUE                         (Input_Capsense_dsRam.status)
#define Input_Capsense_STATUS_OFFSET                        (12u)
#define Input_Capsense_STATUS_SIZE                          (4u)
#define Input_Capsense_STATUS_PARAM_ID                      (0xCB00000Cu)

#define Input_Capsense_WDGT_ENABLE0_VALUE                   (Input_Capsense_dsRam.wdgtEnable[0u])
#define Input_Capsense_WDGT_ENABLE0_OFFSET                  (16u)
#define Input_Capsense_WDGT_ENABLE0_SIZE                    (4u)
#define Input_Capsense_WDGT_ENABLE0_PARAM_ID                (0xE6000010u)

#define Input_Capsense_WDGT_STATUS0_VALUE                   (Input_Capsense_dsRam.wdgtStatus[0u])
#define Input_Capsense_WDGT_STATUS0_OFFSET                  (20u)
#define Input_Capsense_WDGT_STATUS0_SIZE                    (4u)
#define Input_Capsense_WDGT_STATUS0_PARAM_ID                (0xCC000014u)

#define Input_Capsense_SNS_STATUS0_VALUE                    (Input_Capsense_dsRam.snsStatus[0u])
#define Input_Capsense_SNS_STATUS0_OFFSET                   (24u)
#define Input_Capsense_SNS_STATUS0_SIZE                     (1u)
#define Input_Capsense_SNS_STATUS0_PARAM_ID                 (0x48000018u)

#define Input_Capsense_SNS_STATUS1_VALUE                    (Input_Capsense_dsRam.snsStatus[1u])
#define Input_Capsense_SNS_STATUS1_OFFSET                   (25u)
#define Input_Capsense_SNS_STATUS1_SIZE                     (1u)
#define Input_Capsense_SNS_STATUS1_PARAM_ID                 (0x4E000019u)

#define Input_Capsense_SNS_STATUS2_VALUE                    (Input_Capsense_dsRam.snsStatus[2u])
#define Input_Capsense_SNS_STATUS2_OFFSET                   (26u)
#define Input_Capsense_SNS_STATUS2_SIZE                     (1u)
#define Input_Capsense_SNS_STATUS2_PARAM_ID                 (0x4400001Au)

#define Input_Capsense_SNS_STATUS3_VALUE                    (Input_Capsense_dsRam.snsStatus[3u])
#define Input_Capsense_SNS_STATUS3_OFFSET                   (27u)
#define Input_Capsense_SNS_STATUS3_SIZE                     (1u)
#define Input_Capsense_SNS_STATUS3_PARAM_ID                 (0x4200001Bu)

#define Input_Capsense_SNS_STATUS4_VALUE                    (Input_Capsense_dsRam.snsStatus[4u])
#define Input_Capsense_SNS_STATUS4_OFFSET                   (28u)
#define Input_Capsense_SNS_STATUS4_SIZE                     (1u)
#define Input_Capsense_SNS_STATUS4_PARAM_ID                 (0x4900001Cu)

#define Input_Capsense_SNS_STATUS5_VALUE                    (Input_Capsense_dsRam.snsStatus[5u])
#define Input_Capsense_SNS_STATUS5_OFFSET                   (29u)
#define Input_Capsense_SNS_STATUS5_SIZE                     (1u)
#define Input_Capsense_SNS_STATUS5_PARAM_ID                 (0x4F00001Du)

#define Input_Capsense_SNS_STATUS6_VALUE                    (Input_Capsense_dsRam.snsStatus[6u])
#define Input_Capsense_SNS_STATUS6_OFFSET                   (30u)
#define Input_Capsense_SNS_STATUS6_SIZE                     (1u)
#define Input_Capsense_SNS_STATUS6_PARAM_ID                 (0x4500001Eu)

#define Input_Capsense_SNS_STATUS7_VALUE                    (Input_Capsense_dsRam.snsStatus[7u])
#define Input_Capsense_SNS_STATUS7_OFFSET                   (31u)
#define Input_Capsense_SNS_STATUS7_SIZE                     (1u)
#define Input_Capsense_SNS_STATUS7_PARAM_ID                 (0x4300001Fu)

#define Input_Capsense_SNS_STATUS8_VALUE                    (Input_Capsense_dsRam.snsStatus[8u])
#define Input_Capsense_SNS_STATUS8_OFFSET                   (32u)
#define Input_Capsense_SNS_STATUS8_SIZE                     (1u)
#define Input_Capsense_SNS_STATUS8_PARAM_ID                 (0x45000020u)

#define Input_Capsense_SNS_STATUS9_VALUE                    (Input_Capsense_dsRam.snsStatus[9u])
#define Input_Capsense_SNS_STATUS9_OFFSET                   (33u)
#define Input_Capsense_SNS_STATUS9_SIZE                     (1u)
#define Input_Capsense_SNS_STATUS9_PARAM_ID                 (0x43000021u)

#define Input_Capsense_SNS_STATUS10_VALUE                   (Input_Capsense_dsRam.snsStatus[10u])
#define Input_Capsense_SNS_STATUS10_OFFSET                  (34u)
#define Input_Capsense_SNS_STATUS10_SIZE                    (1u)
#define Input_Capsense_SNS_STATUS10_PARAM_ID                (0x49000022u)

#define Input_Capsense_SNS_STATUS11_VALUE                   (Input_Capsense_dsRam.snsStatus[11u])
#define Input_Capsense_SNS_STATUS11_OFFSET                  (35u)
#define Input_Capsense_SNS_STATUS11_SIZE                    (1u)
#define Input_Capsense_SNS_STATUS11_PARAM_ID                (0x4F000023u)

#define Input_Capsense_SNS_STATUS12_VALUE                   (Input_Capsense_dsRam.snsStatus[12u])
#define Input_Capsense_SNS_STATUS12_OFFSET                  (36u)
#define Input_Capsense_SNS_STATUS12_SIZE                    (1u)
#define Input_Capsense_SNS_STATUS12_PARAM_ID                (0x44000024u)

#define Input_Capsense_CSD0_CONFIG_VALUE                    (Input_Capsense_dsRam.csd0Config)
#define Input_Capsense_CSD0_CONFIG_OFFSET                   (38u)
#define Input_Capsense_CSD0_CONFIG_SIZE                     (2u)
#define Input_Capsense_CSD0_CONFIG_PARAM_ID                 (0xA6800026u)

#define Input_Capsense_MOD_CSD_CLK_VALUE                    (Input_Capsense_dsRam.modCsdClk)
#define Input_Capsense_MOD_CSD_CLK_OFFSET                   (40u)
#define Input_Capsense_MOD_CSD_CLK_SIZE                     (1u)
#define Input_Capsense_MOD_CSD_CLK_PARAM_ID                 (0x61800028u)

#define Input_Capsense_SW100_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw100.resolution)
#define Input_Capsense_SW100_RESOLUTION_OFFSET              (42u)
#define Input_Capsense_SW100_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW100_RESOLUTION_PARAM_ID            (0x8E80002Au)

#define Input_Capsense_SW100_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw100.fingerTh)
#define Input_Capsense_SW100_FINGER_TH_OFFSET               (44u)
#define Input_Capsense_SW100_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW100_FINGER_TH_PARAM_ID             (0x8380002Cu)

#define Input_Capsense_SW100_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw100.noiseTh)
#define Input_Capsense_SW100_NOISE_TH_OFFSET                (46u)
#define Input_Capsense_SW100_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW100_NOISE_TH_PARAM_ID              (0x4780002Eu)

#define Input_Capsense_SW100_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw100.nNoiseTh)
#define Input_Capsense_SW100_NNOISE_TH_OFFSET               (47u)
#define Input_Capsense_SW100_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW100_NNOISE_TH_PARAM_ID             (0x4180002Fu)

#define Input_Capsense_SW100_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw100.hysteresis)
#define Input_Capsense_SW100_HYSTERESIS_OFFSET              (48u)
#define Input_Capsense_SW100_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW100_HYSTERESIS_PARAM_ID            (0x4D800030u)

#define Input_Capsense_SW100_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw100.onDebounce)
#define Input_Capsense_SW100_ON_DEBOUNCE_OFFSET             (49u)
#define Input_Capsense_SW100_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW100_ON_DEBOUNCE_PARAM_ID           (0x4B800031u)

#define Input_Capsense_SW100_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw100.lowBslnRst)
#define Input_Capsense_SW100_LOW_BSLN_RST_OFFSET            (50u)
#define Input_Capsense_SW100_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW100_LOW_BSLN_RST_PARAM_ID          (0x41800032u)

#define Input_Capsense_SW100_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw100.idacMod[0u])
#define Input_Capsense_SW100_IDAC_MOD0_OFFSET               (51u)
#define Input_Capsense_SW100_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW100_IDAC_MOD0_PARAM_ID             (0x4A000033u)

#define Input_Capsense_SW100_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw100.idacGainIndex)
#define Input_Capsense_SW100_IDAC_GAIN_INDEX_OFFSET         (52u)
#define Input_Capsense_SW100_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW100_IDAC_GAIN_INDEX_PARAM_ID       (0x4C800034u)

#define Input_Capsense_SW100_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw100.snsClk)
#define Input_Capsense_SW100_SNS_CLK_OFFSET                 (54u)
#define Input_Capsense_SW100_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW100_SNS_CLK_PARAM_ID               (0x88800036u)

#define Input_Capsense_SW100_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw100.snsClkSource)
#define Input_Capsense_SW100_SNS_CLK_SOURCE_OFFSET          (56u)
#define Input_Capsense_SW100_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW100_SNS_CLK_SOURCE_PARAM_ID        (0x4F800038u)

#define Input_Capsense_SW100_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw100.fingerCap)
#define Input_Capsense_SW100_FINGER_CAP_OFFSET              (58u)
#define Input_Capsense_SW100_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW100_FINGER_CAP_PARAM_ID            (0xAD00003Au)

#define Input_Capsense_SW100_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw100.sigPFC)
#define Input_Capsense_SW100_SIGPFC_OFFSET                  (60u)
#define Input_Capsense_SW100_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW100_SIGPFC_PARAM_ID                (0xA000003Cu)

#define Input_Capsense_SW101_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw101.resolution)
#define Input_Capsense_SW101_RESOLUTION_OFFSET              (62u)
#define Input_Capsense_SW101_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW101_RESOLUTION_PARAM_ID            (0x8981003Eu)

#define Input_Capsense_SW101_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw101.fingerTh)
#define Input_Capsense_SW101_FINGER_TH_OFFSET               (64u)
#define Input_Capsense_SW101_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW101_FINGER_TH_PARAM_ID             (0x84810040u)

#define Input_Capsense_SW101_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw101.noiseTh)
#define Input_Capsense_SW101_NOISE_TH_OFFSET                (66u)
#define Input_Capsense_SW101_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW101_NOISE_TH_PARAM_ID              (0x40810042u)

#define Input_Capsense_SW101_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw101.nNoiseTh)
#define Input_Capsense_SW101_NNOISE_TH_OFFSET               (67u)
#define Input_Capsense_SW101_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW101_NNOISE_TH_PARAM_ID             (0x46810043u)

#define Input_Capsense_SW101_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw101.hysteresis)
#define Input_Capsense_SW101_HYSTERESIS_OFFSET              (68u)
#define Input_Capsense_SW101_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW101_HYSTERESIS_PARAM_ID            (0x4D810044u)

#define Input_Capsense_SW101_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw101.onDebounce)
#define Input_Capsense_SW101_ON_DEBOUNCE_OFFSET             (69u)
#define Input_Capsense_SW101_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW101_ON_DEBOUNCE_PARAM_ID           (0x4B810045u)

#define Input_Capsense_SW101_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw101.lowBslnRst)
#define Input_Capsense_SW101_LOW_BSLN_RST_OFFSET            (70u)
#define Input_Capsense_SW101_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW101_LOW_BSLN_RST_PARAM_ID          (0x41810046u)

#define Input_Capsense_SW101_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw101.idacMod[0u])
#define Input_Capsense_SW101_IDAC_MOD0_OFFSET               (71u)
#define Input_Capsense_SW101_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW101_IDAC_MOD0_PARAM_ID             (0x4A010047u)

#define Input_Capsense_SW101_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw101.idacGainIndex)
#define Input_Capsense_SW101_IDAC_GAIN_INDEX_OFFSET         (72u)
#define Input_Capsense_SW101_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW101_IDAC_GAIN_INDEX_PARAM_ID       (0x4E810048u)

#define Input_Capsense_SW101_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw101.snsClk)
#define Input_Capsense_SW101_SNS_CLK_OFFSET                 (74u)
#define Input_Capsense_SW101_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW101_SNS_CLK_PARAM_ID               (0x8A81004Au)

#define Input_Capsense_SW101_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw101.snsClkSource)
#define Input_Capsense_SW101_SNS_CLK_SOURCE_OFFSET          (76u)
#define Input_Capsense_SW101_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW101_SNS_CLK_SOURCE_PARAM_ID        (0x4F81004Cu)

#define Input_Capsense_SW101_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw101.fingerCap)
#define Input_Capsense_SW101_FINGER_CAP_OFFSET              (78u)
#define Input_Capsense_SW101_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW101_FINGER_CAP_PARAM_ID            (0xAD01004Eu)

#define Input_Capsense_SW101_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw101.sigPFC)
#define Input_Capsense_SW101_SIGPFC_OFFSET                  (80u)
#define Input_Capsense_SW101_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW101_SIGPFC_PARAM_ID                (0xA7010050u)

#define Input_Capsense_SW102_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw102.resolution)
#define Input_Capsense_SW102_RESOLUTION_OFFSET              (82u)
#define Input_Capsense_SW102_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW102_RESOLUTION_PARAM_ID            (0x88820052u)

#define Input_Capsense_SW102_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw102.fingerTh)
#define Input_Capsense_SW102_FINGER_TH_OFFSET               (84u)
#define Input_Capsense_SW102_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW102_FINGER_TH_PARAM_ID             (0x85820054u)

#define Input_Capsense_SW102_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw102.noiseTh)
#define Input_Capsense_SW102_NOISE_TH_OFFSET                (86u)
#define Input_Capsense_SW102_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW102_NOISE_TH_PARAM_ID              (0x41820056u)

#define Input_Capsense_SW102_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw102.nNoiseTh)
#define Input_Capsense_SW102_NNOISE_TH_OFFSET               (87u)
#define Input_Capsense_SW102_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW102_NNOISE_TH_PARAM_ID             (0x47820057u)

#define Input_Capsense_SW102_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw102.hysteresis)
#define Input_Capsense_SW102_HYSTERESIS_OFFSET              (88u)
#define Input_Capsense_SW102_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW102_HYSTERESIS_PARAM_ID            (0x4E820058u)

#define Input_Capsense_SW102_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw102.onDebounce)
#define Input_Capsense_SW102_ON_DEBOUNCE_OFFSET             (89u)
#define Input_Capsense_SW102_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW102_ON_DEBOUNCE_PARAM_ID           (0x48820059u)

#define Input_Capsense_SW102_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw102.lowBslnRst)
#define Input_Capsense_SW102_LOW_BSLN_RST_OFFSET            (90u)
#define Input_Capsense_SW102_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW102_LOW_BSLN_RST_PARAM_ID          (0x4282005Au)

#define Input_Capsense_SW102_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw102.idacMod[0u])
#define Input_Capsense_SW102_IDAC_MOD0_OFFSET               (91u)
#define Input_Capsense_SW102_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW102_IDAC_MOD0_PARAM_ID             (0x4902005Bu)

#define Input_Capsense_SW102_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw102.idacGainIndex)
#define Input_Capsense_SW102_IDAC_GAIN_INDEX_OFFSET         (92u)
#define Input_Capsense_SW102_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW102_IDAC_GAIN_INDEX_PARAM_ID       (0x4F82005Cu)

#define Input_Capsense_SW102_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw102.snsClk)
#define Input_Capsense_SW102_SNS_CLK_OFFSET                 (94u)
#define Input_Capsense_SW102_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW102_SNS_CLK_PARAM_ID               (0x8B82005Eu)

#define Input_Capsense_SW102_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw102.snsClkSource)
#define Input_Capsense_SW102_SNS_CLK_SOURCE_OFFSET          (96u)
#define Input_Capsense_SW102_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW102_SNS_CLK_SOURCE_PARAM_ID        (0x43820060u)

#define Input_Capsense_SW102_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw102.fingerCap)
#define Input_Capsense_SW102_FINGER_CAP_OFFSET              (98u)
#define Input_Capsense_SW102_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW102_FINGER_CAP_PARAM_ID            (0xA1020062u)

#define Input_Capsense_SW102_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw102.sigPFC)
#define Input_Capsense_SW102_SIGPFC_OFFSET                  (100u)
#define Input_Capsense_SW102_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW102_SIGPFC_PARAM_ID                (0xAC020064u)

#define Input_Capsense_SW103_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw103.resolution)
#define Input_Capsense_SW103_RESOLUTION_OFFSET              (102u)
#define Input_Capsense_SW103_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW103_RESOLUTION_PARAM_ID            (0x85830066u)

#define Input_Capsense_SW103_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw103.fingerTh)
#define Input_Capsense_SW103_FINGER_TH_OFFSET               (104u)
#define Input_Capsense_SW103_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW103_FINGER_TH_PARAM_ID             (0x8A830068u)

#define Input_Capsense_SW103_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw103.noiseTh)
#define Input_Capsense_SW103_NOISE_TH_OFFSET                (106u)
#define Input_Capsense_SW103_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW103_NOISE_TH_PARAM_ID              (0x4E83006Au)

#define Input_Capsense_SW103_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw103.nNoiseTh)
#define Input_Capsense_SW103_NNOISE_TH_OFFSET               (107u)
#define Input_Capsense_SW103_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW103_NNOISE_TH_PARAM_ID             (0x4883006Bu)

#define Input_Capsense_SW103_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw103.hysteresis)
#define Input_Capsense_SW103_HYSTERESIS_OFFSET              (108u)
#define Input_Capsense_SW103_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW103_HYSTERESIS_PARAM_ID            (0x4383006Cu)

#define Input_Capsense_SW103_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw103.onDebounce)
#define Input_Capsense_SW103_ON_DEBOUNCE_OFFSET             (109u)
#define Input_Capsense_SW103_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW103_ON_DEBOUNCE_PARAM_ID           (0x4583006Du)

#define Input_Capsense_SW103_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw103.lowBslnRst)
#define Input_Capsense_SW103_LOW_BSLN_RST_OFFSET            (110u)
#define Input_Capsense_SW103_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW103_LOW_BSLN_RST_PARAM_ID          (0x4F83006Eu)

#define Input_Capsense_SW103_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw103.idacMod[0u])
#define Input_Capsense_SW103_IDAC_MOD0_OFFSET               (111u)
#define Input_Capsense_SW103_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW103_IDAC_MOD0_PARAM_ID             (0x4403006Fu)

#define Input_Capsense_SW103_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw103.idacGainIndex)
#define Input_Capsense_SW103_IDAC_GAIN_INDEX_OFFSET         (112u)
#define Input_Capsense_SW103_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW103_IDAC_GAIN_INDEX_PARAM_ID       (0x45830070u)

#define Input_Capsense_SW103_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw103.snsClk)
#define Input_Capsense_SW103_SNS_CLK_OFFSET                 (114u)
#define Input_Capsense_SW103_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW103_SNS_CLK_PARAM_ID               (0x81830072u)

#define Input_Capsense_SW103_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw103.snsClkSource)
#define Input_Capsense_SW103_SNS_CLK_SOURCE_OFFSET          (116u)
#define Input_Capsense_SW103_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW103_SNS_CLK_SOURCE_PARAM_ID        (0x44830074u)

#define Input_Capsense_SW103_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw103.fingerCap)
#define Input_Capsense_SW103_FINGER_CAP_OFFSET              (118u)
#define Input_Capsense_SW103_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW103_FINGER_CAP_PARAM_ID            (0xA6030076u)

#define Input_Capsense_SW103_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw103.sigPFC)
#define Input_Capsense_SW103_SIGPFC_OFFSET                  (120u)
#define Input_Capsense_SW103_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW103_SIGPFC_PARAM_ID                (0xA9030078u)

#define Input_Capsense_SW104_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw104.resolution)
#define Input_Capsense_SW104_RESOLUTION_OFFSET              (122u)
#define Input_Capsense_SW104_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW104_RESOLUTION_PARAM_ID            (0x8A84007Au)

#define Input_Capsense_SW104_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw104.fingerTh)
#define Input_Capsense_SW104_FINGER_TH_OFFSET               (124u)
#define Input_Capsense_SW104_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW104_FINGER_TH_PARAM_ID             (0x8784007Cu)

#define Input_Capsense_SW104_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw104.noiseTh)
#define Input_Capsense_SW104_NOISE_TH_OFFSET                (126u)
#define Input_Capsense_SW104_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW104_NOISE_TH_PARAM_ID              (0x4384007Eu)

#define Input_Capsense_SW104_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw104.nNoiseTh)
#define Input_Capsense_SW104_NNOISE_TH_OFFSET               (127u)
#define Input_Capsense_SW104_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW104_NNOISE_TH_PARAM_ID             (0x4584007Fu)

#define Input_Capsense_SW104_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw104.hysteresis)
#define Input_Capsense_SW104_HYSTERESIS_OFFSET              (128u)
#define Input_Capsense_SW104_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW104_HYSTERESIS_PARAM_ID            (0x4D840080u)

#define Input_Capsense_SW104_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw104.onDebounce)
#define Input_Capsense_SW104_ON_DEBOUNCE_OFFSET             (129u)
#define Input_Capsense_SW104_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW104_ON_DEBOUNCE_PARAM_ID           (0x4B840081u)

#define Input_Capsense_SW104_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw104.lowBslnRst)
#define Input_Capsense_SW104_LOW_BSLN_RST_OFFSET            (130u)
#define Input_Capsense_SW104_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW104_LOW_BSLN_RST_PARAM_ID          (0x41840082u)

#define Input_Capsense_SW104_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw104.idacMod[0u])
#define Input_Capsense_SW104_IDAC_MOD0_OFFSET               (131u)
#define Input_Capsense_SW104_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW104_IDAC_MOD0_PARAM_ID             (0x4A040083u)

#define Input_Capsense_SW104_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw104.idacGainIndex)
#define Input_Capsense_SW104_IDAC_GAIN_INDEX_OFFSET         (132u)
#define Input_Capsense_SW104_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW104_IDAC_GAIN_INDEX_PARAM_ID       (0x4C840084u)

#define Input_Capsense_SW104_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw104.snsClk)
#define Input_Capsense_SW104_SNS_CLK_OFFSET                 (134u)
#define Input_Capsense_SW104_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW104_SNS_CLK_PARAM_ID               (0x88840086u)

#define Input_Capsense_SW104_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw104.snsClkSource)
#define Input_Capsense_SW104_SNS_CLK_SOURCE_OFFSET          (136u)
#define Input_Capsense_SW104_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW104_SNS_CLK_SOURCE_PARAM_ID        (0x4F840088u)

#define Input_Capsense_SW104_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw104.fingerCap)
#define Input_Capsense_SW104_FINGER_CAP_OFFSET              (138u)
#define Input_Capsense_SW104_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW104_FINGER_CAP_PARAM_ID            (0xAD04008Au)

#define Input_Capsense_SW104_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw104.sigPFC)
#define Input_Capsense_SW104_SIGPFC_OFFSET                  (140u)
#define Input_Capsense_SW104_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW104_SIGPFC_PARAM_ID                (0xA004008Cu)

#define Input_Capsense_SW105_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw105.resolution)
#define Input_Capsense_SW105_RESOLUTION_OFFSET              (142u)
#define Input_Capsense_SW105_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW105_RESOLUTION_PARAM_ID            (0x8985008Eu)

#define Input_Capsense_SW105_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw105.fingerTh)
#define Input_Capsense_SW105_FINGER_TH_OFFSET               (144u)
#define Input_Capsense_SW105_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW105_FINGER_TH_PARAM_ID             (0x83850090u)

#define Input_Capsense_SW105_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw105.noiseTh)
#define Input_Capsense_SW105_NOISE_TH_OFFSET                (146u)
#define Input_Capsense_SW105_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW105_NOISE_TH_PARAM_ID              (0x47850092u)

#define Input_Capsense_SW105_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw105.nNoiseTh)
#define Input_Capsense_SW105_NNOISE_TH_OFFSET               (147u)
#define Input_Capsense_SW105_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW105_NNOISE_TH_PARAM_ID             (0x41850093u)

#define Input_Capsense_SW105_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw105.hysteresis)
#define Input_Capsense_SW105_HYSTERESIS_OFFSET              (148u)
#define Input_Capsense_SW105_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW105_HYSTERESIS_PARAM_ID            (0x4A850094u)

#define Input_Capsense_SW105_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw105.onDebounce)
#define Input_Capsense_SW105_ON_DEBOUNCE_OFFSET             (149u)
#define Input_Capsense_SW105_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW105_ON_DEBOUNCE_PARAM_ID           (0x4C850095u)

#define Input_Capsense_SW105_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw105.lowBslnRst)
#define Input_Capsense_SW105_LOW_BSLN_RST_OFFSET            (150u)
#define Input_Capsense_SW105_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW105_LOW_BSLN_RST_PARAM_ID          (0x46850096u)

#define Input_Capsense_SW105_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw105.idacMod[0u])
#define Input_Capsense_SW105_IDAC_MOD0_OFFSET               (151u)
#define Input_Capsense_SW105_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW105_IDAC_MOD0_PARAM_ID             (0x4D050097u)

#define Input_Capsense_SW105_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw105.idacGainIndex)
#define Input_Capsense_SW105_IDAC_GAIN_INDEX_OFFSET         (152u)
#define Input_Capsense_SW105_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW105_IDAC_GAIN_INDEX_PARAM_ID       (0x49850098u)

#define Input_Capsense_SW105_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw105.snsClk)
#define Input_Capsense_SW105_SNS_CLK_OFFSET                 (154u)
#define Input_Capsense_SW105_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW105_SNS_CLK_PARAM_ID               (0x8D85009Au)

#define Input_Capsense_SW105_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw105.snsClkSource)
#define Input_Capsense_SW105_SNS_CLK_SOURCE_OFFSET          (156u)
#define Input_Capsense_SW105_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW105_SNS_CLK_SOURCE_PARAM_ID        (0x4885009Cu)

#define Input_Capsense_SW105_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw105.fingerCap)
#define Input_Capsense_SW105_FINGER_CAP_OFFSET              (158u)
#define Input_Capsense_SW105_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW105_FINGER_CAP_PARAM_ID            (0xAA05009Eu)

#define Input_Capsense_SW105_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw105.sigPFC)
#define Input_Capsense_SW105_SIGPFC_OFFSET                  (160u)
#define Input_Capsense_SW105_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW105_SIGPFC_PARAM_ID                (0xAA0500A0u)

#define Input_Capsense_SW106_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw106.resolution)
#define Input_Capsense_SW106_RESOLUTION_OFFSET              (162u)
#define Input_Capsense_SW106_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW106_RESOLUTION_PARAM_ID            (0x858600A2u)

#define Input_Capsense_SW106_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw106.fingerTh)
#define Input_Capsense_SW106_FINGER_TH_OFFSET               (164u)
#define Input_Capsense_SW106_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW106_FINGER_TH_PARAM_ID             (0x888600A4u)

#define Input_Capsense_SW106_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw106.noiseTh)
#define Input_Capsense_SW106_NOISE_TH_OFFSET                (166u)
#define Input_Capsense_SW106_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW106_NOISE_TH_PARAM_ID              (0x4C8600A6u)

#define Input_Capsense_SW106_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw106.nNoiseTh)
#define Input_Capsense_SW106_NNOISE_TH_OFFSET               (167u)
#define Input_Capsense_SW106_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW106_NNOISE_TH_PARAM_ID             (0x4A8600A7u)

#define Input_Capsense_SW106_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw106.hysteresis)
#define Input_Capsense_SW106_HYSTERESIS_OFFSET              (168u)
#define Input_Capsense_SW106_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW106_HYSTERESIS_PARAM_ID            (0x438600A8u)

#define Input_Capsense_SW106_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw106.onDebounce)
#define Input_Capsense_SW106_ON_DEBOUNCE_OFFSET             (169u)
#define Input_Capsense_SW106_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW106_ON_DEBOUNCE_PARAM_ID           (0x458600A9u)

#define Input_Capsense_SW106_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw106.lowBslnRst)
#define Input_Capsense_SW106_LOW_BSLN_RST_OFFSET            (170u)
#define Input_Capsense_SW106_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW106_LOW_BSLN_RST_PARAM_ID          (0x4F8600AAu)

#define Input_Capsense_SW106_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw106.idacMod[0u])
#define Input_Capsense_SW106_IDAC_MOD0_OFFSET               (171u)
#define Input_Capsense_SW106_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW106_IDAC_MOD0_PARAM_ID             (0x440600ABu)

#define Input_Capsense_SW106_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw106.idacGainIndex)
#define Input_Capsense_SW106_IDAC_GAIN_INDEX_OFFSET         (172u)
#define Input_Capsense_SW106_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW106_IDAC_GAIN_INDEX_PARAM_ID       (0x428600ACu)

#define Input_Capsense_SW106_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw106.snsClk)
#define Input_Capsense_SW106_SNS_CLK_OFFSET                 (174u)
#define Input_Capsense_SW106_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW106_SNS_CLK_PARAM_ID               (0x868600AEu)

#define Input_Capsense_SW106_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw106.snsClkSource)
#define Input_Capsense_SW106_SNS_CLK_SOURCE_OFFSET          (176u)
#define Input_Capsense_SW106_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW106_SNS_CLK_SOURCE_PARAM_ID        (0x448600B0u)

#define Input_Capsense_SW106_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw106.fingerCap)
#define Input_Capsense_SW106_FINGER_CAP_OFFSET              (178u)
#define Input_Capsense_SW106_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW106_FINGER_CAP_PARAM_ID            (0xA60600B2u)

#define Input_Capsense_SW106_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw106.sigPFC)
#define Input_Capsense_SW106_SIGPFC_OFFSET                  (180u)
#define Input_Capsense_SW106_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW106_SIGPFC_PARAM_ID                (0xAB0600B4u)

#define Input_Capsense_SW107_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw107.resolution)
#define Input_Capsense_SW107_RESOLUTION_OFFSET              (182u)
#define Input_Capsense_SW107_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW107_RESOLUTION_PARAM_ID            (0x828700B6u)

#define Input_Capsense_SW107_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw107.fingerTh)
#define Input_Capsense_SW107_FINGER_TH_OFFSET               (184u)
#define Input_Capsense_SW107_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW107_FINGER_TH_PARAM_ID             (0x8D8700B8u)

#define Input_Capsense_SW107_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw107.noiseTh)
#define Input_Capsense_SW107_NOISE_TH_OFFSET                (186u)
#define Input_Capsense_SW107_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW107_NOISE_TH_PARAM_ID              (0x498700BAu)

#define Input_Capsense_SW107_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw107.nNoiseTh)
#define Input_Capsense_SW107_NNOISE_TH_OFFSET               (187u)
#define Input_Capsense_SW107_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW107_NNOISE_TH_PARAM_ID             (0x4F8700BBu)

#define Input_Capsense_SW107_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw107.hysteresis)
#define Input_Capsense_SW107_HYSTERESIS_OFFSET              (188u)
#define Input_Capsense_SW107_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW107_HYSTERESIS_PARAM_ID            (0x448700BCu)

#define Input_Capsense_SW107_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw107.onDebounce)
#define Input_Capsense_SW107_ON_DEBOUNCE_OFFSET             (189u)
#define Input_Capsense_SW107_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW107_ON_DEBOUNCE_PARAM_ID           (0x428700BDu)

#define Input_Capsense_SW107_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw107.lowBslnRst)
#define Input_Capsense_SW107_LOW_BSLN_RST_OFFSET            (190u)
#define Input_Capsense_SW107_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW107_LOW_BSLN_RST_PARAM_ID          (0x488700BEu)

#define Input_Capsense_SW107_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw107.idacMod[0u])
#define Input_Capsense_SW107_IDAC_MOD0_OFFSET               (191u)
#define Input_Capsense_SW107_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW107_IDAC_MOD0_PARAM_ID             (0x430700BFu)

#define Input_Capsense_SW107_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw107.idacGainIndex)
#define Input_Capsense_SW107_IDAC_GAIN_INDEX_OFFSET         (192u)
#define Input_Capsense_SW107_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW107_IDAC_GAIN_INDEX_PARAM_ID       (0x458700C0u)

#define Input_Capsense_SW107_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw107.snsClk)
#define Input_Capsense_SW107_SNS_CLK_OFFSET                 (194u)
#define Input_Capsense_SW107_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW107_SNS_CLK_PARAM_ID               (0x818700C2u)

#define Input_Capsense_SW107_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw107.snsClkSource)
#define Input_Capsense_SW107_SNS_CLK_SOURCE_OFFSET          (196u)
#define Input_Capsense_SW107_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW107_SNS_CLK_SOURCE_PARAM_ID        (0x448700C4u)

#define Input_Capsense_SW107_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw107.fingerCap)
#define Input_Capsense_SW107_FINGER_CAP_OFFSET              (198u)
#define Input_Capsense_SW107_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW107_FINGER_CAP_PARAM_ID            (0xA60700C6u)

#define Input_Capsense_SW107_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw107.sigPFC)
#define Input_Capsense_SW107_SIGPFC_OFFSET                  (200u)
#define Input_Capsense_SW107_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW107_SIGPFC_PARAM_ID                (0xA90700C8u)

#define Input_Capsense_SW108_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw108.resolution)
#define Input_Capsense_SW108_RESOLUTION_OFFSET              (202u)
#define Input_Capsense_SW108_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW108_RESOLUTION_PARAM_ID            (0x8B8800CAu)

#define Input_Capsense_SW108_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw108.fingerTh)
#define Input_Capsense_SW108_FINGER_TH_OFFSET               (204u)
#define Input_Capsense_SW108_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW108_FINGER_TH_PARAM_ID             (0x868800CCu)

#define Input_Capsense_SW108_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw108.noiseTh)
#define Input_Capsense_SW108_NOISE_TH_OFFSET                (206u)
#define Input_Capsense_SW108_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW108_NOISE_TH_PARAM_ID              (0x428800CEu)

#define Input_Capsense_SW108_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw108.nNoiseTh)
#define Input_Capsense_SW108_NNOISE_TH_OFFSET               (207u)
#define Input_Capsense_SW108_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW108_NNOISE_TH_PARAM_ID             (0x448800CFu)

#define Input_Capsense_SW108_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw108.hysteresis)
#define Input_Capsense_SW108_HYSTERESIS_OFFSET              (208u)
#define Input_Capsense_SW108_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW108_HYSTERESIS_PARAM_ID            (0x488800D0u)

#define Input_Capsense_SW108_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw108.onDebounce)
#define Input_Capsense_SW108_ON_DEBOUNCE_OFFSET             (209u)
#define Input_Capsense_SW108_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW108_ON_DEBOUNCE_PARAM_ID           (0x4E8800D1u)

#define Input_Capsense_SW108_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw108.lowBslnRst)
#define Input_Capsense_SW108_LOW_BSLN_RST_OFFSET            (210u)
#define Input_Capsense_SW108_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW108_LOW_BSLN_RST_PARAM_ID          (0x448800D2u)

#define Input_Capsense_SW108_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw108.idacMod[0u])
#define Input_Capsense_SW108_IDAC_MOD0_OFFSET               (211u)
#define Input_Capsense_SW108_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW108_IDAC_MOD0_PARAM_ID             (0x4F0800D3u)

#define Input_Capsense_SW108_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw108.idacGainIndex)
#define Input_Capsense_SW108_IDAC_GAIN_INDEX_OFFSET         (212u)
#define Input_Capsense_SW108_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW108_IDAC_GAIN_INDEX_PARAM_ID       (0x498800D4u)

#define Input_Capsense_SW108_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw108.snsClk)
#define Input_Capsense_SW108_SNS_CLK_OFFSET                 (214u)
#define Input_Capsense_SW108_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW108_SNS_CLK_PARAM_ID               (0x8D8800D6u)

#define Input_Capsense_SW108_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw108.snsClkSource)
#define Input_Capsense_SW108_SNS_CLK_SOURCE_OFFSET          (216u)
#define Input_Capsense_SW108_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW108_SNS_CLK_SOURCE_PARAM_ID        (0x4A8800D8u)

#define Input_Capsense_SW108_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw108.fingerCap)
#define Input_Capsense_SW108_FINGER_CAP_OFFSET              (218u)
#define Input_Capsense_SW108_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW108_FINGER_CAP_PARAM_ID            (0xA80800DAu)

#define Input_Capsense_SW108_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw108.sigPFC)
#define Input_Capsense_SW108_SIGPFC_OFFSET                  (220u)
#define Input_Capsense_SW108_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW108_SIGPFC_PARAM_ID                (0xA50800DCu)

#define Input_Capsense_SW109_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw109.resolution)
#define Input_Capsense_SW109_RESOLUTION_OFFSET              (222u)
#define Input_Capsense_SW109_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW109_RESOLUTION_PARAM_ID            (0x8C8900DEu)

#define Input_Capsense_SW109_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw109.fingerTh)
#define Input_Capsense_SW109_FINGER_TH_OFFSET               (224u)
#define Input_Capsense_SW109_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW109_FINGER_TH_PARAM_ID             (0x8C8900E0u)

#define Input_Capsense_SW109_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw109.noiseTh)
#define Input_Capsense_SW109_NOISE_TH_OFFSET                (226u)
#define Input_Capsense_SW109_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW109_NOISE_TH_PARAM_ID              (0x488900E2u)

#define Input_Capsense_SW109_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw109.nNoiseTh)
#define Input_Capsense_SW109_NNOISE_TH_OFFSET               (227u)
#define Input_Capsense_SW109_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW109_NNOISE_TH_PARAM_ID             (0x4E8900E3u)

#define Input_Capsense_SW109_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw109.hysteresis)
#define Input_Capsense_SW109_HYSTERESIS_OFFSET              (228u)
#define Input_Capsense_SW109_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW109_HYSTERESIS_PARAM_ID            (0x458900E4u)

#define Input_Capsense_SW109_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw109.onDebounce)
#define Input_Capsense_SW109_ON_DEBOUNCE_OFFSET             (229u)
#define Input_Capsense_SW109_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW109_ON_DEBOUNCE_PARAM_ID           (0x438900E5u)

#define Input_Capsense_SW109_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw109.lowBslnRst)
#define Input_Capsense_SW109_LOW_BSLN_RST_OFFSET            (230u)
#define Input_Capsense_SW109_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW109_LOW_BSLN_RST_PARAM_ID          (0x498900E6u)

#define Input_Capsense_SW109_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw109.idacMod[0u])
#define Input_Capsense_SW109_IDAC_MOD0_OFFSET               (231u)
#define Input_Capsense_SW109_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW109_IDAC_MOD0_PARAM_ID             (0x420900E7u)

#define Input_Capsense_SW109_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw109.idacGainIndex)
#define Input_Capsense_SW109_IDAC_GAIN_INDEX_OFFSET         (232u)
#define Input_Capsense_SW109_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW109_IDAC_GAIN_INDEX_PARAM_ID       (0x468900E8u)

#define Input_Capsense_SW109_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw109.snsClk)
#define Input_Capsense_SW109_SNS_CLK_OFFSET                 (234u)
#define Input_Capsense_SW109_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW109_SNS_CLK_PARAM_ID               (0x828900EAu)

#define Input_Capsense_SW109_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw109.snsClkSource)
#define Input_Capsense_SW109_SNS_CLK_SOURCE_OFFSET          (236u)
#define Input_Capsense_SW109_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW109_SNS_CLK_SOURCE_PARAM_ID        (0x478900ECu)

#define Input_Capsense_SW109_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw109.fingerCap)
#define Input_Capsense_SW109_FINGER_CAP_OFFSET              (238u)
#define Input_Capsense_SW109_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW109_FINGER_CAP_PARAM_ID            (0xA50900EEu)

#define Input_Capsense_SW109_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw109.sigPFC)
#define Input_Capsense_SW109_SIGPFC_OFFSET                  (240u)
#define Input_Capsense_SW109_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW109_SIGPFC_PARAM_ID                (0xAF0900F0u)

#define Input_Capsense_SW110_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw110.resolution)
#define Input_Capsense_SW110_RESOLUTION_OFFSET              (242u)
#define Input_Capsense_SW110_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW110_RESOLUTION_PARAM_ID            (0x808A00F2u)

#define Input_Capsense_SW110_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw110.fingerTh)
#define Input_Capsense_SW110_FINGER_TH_OFFSET               (244u)
#define Input_Capsense_SW110_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW110_FINGER_TH_PARAM_ID             (0x8D8A00F4u)

#define Input_Capsense_SW110_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw110.noiseTh)
#define Input_Capsense_SW110_NOISE_TH_OFFSET                (246u)
#define Input_Capsense_SW110_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW110_NOISE_TH_PARAM_ID              (0x498A00F6u)

#define Input_Capsense_SW110_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw110.nNoiseTh)
#define Input_Capsense_SW110_NNOISE_TH_OFFSET               (247u)
#define Input_Capsense_SW110_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW110_NNOISE_TH_PARAM_ID             (0x4F8A00F7u)

#define Input_Capsense_SW110_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw110.hysteresis)
#define Input_Capsense_SW110_HYSTERESIS_OFFSET              (248u)
#define Input_Capsense_SW110_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW110_HYSTERESIS_PARAM_ID            (0x468A00F8u)

#define Input_Capsense_SW110_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw110.onDebounce)
#define Input_Capsense_SW110_ON_DEBOUNCE_OFFSET             (249u)
#define Input_Capsense_SW110_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW110_ON_DEBOUNCE_PARAM_ID           (0x408A00F9u)

#define Input_Capsense_SW110_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw110.lowBslnRst)
#define Input_Capsense_SW110_LOW_BSLN_RST_OFFSET            (250u)
#define Input_Capsense_SW110_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW110_LOW_BSLN_RST_PARAM_ID          (0x4A8A00FAu)

#define Input_Capsense_SW110_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw110.idacMod[0u])
#define Input_Capsense_SW110_IDAC_MOD0_OFFSET               (251u)
#define Input_Capsense_SW110_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW110_IDAC_MOD0_PARAM_ID             (0x410A00FBu)

#define Input_Capsense_SW110_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw110.idacGainIndex)
#define Input_Capsense_SW110_IDAC_GAIN_INDEX_OFFSET         (252u)
#define Input_Capsense_SW110_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW110_IDAC_GAIN_INDEX_PARAM_ID       (0x478A00FCu)

#define Input_Capsense_SW110_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw110.snsClk)
#define Input_Capsense_SW110_SNS_CLK_OFFSET                 (254u)
#define Input_Capsense_SW110_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW110_SNS_CLK_PARAM_ID               (0x838A00FEu)

#define Input_Capsense_SW110_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw110.snsClkSource)
#define Input_Capsense_SW110_SNS_CLK_SOURCE_OFFSET          (256u)
#define Input_Capsense_SW110_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW110_SNS_CLK_SOURCE_PARAM_ID        (0x4E8A0100u)

#define Input_Capsense_SW110_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw110.fingerCap)
#define Input_Capsense_SW110_FINGER_CAP_OFFSET              (258u)
#define Input_Capsense_SW110_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW110_FINGER_CAP_PARAM_ID            (0xAC0A0102u)

#define Input_Capsense_SW110_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw110.sigPFC)
#define Input_Capsense_SW110_SIGPFC_OFFSET                  (260u)
#define Input_Capsense_SW110_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW110_SIGPFC_PARAM_ID                (0xA10A0104u)

#define Input_Capsense_SW111_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw111.resolution)
#define Input_Capsense_SW111_RESOLUTION_OFFSET              (262u)
#define Input_Capsense_SW111_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW111_RESOLUTION_PARAM_ID            (0x888B0106u)

#define Input_Capsense_SW111_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw111.fingerTh)
#define Input_Capsense_SW111_FINGER_TH_OFFSET               (264u)
#define Input_Capsense_SW111_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW111_FINGER_TH_PARAM_ID             (0x878B0108u)

#define Input_Capsense_SW111_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw111.noiseTh)
#define Input_Capsense_SW111_NOISE_TH_OFFSET                (266u)
#define Input_Capsense_SW111_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW111_NOISE_TH_PARAM_ID              (0x438B010Au)

#define Input_Capsense_SW111_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw111.nNoiseTh)
#define Input_Capsense_SW111_NNOISE_TH_OFFSET               (267u)
#define Input_Capsense_SW111_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW111_NNOISE_TH_PARAM_ID             (0x458B010Bu)

#define Input_Capsense_SW111_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw111.hysteresis)
#define Input_Capsense_SW111_HYSTERESIS_OFFSET              (268u)
#define Input_Capsense_SW111_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW111_HYSTERESIS_PARAM_ID            (0x4E8B010Cu)

#define Input_Capsense_SW111_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw111.onDebounce)
#define Input_Capsense_SW111_ON_DEBOUNCE_OFFSET             (269u)
#define Input_Capsense_SW111_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW111_ON_DEBOUNCE_PARAM_ID           (0x488B010Du)

#define Input_Capsense_SW111_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw111.lowBslnRst)
#define Input_Capsense_SW111_LOW_BSLN_RST_OFFSET            (270u)
#define Input_Capsense_SW111_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW111_LOW_BSLN_RST_PARAM_ID          (0x428B010Eu)

#define Input_Capsense_SW111_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw111.idacMod[0u])
#define Input_Capsense_SW111_IDAC_MOD0_OFFSET               (271u)
#define Input_Capsense_SW111_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW111_IDAC_MOD0_PARAM_ID             (0x490B010Fu)

#define Input_Capsense_SW111_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw111.idacGainIndex)
#define Input_Capsense_SW111_IDAC_GAIN_INDEX_OFFSET         (272u)
#define Input_Capsense_SW111_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW111_IDAC_GAIN_INDEX_PARAM_ID       (0x488B0110u)

#define Input_Capsense_SW111_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw111.snsClk)
#define Input_Capsense_SW111_SNS_CLK_OFFSET                 (274u)
#define Input_Capsense_SW111_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW111_SNS_CLK_PARAM_ID               (0x8C8B0112u)

#define Input_Capsense_SW111_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw111.snsClkSource)
#define Input_Capsense_SW111_SNS_CLK_SOURCE_OFFSET          (276u)
#define Input_Capsense_SW111_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW111_SNS_CLK_SOURCE_PARAM_ID        (0x498B0114u)

#define Input_Capsense_SW111_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw111.fingerCap)
#define Input_Capsense_SW111_FINGER_CAP_OFFSET              (278u)
#define Input_Capsense_SW111_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW111_FINGER_CAP_PARAM_ID            (0xAB0B0116u)

#define Input_Capsense_SW111_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw111.sigPFC)
#define Input_Capsense_SW111_SIGPFC_OFFSET                  (280u)
#define Input_Capsense_SW111_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW111_SIGPFC_PARAM_ID                (0xA40B0118u)

#define Input_Capsense_SW112_RESOLUTION_VALUE               (Input_Capsense_dsRam.wdgtList.sw112.resolution)
#define Input_Capsense_SW112_RESOLUTION_OFFSET              (282u)
#define Input_Capsense_SW112_RESOLUTION_SIZE                (2u)
#define Input_Capsense_SW112_RESOLUTION_PARAM_ID            (0x878C011Au)

#define Input_Capsense_SW112_FINGER_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw112.fingerTh)
#define Input_Capsense_SW112_FINGER_TH_OFFSET               (284u)
#define Input_Capsense_SW112_FINGER_TH_SIZE                 (2u)
#define Input_Capsense_SW112_FINGER_TH_PARAM_ID             (0x8A8C011Cu)

#define Input_Capsense_SW112_NOISE_TH_VALUE                 (Input_Capsense_dsRam.wdgtList.sw112.noiseTh)
#define Input_Capsense_SW112_NOISE_TH_OFFSET                (286u)
#define Input_Capsense_SW112_NOISE_TH_SIZE                  (1u)
#define Input_Capsense_SW112_NOISE_TH_PARAM_ID              (0x4E8C011Eu)

#define Input_Capsense_SW112_NNOISE_TH_VALUE                (Input_Capsense_dsRam.wdgtList.sw112.nNoiseTh)
#define Input_Capsense_SW112_NNOISE_TH_OFFSET               (287u)
#define Input_Capsense_SW112_NNOISE_TH_SIZE                 (1u)
#define Input_Capsense_SW112_NNOISE_TH_PARAM_ID             (0x488C011Fu)

#define Input_Capsense_SW112_HYSTERESIS_VALUE               (Input_Capsense_dsRam.wdgtList.sw112.hysteresis)
#define Input_Capsense_SW112_HYSTERESIS_OFFSET              (288u)
#define Input_Capsense_SW112_HYSTERESIS_SIZE                (1u)
#define Input_Capsense_SW112_HYSTERESIS_PARAM_ID            (0x4E8C0120u)

#define Input_Capsense_SW112_ON_DEBOUNCE_VALUE              (Input_Capsense_dsRam.wdgtList.sw112.onDebounce)
#define Input_Capsense_SW112_ON_DEBOUNCE_OFFSET             (289u)
#define Input_Capsense_SW112_ON_DEBOUNCE_SIZE               (1u)
#define Input_Capsense_SW112_ON_DEBOUNCE_PARAM_ID           (0x488C0121u)

#define Input_Capsense_SW112_LOW_BSLN_RST_VALUE             (Input_Capsense_dsRam.wdgtList.sw112.lowBslnRst)
#define Input_Capsense_SW112_LOW_BSLN_RST_OFFSET            (290u)
#define Input_Capsense_SW112_LOW_BSLN_RST_SIZE              (1u)
#define Input_Capsense_SW112_LOW_BSLN_RST_PARAM_ID          (0x428C0122u)

#define Input_Capsense_SW112_IDAC_MOD0_VALUE                (Input_Capsense_dsRam.wdgtList.sw112.idacMod[0u])
#define Input_Capsense_SW112_IDAC_MOD0_OFFSET               (291u)
#define Input_Capsense_SW112_IDAC_MOD0_SIZE                 (1u)
#define Input_Capsense_SW112_IDAC_MOD0_PARAM_ID             (0x490C0123u)

#define Input_Capsense_SW112_IDAC_GAIN_INDEX_VALUE          (Input_Capsense_dsRam.wdgtList.sw112.idacGainIndex)
#define Input_Capsense_SW112_IDAC_GAIN_INDEX_OFFSET         (292u)
#define Input_Capsense_SW112_IDAC_GAIN_INDEX_SIZE           (1u)
#define Input_Capsense_SW112_IDAC_GAIN_INDEX_PARAM_ID       (0x4F8C0124u)

#define Input_Capsense_SW112_SNS_CLK_VALUE                  (Input_Capsense_dsRam.wdgtList.sw112.snsClk)
#define Input_Capsense_SW112_SNS_CLK_OFFSET                 (294u)
#define Input_Capsense_SW112_SNS_CLK_SIZE                   (2u)
#define Input_Capsense_SW112_SNS_CLK_PARAM_ID               (0x8B8C0126u)

#define Input_Capsense_SW112_SNS_CLK_SOURCE_VALUE           (Input_Capsense_dsRam.wdgtList.sw112.snsClkSource)
#define Input_Capsense_SW112_SNS_CLK_SOURCE_OFFSET          (296u)
#define Input_Capsense_SW112_SNS_CLK_SOURCE_SIZE            (1u)
#define Input_Capsense_SW112_SNS_CLK_SOURCE_PARAM_ID        (0x4C8C0128u)

#define Input_Capsense_SW112_FINGER_CAP_VALUE               (Input_Capsense_dsRam.wdgtList.sw112.fingerCap)
#define Input_Capsense_SW112_FINGER_CAP_OFFSET              (298u)
#define Input_Capsense_SW112_FINGER_CAP_SIZE                (2u)
#define Input_Capsense_SW112_FINGER_CAP_PARAM_ID            (0xAE0C012Au)

#define Input_Capsense_SW112_SIGPFC_VALUE                   (Input_Capsense_dsRam.wdgtList.sw112.sigPFC)
#define Input_Capsense_SW112_SIGPFC_OFFSET                  (300u)
#define Input_Capsense_SW112_SIGPFC_SIZE                    (2u)
#define Input_Capsense_SW112_SIGPFC_PARAM_ID                (0xA30C012Cu)

#define Input_Capsense_SW100_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw100[0u].raw[0u])
#define Input_Capsense_SW100_SNS0_RAW0_OFFSET               (302u)
#define Input_Capsense_SW100_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW100_SNS0_RAW0_PARAM_ID             (0x8900012Eu)

#define Input_Capsense_SW100_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw100[0u].bsln[0u])
#define Input_Capsense_SW100_SNS0_BSLN0_OFFSET              (304u)
#define Input_Capsense_SW100_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW100_SNS0_BSLN0_PARAM_ID            (0x83000130u)

#define Input_Capsense_SW100_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw100[0u].bslnExt[0u])
#define Input_Capsense_SW100_SNS0_BSLN_EXT0_OFFSET          (306u)
#define Input_Capsense_SW100_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW100_SNS0_BSLN_EXT0_PARAM_ID        (0x47000132u)

#define Input_Capsense_SW100_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw100[0u].diff)
#define Input_Capsense_SW100_SNS0_DIFF_OFFSET               (308u)
#define Input_Capsense_SW100_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW100_SNS0_DIFF_PARAM_ID             (0x82000134u)

#define Input_Capsense_SW100_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw100[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW100_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (310u)
#define Input_Capsense_SW100_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW100_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x46000136u)

#define Input_Capsense_SW100_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw100[0u].idacComp[0u])
#define Input_Capsense_SW100_SNS0_IDAC_COMP0_OFFSET         (311u)
#define Input_Capsense_SW100_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW100_SNS0_IDAC_COMP0_PARAM_ID       (0x40000137u)

#define Input_Capsense_SW101_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw101[0u].raw[0u])
#define Input_Capsense_SW101_SNS0_RAW0_OFFSET               (312u)
#define Input_Capsense_SW101_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW101_SNS0_RAW0_PARAM_ID             (0x81000138u)

#define Input_Capsense_SW101_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw101[0u].bsln[0u])
#define Input_Capsense_SW101_SNS0_BSLN0_OFFSET              (314u)
#define Input_Capsense_SW101_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW101_SNS0_BSLN0_PARAM_ID            (0x8D00013Au)

#define Input_Capsense_SW101_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw101[0u].bslnExt[0u])
#define Input_Capsense_SW101_SNS0_BSLN_EXT0_OFFSET          (316u)
#define Input_Capsense_SW101_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW101_SNS0_BSLN_EXT0_PARAM_ID        (0x4800013Cu)

#define Input_Capsense_SW101_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw101[0u].diff)
#define Input_Capsense_SW101_SNS0_DIFF_OFFSET               (318u)
#define Input_Capsense_SW101_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW101_SNS0_DIFF_PARAM_ID             (0x8C00013Eu)

#define Input_Capsense_SW101_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw101[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW101_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (320u)
#define Input_Capsense_SW101_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW101_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x49000140u)

#define Input_Capsense_SW101_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw101[0u].idacComp[0u])
#define Input_Capsense_SW101_SNS0_IDAC_COMP0_OFFSET         (321u)
#define Input_Capsense_SW101_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW101_SNS0_IDAC_COMP0_PARAM_ID       (0x4F000141u)

#define Input_Capsense_SW102_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw102[0u].raw[0u])
#define Input_Capsense_SW102_SNS0_RAW0_OFFSET               (322u)
#define Input_Capsense_SW102_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW102_SNS0_RAW0_PARAM_ID             (0x8D000142u)

#define Input_Capsense_SW102_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw102[0u].bsln[0u])
#define Input_Capsense_SW102_SNS0_BSLN0_OFFSET              (324u)
#define Input_Capsense_SW102_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW102_SNS0_BSLN0_PARAM_ID            (0x80000144u)

#define Input_Capsense_SW102_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw102[0u].bslnExt[0u])
#define Input_Capsense_SW102_SNS0_BSLN_EXT0_OFFSET          (326u)
#define Input_Capsense_SW102_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW102_SNS0_BSLN_EXT0_PARAM_ID        (0x44000146u)

#define Input_Capsense_SW102_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw102[0u].diff)
#define Input_Capsense_SW102_SNS0_DIFF_OFFSET               (328u)
#define Input_Capsense_SW102_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW102_SNS0_DIFF_PARAM_ID             (0x83000148u)

#define Input_Capsense_SW102_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw102[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW102_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (330u)
#define Input_Capsense_SW102_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW102_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x4700014Au)

#define Input_Capsense_SW102_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw102[0u].idacComp[0u])
#define Input_Capsense_SW102_SNS0_IDAC_COMP0_OFFSET         (331u)
#define Input_Capsense_SW102_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW102_SNS0_IDAC_COMP0_PARAM_ID       (0x4100014Bu)

#define Input_Capsense_SW103_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw103[0u].raw[0u])
#define Input_Capsense_SW103_SNS0_RAW0_OFFSET               (332u)
#define Input_Capsense_SW103_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW103_SNS0_RAW0_PARAM_ID             (0x8200014Cu)

#define Input_Capsense_SW103_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw103[0u].bsln[0u])
#define Input_Capsense_SW103_SNS0_BSLN0_OFFSET              (334u)
#define Input_Capsense_SW103_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW103_SNS0_BSLN0_PARAM_ID            (0x8E00014Eu)

#define Input_Capsense_SW103_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw103[0u].bslnExt[0u])
#define Input_Capsense_SW103_SNS0_BSLN_EXT0_OFFSET          (336u)
#define Input_Capsense_SW103_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW103_SNS0_BSLN_EXT0_PARAM_ID        (0x4C000150u)

#define Input_Capsense_SW103_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw103[0u].diff)
#define Input_Capsense_SW103_SNS0_DIFF_OFFSET               (338u)
#define Input_Capsense_SW103_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW103_SNS0_DIFF_PARAM_ID             (0x88000152u)

#define Input_Capsense_SW103_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw103[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW103_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (340u)
#define Input_Capsense_SW103_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW103_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x4D000154u)

#define Input_Capsense_SW103_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw103[0u].idacComp[0u])
#define Input_Capsense_SW103_SNS0_IDAC_COMP0_OFFSET         (341u)
#define Input_Capsense_SW103_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW103_SNS0_IDAC_COMP0_PARAM_ID       (0x4B000155u)

#define Input_Capsense_SW104_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw104[0u].raw[0u])
#define Input_Capsense_SW104_SNS0_RAW0_OFFSET               (342u)
#define Input_Capsense_SW104_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW104_SNS0_RAW0_PARAM_ID             (0x89000156u)

#define Input_Capsense_SW104_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw104[0u].bsln[0u])
#define Input_Capsense_SW104_SNS0_BSLN0_OFFSET              (344u)
#define Input_Capsense_SW104_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW104_SNS0_BSLN0_PARAM_ID            (0x86000158u)

#define Input_Capsense_SW104_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw104[0u].bslnExt[0u])
#define Input_Capsense_SW104_SNS0_BSLN_EXT0_OFFSET          (346u)
#define Input_Capsense_SW104_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW104_SNS0_BSLN_EXT0_PARAM_ID        (0x4200015Au)

#define Input_Capsense_SW104_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw104[0u].diff)
#define Input_Capsense_SW104_SNS0_DIFF_OFFSET               (348u)
#define Input_Capsense_SW104_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW104_SNS0_DIFF_PARAM_ID             (0x8700015Cu)

#define Input_Capsense_SW104_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw104[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW104_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (350u)
#define Input_Capsense_SW104_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW104_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x4300015Eu)

#define Input_Capsense_SW104_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw104[0u].idacComp[0u])
#define Input_Capsense_SW104_SNS0_IDAC_COMP0_OFFSET         (351u)
#define Input_Capsense_SW104_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW104_SNS0_IDAC_COMP0_PARAM_ID       (0x4500015Fu)

#define Input_Capsense_SW105_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw105[0u].raw[0u])
#define Input_Capsense_SW105_SNS0_RAW0_OFFSET               (352u)
#define Input_Capsense_SW105_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW105_SNS0_RAW0_PARAM_ID             (0x8B000160u)

#define Input_Capsense_SW105_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw105[0u].bsln[0u])
#define Input_Capsense_SW105_SNS0_BSLN0_OFFSET              (354u)
#define Input_Capsense_SW105_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW105_SNS0_BSLN0_PARAM_ID            (0x87000162u)

#define Input_Capsense_SW105_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw105[0u].bslnExt[0u])
#define Input_Capsense_SW105_SNS0_BSLN_EXT0_OFFSET          (356u)
#define Input_Capsense_SW105_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW105_SNS0_BSLN_EXT0_PARAM_ID        (0x42000164u)

#define Input_Capsense_SW105_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw105[0u].diff)
#define Input_Capsense_SW105_SNS0_DIFF_OFFSET               (358u)
#define Input_Capsense_SW105_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW105_SNS0_DIFF_PARAM_ID             (0x86000166u)

#define Input_Capsense_SW105_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw105[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW105_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (360u)
#define Input_Capsense_SW105_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW105_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x41000168u)

#define Input_Capsense_SW105_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw105[0u].idacComp[0u])
#define Input_Capsense_SW105_SNS0_IDAC_COMP0_OFFSET         (361u)
#define Input_Capsense_SW105_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW105_SNS0_IDAC_COMP0_PARAM_ID       (0x47000169u)

#define Input_Capsense_SW106_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw106[0u].raw[0u])
#define Input_Capsense_SW106_SNS0_RAW0_OFFSET               (362u)
#define Input_Capsense_SW106_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW106_SNS0_RAW0_PARAM_ID             (0x8500016Au)

#define Input_Capsense_SW106_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw106[0u].bsln[0u])
#define Input_Capsense_SW106_SNS0_BSLN0_OFFSET              (364u)
#define Input_Capsense_SW106_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW106_SNS0_BSLN0_PARAM_ID            (0x8800016Cu)

#define Input_Capsense_SW106_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw106[0u].bslnExt[0u])
#define Input_Capsense_SW106_SNS0_BSLN_EXT0_OFFSET          (366u)
#define Input_Capsense_SW106_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW106_SNS0_BSLN_EXT0_PARAM_ID        (0x4C00016Eu)

#define Input_Capsense_SW106_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw106[0u].diff)
#define Input_Capsense_SW106_SNS0_DIFF_OFFSET               (368u)
#define Input_Capsense_SW106_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW106_SNS0_DIFF_PARAM_ID             (0x8E000170u)

#define Input_Capsense_SW106_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw106[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW106_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (370u)
#define Input_Capsense_SW106_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW106_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x4A000172u)

#define Input_Capsense_SW106_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw106[0u].idacComp[0u])
#define Input_Capsense_SW106_SNS0_IDAC_COMP0_OFFSET         (371u)
#define Input_Capsense_SW106_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW106_SNS0_IDAC_COMP0_PARAM_ID       (0x4C000173u)

#define Input_Capsense_SW107_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw107[0u].raw[0u])
#define Input_Capsense_SW107_SNS0_RAW0_OFFSET               (372u)
#define Input_Capsense_SW107_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW107_SNS0_RAW0_PARAM_ID             (0x8F000174u)

#define Input_Capsense_SW107_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw107[0u].bsln[0u])
#define Input_Capsense_SW107_SNS0_BSLN0_OFFSET              (374u)
#define Input_Capsense_SW107_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW107_SNS0_BSLN0_PARAM_ID            (0x83000176u)

#define Input_Capsense_SW107_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw107[0u].bslnExt[0u])
#define Input_Capsense_SW107_SNS0_BSLN_EXT0_OFFSET          (376u)
#define Input_Capsense_SW107_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW107_SNS0_BSLN_EXT0_PARAM_ID        (0x44000178u)

#define Input_Capsense_SW107_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw107[0u].diff)
#define Input_Capsense_SW107_SNS0_DIFF_OFFSET               (378u)
#define Input_Capsense_SW107_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW107_SNS0_DIFF_PARAM_ID             (0x8000017Au)

#define Input_Capsense_SW107_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw107[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW107_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (380u)
#define Input_Capsense_SW107_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW107_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x4500017Cu)

#define Input_Capsense_SW107_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw107[0u].idacComp[0u])
#define Input_Capsense_SW107_SNS0_IDAC_COMP0_OFFSET         (381u)
#define Input_Capsense_SW107_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW107_SNS0_IDAC_COMP0_PARAM_ID       (0x4300017Du)

#define Input_Capsense_SW108_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw108[0u].raw[0u])
#define Input_Capsense_SW108_SNS0_RAW0_OFFSET               (382u)
#define Input_Capsense_SW108_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW108_SNS0_RAW0_PARAM_ID             (0x8100017Eu)

#define Input_Capsense_SW108_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw108[0u].bsln[0u])
#define Input_Capsense_SW108_SNS0_BSLN0_OFFSET              (384u)
#define Input_Capsense_SW108_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW108_SNS0_BSLN0_PARAM_ID            (0x8F000180u)

#define Input_Capsense_SW108_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw108[0u].bslnExt[0u])
#define Input_Capsense_SW108_SNS0_BSLN_EXT0_OFFSET          (386u)
#define Input_Capsense_SW108_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW108_SNS0_BSLN_EXT0_PARAM_ID        (0x4B000182u)

#define Input_Capsense_SW108_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw108[0u].diff)
#define Input_Capsense_SW108_SNS0_DIFF_OFFSET               (388u)
#define Input_Capsense_SW108_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW108_SNS0_DIFF_PARAM_ID             (0x8E000184u)

#define Input_Capsense_SW108_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw108[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW108_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (390u)
#define Input_Capsense_SW108_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW108_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x4A000186u)

#define Input_Capsense_SW108_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw108[0u].idacComp[0u])
#define Input_Capsense_SW108_SNS0_IDAC_COMP0_OFFSET         (391u)
#define Input_Capsense_SW108_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW108_SNS0_IDAC_COMP0_PARAM_ID       (0x4C000187u)

#define Input_Capsense_SW109_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw109[0u].raw[0u])
#define Input_Capsense_SW109_SNS0_RAW0_OFFSET               (392u)
#define Input_Capsense_SW109_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW109_SNS0_RAW0_PARAM_ID             (0x8D000188u)

#define Input_Capsense_SW109_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw109[0u].bsln[0u])
#define Input_Capsense_SW109_SNS0_BSLN0_OFFSET              (394u)
#define Input_Capsense_SW109_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW109_SNS0_BSLN0_PARAM_ID            (0x8100018Au)

#define Input_Capsense_SW109_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw109[0u].bslnExt[0u])
#define Input_Capsense_SW109_SNS0_BSLN_EXT0_OFFSET          (396u)
#define Input_Capsense_SW109_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW109_SNS0_BSLN_EXT0_PARAM_ID        (0x4400018Cu)

#define Input_Capsense_SW109_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw109[0u].diff)
#define Input_Capsense_SW109_SNS0_DIFF_OFFSET               (398u)
#define Input_Capsense_SW109_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW109_SNS0_DIFF_PARAM_ID             (0x8000018Eu)

#define Input_Capsense_SW109_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw109[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW109_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (400u)
#define Input_Capsense_SW109_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW109_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x42000190u)

#define Input_Capsense_SW109_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw109[0u].idacComp[0u])
#define Input_Capsense_SW109_SNS0_IDAC_COMP0_OFFSET         (401u)
#define Input_Capsense_SW109_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW109_SNS0_IDAC_COMP0_PARAM_ID       (0x44000191u)

#define Input_Capsense_SW110_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw110[0u].raw[0u])
#define Input_Capsense_SW110_SNS0_RAW0_OFFSET               (402u)
#define Input_Capsense_SW110_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW110_SNS0_RAW0_PARAM_ID             (0x86000192u)

#define Input_Capsense_SW110_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw110[0u].bsln[0u])
#define Input_Capsense_SW110_SNS0_BSLN0_OFFSET              (404u)
#define Input_Capsense_SW110_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW110_SNS0_BSLN0_PARAM_ID            (0x8B000194u)

#define Input_Capsense_SW110_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw110[0u].bslnExt[0u])
#define Input_Capsense_SW110_SNS0_BSLN_EXT0_OFFSET          (406u)
#define Input_Capsense_SW110_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW110_SNS0_BSLN_EXT0_PARAM_ID        (0x4F000196u)

#define Input_Capsense_SW110_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw110[0u].diff)
#define Input_Capsense_SW110_SNS0_DIFF_OFFSET               (408u)
#define Input_Capsense_SW110_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW110_SNS0_DIFF_PARAM_ID             (0x88000198u)

#define Input_Capsense_SW110_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw110[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW110_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (410u)
#define Input_Capsense_SW110_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW110_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x4C00019Au)

#define Input_Capsense_SW110_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw110[0u].idacComp[0u])
#define Input_Capsense_SW110_SNS0_IDAC_COMP0_OFFSET         (411u)
#define Input_Capsense_SW110_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW110_SNS0_IDAC_COMP0_PARAM_ID       (0x4A00019Bu)

#define Input_Capsense_SW111_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw111[0u].raw[0u])
#define Input_Capsense_SW111_SNS0_RAW0_OFFSET               (412u)
#define Input_Capsense_SW111_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW111_SNS0_RAW0_PARAM_ID             (0x8900019Cu)

#define Input_Capsense_SW111_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw111[0u].bsln[0u])
#define Input_Capsense_SW111_SNS0_BSLN0_OFFSET              (414u)
#define Input_Capsense_SW111_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW111_SNS0_BSLN0_PARAM_ID            (0x8500019Eu)

#define Input_Capsense_SW111_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw111[0u].bslnExt[0u])
#define Input_Capsense_SW111_SNS0_BSLN_EXT0_OFFSET          (416u)
#define Input_Capsense_SW111_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW111_SNS0_BSLN_EXT0_PARAM_ID        (0x4D0001A0u)

#define Input_Capsense_SW111_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw111[0u].diff)
#define Input_Capsense_SW111_SNS0_DIFF_OFFSET               (418u)
#define Input_Capsense_SW111_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW111_SNS0_DIFF_PARAM_ID             (0x890001A2u)

#define Input_Capsense_SW111_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw111[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW111_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (420u)
#define Input_Capsense_SW111_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW111_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x4C0001A4u)

#define Input_Capsense_SW111_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw111[0u].idacComp[0u])
#define Input_Capsense_SW111_SNS0_IDAC_COMP0_OFFSET         (421u)
#define Input_Capsense_SW111_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW111_SNS0_IDAC_COMP0_PARAM_ID       (0x4A0001A5u)

#define Input_Capsense_SW112_SNS0_RAW0_VALUE                (Input_Capsense_dsRam.snsList.sw112[0u].raw[0u])
#define Input_Capsense_SW112_SNS0_RAW0_OFFSET               (422u)
#define Input_Capsense_SW112_SNS0_RAW0_SIZE                 (2u)
#define Input_Capsense_SW112_SNS0_RAW0_PARAM_ID             (0x880001A6u)

#define Input_Capsense_SW112_SNS0_BSLN0_VALUE               (Input_Capsense_dsRam.snsList.sw112[0u].bsln[0u])
#define Input_Capsense_SW112_SNS0_BSLN0_OFFSET              (424u)
#define Input_Capsense_SW112_SNS0_BSLN0_SIZE                (2u)
#define Input_Capsense_SW112_SNS0_BSLN0_PARAM_ID            (0x870001A8u)

#define Input_Capsense_SW112_SNS0_BSLN_EXT0_VALUE           (Input_Capsense_dsRam.snsList.sw112[0u].bslnExt[0u])
#define Input_Capsense_SW112_SNS0_BSLN_EXT0_OFFSET          (426u)
#define Input_Capsense_SW112_SNS0_BSLN_EXT0_SIZE            (1u)
#define Input_Capsense_SW112_SNS0_BSLN_EXT0_PARAM_ID        (0x430001AAu)

#define Input_Capsense_SW112_SNS0_DIFF_VALUE                (Input_Capsense_dsRam.snsList.sw112[0u].diff)
#define Input_Capsense_SW112_SNS0_DIFF_OFFSET               (428u)
#define Input_Capsense_SW112_SNS0_DIFF_SIZE                 (2u)
#define Input_Capsense_SW112_SNS0_DIFF_PARAM_ID             (0x860001ACu)

#define Input_Capsense_SW112_SNS0_NEG_BSLN_RST_CNT0_VALUE   (Input_Capsense_dsRam.snsList.sw112[0u].negBslnRstCnt[0u])
#define Input_Capsense_SW112_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (430u)
#define Input_Capsense_SW112_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define Input_Capsense_SW112_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x420001AEu)

#define Input_Capsense_SW112_SNS0_IDAC_COMP0_VALUE          (Input_Capsense_dsRam.snsList.sw112[0u].idacComp[0u])
#define Input_Capsense_SW112_SNS0_IDAC_COMP0_OFFSET         (431u)
#define Input_Capsense_SW112_SNS0_IDAC_COMP0_SIZE           (1u)
#define Input_Capsense_SW112_SNS0_IDAC_COMP0_PARAM_ID       (0x440001AFu)

#define Input_Capsense_SNR_TEST_WIDGET_ID_VALUE             (Input_Capsense_dsRam.snrTestWidgetId)
#define Input_Capsense_SNR_TEST_WIDGET_ID_OFFSET            (432u)
#define Input_Capsense_SNR_TEST_WIDGET_ID_SIZE              (1u)
#define Input_Capsense_SNR_TEST_WIDGET_ID_PARAM_ID          (0x630001B0u)

#define Input_Capsense_SNR_TEST_SENSOR_ID_VALUE             (Input_Capsense_dsRam.snrTestSensorId)
#define Input_Capsense_SNR_TEST_SENSOR_ID_OFFSET            (433u)
#define Input_Capsense_SNR_TEST_SENSOR_ID_SIZE              (1u)
#define Input_Capsense_SNR_TEST_SENSOR_ID_PARAM_ID          (0x650001B1u)

#define Input_Capsense_SNR_TEST_SCAN_COUNTER_VALUE          (Input_Capsense_dsRam.snrTestScanCounter)
#define Input_Capsense_SNR_TEST_SCAN_COUNTER_OFFSET         (434u)
#define Input_Capsense_SNR_TEST_SCAN_COUNTER_SIZE           (2u)
#define Input_Capsense_SNR_TEST_SCAN_COUNTER_PARAM_ID       (0x8C0001B2u)

#define Input_Capsense_SNR_TEST_RAW_COUNT0_VALUE            (Input_Capsense_dsRam.snrTestRawCount[0u])
#define Input_Capsense_SNR_TEST_RAW_COUNT0_OFFSET           (436u)
#define Input_Capsense_SNR_TEST_RAW_COUNT0_SIZE             (2u)
#define Input_Capsense_SNR_TEST_RAW_COUNT0_PARAM_ID         (0x810001B4u)

#define Input_Capsense_SCAN_CSD_ISC_VALUE                   (Input_Capsense_dsRam.scanCsdISC)
#define Input_Capsense_SCAN_CSD_ISC_OFFSET                  (438u)
#define Input_Capsense_SCAN_CSD_ISC_SIZE                    (1u)
#define Input_Capsense_SCAN_CSD_ISC_PARAM_ID                (0x450001B6u)

#define Input_Capsense_SCAN_CURRENT_ISC_VALUE               (Input_Capsense_dsRam.scanCurrentISC)
#define Input_Capsense_SCAN_CURRENT_ISC_OFFSET              (439u)
#define Input_Capsense_SCAN_CURRENT_ISC_SIZE                (1u)
#define Input_Capsense_SCAN_CURRENT_ISC_PARAM_ID            (0x430001B7u)


/*****************************************************************************/
/* Flash Data structure register definitions                                 */
/*****************************************************************************/
#define Input_Capsense_SW100_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[0].ptr2SnsFlash)
#define Input_Capsense_SW100_PTR2SNS_FLASH_OFFSET           (0u)
#define Input_Capsense_SW100_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW100_PTR2SNS_FLASH_PARAM_ID         (0xD1000000u)

#define Input_Capsense_SW100_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[0].ptr2WdgtRam)
#define Input_Capsense_SW100_PTR2WD_RAM_OFFSET              (4u)
#define Input_Capsense_SW100_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW100_PTR2WD_RAM_PARAM_ID            (0xD0000004u)

#define Input_Capsense_SW100_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[0].ptr2SnsRam)
#define Input_Capsense_SW100_PTR2SNS_RAM_OFFSET             (8u)
#define Input_Capsense_SW100_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW100_PTR2SNS_RAM_PARAM_ID           (0xD3000008u)

#define Input_Capsense_SW100_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[0].ptr2FltrHistory)
#define Input_Capsense_SW100_PTR2FLTR_HISTORY_OFFSET        (12u)
#define Input_Capsense_SW100_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW100_PTR2FLTR_HISTORY_PARAM_ID      (0xD200000Cu)

#define Input_Capsense_SW100_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[0].ptr2DebounceArr)
#define Input_Capsense_SW100_PTR2DEBOUNCE_OFFSET            (16u)
#define Input_Capsense_SW100_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW100_PTR2DEBOUNCE_PARAM_ID          (0xD4000010u)

#define Input_Capsense_SW100_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[0].staticConfig)
#define Input_Capsense_SW100_STATIC_CONFIG_OFFSET           (20u)
#define Input_Capsense_SW100_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW100_STATIC_CONFIG_PARAM_ID         (0xD5000014u)

#define Input_Capsense_SW100_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[0].totalNumSns)
#define Input_Capsense_SW100_TOTAL_NUM_SNS_OFFSET           (24u)
#define Input_Capsense_SW100_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW100_TOTAL_NUM_SNS_PARAM_ID         (0x99000018u)

#define Input_Capsense_SW100_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[0].wdgtType)
#define Input_Capsense_SW100_TYPE_OFFSET                    (26u)
#define Input_Capsense_SW100_TYPE_SIZE                      (1u)
#define Input_Capsense_SW100_TYPE_PARAM_ID                  (0x5D00001Au)

#define Input_Capsense_SW100_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[0].numCols)
#define Input_Capsense_SW100_NUM_COLS_OFFSET                (27u)
#define Input_Capsense_SW100_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW100_NUM_COLS_PARAM_ID              (0x5B00001Bu)

#define Input_Capsense_SW100_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[0].ptr2NoiseEnvlp)
#define Input_Capsense_SW100_PTR2NOISE_ENVLP_OFFSET         (28u)
#define Input_Capsense_SW100_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW100_PTR2NOISE_ENVLP_PARAM_ID       (0xD700001Cu)

#define Input_Capsense_SW101_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[1].ptr2SnsFlash)
#define Input_Capsense_SW101_PTR2SNS_FLASH_OFFSET           (32u)
#define Input_Capsense_SW101_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW101_PTR2SNS_FLASH_PARAM_ID         (0xD8010020u)

#define Input_Capsense_SW101_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[1].ptr2WdgtRam)
#define Input_Capsense_SW101_PTR2WD_RAM_OFFSET              (36u)
#define Input_Capsense_SW101_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW101_PTR2WD_RAM_PARAM_ID            (0xD9010024u)

#define Input_Capsense_SW101_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[1].ptr2SnsRam)
#define Input_Capsense_SW101_PTR2SNS_RAM_OFFSET             (40u)
#define Input_Capsense_SW101_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW101_PTR2SNS_RAM_PARAM_ID           (0xDA010028u)

#define Input_Capsense_SW101_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[1].ptr2FltrHistory)
#define Input_Capsense_SW101_PTR2FLTR_HISTORY_OFFSET        (44u)
#define Input_Capsense_SW101_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW101_PTR2FLTR_HISTORY_PARAM_ID      (0xDB01002Cu)

#define Input_Capsense_SW101_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[1].ptr2DebounceArr)
#define Input_Capsense_SW101_PTR2DEBOUNCE_OFFSET            (48u)
#define Input_Capsense_SW101_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW101_PTR2DEBOUNCE_PARAM_ID          (0xDD010030u)

#define Input_Capsense_SW101_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[1].staticConfig)
#define Input_Capsense_SW101_STATIC_CONFIG_OFFSET           (52u)
#define Input_Capsense_SW101_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW101_STATIC_CONFIG_PARAM_ID         (0xDC010034u)

#define Input_Capsense_SW101_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[1].totalNumSns)
#define Input_Capsense_SW101_TOTAL_NUM_SNS_OFFSET           (56u)
#define Input_Capsense_SW101_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW101_TOTAL_NUM_SNS_PARAM_ID         (0x90010038u)

#define Input_Capsense_SW101_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[1].wdgtType)
#define Input_Capsense_SW101_TYPE_OFFSET                    (58u)
#define Input_Capsense_SW101_TYPE_SIZE                      (1u)
#define Input_Capsense_SW101_TYPE_PARAM_ID                  (0x5401003Au)

#define Input_Capsense_SW101_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[1].numCols)
#define Input_Capsense_SW101_NUM_COLS_OFFSET                (59u)
#define Input_Capsense_SW101_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW101_NUM_COLS_PARAM_ID              (0x5201003Bu)

#define Input_Capsense_SW101_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[1].ptr2NoiseEnvlp)
#define Input_Capsense_SW101_PTR2NOISE_ENVLP_OFFSET         (60u)
#define Input_Capsense_SW101_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW101_PTR2NOISE_ENVLP_PARAM_ID       (0xDE01003Cu)

#define Input_Capsense_SW102_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[2].ptr2SnsFlash)
#define Input_Capsense_SW102_PTR2SNS_FLASH_OFFSET           (64u)
#define Input_Capsense_SW102_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW102_PTR2SNS_FLASH_PARAM_ID         (0xDA020040u)

#define Input_Capsense_SW102_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[2].ptr2WdgtRam)
#define Input_Capsense_SW102_PTR2WD_RAM_OFFSET              (68u)
#define Input_Capsense_SW102_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW102_PTR2WD_RAM_PARAM_ID            (0xDB020044u)

#define Input_Capsense_SW102_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[2].ptr2SnsRam)
#define Input_Capsense_SW102_PTR2SNS_RAM_OFFSET             (72u)
#define Input_Capsense_SW102_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW102_PTR2SNS_RAM_PARAM_ID           (0xD8020048u)

#define Input_Capsense_SW102_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[2].ptr2FltrHistory)
#define Input_Capsense_SW102_PTR2FLTR_HISTORY_OFFSET        (76u)
#define Input_Capsense_SW102_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW102_PTR2FLTR_HISTORY_PARAM_ID      (0xD902004Cu)

#define Input_Capsense_SW102_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[2].ptr2DebounceArr)
#define Input_Capsense_SW102_PTR2DEBOUNCE_OFFSET            (80u)
#define Input_Capsense_SW102_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW102_PTR2DEBOUNCE_PARAM_ID          (0xDF020050u)

#define Input_Capsense_SW102_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[2].staticConfig)
#define Input_Capsense_SW102_STATIC_CONFIG_OFFSET           (84u)
#define Input_Capsense_SW102_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW102_STATIC_CONFIG_PARAM_ID         (0xDE020054u)

#define Input_Capsense_SW102_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[2].totalNumSns)
#define Input_Capsense_SW102_TOTAL_NUM_SNS_OFFSET           (88u)
#define Input_Capsense_SW102_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW102_TOTAL_NUM_SNS_PARAM_ID         (0x92020058u)

#define Input_Capsense_SW102_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[2].wdgtType)
#define Input_Capsense_SW102_TYPE_OFFSET                    (90u)
#define Input_Capsense_SW102_TYPE_SIZE                      (1u)
#define Input_Capsense_SW102_TYPE_PARAM_ID                  (0x5602005Au)

#define Input_Capsense_SW102_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[2].numCols)
#define Input_Capsense_SW102_NUM_COLS_OFFSET                (91u)
#define Input_Capsense_SW102_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW102_NUM_COLS_PARAM_ID              (0x5002005Bu)

#define Input_Capsense_SW102_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[2].ptr2NoiseEnvlp)
#define Input_Capsense_SW102_PTR2NOISE_ENVLP_OFFSET         (92u)
#define Input_Capsense_SW102_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW102_PTR2NOISE_ENVLP_PARAM_ID       (0xDC02005Cu)

#define Input_Capsense_SW103_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[3].ptr2SnsFlash)
#define Input_Capsense_SW103_PTR2SNS_FLASH_OFFSET           (96u)
#define Input_Capsense_SW103_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW103_PTR2SNS_FLASH_PARAM_ID         (0xD3030060u)

#define Input_Capsense_SW103_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[3].ptr2WdgtRam)
#define Input_Capsense_SW103_PTR2WD_RAM_OFFSET              (100u)
#define Input_Capsense_SW103_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW103_PTR2WD_RAM_PARAM_ID            (0xD2030064u)

#define Input_Capsense_SW103_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[3].ptr2SnsRam)
#define Input_Capsense_SW103_PTR2SNS_RAM_OFFSET             (104u)
#define Input_Capsense_SW103_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW103_PTR2SNS_RAM_PARAM_ID           (0xD1030068u)

#define Input_Capsense_SW103_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[3].ptr2FltrHistory)
#define Input_Capsense_SW103_PTR2FLTR_HISTORY_OFFSET        (108u)
#define Input_Capsense_SW103_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW103_PTR2FLTR_HISTORY_PARAM_ID      (0xD003006Cu)

#define Input_Capsense_SW103_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[3].ptr2DebounceArr)
#define Input_Capsense_SW103_PTR2DEBOUNCE_OFFSET            (112u)
#define Input_Capsense_SW103_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW103_PTR2DEBOUNCE_PARAM_ID          (0xD6030070u)

#define Input_Capsense_SW103_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[3].staticConfig)
#define Input_Capsense_SW103_STATIC_CONFIG_OFFSET           (116u)
#define Input_Capsense_SW103_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW103_STATIC_CONFIG_PARAM_ID         (0xD7030074u)

#define Input_Capsense_SW103_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[3].totalNumSns)
#define Input_Capsense_SW103_TOTAL_NUM_SNS_OFFSET           (120u)
#define Input_Capsense_SW103_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW103_TOTAL_NUM_SNS_PARAM_ID         (0x9B030078u)

#define Input_Capsense_SW103_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[3].wdgtType)
#define Input_Capsense_SW103_TYPE_OFFSET                    (122u)
#define Input_Capsense_SW103_TYPE_SIZE                      (1u)
#define Input_Capsense_SW103_TYPE_PARAM_ID                  (0x5F03007Au)

#define Input_Capsense_SW103_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[3].numCols)
#define Input_Capsense_SW103_NUM_COLS_OFFSET                (123u)
#define Input_Capsense_SW103_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW103_NUM_COLS_PARAM_ID              (0x5903007Bu)

#define Input_Capsense_SW103_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[3].ptr2NoiseEnvlp)
#define Input_Capsense_SW103_PTR2NOISE_ENVLP_OFFSET         (124u)
#define Input_Capsense_SW103_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW103_PTR2NOISE_ENVLP_PARAM_ID       (0xD503007Cu)

#define Input_Capsense_SW104_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[4].ptr2SnsFlash)
#define Input_Capsense_SW104_PTR2SNS_FLASH_OFFSET           (128u)
#define Input_Capsense_SW104_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW104_PTR2SNS_FLASH_PARAM_ID         (0xDE040080u)

#define Input_Capsense_SW104_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[4].ptr2WdgtRam)
#define Input_Capsense_SW104_PTR2WD_RAM_OFFSET              (132u)
#define Input_Capsense_SW104_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW104_PTR2WD_RAM_PARAM_ID            (0xDF040084u)

#define Input_Capsense_SW104_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[4].ptr2SnsRam)
#define Input_Capsense_SW104_PTR2SNS_RAM_OFFSET             (136u)
#define Input_Capsense_SW104_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW104_PTR2SNS_RAM_PARAM_ID           (0xDC040088u)

#define Input_Capsense_SW104_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[4].ptr2FltrHistory)
#define Input_Capsense_SW104_PTR2FLTR_HISTORY_OFFSET        (140u)
#define Input_Capsense_SW104_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW104_PTR2FLTR_HISTORY_PARAM_ID      (0xDD04008Cu)

#define Input_Capsense_SW104_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[4].ptr2DebounceArr)
#define Input_Capsense_SW104_PTR2DEBOUNCE_OFFSET            (144u)
#define Input_Capsense_SW104_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW104_PTR2DEBOUNCE_PARAM_ID          (0xDB040090u)

#define Input_Capsense_SW104_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[4].staticConfig)
#define Input_Capsense_SW104_STATIC_CONFIG_OFFSET           (148u)
#define Input_Capsense_SW104_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW104_STATIC_CONFIG_PARAM_ID         (0xDA040094u)

#define Input_Capsense_SW104_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[4].totalNumSns)
#define Input_Capsense_SW104_TOTAL_NUM_SNS_OFFSET           (152u)
#define Input_Capsense_SW104_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW104_TOTAL_NUM_SNS_PARAM_ID         (0x96040098u)

#define Input_Capsense_SW104_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[4].wdgtType)
#define Input_Capsense_SW104_TYPE_OFFSET                    (154u)
#define Input_Capsense_SW104_TYPE_SIZE                      (1u)
#define Input_Capsense_SW104_TYPE_PARAM_ID                  (0x5204009Au)

#define Input_Capsense_SW104_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[4].numCols)
#define Input_Capsense_SW104_NUM_COLS_OFFSET                (155u)
#define Input_Capsense_SW104_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW104_NUM_COLS_PARAM_ID              (0x5404009Bu)

#define Input_Capsense_SW104_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[4].ptr2NoiseEnvlp)
#define Input_Capsense_SW104_PTR2NOISE_ENVLP_OFFSET         (156u)
#define Input_Capsense_SW104_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW104_PTR2NOISE_ENVLP_PARAM_ID       (0xD804009Cu)

#define Input_Capsense_SW105_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[5].ptr2SnsFlash)
#define Input_Capsense_SW105_PTR2SNS_FLASH_OFFSET           (160u)
#define Input_Capsense_SW105_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW105_PTR2SNS_FLASH_PARAM_ID         (0xD70500A0u)

#define Input_Capsense_SW105_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[5].ptr2WdgtRam)
#define Input_Capsense_SW105_PTR2WD_RAM_OFFSET              (164u)
#define Input_Capsense_SW105_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW105_PTR2WD_RAM_PARAM_ID            (0xD60500A4u)

#define Input_Capsense_SW105_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[5].ptr2SnsRam)
#define Input_Capsense_SW105_PTR2SNS_RAM_OFFSET             (168u)
#define Input_Capsense_SW105_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW105_PTR2SNS_RAM_PARAM_ID           (0xD50500A8u)

#define Input_Capsense_SW105_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[5].ptr2FltrHistory)
#define Input_Capsense_SW105_PTR2FLTR_HISTORY_OFFSET        (172u)
#define Input_Capsense_SW105_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW105_PTR2FLTR_HISTORY_PARAM_ID      (0xD40500ACu)

#define Input_Capsense_SW105_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[5].ptr2DebounceArr)
#define Input_Capsense_SW105_PTR2DEBOUNCE_OFFSET            (176u)
#define Input_Capsense_SW105_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW105_PTR2DEBOUNCE_PARAM_ID          (0xD20500B0u)

#define Input_Capsense_SW105_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[5].staticConfig)
#define Input_Capsense_SW105_STATIC_CONFIG_OFFSET           (180u)
#define Input_Capsense_SW105_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW105_STATIC_CONFIG_PARAM_ID         (0xD30500B4u)

#define Input_Capsense_SW105_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[5].totalNumSns)
#define Input_Capsense_SW105_TOTAL_NUM_SNS_OFFSET           (184u)
#define Input_Capsense_SW105_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW105_TOTAL_NUM_SNS_PARAM_ID         (0x9F0500B8u)

#define Input_Capsense_SW105_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[5].wdgtType)
#define Input_Capsense_SW105_TYPE_OFFSET                    (186u)
#define Input_Capsense_SW105_TYPE_SIZE                      (1u)
#define Input_Capsense_SW105_TYPE_PARAM_ID                  (0x5B0500BAu)

#define Input_Capsense_SW105_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[5].numCols)
#define Input_Capsense_SW105_NUM_COLS_OFFSET                (187u)
#define Input_Capsense_SW105_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW105_NUM_COLS_PARAM_ID              (0x5D0500BBu)

#define Input_Capsense_SW105_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[5].ptr2NoiseEnvlp)
#define Input_Capsense_SW105_PTR2NOISE_ENVLP_OFFSET         (188u)
#define Input_Capsense_SW105_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW105_PTR2NOISE_ENVLP_PARAM_ID       (0xD10500BCu)

#define Input_Capsense_SW106_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[6].ptr2SnsFlash)
#define Input_Capsense_SW106_PTR2SNS_FLASH_OFFSET           (192u)
#define Input_Capsense_SW106_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW106_PTR2SNS_FLASH_PARAM_ID         (0xD50600C0u)

#define Input_Capsense_SW106_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[6].ptr2WdgtRam)
#define Input_Capsense_SW106_PTR2WD_RAM_OFFSET              (196u)
#define Input_Capsense_SW106_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW106_PTR2WD_RAM_PARAM_ID            (0xD40600C4u)

#define Input_Capsense_SW106_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[6].ptr2SnsRam)
#define Input_Capsense_SW106_PTR2SNS_RAM_OFFSET             (200u)
#define Input_Capsense_SW106_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW106_PTR2SNS_RAM_PARAM_ID           (0xD70600C8u)

#define Input_Capsense_SW106_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[6].ptr2FltrHistory)
#define Input_Capsense_SW106_PTR2FLTR_HISTORY_OFFSET        (204u)
#define Input_Capsense_SW106_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW106_PTR2FLTR_HISTORY_PARAM_ID      (0xD60600CCu)

#define Input_Capsense_SW106_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[6].ptr2DebounceArr)
#define Input_Capsense_SW106_PTR2DEBOUNCE_OFFSET            (208u)
#define Input_Capsense_SW106_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW106_PTR2DEBOUNCE_PARAM_ID          (0xD00600D0u)

#define Input_Capsense_SW106_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[6].staticConfig)
#define Input_Capsense_SW106_STATIC_CONFIG_OFFSET           (212u)
#define Input_Capsense_SW106_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW106_STATIC_CONFIG_PARAM_ID         (0xD10600D4u)

#define Input_Capsense_SW106_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[6].totalNumSns)
#define Input_Capsense_SW106_TOTAL_NUM_SNS_OFFSET           (216u)
#define Input_Capsense_SW106_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW106_TOTAL_NUM_SNS_PARAM_ID         (0x9D0600D8u)

#define Input_Capsense_SW106_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[6].wdgtType)
#define Input_Capsense_SW106_TYPE_OFFSET                    (218u)
#define Input_Capsense_SW106_TYPE_SIZE                      (1u)
#define Input_Capsense_SW106_TYPE_PARAM_ID                  (0x590600DAu)

#define Input_Capsense_SW106_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[6].numCols)
#define Input_Capsense_SW106_NUM_COLS_OFFSET                (219u)
#define Input_Capsense_SW106_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW106_NUM_COLS_PARAM_ID              (0x5F0600DBu)

#define Input_Capsense_SW106_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[6].ptr2NoiseEnvlp)
#define Input_Capsense_SW106_PTR2NOISE_ENVLP_OFFSET         (220u)
#define Input_Capsense_SW106_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW106_PTR2NOISE_ENVLP_PARAM_ID       (0xD30600DCu)

#define Input_Capsense_SW107_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[7].ptr2SnsFlash)
#define Input_Capsense_SW107_PTR2SNS_FLASH_OFFSET           (224u)
#define Input_Capsense_SW107_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW107_PTR2SNS_FLASH_PARAM_ID         (0xDC0700E0u)

#define Input_Capsense_SW107_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[7].ptr2WdgtRam)
#define Input_Capsense_SW107_PTR2WD_RAM_OFFSET              (228u)
#define Input_Capsense_SW107_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW107_PTR2WD_RAM_PARAM_ID            (0xDD0700E4u)

#define Input_Capsense_SW107_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[7].ptr2SnsRam)
#define Input_Capsense_SW107_PTR2SNS_RAM_OFFSET             (232u)
#define Input_Capsense_SW107_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW107_PTR2SNS_RAM_PARAM_ID           (0xDE0700E8u)

#define Input_Capsense_SW107_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[7].ptr2FltrHistory)
#define Input_Capsense_SW107_PTR2FLTR_HISTORY_OFFSET        (236u)
#define Input_Capsense_SW107_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW107_PTR2FLTR_HISTORY_PARAM_ID      (0xDF0700ECu)

#define Input_Capsense_SW107_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[7].ptr2DebounceArr)
#define Input_Capsense_SW107_PTR2DEBOUNCE_OFFSET            (240u)
#define Input_Capsense_SW107_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW107_PTR2DEBOUNCE_PARAM_ID          (0xD90700F0u)

#define Input_Capsense_SW107_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[7].staticConfig)
#define Input_Capsense_SW107_STATIC_CONFIG_OFFSET           (244u)
#define Input_Capsense_SW107_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW107_STATIC_CONFIG_PARAM_ID         (0xD80700F4u)

#define Input_Capsense_SW107_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[7].totalNumSns)
#define Input_Capsense_SW107_TOTAL_NUM_SNS_OFFSET           (248u)
#define Input_Capsense_SW107_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW107_TOTAL_NUM_SNS_PARAM_ID         (0x940700F8u)

#define Input_Capsense_SW107_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[7].wdgtType)
#define Input_Capsense_SW107_TYPE_OFFSET                    (250u)
#define Input_Capsense_SW107_TYPE_SIZE                      (1u)
#define Input_Capsense_SW107_TYPE_PARAM_ID                  (0x500700FAu)

#define Input_Capsense_SW107_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[7].numCols)
#define Input_Capsense_SW107_NUM_COLS_OFFSET                (251u)
#define Input_Capsense_SW107_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW107_NUM_COLS_PARAM_ID              (0x560700FBu)

#define Input_Capsense_SW107_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[7].ptr2NoiseEnvlp)
#define Input_Capsense_SW107_PTR2NOISE_ENVLP_OFFSET         (252u)
#define Input_Capsense_SW107_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW107_PTR2NOISE_ENVLP_PARAM_ID       (0xDA0700FCu)

#define Input_Capsense_SW108_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[8].ptr2SnsFlash)
#define Input_Capsense_SW108_PTR2SNS_FLASH_OFFSET           (256u)
#define Input_Capsense_SW108_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW108_PTR2SNS_FLASH_PARAM_ID         (0xDB080100u)

#define Input_Capsense_SW108_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[8].ptr2WdgtRam)
#define Input_Capsense_SW108_PTR2WD_RAM_OFFSET              (260u)
#define Input_Capsense_SW108_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW108_PTR2WD_RAM_PARAM_ID            (0xDA080104u)

#define Input_Capsense_SW108_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[8].ptr2SnsRam)
#define Input_Capsense_SW108_PTR2SNS_RAM_OFFSET             (264u)
#define Input_Capsense_SW108_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW108_PTR2SNS_RAM_PARAM_ID           (0xD9080108u)

#define Input_Capsense_SW108_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[8].ptr2FltrHistory)
#define Input_Capsense_SW108_PTR2FLTR_HISTORY_OFFSET        (268u)
#define Input_Capsense_SW108_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW108_PTR2FLTR_HISTORY_PARAM_ID      (0xD808010Cu)

#define Input_Capsense_SW108_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[8].ptr2DebounceArr)
#define Input_Capsense_SW108_PTR2DEBOUNCE_OFFSET            (272u)
#define Input_Capsense_SW108_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW108_PTR2DEBOUNCE_PARAM_ID          (0xDE080110u)

#define Input_Capsense_SW108_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[8].staticConfig)
#define Input_Capsense_SW108_STATIC_CONFIG_OFFSET           (276u)
#define Input_Capsense_SW108_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW108_STATIC_CONFIG_PARAM_ID         (0xDF080114u)

#define Input_Capsense_SW108_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[8].totalNumSns)
#define Input_Capsense_SW108_TOTAL_NUM_SNS_OFFSET           (280u)
#define Input_Capsense_SW108_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW108_TOTAL_NUM_SNS_PARAM_ID         (0x93080118u)

#define Input_Capsense_SW108_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[8].wdgtType)
#define Input_Capsense_SW108_TYPE_OFFSET                    (282u)
#define Input_Capsense_SW108_TYPE_SIZE                      (1u)
#define Input_Capsense_SW108_TYPE_PARAM_ID                  (0x5708011Au)

#define Input_Capsense_SW108_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[8].numCols)
#define Input_Capsense_SW108_NUM_COLS_OFFSET                (283u)
#define Input_Capsense_SW108_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW108_NUM_COLS_PARAM_ID              (0x5108011Bu)

#define Input_Capsense_SW108_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[8].ptr2NoiseEnvlp)
#define Input_Capsense_SW108_PTR2NOISE_ENVLP_OFFSET         (284u)
#define Input_Capsense_SW108_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW108_PTR2NOISE_ENVLP_PARAM_ID       (0xDD08011Cu)

#define Input_Capsense_SW109_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[9].ptr2SnsFlash)
#define Input_Capsense_SW109_PTR2SNS_FLASH_OFFSET           (288u)
#define Input_Capsense_SW109_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW109_PTR2SNS_FLASH_PARAM_ID         (0xD2090120u)

#define Input_Capsense_SW109_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[9].ptr2WdgtRam)
#define Input_Capsense_SW109_PTR2WD_RAM_OFFSET              (292u)
#define Input_Capsense_SW109_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW109_PTR2WD_RAM_PARAM_ID            (0xD3090124u)

#define Input_Capsense_SW109_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[9].ptr2SnsRam)
#define Input_Capsense_SW109_PTR2SNS_RAM_OFFSET             (296u)
#define Input_Capsense_SW109_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW109_PTR2SNS_RAM_PARAM_ID           (0xD0090128u)

#define Input_Capsense_SW109_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[9].ptr2FltrHistory)
#define Input_Capsense_SW109_PTR2FLTR_HISTORY_OFFSET        (300u)
#define Input_Capsense_SW109_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW109_PTR2FLTR_HISTORY_PARAM_ID      (0xD109012Cu)

#define Input_Capsense_SW109_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[9].ptr2DebounceArr)
#define Input_Capsense_SW109_PTR2DEBOUNCE_OFFSET            (304u)
#define Input_Capsense_SW109_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW109_PTR2DEBOUNCE_PARAM_ID          (0xD7090130u)

#define Input_Capsense_SW109_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[9].staticConfig)
#define Input_Capsense_SW109_STATIC_CONFIG_OFFSET           (308u)
#define Input_Capsense_SW109_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW109_STATIC_CONFIG_PARAM_ID         (0xD6090134u)

#define Input_Capsense_SW109_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[9].totalNumSns)
#define Input_Capsense_SW109_TOTAL_NUM_SNS_OFFSET           (312u)
#define Input_Capsense_SW109_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW109_TOTAL_NUM_SNS_PARAM_ID         (0x9A090138u)

#define Input_Capsense_SW109_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[9].wdgtType)
#define Input_Capsense_SW109_TYPE_OFFSET                    (314u)
#define Input_Capsense_SW109_TYPE_SIZE                      (1u)
#define Input_Capsense_SW109_TYPE_PARAM_ID                  (0x5E09013Au)

#define Input_Capsense_SW109_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[9].numCols)
#define Input_Capsense_SW109_NUM_COLS_OFFSET                (315u)
#define Input_Capsense_SW109_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW109_NUM_COLS_PARAM_ID              (0x5809013Bu)

#define Input_Capsense_SW109_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[9].ptr2NoiseEnvlp)
#define Input_Capsense_SW109_PTR2NOISE_ENVLP_OFFSET         (316u)
#define Input_Capsense_SW109_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW109_PTR2NOISE_ENVLP_PARAM_ID       (0xD409013Cu)

#define Input_Capsense_SW110_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[10].ptr2SnsFlash)
#define Input_Capsense_SW110_PTR2SNS_FLASH_OFFSET           (320u)
#define Input_Capsense_SW110_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW110_PTR2SNS_FLASH_PARAM_ID         (0xD00A0140u)

#define Input_Capsense_SW110_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[10].ptr2WdgtRam)
#define Input_Capsense_SW110_PTR2WD_RAM_OFFSET              (324u)
#define Input_Capsense_SW110_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW110_PTR2WD_RAM_PARAM_ID            (0xD10A0144u)

#define Input_Capsense_SW110_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[10].ptr2SnsRam)
#define Input_Capsense_SW110_PTR2SNS_RAM_OFFSET             (328u)
#define Input_Capsense_SW110_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW110_PTR2SNS_RAM_PARAM_ID           (0xD20A0148u)

#define Input_Capsense_SW110_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[10].ptr2FltrHistory)
#define Input_Capsense_SW110_PTR2FLTR_HISTORY_OFFSET        (332u)
#define Input_Capsense_SW110_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW110_PTR2FLTR_HISTORY_PARAM_ID      (0xD30A014Cu)

#define Input_Capsense_SW110_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[10].ptr2DebounceArr)
#define Input_Capsense_SW110_PTR2DEBOUNCE_OFFSET            (336u)
#define Input_Capsense_SW110_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW110_PTR2DEBOUNCE_PARAM_ID          (0xD50A0150u)

#define Input_Capsense_SW110_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[10].staticConfig)
#define Input_Capsense_SW110_STATIC_CONFIG_OFFSET           (340u)
#define Input_Capsense_SW110_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW110_STATIC_CONFIG_PARAM_ID         (0xD40A0154u)

#define Input_Capsense_SW110_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[10].totalNumSns)
#define Input_Capsense_SW110_TOTAL_NUM_SNS_OFFSET           (344u)
#define Input_Capsense_SW110_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW110_TOTAL_NUM_SNS_PARAM_ID         (0x980A0158u)

#define Input_Capsense_SW110_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[10].wdgtType)
#define Input_Capsense_SW110_TYPE_OFFSET                    (346u)
#define Input_Capsense_SW110_TYPE_SIZE                      (1u)
#define Input_Capsense_SW110_TYPE_PARAM_ID                  (0x5C0A015Au)

#define Input_Capsense_SW110_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[10].numCols)
#define Input_Capsense_SW110_NUM_COLS_OFFSET                (347u)
#define Input_Capsense_SW110_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW110_NUM_COLS_PARAM_ID              (0x5A0A015Bu)

#define Input_Capsense_SW110_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[10].ptr2NoiseEnvlp)
#define Input_Capsense_SW110_PTR2NOISE_ENVLP_OFFSET         (348u)
#define Input_Capsense_SW110_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW110_PTR2NOISE_ENVLP_PARAM_ID       (0xD60A015Cu)

#define Input_Capsense_SW111_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[11].ptr2SnsFlash)
#define Input_Capsense_SW111_PTR2SNS_FLASH_OFFSET           (352u)
#define Input_Capsense_SW111_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW111_PTR2SNS_FLASH_PARAM_ID         (0xD90B0160u)

#define Input_Capsense_SW111_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[11].ptr2WdgtRam)
#define Input_Capsense_SW111_PTR2WD_RAM_OFFSET              (356u)
#define Input_Capsense_SW111_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW111_PTR2WD_RAM_PARAM_ID            (0xD80B0164u)

#define Input_Capsense_SW111_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[11].ptr2SnsRam)
#define Input_Capsense_SW111_PTR2SNS_RAM_OFFSET             (360u)
#define Input_Capsense_SW111_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW111_PTR2SNS_RAM_PARAM_ID           (0xDB0B0168u)

#define Input_Capsense_SW111_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[11].ptr2FltrHistory)
#define Input_Capsense_SW111_PTR2FLTR_HISTORY_OFFSET        (364u)
#define Input_Capsense_SW111_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW111_PTR2FLTR_HISTORY_PARAM_ID      (0xDA0B016Cu)

#define Input_Capsense_SW111_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[11].ptr2DebounceArr)
#define Input_Capsense_SW111_PTR2DEBOUNCE_OFFSET            (368u)
#define Input_Capsense_SW111_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW111_PTR2DEBOUNCE_PARAM_ID          (0xDC0B0170u)

#define Input_Capsense_SW111_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[11].staticConfig)
#define Input_Capsense_SW111_STATIC_CONFIG_OFFSET           (372u)
#define Input_Capsense_SW111_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW111_STATIC_CONFIG_PARAM_ID         (0xDD0B0174u)

#define Input_Capsense_SW111_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[11].totalNumSns)
#define Input_Capsense_SW111_TOTAL_NUM_SNS_OFFSET           (376u)
#define Input_Capsense_SW111_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW111_TOTAL_NUM_SNS_PARAM_ID         (0x910B0178u)

#define Input_Capsense_SW111_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[11].wdgtType)
#define Input_Capsense_SW111_TYPE_OFFSET                    (378u)
#define Input_Capsense_SW111_TYPE_SIZE                      (1u)
#define Input_Capsense_SW111_TYPE_PARAM_ID                  (0x550B017Au)

#define Input_Capsense_SW111_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[11].numCols)
#define Input_Capsense_SW111_NUM_COLS_OFFSET                (379u)
#define Input_Capsense_SW111_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW111_NUM_COLS_PARAM_ID              (0x530B017Bu)

#define Input_Capsense_SW111_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[11].ptr2NoiseEnvlp)
#define Input_Capsense_SW111_PTR2NOISE_ENVLP_OFFSET         (380u)
#define Input_Capsense_SW111_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW111_PTR2NOISE_ENVLP_PARAM_ID       (0xDF0B017Cu)

#define Input_Capsense_SW112_PTR2SNS_FLASH_VALUE            (Input_Capsense_dsFlash.wdgtArray[12].ptr2SnsFlash)
#define Input_Capsense_SW112_PTR2SNS_FLASH_OFFSET           (384u)
#define Input_Capsense_SW112_PTR2SNS_FLASH_SIZE             (4u)
#define Input_Capsense_SW112_PTR2SNS_FLASH_PARAM_ID         (0xD40C0180u)

#define Input_Capsense_SW112_PTR2WD_RAM_VALUE               (Input_Capsense_dsFlash.wdgtArray[12].ptr2WdgtRam)
#define Input_Capsense_SW112_PTR2WD_RAM_OFFSET              (388u)
#define Input_Capsense_SW112_PTR2WD_RAM_SIZE                (4u)
#define Input_Capsense_SW112_PTR2WD_RAM_PARAM_ID            (0xD50C0184u)

#define Input_Capsense_SW112_PTR2SNS_RAM_VALUE              (Input_Capsense_dsFlash.wdgtArray[12].ptr2SnsRam)
#define Input_Capsense_SW112_PTR2SNS_RAM_OFFSET             (392u)
#define Input_Capsense_SW112_PTR2SNS_RAM_SIZE               (4u)
#define Input_Capsense_SW112_PTR2SNS_RAM_PARAM_ID           (0xD60C0188u)

#define Input_Capsense_SW112_PTR2FLTR_HISTORY_VALUE         (Input_Capsense_dsFlash.wdgtArray[12].ptr2FltrHistory)
#define Input_Capsense_SW112_PTR2FLTR_HISTORY_OFFSET        (396u)
#define Input_Capsense_SW112_PTR2FLTR_HISTORY_SIZE          (4u)
#define Input_Capsense_SW112_PTR2FLTR_HISTORY_PARAM_ID      (0xD70C018Cu)

#define Input_Capsense_SW112_PTR2DEBOUNCE_VALUE             (Input_Capsense_dsFlash.wdgtArray[12].ptr2DebounceArr)
#define Input_Capsense_SW112_PTR2DEBOUNCE_OFFSET            (400u)
#define Input_Capsense_SW112_PTR2DEBOUNCE_SIZE              (4u)
#define Input_Capsense_SW112_PTR2DEBOUNCE_PARAM_ID          (0xD10C0190u)

#define Input_Capsense_SW112_STATIC_CONFIG_VALUE            (Input_Capsense_dsFlash.wdgtArray[12].staticConfig)
#define Input_Capsense_SW112_STATIC_CONFIG_OFFSET           (404u)
#define Input_Capsense_SW112_STATIC_CONFIG_SIZE             (4u)
#define Input_Capsense_SW112_STATIC_CONFIG_PARAM_ID         (0xD00C0194u)

#define Input_Capsense_SW112_TOTAL_NUM_SNS_VALUE            (Input_Capsense_dsFlash.wdgtArray[12].totalNumSns)
#define Input_Capsense_SW112_TOTAL_NUM_SNS_OFFSET           (408u)
#define Input_Capsense_SW112_TOTAL_NUM_SNS_SIZE             (2u)
#define Input_Capsense_SW112_TOTAL_NUM_SNS_PARAM_ID         (0x9C0C0198u)

#define Input_Capsense_SW112_TYPE_VALUE                     (Input_Capsense_dsFlash.wdgtArray[12].wdgtType)
#define Input_Capsense_SW112_TYPE_OFFSET                    (410u)
#define Input_Capsense_SW112_TYPE_SIZE                      (1u)
#define Input_Capsense_SW112_TYPE_PARAM_ID                  (0x580C019Au)

#define Input_Capsense_SW112_NUM_COLS_VALUE                 (Input_Capsense_dsFlash.wdgtArray[12].numCols)
#define Input_Capsense_SW112_NUM_COLS_OFFSET                (411u)
#define Input_Capsense_SW112_NUM_COLS_SIZE                  (1u)
#define Input_Capsense_SW112_NUM_COLS_PARAM_ID              (0x5E0C019Bu)

#define Input_Capsense_SW112_PTR2NOISE_ENVLP_VALUE          (Input_Capsense_dsFlash.wdgtArray[12].ptr2NoiseEnvlp)
#define Input_Capsense_SW112_PTR2NOISE_ENVLP_OFFSET         (412u)
#define Input_Capsense_SW112_PTR2NOISE_ENVLP_SIZE           (4u)
#define Input_Capsense_SW112_PTR2NOISE_ENVLP_PARAM_ID       (0xD20C019Cu)


#endif /* End CY_SENSE_Input_Capsense_REGISTER_MAP_H */


/* [] END OF FILE */
