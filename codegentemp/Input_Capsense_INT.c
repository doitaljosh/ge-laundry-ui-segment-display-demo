/***************************************************************************//**
* \file Input_Capsense_INT.c
* \version 7.0
*
* \brief
*   This file contains the source code for implementation of the Component's
*   Interrupt Service Routine (ISR).
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
#include "cytypes.h"
#include "cyfitter.h"
#include "Input_Capsense_Configuration.h"
#include "Input_Capsense_Structure.h"
#include "Input_Capsense_Sensing.h"
#if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
    #include "Input_Capsense_SensingCSD_LL.h"
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) */
#include "cyapicallbacks.h"

/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/
/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

#if (((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) || (Input_Capsense_ENABLE == Input_Capsense_CSD_CSX_EN)) && \
     (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN))
    static void Input_Capsense_SsNextFrequencyScan(void);
#endif /* (((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) || (Input_Capsense_ENABLE == Input_Capsense_CSD_CSX_EN)) && \
            (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)) */

#if ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) || (Input_Capsense_ENABLE == Input_Capsense_CSD_CSX_EN))
    static void Input_Capsense_SsCSDPostScan(void);
    static void Input_Capsense_SsCSDInitNextScan(void);
#endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) || (Input_Capsense_ENABLE == Input_Capsense_CSD_CSX_EN)) */
/** \}
* \endcond */


/**
* \cond SECTION_C_INTERRUPT
* \addtogroup group_c_interrupt
* \{
*/


#if ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) || (Input_Capsense_ENABLE == Input_Capsense_CSD_CSX_EN))

