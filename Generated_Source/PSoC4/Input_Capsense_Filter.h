/***************************************************************************//**
* \file Input_Capsense_Filter.h
* \version 7.0
*
* \brief
*   This file contains the definitions for all firmware filters
*   implementation.
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

#if !defined(CY_SENSE_Input_Capsense_FILTER_H)
#define CY_SENSE_Input_Capsense_FILTER_H

#include "cytypes.h"
#include "CyLib.h"
#include "cyfitter.h"

#include "Input_Capsense_Structure.h"
#include "Input_Capsense_Configuration.h"

/***************************************
* Function Prototypes
***************************************/

/*******************************************************************************
* LOW LEVEL API
*******************************************************************************/
/**
* \cond (SECTION_C_LOW_LEVEL || SECTION_I_LOW_LEVEL)
* \addtogroup group_c_low_level
* \{
*/

cystatus Input_Capsense_UpdateAllBaselines(void);
cystatus Input_Capsense_UpdateWidgetBaseline(uint32 widgetId);
cystatus Input_Capsense_UpdateSensorBaseline(uint32 widgetId, uint32 sensorId);

void Input_Capsense_InitializeAllBaselines(void);
void Input_Capsense_InitializeWidgetBaseline(uint32 widgetId);
void Input_Capsense_InitializeSensorBaseline(uint32 widgetId, uint32 sensorId);

#if ((Input_Capsense_ENABLE == Input_Capsense_RC_FILTER_EN) || \
     (0u != (Input_Capsense_CSD_AUTOTUNE & Input_Capsense_CSD_SS_TH_EN)))
    void Input_Capsense_InitializeAllFilters(void);
    void Input_Capsense_InitializeWidgetFilter(uint32 widgetId);
#endif /* ((Input_Capsense_ENABLE == Input_Capsense_RC_FILTER_EN) || \
           (0u != (Input_Capsense_CSD_AUTOTUNE & Input_Capsense_CSD_SS_TH_EN))) */

/** \}
* \endcond */


/*******************************************************************************
* Function Prototypes - internal functions
*******************************************************************************/
/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

void Input_Capsense_FtInitialize(void);

#if (0u != (Input_Capsense_CSD_AUTOTUNE & Input_Capsense_CSD_SS_TH_EN))
    void Input_Capsense_RunNoiseEnvelope(uint32 widgetId, uint32 sensorId);
    void Input_Capsense_InitializeNoiseEnvelope(uint32 widgetId, uint32 sensorId);
#endif /* (0u != (Input_Capsense_CSD_AUTOTUNE & Input_Capsense_CSD_SS_TH_EN)) */

#if (Input_Capsense_REGULAR_RC_IIR_FILTER_EN || Input_Capsense_PROX_RC_IIR_FILTER_EN)
    void Input_Capsense_InitializeIIR(uint32 widgetId, uint32 sensorId);
    void Input_Capsense_RunIIR(uint32 widgetId, uint32 sensorId);
#endif /* (Input_Capsense_REGULAR_RC_IIR_FILTER_EN || Input_Capsense_PROX_RC_IIR_FILTER_EN) */

#if (Input_Capsense_REGULAR_RC_MEDIAN_FILTER_EN || Input_Capsense_PROX_RC_MEDIAN_FILTER_EN)
    void Input_Capsense_InitializeMedian(uint32 widgetId, uint32 sensorId);
    void Input_Capsense_RunMedian(uint32 widgetId, uint32 sensorId);
#endif /* (Input_Capsense_REGULAR_RC_MEDIAN_FILTER_EN || Input_Capsense_PROX_RC_MEDIAN_FILTER_EN) */

#if (Input_Capsense_REGULAR_RC_AVERAGE_FILTER_EN || Input_Capsense_PROX_RC_AVERAGE_FILTER_EN)
    void Input_Capsense_InitializeAverage(uint32 widgetId, uint32 sensorId);
    void Input_Capsense_RunAverage(uint32 widgetId, uint32 sensorId);
#endif /* (Input_Capsense_REGULAR_RC_AVERAGE_FILTER_EN || Input_Capsense_PROX_RC_AVERAGE_FILTER_EN) */

void Input_Capsense_FtInitializeBaseline(Input_Capsense_RAM_SNS_STRUCT *ptrSensor, uint32 wdType);
uint32 Input_Capsense_FtUpdateBaseline(
                            Input_Capsense_RAM_WD_BASE_STRUCT *ptrWidgetRam,
                            Input_Capsense_RAM_SNS_STRUCT *ptrSensor,
                            uint32 wdType);

#if (Input_Capsense_POS_MEDIAN_FILTER_EN || Input_Capsense_REGULAR_RC_MEDIAN_FILTER_EN || Input_Capsense_PROX_RC_MEDIAN_FILTER_EN)
uint32 Input_Capsense_FtMedian(uint32 x1, uint32 x2, uint32 x3);
#endif /*Input_Capsense_POS_MEDIAN_FILTER_EN || Input_Capsense_REGULAR_RC_MEDIAN_FILTER_EN || Input_Capsense_PROX_RC_MEDIAN_FILTER_EN*/