#if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
    /* Fourth-generation HW block part */

    /*******************************************************************************
    * Function Name: Input_Capsense_CSDPostSingleScan
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the single-sensor scanning implementation.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  Input_Capsense_CSDScanExt() function.
    *
    *  The following tasks are performed for Third-generation HW block:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Update the Scan Counter.
    *    5. Reset the BUSY flag.
    *    6. Enable the CSD interrupt.
    *
    *  The following tasks are performed for Fourth-generation HW block:
    *    1. Check if the raw data is not noisy.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Configure and start the scan for the next frequency if the
    *      multi-frequency is enabled.
    *    4. Update the Scan Counter.
    *    5. Reset the BUSY flag.
    *    6. Enable the CSD interrupt.
    *
    *  The ISR handler changes the IMO and initializes scanning for the next frequency
    *  channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user code
    *  from macros specified in Component's generated code. Refer to the
    *  \ref group_c_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    CY_ISR(Input_Capsense_CSDPostSingleScan)
    {
        #ifdef Input_Capsense_ENTRY_CALLBACK
            Input_Capsense_EntryCallback();
        #endif /* Input_Capsense_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(Input_Capsense_INTR_PTR, Input_Capsense_INTR_SET_MASK);

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN)
            if ((Input_Capsense_CSD_NOISE_METRIC_TH < ((CY_GET_REG32(Input_Capsense_RESULT_VAL1_PTR) &
                                                        Input_Capsense_RESULT_VAL1_BAD_CONVS_MASK) >>
                                                        Input_Capsense_RESULT_VAL1_BAD_CONVS_SHIFT)) &&
                                                        (0u < Input_Capsense_badConversionsNum))
            {
                /* Decrement bad conversions number */
                Input_Capsense_badConversionsNum--;

                /* Start the re-scan */
                CY_SET_REG32(Input_Capsense_SEQ_START_PTR, Input_Capsense_SEQ_START_AZ0_SKIP_MASK |
                                                             Input_Capsense_SEQ_START_AZ1_SKIP_MASK |
                                                             Input_Capsense_SEQ_START_START_MASK);
            }
            else
            {
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN) */

            Input_Capsense_SsCSDPostScan();

            #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
                if (Input_Capsense_FREQ_CHANNEL_2 > Input_Capsense_scanFreqIndex)
                {
                    /* Scan the next channel */
                    Input_Capsense_SsNextFrequencyScan();
                }
                else
                {
                    /* All channels are scanned. Set IMO to zero channel */
                    Input_Capsense_scanFreqIndex = Input_Capsense_FREQ_CHANNEL_0;

                    #if (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD)
                        Input_Capsense_SsChangeImoFreq(Input_Capsense_FREQ_CHANNEL_0);
                    #else
                        Input_Capsense_SsChangeClkFreq(Input_Capsense_FREQ_CHANNEL_0);
                    #endif /* (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD) */

                    #if (Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN)
                        /* Disable Fourth-generation HW block */
                        CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd);
                    #endif /* (Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN) */

                    /* Update Scan Counter */
                    Input_Capsense_dsRam.scanCounter++;

                    /* Sensor is totally scanned. Reset BUSY flag */
                    Input_Capsense_dsRam.status &= ~(Input_Capsense_SW_STS_BUSY | Input_Capsense_WDGT_SW_STS_BUSY);
                }
            #else
                {
                    #if (Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN)
                        /* Disable Fourth-generation HW block */
                        CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd);
                    #endif /* (Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN) */

                    /* Update Scan Counter */
                    Input_Capsense_dsRam.scanCounter++;

                    /* Sensor is totally scanned. Reset BUSY flag */
                    Input_Capsense_dsRam.status &= ~(Input_Capsense_SW_STS_BUSY | Input_Capsense_WDGT_SW_STS_BUSY);
                }
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */
    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN)
        }
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN) */

        #ifdef Input_Capsense_EXIT_CALLBACK
            Input_Capsense_ExitCallback();
        #endif /* Input_Capsense_EXIT_CALLBACK */
    }


    /*******************************************************************************
    * Function Name: Input_Capsense_CSDPostMultiScan
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the multiple-sensor scanning
    *  implementation.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  Input_Capsense_Scan() or Input_Capsense_ScanAllWidgets() APIs.
    *
    *  The following tasks are performed:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Disable the CSD block (after the widget has been scanned).
    *    5. Update the Scan Counter.
    *    6. Reset the BUSY flag.
    *    7. Enable the CSD interrupt.
    *
    *  The ISR handler initializes scanning for the previous sensor when the
    *  widget has more than one sensor.
    *  The ISR handler initializes scanning for the next widget when the
    *  Input_Capsense_ScanAllWidgets() APIs are called and the project has
    *  more than one widget.
    *  The ISR handler changes the IMO and initializes scanning for the next
    *  frequency channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user
    *  code from macros specified in Component's generated code. Refer to the
    *  \ref group_c_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    CY_ISR(Input_Capsense_CSDPostMultiScan)
    {
        /* Declare and initialize ptr to sensor IO structure to appropriate address */
        Input_Capsense_FLASH_IO_STRUCT const *curSnsIOPtr = (Input_Capsense_FLASH_IO_STRUCT const *)
                                                          Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2SnsFlash
                                                          + Input_Capsense_sensorIndex;

        #ifdef Input_Capsense_ENTRY_CALLBACK
            Input_Capsense_EntryCallback();
        #endif /* Input_Capsense_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(Input_Capsense_INTR_PTR, Input_Capsense_INTR_SET_MASK);

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN)
            if ((Input_Capsense_CSD_NOISE_METRIC_TH < ((CY_GET_REG32(Input_Capsense_RESULT_VAL1_PTR) &
                                                      Input_Capsense_RESULT_VAL1_BAD_CONVS_MASK) >>
                                                      Input_Capsense_RESULT_VAL1_BAD_CONVS_SHIFT)) &&
                                                      (0u < Input_Capsense_badConversionsNum))
            {
                /* Decrement bad conversions number */
                Input_Capsense_badConversionsNum--;

                /* Start the re-scan */
                CY_SET_REG32(Input_Capsense_SEQ_START_PTR, Input_Capsense_SEQ_START_AZ0_SKIP_MASK |
                                                             Input_Capsense_SEQ_START_AZ1_SKIP_MASK |
                                                             Input_Capsense_SEQ_START_START_MASK);
            }
            else
            {
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN) */

            Input_Capsense_SsCSDPostScan();

            /* Disable sensor when all frequency channels are scanned */
            #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
                if (Input_Capsense_FREQ_CHANNEL_2 == Input_Capsense_scanFreqIndex)
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */
            {
                /* Disable sensor */
                Input_Capsense_CSDDisconnectSns(curSnsIOPtr);
            }

            #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
                if (Input_Capsense_FREQ_CHANNEL_2 > Input_Capsense_scanFreqIndex)
                {
                     /* Scan the next channel */
                    Input_Capsense_SsNextFrequencyScan();
                }
                else
                {
                     /* All channels are scanned. Set IMO to zero channel */
                    Input_Capsense_scanFreqIndex = Input_Capsense_FREQ_CHANNEL_0;

                    #if (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD)
                        Input_Capsense_SsChangeImoFreq(Input_Capsense_FREQ_CHANNEL_0);
                    #else
                        Input_Capsense_SsChangeClkFreq(Input_Capsense_FREQ_CHANNEL_0);
                    #endif /* (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD) */

                     /* Scan the next sensor */
                    Input_Capsense_SsCSDInitNextScan();
                }
            #else
                /* Scan the next sensor */
                Input_Capsense_SsCSDInitNextScan();
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN)
            }
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN) */

        #ifdef Input_Capsense_EXIT_CALLBACK
            Input_Capsense_ExitCallback();
        #endif /* Input_Capsense_EXIT_CALLBACK */
    }


    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
    /*******************************************************************************
    * Function Name: Input_Capsense_CSDPostMultiScanGanged
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the multiple-sensor scanning
    *  implementation for ganged sensors.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  Input_Capsense_Scan() API for a ganged sensor or the
    *  Input_Capsense_ScanAllWidgets() API in the project with ganged sensors.
    *
    *  The following tasks are performed:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Disable the CSD block (after the widget has been scanned).
    *    5. Update the Scan Counter.
    *    6. Reset the BUSY flag.
    *    7. Enable the CSD interrupt.
    *
    *  The ISR handler initializes scanning for the previous sensor when the
    *  widget has more than one sensor.
    *  The ISR handler initializes scanning for the next widget when the
    *  Input_Capsense_ScanAllWidgets() APIs are called and the project has
    *  more than one widget.
    *  The ISR handler changes the IMO and initializes scanning for the next
    *  frequency channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user
    *  code from macros specified in Component's generated code. Refer to the
    *  \ref group_c_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    CY_ISR(Input_Capsense_CSDPostMultiScanGanged)
    {
        #ifdef Input_Capsense_ENTRY_CALLBACK
            Input_Capsense_EntryCallback();
        #endif /* Input_Capsense_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(Input_Capsense_INTR_PTR, Input_Capsense_INTR_SET_MASK);

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN)
            if ((Input_Capsense_CSD_NOISE_METRIC_TH < ((CY_GET_REG32(Input_Capsense_RESULT_VAL1_PTR) &
                                                      Input_Capsense_RESULT_VAL1_BAD_CONVS_MASK) >>
                                                      Input_Capsense_RESULT_VAL1_BAD_CONVS_SHIFT)) &&
                                                      (0u < Input_Capsense_badConversionsNum))
            {
                /* Decrement bad conversions number */
                Input_Capsense_badConversionsNum--;

                /* Start the re-scan */
                CY_SET_REG32(Input_Capsense_SEQ_START_PTR, Input_Capsense_SEQ_START_AZ0_SKIP_MASK |
                                                             Input_Capsense_SEQ_START_AZ1_SKIP_MASK |
                                                             Input_Capsense_SEQ_START_START_MASK);
            }
            else
            {
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN) */

            Input_Capsense_SsCSDPostScan();

            #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
                if (Input_Capsense_FREQ_CHANNEL_2 == Input_Capsense_scanFreqIndex)
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */
            {
                Input_Capsense_SsCSDDisconnectSnsExt((uint32)Input_Capsense_widgetIndex, (uint32)Input_Capsense_sensorIndex);
            }

            #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
                if (Input_Capsense_FREQ_CHANNEL_2 > Input_Capsense_scanFreqIndex)
                {
                     /* Scan the next channel */
                    Input_Capsense_SsNextFrequencyScan();
                }
                else
                {
                    /* All channels are scanned. Set IMO to zero channel */
                    Input_Capsense_scanFreqIndex = Input_Capsense_FREQ_CHANNEL_0;

                    #if (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD)
                        Input_Capsense_SsChangeImoFreq(Input_Capsense_FREQ_CHANNEL_0);
                    #else
                        Input_Capsense_SsChangeClkFreq(Input_Capsense_FREQ_CHANNEL_0);
                    #endif /* (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD) */

                     /* Scan the next sensor */
                    Input_Capsense_SsCSDInitNextScan();
                }
            #else
                 /* Scan the next sensor */
                Input_Capsense_SsCSDInitNextScan();
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN)
            }
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN) */

        #ifdef Input_Capsense_EXIT_CALLBACK
            Input_Capsense_ExitCallback();
        #endif /* Input_Capsense_EXIT_CALLBACK */
    }
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN) */

#else

    /* Third-generation HW block part */

    /*******************************************************************************
    * Function Name: Input_Capsense_CSDPostSingleScan
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the single-sensor scanning implementation.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  Input_Capsense_CSDScanExt() function.
    *
    *  The following tasks are performed for Third-generation HW block:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Update the Scan Counter.
    *    5. Reset the BUSY flag.
    *    6. Enable the CSD interrupt.
    *
    *  The following tasks are performed for Fourth-generation HW block:
    *    1. Check if the raw data is not noisy.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Configure and start the scan for the next frequency if the
    *      multi-frequency is enabled.
    *    4. Update the Scan Counter.
    *    5. Reset the BUSY flag.
    *    6. Enable the CSD interrupt.
    *
    *  The ISR handler changes the IMO and initializes scanning for the next frequency
    *  channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user code
    *  from macros specified in Component's generated code. Refer to the
    *  \ref group_c_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    CY_ISR(Input_Capsense_CSDPostSingleScan)
    {
        #ifdef Input_Capsense_ENTRY_CALLBACK
            Input_Capsense_EntryCallback();
        #endif /* Input_Capsense_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(Input_Capsense_INTR_PTR, Input_Capsense_INTR_SET_MASK);

        /* Read Rawdata */
        Input_Capsense_SsCSDPostScan();

        #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
            if (Input_Capsense_FREQ_CHANNEL_2 > Input_Capsense_scanFreqIndex)
            {
                /* Connect Vref Buffer to AMUX bus. Third-generation HW block is enabled */
                CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CTANK_PRECHARGE_CONFIG_CSD_EN);

                Input_Capsense_SsNextFrequencyScan();
            }
            else
            {
                Input_Capsense_scanFreqIndex = Input_Capsense_FREQ_CHANNEL_0;

                #if (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD)
                    Input_Capsense_SsChangeImoFreq(Input_Capsense_FREQ_CHANNEL_0);
                #else
                    Input_Capsense_SsChangeClkFreq(Input_Capsense_FREQ_CHANNEL_0);
                #endif /* (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD) */

                #if (Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN)
                    /* Disable Third-generation HW block. Connect Vref Buffer to AMUX bus */
                    #if ((Input_Capsense_CSH_PRECHARGE_IO_BUF == Input_Capsense_CSD_CSH_PRECHARGE_SRC) &&\
                         (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN))
                        CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CMOD_PRECHARGE_CONFIG);
                    #else
                        CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CTANK_PRECHARGE_CONFIG);
                    #endif
                #else
                    /* Connect Vref Buffer to AMUX bus. Third-generation HW block is enabled */
                    CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CTANK_PRECHARGE_CONFIG_CSD_EN);
                #endif

                /* Update Scan Counter */
                Input_Capsense_dsRam.scanCounter++;

                /* Sensor is totally scanned. Reset BUSY flag */
                Input_Capsense_dsRam.status &= ~(Input_Capsense_SW_STS_BUSY | Input_Capsense_WDGT_SW_STS_BUSY);
            }
        #else
            {
                #if (Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN)
                    /* Disable Third-generation HW block. Connect Vref Buffer to AMUX bus */
                    #if ((Input_Capsense_CSH_PRECHARGE_IO_BUF == Input_Capsense_CSD_CSH_PRECHARGE_SRC) &&\
                         (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN))
                        CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CMOD_PRECHARGE_CONFIG);
                    #else
                        CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CTANK_PRECHARGE_CONFIG);
                    #endif
                #else
                    /* Connect Vref Buffer to AMUX bus. Third-generation HW block is enabled */
                    CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CTANK_PRECHARGE_CONFIG_CSD_EN);
                #endif

                /* Update Scan Counter */
                Input_Capsense_dsRam.scanCounter++;

                /* Sensor is totally scanned. Reset BUSY flag */
                Input_Capsense_dsRam.status &= ~(Input_Capsense_SW_STS_BUSY | Input_Capsense_WDGT_SW_STS_BUSY);
            }
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */

        #ifdef Input_Capsense_EXIT_CALLBACK
            Input_Capsense_ExitCallback();
        #endif /* Input_Capsense_EXIT_CALLBACK */
    }


    /*******************************************************************************
    * Function Name: Input_Capsense_CSDPostMultiScan
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the multiple-sensor scanning
    *  implementation.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  Input_Capsense_Scan() or Input_Capsense_ScanAllWidgets() APIs.
    *
    *  The following tasks are performed:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Disable the CSD block (after the widget has been scanned).
    *    5. Update the Scan Counter.
    *    6. Reset the BUSY flag.
    *    7. Enable the CSD interrupt.
    *
    *  The ISR handler initializes scanning for the previous sensor when the
    *  widget has more than one sensor.
    *  The ISR handler initializes scanning for the next widget when the
    *  Input_Capsense_ScanAllWidgets() APIs are called and the project has
    *  more than one widget.
    *  The ISR handler changes the IMO and initializes scanning for the next
    *  frequency channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user
    *  code from macros specified in Component's generated code. Refer to the
    *  \ref group_c_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    CY_ISR(Input_Capsense_CSDPostMultiScan)
    {
        /* Declare and initialize ptr to sensor IO structure to appropriate address        */
        Input_Capsense_FLASH_IO_STRUCT const *curSnsIOPtr = (Input_Capsense_FLASH_IO_STRUCT const *)
                                                          Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2SnsFlash
                                                          + Input_Capsense_sensorIndex;

        #ifdef Input_Capsense_ENTRY_CALLBACK
            Input_Capsense_EntryCallback();
        #endif /* Input_Capsense_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(Input_Capsense_INTR_PTR, Input_Capsense_INTR_SET_MASK);

         /* Read Rawdata */
        Input_Capsense_SsCSDPostScan();

        /* Connect Vref Buffer to AMUX bus */
        CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CTANK_PRECHARGE_CONFIG_CSD_EN);

        #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
            /* Disable sensor when all frequency channels are scanned */
            if (Input_Capsense_FREQ_CHANNEL_2 == Input_Capsense_scanFreqIndex)
            {
                /* Disable sensor */
                Input_Capsense_CSDDisconnectSns(curSnsIOPtr);
            }
        #else
            /* Disable sensor */
            Input_Capsense_CSDDisconnectSns(curSnsIOPtr);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */

        #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
            if (Input_Capsense_FREQ_CHANNEL_2 > Input_Capsense_scanFreqIndex)
            {
                 /* Scan the next channel */
                Input_Capsense_SsNextFrequencyScan();
            }
            else
            {
                 /* All channels are scanned. Set IMO to zero channel */
                Input_Capsense_scanFreqIndex = Input_Capsense_FREQ_CHANNEL_0;

                #if (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD)
                    Input_Capsense_SsChangeImoFreq(Input_Capsense_FREQ_CHANNEL_0);
                #else
                    Input_Capsense_SsChangeClkFreq(Input_Capsense_FREQ_CHANNEL_0);
                #endif /* (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD) */

                 /* Scan the next sensor */
                Input_Capsense_SsCSDInitNextScan();
            }
        #else
            /* Scan the next sensor */
            Input_Capsense_SsCSDInitNextScan();
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */

        #ifdef Input_Capsense_EXIT_CALLBACK
            Input_Capsense_ExitCallback();
        #endif /* Input_Capsense_EXIT_CALLBACK */
    }


    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
    /*******************************************************************************
    * Function Name: Input_Capsense_CSDPostMultiScanGanged
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the multiple-sensor scanning
    *  implementation for ganged sensors.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  Input_Capsense_Scan() API for a ganged sensor or the
    *  Input_Capsense_ScanAllWidgets() API in the project with ganged sensors.
    *
    *  The following tasks are performed:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Disable the CSD block (after the widget has been scanned).
    *    5. Update the Scan Counter.
    *    6. Reset the BUSY flag.
    *    7. Enable the CSD interrupt.
    *
    *  The ISR handler initializes scanning for the previous sensor when the
    *  widget has more than one sensor.
    *  The ISR handler initializes scanning for the next widget when the
    *  Input_Capsense_ScanAllWidgets() APIs are called and the project has
    *  more than one widget.
    *  The ISR handler changes the IMO and initializes scanning for the next
    *  frequency channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user
    *  code from macros specified in Component's generated code. Refer to the
    *  \ref group_c_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    CY_ISR(Input_Capsense_CSDPostMultiScanGanged)
    {
        #ifdef Input_Capsense_ENTRY_CALLBACK
            Input_Capsense_EntryCallback();
        #endif /* Input_Capsense_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(Input_Capsense_INTR_PTR, Input_Capsense_INTR_SET_MASK);

         /* Read Rawdata */
        Input_Capsense_SsCSDPostScan();

        /* Connect Vref Buffer to AMUX bus */
        CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CTANK_PRECHARGE_CONFIG_CSD_EN);

        #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
            if (Input_Capsense_FREQ_CHANNEL_2 == Input_Capsense_scanFreqIndex)
            {
                Input_Capsense_SsCSDDisconnectSnsExt((uint32)Input_Capsense_widgetIndex, (uint32)Input_Capsense_sensorIndex);
            }
        #else
            Input_Capsense_SsCSDDisconnectSnsExt((uint32)Input_Capsense_widgetIndex, (uint32)Input_Capsense_sensorIndex);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */

        #if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
            if (Input_Capsense_FREQ_CHANNEL_2 > Input_Capsense_scanFreqIndex)
            {
                 /* Scan the next channel */
                Input_Capsense_SsNextFrequencyScan();
            }
            else
            {
                /* All channels are scanned. Set IMO to zero channel */
                Input_Capsense_scanFreqIndex = Input_Capsense_FREQ_CHANNEL_0;

                #if (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD)
                    Input_Capsense_SsChangeImoFreq(Input_Capsense_FREQ_CHANNEL_0);
                #else
                    Input_Capsense_SsChangeClkFreq(Input_Capsense_FREQ_CHANNEL_0);
                #endif /* (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD) */

                 /* Scan the next sensor */
                Input_Capsense_SsCSDInitNextScan();
            }
        #else
             /* Scan the next sensor */
            Input_Capsense_SsCSDInitNextScan();
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */

        #ifdef Input_Capsense_EXIT_CALLBACK
            Input_Capsense_ExitCallback();
        #endif /* Input_Capsense_EXIT_CALLBACK */
    }
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN) */