uint32 Input_Capsense_FtIIR1stOrder(uint32 input, uint32 prevOutput, uint32 n, uint32 shift);

#if (Input_Capsense_POS_JITTER_FILTER_EN)
    uint32 Input_Capsense_FtJitter(uint32 input, uint32 prevOutput);
#endif /* Input_Capsense_POS_JITTER_FILTER_EN */

void Input_Capsense_FtInitializeBaselineChannel(Input_Capsense_RAM_SNS_STRUCT *ptrSensor, uint32 wdType, uint32 channel);

#if (Input_Capsense_ENABLE == Input_Capsense_RC_FILTER_EN)
    void Input_Capsense_FtRunEnabledFilters(uint32 widgetId, uint32 sensorId);
    void Input_Capsense_FtRunEnabledFiltersInternal(Input_Capsense_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                      Input_Capsense_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
#endif /* (Input_Capsense_ENABLE == Input_Capsense_RC_FILTER_EN) */


#if (Input_Capsense_REGULAR_RC_IIR_FILTER_EN || Input_Capsense_PROX_RC_IIR_FILTER_EN)
    void Input_Capsense_InitializeIIRInternal(Input_Capsense_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                  Input_Capsense_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
    void Input_Capsense_RunIIRInternal(Input_Capsense_PTR_FILTER_VARIANT ptrFilterHistObj,
                                           Input_Capsense_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
#endif /* (Input_Capsense_REGULAR_RC_IIR_FILTER_EN || Input_Capsense_PROX_RC_IIR_FILTER_EN) */

#if (Input_Capsense_REGULAR_RC_MEDIAN_FILTER_EN || Input_Capsense_PROX_RC_MEDIAN_FILTER_EN)
    void Input_Capsense_InitializeMedianInternal(Input_Capsense_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                     Input_Capsense_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
    void Input_Capsense_RunMedianInternal(Input_Capsense_PTR_FILTER_VARIANT ptrFilterHistObj,
                                              Input_Capsense_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
#endif /* (Input_Capsense_REGULAR_RC_MEDIAN_FILTER_EN || Input_Capsense_PROX_RC_MEDIAN_FILTER_EN) */

#if (Input_Capsense_REGULAR_RC_AVERAGE_FILTER_EN || Input_Capsense_PROX_RC_AVERAGE_FILTER_EN)
    void Input_Capsense_InitializeAverageInternal(Input_Capsense_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                      Input_Capsense_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
    void Input_Capsense_RunAverageInternal(Input_Capsense_PTR_FILTER_VARIANT ptrFilterHistObj,
                                               Input_Capsense_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
#endif /* (Input_Capsense_REGULAR_RC_AVERAGE_FILTER_EN || Input_Capsense_PROX_RC_AVERAGE_FILTER_EN) */

#if (Input_Capsense_ENABLE == Input_Capsense_ALP_FILTER_EN)
    void Input_Capsense_InitializeALP(uint32 widgetId, uint32 sensorId);
    void Input_Capsense_RunALP(uint32 widgetId, uint32 sensorId);
    void Input_Capsense_InitializeALPInternal(Input_Capsense_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                Input_Capsense_RAM_SNS_STRUCT *ptrSensorObj,
                                                uint32 wdType);
    void Input_Capsense_ConfigRunALPInternal(Input_Capsense_PTR_FILTER_VARIANT ptrFilterHistObj,
                                        Input_Capsense_RAM_WD_BASE_STRUCT *ptrRamWdgt,
                                        Input_Capsense_RAM_SNS_STRUCT *ptrSensorObj,
                                        uint32 wdType);
    void Input_Capsense_RunALPInternal(Input_Capsense_PTR_FILTER_VARIANT ptrFilterHistObj,
                                        ALP_FLTR_CONFIG_STRUCT *ptrAlpFilterConfig,
                                        Input_Capsense_RAM_SNS_STRUCT *ptrSensorObj,
                                        uint32 wdType);
#endif /* (Input_Capsense_ENABLE == Input_Capsense_ALP_FILTER_EN) */

/** \}
* \endcond */

/***************************************
* Initial Parameter Constants
***************************************/
#define NOISE_ENVELOPE_SHIFT                        (0x02u)
#define NOISE_ENVELOPE_RUN_DIFF_SHIFT               (0x03u)
#define NOISE_ENVELOPE_SIGN_REG                     (0x0Fu)
#define NOISE_ENVELOPE_SIGN_REG_SHIFT               (0x01u)
#define NOISE_ENVELOPE_RESET_COUNTER                (0x0Au)
#define NOISE_ENVELOPE_4_TIMES                      (0x02u)

#endif /* End CY_SENSE_Input_Capsense_FILTER_H */


/* [] END OF FILE */