#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */

#endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) || (Input_Capsense_ENABLE == Input_Capsense_CSD_CSX_EN)) */

/** \}
 * \endcond */


#if ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) || (Input_Capsense_ENABLE == Input_Capsense_CSD_CSX_EN))

/*******************************************************************************
* Function Name: Input_Capsense_SsCSDPostScan
****************************************************************************//**
*
* \brief
*   This function reads rawdata and releases required HW resources after scan.
*
* \details
*   This function performs following tasks after scan:
*   - Reads SlotResult from Raw Counter;
*   - Inits bad Conversions number;
*   - Disconnects Vrefhi from AMUBUF positive input;
*   - Disconnects AMUBUF output from CSDBUSB with sych PHI2+HSCMP;
*   - Opens HCBV and HCBG switches.
*
*******************************************************************************/
static void Input_Capsense_SsCSDPostScan(void)
{
    #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)

        uint32 tmpRawData;
        uint32 tmpMaxCount;
        Input_Capsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (Input_Capsense_RAM_WD_BASE_STRUCT *)
                                            Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2WdgtRam;

        /* Read SlotResult from Raw Counter */
        tmpRawData = Input_Capsense_RESULT_VAL1_VALUE_MASK & CY_GET_REG32(Input_Capsense_COUNTER_PTR);

        tmpMaxCount = ((1uL << ptrWdgt->resolution) - 1uL);
        if(tmpRawData < tmpMaxCount)
        {
            Input_Capsense_curRamSnsPtr->raw[Input_Capsense_scanFreqIndex] = LO16(tmpRawData);
        }
        else
        {
            Input_Capsense_curRamSnsPtr->raw[Input_Capsense_scanFreqIndex] = LO16(tmpMaxCount);
        }

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN)
            /* Init bad Conversions number */
            Input_Capsense_badConversionsNum = Input_Capsense_BAD_CONVERSIONS_NUM;
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_NOISE_METRIC_EN) */

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
            /* Open HCBV and HCBG switches */
            CY_SET_REG32(Input_Capsense_SW_SHIELD_SEL_PTR, Input_Capsense_SW_SHIELD_SEL_SW_HCBV_STATIC_OPEN |
                                                             Input_Capsense_SW_SHIELD_SEL_SW_HCBG_STATIC_OPEN);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */

    #else

        /* Read SlotResult from Raw Counter */
       Input_Capsense_curRamSnsPtr->raw[Input_Capsense_scanFreqIndex] = (uint16)CY_GET_REG32(Input_Capsense_COUNTER_PTR);

    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
}


/*******************************************************************************
* Function Name: Input_Capsense_SsCSDInitNextScan
****************************************************************************//**
*
* \brief
*   This function initializes the next sensor scan.
*
* \details
*   The function increments the sensor index, updates sense clock for matrix
*   or touchpad widgets only, sets up Compensation IDAC, enables the sensor and
*   scans it. When all the sensors are scanned it continues to set up the next widget
*   until all the widgets are scanned. The CSD block is disabled when all the widgets are
*   scanned.
*
*******************************************************************************/
static void Input_Capsense_SsCSDInitNextScan(void)
{
    /* Declare and initialize ptr to widget and sensor structures to appropriate address */
    #if (((Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) || \
          (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)) || \
          (((Input_Capsense_DISABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN) && \
          (Input_Capsense_ENABLE == Input_Capsense_CSDV2) && \
          (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN))))
        Input_Capsense_RAM_WD_BASE_STRUCT *ptrWdgt = (Input_Capsense_RAM_WD_BASE_STRUCT *)
                                                        Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2WdgtRam;
    #endif

    /* Check if all the sensors are scanned in widget */
    if (((uint8)Input_Capsense_dsFlash.wdgtArray[(Input_Capsense_widgetIndex)].totalNumSns - 1u) > Input_Capsense_sensorIndex)
    {
        /* Increment sensor index to configure next sensor in widget */
        Input_Capsense_sensorIndex++;

        /* Update global pointer to Input_Capsense_RAM_SNS_STRUCT to current sensor  */
        Input_Capsense_curRamSnsPtr = (Input_Capsense_RAM_SNS_STRUCT *)
                                                  Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2SnsRam
                                                  + Input_Capsense_sensorIndex;

        /* Configure clock divider to row or column */
        #if ((Input_Capsense_DISABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN) && \
             (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN))
            Input_Capsense_SsCSDConfigClock();

            #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
                 /* Set up scanning resolution */
                Input_Capsense_SsCSDCalculateScanDuration(ptrWdgt);
            #endif
        #endif

        /* Setup Compensation IDAC for next sensor in widget */
        #if ((Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) || \
             (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN))
            Input_Capsense_SsCSDSetUpIdacs(ptrWdgt);
        #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) || \
                   (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)) */

        /* Enable sensor */
        Input_Capsense_SsCSDConnectSensorExt((uint32)Input_Capsense_widgetIndex, (uint32)Input_Capsense_sensorIndex);

        /* Proceed scanning */
        Input_Capsense_SsCSDStartSample();
    }
    /* Call scan next widget API if requested, if not, complete the scan  */
    else
    {
        Input_Capsense_sensorIndex = 0u;

        /* Current widget is totally scanned. Reset WIDGET BUSY flag */
        Input_Capsense_dsRam.status &= ~Input_Capsense_WDGT_SW_STS_BUSY;

        /* Check if all the widgets have been scanned */
        if (Input_Capsense_ENABLE == Input_Capsense_requestScanAllWidget)
        {
            /* Configure and begin scanning next widget */
            Input_Capsense_SsPostAllWidgetsScan();
        }
        else
        {
            #if (Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN)
                #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
                    /* Disable the CSD block */
                    CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd);
                #else
                    /* Disable the CSD block. Connect Vref Buffer to AMUX bus */
                    #if ((Input_Capsense_CSH_PRECHARGE_IO_BUF == Input_Capsense_CSD_CSH_PRECHARGE_SRC) &&\
                         (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN))
                        CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CMOD_PRECHARGE_CONFIG);
                    #else
                        CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd | Input_Capsense_CTANK_PRECHARGE_CONFIG);
                    #endif
                #endif
            #endif

            /* All widgets are totally scanned. Reset BUSY flag */
            Input_Capsense_dsRam.status &= ~Input_Capsense_SW_STS_BUSY;

            /* Update scan Counter */
            Input_Capsense_dsRam.scanCounter++;
        }
    }
}

#if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
    /*******************************************************************************
    * Function Name: Input_Capsense_SsNextFrequencyScan
    ****************************************************************************//**
    *
    * \brief
    *   This function scans the sensor on the next frequency channel.
    *
    * \details
    *   The function increments the frequency channel, changes IMO and initializes
    *   the scanning process of the same sensor.
    *
    *******************************************************************************/
    static void Input_Capsense_SsNextFrequencyScan(void)
    {
        Input_Capsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (Input_Capsense_RAM_WD_BASE_STRUCT *)
                                                        Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].ptr2WdgtRam;

        Input_Capsense_scanFreqIndex++;

        /* Set Immunity */
        #if (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD)
            Input_Capsense_SsChangeImoFreq((uint32)Input_Capsense_scanFreqIndex);
        #else
            Input_Capsense_SsChangeClkFreq((uint32)Input_Capsense_scanFreqIndex);
        #endif /* (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD) */

        /* Update IDAC registers */
        Input_Capsense_SsCSDSetUpIdacs(ptrWdgt);

        /* Proceed scanning */
        Input_Capsense_SsCSDStartSample();
    }
#endif /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */

#endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) || (Input_Capsense_ENABLE == Input_Capsense_CSD_CSX_EN)) */


/* [] END OF FILE */
