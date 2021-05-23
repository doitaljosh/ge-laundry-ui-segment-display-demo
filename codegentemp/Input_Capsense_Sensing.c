/***************************************************************************//**
* \file Input_Capsense_Sensing.c
* \version 7.0
*
* \brief
*   This file contains the source of functions common for
*   different sensing methods.
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

#include "cyfitter.h"
#include "Input_Capsense_Configuration.h"
#include "Input_Capsense_Structure.h"
#include "Input_Capsense_Sensing.h"
#if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
    #include "Input_Capsense_SensingCSX_LL.h"
#endif
#if (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
    #include "Input_Capsense_SensingISX_LL.h"
#endif
#if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
    #include "Input_Capsense_SensingCSD_LL.h"
#endif
#if (Input_Capsense_CSD_SS_DIS != Input_Capsense_CSD_AUTOTUNE)
    #include "Input_Capsense_SmartSense_LL.h"
#endif
#if (Input_Capsense_ENABLE == Input_Capsense_ADC_EN)
    #include "Input_Capsense_Adc.h"
#endif
#if (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN)
    #include "Input_Capsense_SelfTest.h"
#endif

#if (0u != Input_Capsense_ISX_EN)
    #include "Input_Capsense_DigPrt2.h"
    #if (Input_Capsense_USES_PORT_3)
        #include "Input_Capsense_DigPrt3.h"
    #endif
#endif

/***************************************
* API Constants
***************************************/

#define Input_Capsense_IMO_FREQUENCY_OFFSET_MIN               (0u)
#define Input_Capsense_IMO_FREQUENCY_OFFSET_MAX               (255u)
#define Input_Capsense_AUTOTUNE_CALIBRATION_RESOLUTION        (12u)
#define Input_Capsense_AUTOTUNE_CALIBRATION_FREQ_KHZ          (1500u)
#define Input_Capsense_AUTOTUNE_CAL_LEVEL                     (Input_Capsense_CSD_RAWCOUNT_CAL_LEVEL)
#define Input_Capsense_AUTOTUNE_CAL_UNITS                     (1000u)
#define Input_Capsense_AUTOTUNE_CP_MAX                        (69000Lu)
#define Input_Capsense_CLK_SOURCE_LFSR_SCALE_OFFSET           (4u)

/* HW IP Block limitation */
#if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
    #define Input_Capsense_CSD_SNS_FREQ_KHZ_MAX               (6000u)
#else
    #define Input_Capsense_CSD_SNS_FREQ_KHZ_MAX               (12600u)
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */

#define Input_Capsense_FLIP_FLOP_DIV                          (1u)

#define Input_Capsense_MOD_CSD_CLK_12000KHZ                   (12000uL)
#define Input_Capsense_MOD_CSD_CLK_24000KHZ                   (24000uL)
#define Input_Capsense_MOD_CSD_CLK_48000KHZ                   (48000uL)

/*****************************************************************************/
/* Enumeration types definition                                              */
/*****************************************************************************/

typedef enum
{
    Input_Capsense_RES_PULLUP_E   = 0x02u,
    Input_Capsense_RES_PULLDOWN_E = 0x03u
} Input_Capsense_PORT_TEST_DM;

typedef enum
{
    Input_Capsense_STS_RESET      = 0x01u,
    Input_Capsense_STS_NO_RESET   = 0x02u
} Input_Capsense_TEST_TYPE;


/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/
/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

#if (Input_Capsense_DISABLE == Input_Capsense_CSDV2)
    static void Input_Capsense_SsTrimIdacs(void);
    #if ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || \
         (Input_Capsense_ENABLE == Input_Capsense_ISX_EN) || \
         (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG))
        static void Input_Capsense_SsTrimIdacsSinking(void);
    #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || \
               (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG)) */
    #if ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || \
         (Input_Capsense_ENABLE == Input_Capsense_ISX_EN) || \
         (Input_Capsense_IDAC_SOURCING == Input_Capsense_CSD_IDAC_CONFIG))
        static void Input_Capsense_SsTrimIdacsSourcing(void);
    #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || \
               (Input_Capsense_IDAC_SOURCING == Input_Capsense_CSD_IDAC_CONFIG)) */
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */

#if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
    static void Input_Capsense_SsCSDDisableMode(void);
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) */
#if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
    static void Input_Capsense_SsDisableCSXMode(void);
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSX_EN) */
#if (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
    static void Input_Capsense_SsDisableISXMode(void);
#endif /* (Input_Capsense_ENABLE == Input_Capsense_ISX_EN) */

#if(((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && \
     (Input_Capsense_ENABLE == Input_Capsense_CSDV2) && \
     (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSX_TX_CLK_SOURCE) && \
     (Input_Capsense_DISABLE == Input_Capsense_CSX_SKIP_OVSMPL_SPECIFIC_NODES)) ||\
    ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) && \
     (Input_Capsense_ENABLE == Input_Capsense_CSDV2) && \
     (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE)))
    static uint8 Input_Capsense_SsCalcLfsrSize(uint32 snsClkDivider, uint32 conversionsNum);
    static uint8 Input_Capsense_SsCalcLfsrScale(uint32 snsClkDivider, uint8 lfsrSize);
#endif

#if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
    static void Input_Capsense_SsSetWidgetSenseClkSrc(uint32 wdgtIndex, Input_Capsense_RAM_WD_BASE_STRUCT * ptrWdgt);
#endif

#if ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && (Input_Capsense_ENABLE == Input_Capsense_CSDV2))
    static void Input_Capsense_SsSetWidgetTxClkSrc(uint32 wdgtIndex, Input_Capsense_RAM_WD_BASE_STRUCT * ptrWdgt);
#endif


/** \}
* \endcond */

/*******************************************************************************
* Defines module variables
*******************************************************************************/

Input_Capsense_SENSE_METHOD_ENUM Input_Capsense_currentSenseMethod = Input_Capsense_UNDEFINED_E;

#if(Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
    /* Module variable keep track of multi-frequency scan channel index */
    uint8 Input_Capsense_scanFreqIndex = 0u;
    /* Variable keep frequency offsets */
    uint8 Input_Capsense_immunity[Input_Capsense_NUM_SCAN_FREQS] = {0u, 0u, 0u};
#else
    /* const allows C-compiler to do optimization */
    const uint8 Input_Capsense_scanFreqIndex = 0u;
#endif

/* Global software variables */
volatile uint8 Input_Capsense_widgetIndex = 0u;    /* Index of the scanning widget */
volatile uint8 Input_Capsense_sensorIndex = 0u;    /* Index of the scanning sensor */
uint8 Input_Capsense_requestScanAllWidget = 0u;

/* Pointer to RAM_SNS_STRUCT structure */
Input_Capsense_RAM_SNS_STRUCT *Input_Capsense_curRamSnsPtr;

#if ((Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN) || \
     (Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || \
     (Input_Capsense_ENABLE == Input_Capsense_ISX_EN))
    /* Pointer to Flash structure holding configuration of widget to be scanned */
    Input_Capsense_FLASH_WD_STRUCT const *Input_Capsense_curFlashWdgtPtr = 0u;
#endif

#if (Input_Capsense_ENABLE == Input_Capsense_CSD_GANGED_SNS_EN)
    /* Pointer to Flash structure holding info of sensor to be scanned */
    Input_Capsense_FLASH_SNS_STRUCT const *Input_Capsense_curFlashSnsPtr = 0u;
#endif

/* Pointer to Flash structure to hold Sns electrode that was connected previously */
Input_Capsense_FLASH_IO_STRUCT const *Input_Capsense_curSnsIOPtr;

Input_Capsense_IDAC_GAIN_TABLE_STRUCT const Input_Capsense_idacGainTable[Input_Capsense_IDAC_GAIN_NUMBER] = Input_Capsense_IDAC_GAIN_TABLE_INIT;


/*******************************************************************************
* Function Name: Input_Capsense_IsBusy
****************************************************************************//**
*
* \brief
*  Returns the current status of the Component (Scan is completed or Scan is in
*  progress).
*
* \details
*  This function returns a status of the hardware block whether a scan is
*  currently in progress or not. If the Component is busy, no new scan or Widget
*  setup is made. The critical section (i.e. disable global interrupt)
*  is recommended for the application when the device transitions from
*  the active mode to sleep or deep sleep modes.
*
* \return
*  Returns the current status of the Component:
*    - Input_Capsense_NOT_BUSY - No scan is in progress and a next scan
*      can be initiated.
*    - Input_Capsense_SW_STS_BUSY - The previous scanning is not completed
*      and the hardware block is busy.
*
*******************************************************************************/
uint32 Input_Capsense_IsBusy(void)
{
    return (Input_Capsense_dsRam.status & Input_Capsense_SW_STS_BUSY);
}

/*******************************************************************************
* Function Name: Input_Capsense_SetupWidget
****************************************************************************//**
*
* \brief
*  Performs the initialization required to scan the specified widget.
*
* \details
*  This function prepares the Component to scan all the sensors in the specified
*  widget by executing the following tasks:
*    1. Re-initialize the hardware if it is not configured to perform the
*       sensing method used by the specified widget, this happens only if multiple
*       sensing methods are used in the Component.
*    2. Initialize the hardware with specific sensing configuration (e.g.
*       sensor clock, scan resolution) used by the widget.
*    3. Disconnect all previously connected electrodes, if the electrodes
*       connected by the lower level SetupWidgetExt() or ConnectSns() functions
        and not disconnected.
*
*  This function does not start sensor scanning, the Input_Capsense_Scan()
*  function must be called to start the scan sensors in the widget. If this
*  function is called more than once, it does not break the Component operation,
*  but only the last initialized widget is in effect.
*
* \param widgetId
*  Specifies the ID number of the widget to be initialized for scanning.
*  A macro for the widget ID can be found in the
*  Input_Capsense Configuration header file defined as
*  Input_Capsense_<WidgetName>_WDGT_ID.
*
* \return
*  Returns the status of the widget setting up operation:
*    - CYRET_SUCCESS - The operation is successfully completed.
*    - CYRET_BAD_PARAM - The widget is invalid or if the specified widget is
*      disabled
*    - CYRET_INVALID_STATE - The previous scanning is not completed and the
*      hardware block is busy.
*    - CYRET_UNKNOWN - An unknown sensing method is used by the widget or any
*      other spurious error occurred.
*
**********************************************************************************/
cystatus Input_Capsense_SetupWidget(uint32 widgetId)
{
    cystatus widgetStatus;

    if (Input_Capsense_WDGT_SW_STS_BUSY == (Input_Capsense_dsRam.status & Input_Capsense_WDGT_SW_STS_BUSY))
    {
        /* Previous widget is being scanned. Return error. */
        widgetStatus = CYRET_INVALID_STATE;
    }
    /*
     *  Check if widget id is valid, specified widget is enabled and widget did not
     *  detect any fault conditions if BIST is enabled. If all conditions are met,
     *  set widgetStatus as good, if not, set widgetStatus as bad.
     */
    else if ((Input_Capsense_TOTAL_WIDGETS > widgetId) &&
        (0uL != Input_Capsense_GET_WIDGET_EN_STATUS(widgetId)))

    {
        widgetStatus = CYRET_SUCCESS;
    }
    else
    {
        widgetStatus = CYRET_BAD_PARAM;
    }

    /*
     * Check widgetStatus flag that is set earlier, if flag is good, then set up only
     * widget
     */
    if (CYRET_SUCCESS == widgetStatus)
    {
        switch (Input_Capsense_GET_SENSE_METHOD(&Input_Capsense_dsFlash.wdgtArray[widgetId]))
        {
        #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
            case Input_Capsense_SENSE_METHOD_CSX_E:
                /* Set up widget for CSX scan */
                Input_Capsense_CSXSetupWidget(widgetId);
                break;
        #endif
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
            case Input_Capsense_SENSE_METHOD_CSD_E:
                /* Set up widget for CSD scan */
                Input_Capsense_CSDSetupWidget(widgetId);
                break;
        #endif
        #if (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
            case Input_Capsense_SENSE_METHOD_ISX_E:
                /* Set up widget for ISX scan */
                Input_Capsense_ISXSetupWidget(widgetId);
                break;
        #endif
        default:
            /* Sensing method is invalid, return error to caller */
            widgetStatus = CYRET_UNKNOWN;
            break;
        }
    }
    return (widgetStatus);
}


/*******************************************************************************
* Function Name: Input_Capsense_Scan
****************************************************************************//**
*
* \brief
*  Initiates scanning of all the sensors in the widget initialized by
*  Input_Capsense_SetupWidget(), if no scan is in progress.
*
* \details
*  This function is called only after the Input_Capsense_SetupWidget()
*  function is called to start the scanning of the sensors in the widget. The
*  status of a sensor scan must be checked using the Input_Capsense_IsBusy()
*  API prior to starting a next scan or setting up another widget.
*
* \return
*  Returns the status of the scan initiation operation:
*  - CYRET_SUCCESS - Scanning is successfully started.
*  - CYRET_INVALID_STATE - The previous scanning is not completed and the
*    hardware block is busy.
*  - CYRET_UNKNOWN - An unknown sensing method is used by the widget.
*
********************************************************************************/
cystatus Input_Capsense_Scan(void)
{
    cystatus scanStatus = CYRET_SUCCESS;

    if (Input_Capsense_WDGT_SW_STS_BUSY == (Input_Capsense_dsRam.status & Input_Capsense_WDGT_SW_STS_BUSY))
    {
        /* Previous widget is being scanned. Return error. */
        scanStatus = CYRET_INVALID_STATE;
    }
    else
    {
        switch (Input_Capsense_currentSenseMethod)
        {
        #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
            case Input_Capsense_SENSE_METHOD_CSX_E:
                Input_Capsense_CSXScan();
                break;
        #endif
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
            case Input_Capsense_SENSE_METHOD_CSD_E:
                Input_Capsense_CSDScan();
                break;
        #endif
        #if (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
            case Input_Capsense_SENSE_METHOD_ISX_E:
                Input_Capsense_ISXScan();
                break;
        #endif
        default:
            scanStatus = CYRET_UNKNOWN;
            break;
        }
    }
    return (scanStatus);
}


/*******************************************************************************
* Function Name: Input_Capsense_ScanAllWidgets
****************************************************************************//**
*
* \brief
*  Initializes the first enabled widget and scanning of all the sensors in the
*  widget, then the same process is repeated for all the widgets in the Component,
*  i.e. scanning of all the widgets in the Component.
*
* \details
*  This function initializes a widget and scans all the sensors in the widget,
*  and then repeats the same for all the widgets in the Component. The tasks of
*  the Input_Capsense_SetupWidget() and Input_Capsense_Scan() functions are
*  executed by these functions. The status of a sensor scan must be checked
*  using the Input_Capsense_IsBusy() API prior to starting a next scan
*  or setting up another widget.
*
* \return
*  Returns the status of the operation:
*  - CYRET_SUCCESS - Scanning is successfully started.
*  - CYRET_BAD_PARAM - All the widgets are disabled.
*  - CYRET_INVALID_STATE - The previous scanning is not completed and the HW block is busy.
*  - CYRET_UNKNOWN - There are unknown errors.
*
*******************************************************************************/
cystatus Input_Capsense_ScanAllWidgets(void)
{
    cystatus scanStatus = CYRET_UNKNOWN;

    uint32 wdgtIndex;

    if (Input_Capsense_SW_STS_BUSY == (Input_Capsense_dsRam.status & Input_Capsense_SW_STS_BUSY))
    {
        /* Previous widget is being scanned. Return error. */
        scanStatus = CYRET_INVALID_STATE;
    }
    else
    {
        /*
         *  Set up widget first widget.
         *  If widget returned error, set up next, continue same until widget does not return error.
         */
        for (wdgtIndex = 0u;
             wdgtIndex < Input_Capsense_TOTAL_WIDGETS;
             wdgtIndex++)
        {

            scanStatus = Input_Capsense_SetupWidget(wdgtIndex);

            if (CYRET_SUCCESS == scanStatus)
            {
                #if (0u != (Input_Capsense_TOTAL_WIDGETS - 1u))
                    /* If there are more than one widget to be scanned, request callback to scan next widget */
                    if ((Input_Capsense_TOTAL_WIDGETS - 1u) > wdgtIndex)
                    {
                         /* Request callback to scan next widget in ISR */
                        Input_Capsense_requestScanAllWidget = Input_Capsense_ENABLE;
                    }
                    else
                    {
                        /* Request to exit in ISR (Do not scan the next widgets) */
                        Input_Capsense_requestScanAllWidget = Input_Capsense_DISABLE;
                    }
                #else
                    {
                        /* Request to exit in ISR (We have only one widget) */
                        Input_Capsense_requestScanAllWidget = Input_Capsense_DISABLE;
                    }
                #endif  /* (0u != (Input_Capsense_TOTAL_WIDGETS - 1u)) */

                /* Initiate scan and quit loop */
                scanStatus = Input_Capsense_Scan();

                break;
            }
        }
    }

    return (scanStatus);
}


/*******************************************************************************
* Function Name: Input_Capsense_SetupWidgetExt
****************************************************************************//**
*
* \brief
*  Performs extended initialization for the specified widget and also performs
*  initialization required for a specific sensor in the widget. This function
*  requires using the Input_Capsense_ScanExt() function to initiate a scan.
*
* \details
*  This function does the same as Input_Capsense_SetupWidget() and also
*  does the following tasks:
*    1. Connects the first sensor of the widget.
*    2. Configures the CSD HW block to perform a scan of the specified sensor.
*
*  Once this function is called to initialize a widget and a sensor, the
*  Input_Capsense_ScanExt() function is called to scan the sensor.
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
*  A macro for the widget ID can be found in the Input_Capsense
*  Configuration header file defined as Input_Capsense_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specifies the ID number of the sensor within the widget to perform hardware
*  and firmware initialization required for scanning a specific sensor in a
*  specific widget.
*  A macro for the sensor ID within a specified widget can be found in the
*  Input_Capsense Configuration header file defined as
*  Input_Capsense_<WidgetName>_SNS<SensorNumber>_ID
*
* \return
*  Returns the status of the operation:
*  - CYRET_SUCCESS - The operation is successfully completed.
*  - CYRET_BAD_PARAM - The widget is invalid or if the specified widget is
*    disabled
*  - CYRET_INVALID_STATE - The previous scanning is not completed and the
*    hardware block is busy.
*  - CYRET_UNKNOWN - An unknown sensing method is used by the widget or any
*    other spurious error occurred.
*
*******************************************************************************/
cystatus Input_Capsense_SetupWidgetExt(uint32 widgetId, uint32 sensorId)
{
    cystatus widgetStatus;

    if (Input_Capsense_WDGT_SW_STS_BUSY == (Input_Capsense_dsRam.status & Input_Capsense_WDGT_SW_STS_BUSY))
    {
        /* Previous widget is being scanned. Return error. */
        widgetStatus = CYRET_INVALID_STATE;
    }
    /*
     *  Check if widget id is valid, specified widget is enabled and widget did not
     *  detect any fault conditions if BIST is enabled. If all conditions are met,
     *  set widgetStatus as good, if not, set widgetStatus as bad.
     */
    else if ((Input_Capsense_TOTAL_WIDGETS > widgetId) &&
        (0uL != Input_Capsense_GET_WIDGET_EN_STATUS(widgetId)) &&
        (sensorId < Input_Capsense_GET_SENSOR_COUNT(widgetId)))

    {
        widgetStatus = CYRET_SUCCESS;
    }
    else
    {
        widgetStatus = CYRET_BAD_PARAM;
    }

    /*
     * Check widgetStatus flag that is set earlier, if flag is good, then set up only
     * widget
     */
    if (CYRET_SUCCESS == widgetStatus)
    {
        switch (Input_Capsense_GET_SENSE_METHOD(&Input_Capsense_dsFlash.wdgtArray[widgetId]))
        {
        #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
            case Input_Capsense_SENSE_METHOD_CSX_E:
                /* Set up widget for CSX scan */
                Input_Capsense_CSXSetupWidgetExt(widgetId, sensorId);
                break;
        #endif
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
            case Input_Capsense_SENSE_METHOD_CSD_E:
                /* Set up widget for CSD scan */
                Input_Capsense_CSDSetupWidgetExt(widgetId, sensorId);
                break;
        #endif
        #if (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
            case Input_Capsense_SENSE_METHOD_ISX_E:
                /* Set up widget for ISX scan */
                Input_Capsense_ISXSetupWidgetExt(widgetId, sensorId);
                break;
        #endif
        default:
            /* Sensing method is invalid, return error to caller */
            widgetStatus = CYRET_UNKNOWN;
            break;
        }
    }
    return (widgetStatus);
}


/*******************************************************************************
* Function Name: Input_Capsense_ScanExt
****************************************************************************//**
*
* \brief
*  Starts a conversion on the pre-configured sensor. This function requires
*  using the Input_Capsense_SetupWidgetExt() function to set up the a
*  widget.
*
* \details
*  This function performs single scanning of one sensor in the widget configured
*  by the Input_Capsense_SetupWidgetExt() function.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*  This function is called when no scanning is in progress. I.e.
*  Input_Capsense_IsBusy() returns a non-busy status.
*
*  The sensor must be preconfigured by using the
*  Input_Capsense_SetupWidgetExt() API prior to calling this function.
*  The sensor remains ready for a next scan if a previous scan was triggered
*  by using the Input_Capsense_ScanExt() function. In this case, calling
*  Input_Capsense_SetupWidgetExt() is not required every time before the
*  Input_Capsense_ScanExt() function. If a previous scan was triggered in
*  any other way - Input_Capsense_Scan(), Input_Capsense_ScanAllWidgets() or
*  Input_Capsense_RunTuner() - (see the Input_Capsense_RunTuner() function
*  description for more details), the sensor must be preconfigured again by
*  using the Input_Capsense_SetupWidgetExt() API prior to calling the
*  Input_Capsense_ScanExt() function.
*
*  If disconnection of the sensors is required after calling
*  Input_Capsense_ScanExt(), the Input_Capsense_CSDDisconnectSns() or
*  Input_Capsense_CSXDisconnectTx() or Input_Capsense_CSXDisconnectRx()
*  functions can be used.
*
* \return
*  Returns the status of the scan initiation operation:
*  - CYRET_SUCCESS - Scanning is successfully started.
*  - CYRET_INVALID_STATE - The previous scanning is not completed and the
*    hardware block is busy.
*  - CYRET_UNKNOWN - An unknown sensing method is used by the widget.
*
*******************************************************************************/
cystatus Input_Capsense_ScanExt(void)
{
    cystatus scanStatus = CYRET_SUCCESS;

    if (Input_Capsense_WDGT_SW_STS_BUSY == (Input_Capsense_dsRam.status & Input_Capsense_WDGT_SW_STS_BUSY))
    {
        /* Previous widget is being scanned. Return error. */
        scanStatus = CYRET_INVALID_STATE;
    }
    else
    {
        switch (Input_Capsense_currentSenseMethod)
        {
        #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
            case Input_Capsense_SENSE_METHOD_CSX_E:
                Input_Capsense_CSXScanExt();
                break;
        #endif
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
            case Input_Capsense_SENSE_METHOD_CSD_E:
                Input_Capsense_CSDScanExt();
                break;
        #endif
        #if (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
            case Input_Capsense_SENSE_METHOD_ISX_E:
                Input_Capsense_ISXScanExt();
                break;
        #endif
        default:
            scanStatus = CYRET_UNKNOWN;
            break;
        }
    }
    return (scanStatus);
}


/*******************************************************************************
* Function Name: Input_Capsense_SsInitialize
****************************************************************************//**
*
* \brief
*  Performs hardware and firmware initialization required for proper operation
*  of the Input_Capsense Component. This function is called from
*  the Input_Capsense_Start() API prior to calling any other APIs of the Component.
*
* \details
*  Performs hardware and firmware initialization required for proper operation
*  of the Input_Capsense Component. This function is called from
*  the Input_Capsense_Start() API prior to calling any other APIs of the Component.
*  1. Depending on the configuration, the function initializes the CSD block
*     for the corresponding sensing mode.
*  2. The function updates the dsRam.wdgtWorking variable with 1 when Self-test
*     is enabled.
*
*  Calling the Input_Capsense_Start API is the recommended method to initialize
*  the Input_Capsense Component at power-up. The Input_Capsense_SsInitialize()
*  API should not be used for initialization, resume, or wake-up operations.
*  The dsRam.wdgtWorking variable is updated.
*
* \return status
*  Returns status of operation:
*  - Zero        - Indicates successful initialization.
*  - Non-zero    - One or more errors occurred in the initialization process.
*
*******************************************************************************/
cystatus Input_Capsense_SsInitialize(void)
{
    cystatus initStatus;

    #if ((Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) &&\
         (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD))
        uint8 centerFreqTrim;

        centerFreqTrim = (uint8)CY_GET_REG32(CY_SYS_CLK_IMO_TRIM1_PTR);
        Input_Capsense_immunity[Input_Capsense_FREQ_CHANNEL_0] = centerFreqTrim;

        if (centerFreqTrim < Input_Capsense_IMO_FREQUENCY_OFFSET_F1)
        {
            Input_Capsense_immunity[Input_Capsense_FREQ_CHANNEL_1] = centerFreqTrim + Input_Capsense_IMO_FREQUENCY_OFFSET_F1;
            Input_Capsense_immunity[Input_Capsense_FREQ_CHANNEL_2] = centerFreqTrim + (Input_Capsense_IMO_FREQUENCY_OFFSET_F1 +
                                                                                           Input_Capsense_IMO_FREQUENCY_OFFSET_F2);
        }
        else if (centerFreqTrim > (Input_Capsense_IMO_FREQUENCY_OFFSET_MAX - Input_Capsense_IMO_FREQUENCY_OFFSET_F2))
        {
            Input_Capsense_immunity[Input_Capsense_FREQ_CHANNEL_1] = centerFreqTrim - Input_Capsense_IMO_FREQUENCY_OFFSET_F1;
            Input_Capsense_immunity[Input_Capsense_FREQ_CHANNEL_2] = centerFreqTrim - (Input_Capsense_IMO_FREQUENCY_OFFSET_F1 +
                                                                                           Input_Capsense_IMO_FREQUENCY_OFFSET_F2);
        }
        else
        {
            Input_Capsense_immunity[Input_Capsense_FREQ_CHANNEL_1] = centerFreqTrim - Input_Capsense_IMO_FREQUENCY_OFFSET_F1;
            Input_Capsense_immunity[Input_Capsense_FREQ_CHANNEL_2] = centerFreqTrim + Input_Capsense_IMO_FREQUENCY_OFFSET_F2;
        }

    #endif /* ((Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) &&\
               (Input_Capsense_MFS_IMO == Input_Capsense_MFS_METHOD)) */

    initStatus = CYRET_SUCCESS;

    #if (Input_Capsense_DISABLE == Input_Capsense_CSDV2)
        Input_Capsense_SsTrimIdacs();
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */

    #if((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) ||\
    ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && (Input_Capsense_ENABLE == Input_Capsense_CSDV2)))
        Input_Capsense_SsInitializeSourceSenseClk();
    #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) ||\
              ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && (Input_Capsense_ENABLE == Input_Capsense_CSDV2))) */

    /* Set all IO states to the default state */
    Input_Capsense_SsSetAllIOsState((uint32)Input_Capsense_SNS_CONNECTION_GROUND);
    Input_Capsense_dsRam.scanCurrentISC = Input_Capsense_SNS_CONNECTION_GROUND;

    Input_Capsense_SsSwitchSensingMode(Input_Capsense_UNDEFINED_E);
    #if (Input_Capsense_ENABLE == Input_Capsense_MANY_SENSE_MODES_EN)
    #elif (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
        Input_Capsense_SsSwitchSensingMode(Input_Capsense_SENSE_METHOD_CSD_E);
    #elif (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
        Input_Capsense_SsSwitchSensingMode(Input_Capsense_SENSE_METHOD_CSX_E);
    #elif (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
        Input_Capsense_SsSwitchSensingMode(Input_Capsense_SENSE_METHOD_ISX_E);
    #else
        #error "No sensing method enabled, Component cannot work in this mode"
        initStatus = CYRET_UNKNOWN;
    #endif

    return (initStatus);
}


/*******************************************************************************
* Function Name: Input_Capsense_SetPinState
****************************************************************************//**
*
* \brief
*  Sets the state (drive mode and output state) of the port pin used by a sensor.
*  The possible states are GND, Shield, High-Z, Tx or Rx, Sensor. If the sensor
*  specified in the input parameter is a ganged sensor, then the state of all pins
*  associated with the ganged sensor is updated.
*
* \details
*  This function sets a specified state for a specified sensor element. For the
*  CSD widgets, sensor element is a sensor ID, for the CSX widgets, it is either
*  an Rx or Tx electrode ID. If the specified sensor is a ganged sensor, then
*  the specified state is set for all the electrodes belong to the sensor.
*  This function must not be called while the Component is in the busy state.
*
*  This function accepts the Input_Capsense_SHIELD and
*  Input_Capsense_SENSOR states as an input only if there is at least
*  one CSD widget. Similarly, this function accepts the Input_Capsense_TX_PIN
*  and Input_Capsense_RX_PIN states as an input only if there is at least
*  one CSX widget in the project.

*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the custom-specific
*  use cases. Functions that perform a setup and scan of a sensor/widget
*  automatically set the required pin states. They ignore changes
*  in the design made by the Input_Capsense_SetPinState() function.
*  This function neither check wdgtIndex nor sensorElement for the correctness.
*
* \param widgetId
*  Specifies the ID of the widget to change the pin state of the specified
*  sensor.
*  A macro for the widget ID can be found in the Input_Capsense Configuration
*  header file defined as Input_Capsense_<WidgetName>_WDGT_ID.
*
* \param sensorElement
*  Specifies the ID of the sensor element within the widget to change
*  its pin state.
*  \if SECTION_C_LOW_LEVEL
*  For the CSD widgets, sensorElement is the sensor ID and can be found in the
*  Input_Capsense Configuration header file defined as
*  - Input_Capsense_<WidgetName>_SNS<SensorNumber>_ID.
*  For the CSX widgets, sensorElement is defined either as Rx ID or Tx ID.
*  The first Rx in a widget corresponds to sensorElement = 0, the second
*  Rx in a widget corresponds to sensorElement = 1, and so on.
*  The last Tx in a widget corresponds to sensorElement = (RxNum + TxNum).
*  \endif
*  Macros for Rx and Tx IDs can be found in the
*  Input_Capsense Configuration header file defined as:
*  - Input_Capsense_<WidgetName>_RX<RXNumber>_ID
*  - Input_Capsense_<WidgetName>_TX<TXNumber>_ID.
*
* \param state
*  Specifies the state of the sensor to be set:
*     1. Input_Capsense_GROUND - The pin is connected to the ground.
*     2. Input_Capsense_HIGHZ - The drive mode of the pin is set to High-Z
*        Analog.
*     3. Input_Capsense_SHIELD - The shield signal is routed to the pin
*        (available only if CSD sensing method with shield electrode is enabled).
*     4. Input_Capsense_SENSOR - The pin is connected to the scanning bus
*        (available only if CSD sensing method is enabled).
*     5. Input_Capsense_TX_PIN - The Tx or Lx signal is routed to the sensor
*        (available only if CSX or ISX sensing method is enabled).
*     6. Input_Capsense_RX_PIN - The pin is connected to the scanning bus
*        (available only if CSX or ISX sensing method is enabled).
*
*******************************************************************************/
void Input_Capsense_SetPinState(uint32 widgetId, uint32 sensorElement, uint32 state)
{
    uint32 eltdNum;
    uint32 eltdIndex;
    uint8  interruptState;
    Input_Capsense_FLASH_IO_STRUCT const *ioPtr;
    #if (Input_Capsense_ENABLE == Input_Capsense_GANGED_SNS_EN)
        Input_Capsense_FLASH_SNS_STRUCT const *curFlashSnsPtr;
    #endif

    /* Getting sensor element pointer and number of electrodes */
    #if (Input_Capsense_ENABLE == Input_Capsense_GANGED_SNS_EN)
        /* Check the ganged sns flag */
        if (Input_Capsense_GANGED_SNS_MASK == (Input_Capsense_dsFlash.wdgtArray[widgetId].staticConfig & Input_Capsense_GANGED_SNS_MASK))
        {
            curFlashSnsPtr = Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2SnsFlash;
            curFlashSnsPtr += sensorElement;
            ioPtr = &Input_Capsense_ioList[curFlashSnsPtr->firstPinId];
            eltdNum = curFlashSnsPtr->numPins;
        }
        else
        {
            ioPtr = (Input_Capsense_FLASH_IO_STRUCT const *)Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2SnsFlash + sensorElement;
            eltdNum = 1u;
        }
    #else
        ioPtr = (Input_Capsense_FLASH_IO_STRUCT const *)Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2SnsFlash + sensorElement;
        eltdNum = 1u;
    #endif

    /* Loop through all electrodes of the specified sensor element */
    for (eltdIndex = 0u; eltdIndex < eltdNum; eltdIndex++)
    {
        /* Reset HSIOM and PC registers */
        interruptState = CyEnterCriticalSection();
        CY_SET_REG32(ioPtr->hsiomPtr, CY_GET_REG32(ioPtr->hsiomPtr) & ~(Input_Capsense_HSIOM_SEL_MASK << ioPtr->hsiomShift));
        CY_SET_REG32(ioPtr->pcPtr, CY_GET_REG32(ioPtr->pcPtr) & ~(Input_Capsense_GPIO_PC_MASK << ioPtr->shift));
        CyExitCriticalSection(interruptState);

        switch (state)
        {
        case Input_Capsense_GROUND:

            interruptState = CyEnterCriticalSection();
            CY_SET_REG32(ioPtr->pcPtr, CY_GET_REG32(ioPtr->pcPtr) | (Input_Capsense_SNS_GROUND_CONNECT << ioPtr->shift));
            CY_SET_REG32(ioPtr->drPtr, CY_GET_REG32(ioPtr->drPtr) & (uint32)(~(uint32)((uint32)1u << ioPtr->drShift)));
            CyExitCriticalSection(interruptState);
            break;

        case Input_Capsense_HIGHZ:
            interruptState = CyEnterCriticalSection();
            CY_SET_REG32(ioPtr->drPtr, CY_GET_REG32(ioPtr->drPtr) & (uint32)~(uint32)((uint32)1u << ioPtr->drShift));
            CyExitCriticalSection(interruptState);
            break;

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
            case Input_Capsense_SENSOR:
                /* Enable sensor */
                Input_Capsense_CSDConnectSns(ioPtr);
                break;

            #if (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN)
                case Input_Capsense_SHIELD:
                    /* Set appropriate bit in HSIOM register to configure pin to shield mode */
                    interruptState = CyEnterCriticalSection();
                    CY_SET_REG32(ioPtr->hsiomPtr, CY_GET_REG32(ioPtr->hsiomPtr) | (Input_Capsense_HSIOM_SEL_CSD_SHIELD << ioPtr->hsiomShift));
                    CyExitCriticalSection(interruptState);
                    break;
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) */
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) */

        #if ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || \
             (Input_Capsense_ENABLE == Input_Capsense_ISX_EN))
            case Input_Capsense_TX_PIN:
                interruptState = CyEnterCriticalSection();
                CY_SET_REG32(ioPtr->hsiomPtr, CY_GET_REG32(ioPtr->hsiomPtr) | (Input_Capsense_HSIOM_SEL_CSD_SENSE << ioPtr->hsiomShift));
                CY_SET_REG32(ioPtr->pcPtr, CY_GET_REG32(ioPtr->pcPtr) | (Input_Capsense_GPIO_STRGDRV << ioPtr->shift));
                CyExitCriticalSection(interruptState);
                break;

            case Input_Capsense_RX_PIN:
                interruptState = CyEnterCriticalSection();
                CY_SET_REG32(ioPtr->hsiomPtr, CY_GET_REG32(ioPtr->hsiomPtr) | (Input_Capsense_HSIOM_SEL_AMUXA << ioPtr->hsiomShift));
                CY_SET_REG32(ioPtr->pcPtr, CY_GET_REG32(ioPtr->pcPtr) & ~(Input_Capsense_GPIO_PC_MASK << ioPtr->shift));
                CyExitCriticalSection(interruptState);
                break;
        #endif

        default:
            /* Wrong state */
            break;
        }

        ioPtr++;
    }
}

#if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
    /*******************************************************************************
    * Function Name: Input_Capsense_SsCSDDisableMode
    ****************************************************************************//**
    *
    * \brief
    *  This function disables CSD mode.
    *
    * \details
    *  To disable CSD mode the following tasks are performed:
    *  1. Disconnect Cmod from AMUXBUS-A.
    *  2. Disconnect previous CSX electrode if it has been connected.
    *  3. Disconnect Csh from AMUXBUS-B.
    *  4. Disable Shield Electrodes.
    *
    *******************************************************************************/
    static void Input_Capsense_SsCSDDisableMode(void)
    {
        #if ((Input_Capsense_ENABLE == Input_Capsense_CSDV2) && \
             (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN))

            uint32 newRegValue;

            /* Disconnect IDACA and IDACB */
            newRegValue = CY_GET_REG32(Input_Capsense_SW_REFGEN_SEL_PTR);
            newRegValue &= (uint32)(~Input_Capsense_SW_REFGEN_SEL_SW_IAIB_MASK);
            CY_SET_REG32(Input_Capsense_SW_REFGEN_SEL_PTR, newRegValue);
        #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSDV2) && \
                   (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)) */

        /* Disconnect Cmod from AMUXBUS-A using HSIOM registers */
        Input_Capsense_WriteBitsSafe(Input_Capsense_CMOD_HSIOM_PTR, Input_Capsense_CMOD_HSIOM_MASK, 0u);

        /* Disconnect previous CSD electrode if it has been connected */
        Input_Capsense_SsCSDElectrodeCheck();

        /* Disconnect Csh from AMUXBUS-B */
        #if ((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) && \
             (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN))
            Input_Capsense_WriteBitsSafe(Input_Capsense_CSH_HSIOM_PTR, Input_Capsense_CSH_HSIOM_MASK, 0u);
        #endif

        #if ((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) && \
             (0u != Input_Capsense_CSD_TOTAL_SHIELD_COUNT))
            Input_Capsense_SsCSDDisableShieldElectrodes();
        #endif
    }
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) */


#if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
    /*******************************************************************************
    * Function Name: Input_Capsense_SsDisableCSXMode
    ****************************************************************************//**
    *
    * \brief
    *  This function disables CSX mode.
    *
    * \details
    *  To disable CSX mode the following tasks are performed:
    *  1. Disconnect CintA and CintB from AMUXBUS-A.
    *  2. Disconnect previous CSX electrode if it has been connected.
    *
    *******************************************************************************/
    static void Input_Capsense_SsDisableCSXMode(void)
    {
        /* Disconnect CintA from AMUXBUS-A using HSIOM registers */
        Input_Capsense_WriteBitsSafe(Input_Capsense_CintA_HSIOM_PTR, Input_Capsense_CintA_HSIOM_MASK, 0u);
        /* Disconnect CintB from AMUXBUS-A using HSIOM registers */
        Input_Capsense_WriteBitsSafe(Input_Capsense_CintB_HSIOM_PTR, Input_Capsense_CintB_HSIOM_MASK, 0u);
        /* Disconnect previous CSX electrode if it has been connected */
        Input_Capsense_CSXElectrodeCheck();
    }
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSX_EN) */


#if (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
    /*******************************************************************************
    * Function Name: Input_Capsense_SsDisableISXMode
    ****************************************************************************//**
    *
    * \brief
    *  This function disables ISX mode.
    *
    * \details
    *  To disable ISX mode the following tasks are performed:
    *  1. Disconnect CintA and CintB from AMUXBUS-A
    *  2. Disconnect previous ISX electrode if it has been connected
    *
    *******************************************************************************/
    static void Input_Capsense_SsDisableISXMode(void)
    {
        /* Disconnect CintA from AMUXBUS-A using HSIOM registers */
        Input_Capsense_WriteBitsSafe(Input_Capsense_CintA_HSIOM_PTR, Input_Capsense_CintA_HSIOM_MASK, 0u);
        /* Disconnect CintB from AMUXBUS-A using HSIOM registers */
        Input_Capsense_WriteBitsSafe(Input_Capsense_CintB_HSIOM_PTR, Input_Capsense_CintB_HSIOM_MASK, 0u);
        /* Disconnect previous ISX electrode if it has been connected */
        Input_Capsense_ISXElectrodeCheck();
        Input_Capsense_DigPrt2_Stop();
        #if (Input_Capsense_USES_PORT_3)
            Input_Capsense_DigPrt3_Stop();
        #endif
    }
#endif /* (Input_Capsense_ENABLE == Input_Capsense_ISX_EN) */


/*******************************************************************************
* Function Name: Input_Capsense_SsSwitchSensingMode
****************************************************************************//**
*
* \brief
*  This function changes the Сomponent settings for operation in a specified
*  sensing mode.
*
* \details
*  This function performs following tasks:
*  1. Releasing the CSD HW block.
*  2. Disconnecting external capacitors.
*  3. Setting new mode.
*  4. Configuring HW to the new sensing mode.
*
* \param mode
*  Specifies the scan mode:
*  - Input_Capsense_SENSE_METHOD_CSD_E
*  - Input_Capsense_SENSE_METHOD_CSX_E
*  - Input_Capsense_SENSE_METHOD_ISX_E
*  - Input_Capsense_SENSE_METHOD_BIST_E
*  - Input_Capsense_UNDEFINED_E
*
*******************************************************************************/
void Input_Capsense_SsSwitchSensingMode(Input_Capsense_SENSE_METHOD_ENUM mode)
{
    if (Input_Capsense_currentSenseMethod != mode)
    {
        /* The requested mode differs to the current one. Disable the current mode */
        if (Input_Capsense_SENSE_METHOD_CSD_E == Input_Capsense_currentSenseMethod)
        {
            #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
                Input_Capsense_SsCSDDisableMode();
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) */
        }
        else if (Input_Capsense_SENSE_METHOD_CSX_E == Input_Capsense_currentSenseMethod)
        {
            #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
                Input_Capsense_SsDisableCSXMode();
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSX_EN) */
        }
        else if (Input_Capsense_SENSE_METHOD_ISX_E == Input_Capsense_currentSenseMethod)
        {
            #if (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
                Input_Capsense_SsDisableISXMode();
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_ISX_EN) */
        }
        else if (Input_Capsense_SENSE_METHOD_BIST_E == Input_Capsense_currentSenseMethod)
        {
            #if (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN)
                Input_Capsense_BistDisableMode();
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN) */
        }
        else
        {
            #if (Input_Capsense_ENABLE == Input_Capsense_ADC_EN)
                /* Release ADC resources */
                (void)Input_Capsense_AdcReleaseResources();
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_ADC_EN) */
        }

        /* Enable the specified mode */
        if (Input_Capsense_SENSE_METHOD_CSD_E == mode)
        {
            #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
                /* Initialize CSD mode to guarantee configured CSD mode */
                Input_Capsense_SsCSDInitialize();
                Input_Capsense_currentSenseMethod = Input_Capsense_SENSE_METHOD_CSD_E;
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) */
        }
        else if (Input_Capsense_SENSE_METHOD_CSX_E == mode)
        {
            #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
                /* Initialize CSX mode to guarantee configured CSX mode */
                Input_Capsense_CSXInitialize();
                Input_Capsense_currentSenseMethod = Input_Capsense_SENSE_METHOD_CSX_E;
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSX_EN) */
        }
        else if (Input_Capsense_SENSE_METHOD_ISX_E == mode)
        {
            #if (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
                /* Initialize ISX mode to guarantee configured ISX mode */
                Input_Capsense_ISXInitialize();
                Input_Capsense_currentSenseMethod = Input_Capsense_SENSE_METHOD_ISX_E;
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_ISX_EN) */
        }
        else if (Input_Capsense_SENSE_METHOD_BIST_E == mode)
        {
            #if (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN)
                Input_Capsense_BistInitialize();
                Input_Capsense_currentSenseMethod = Input_Capsense_SENSE_METHOD_BIST_E;
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN) */
        }
        else
        {
            Input_Capsense_currentSenseMethod = Input_Capsense_UNDEFINED_E;
        }
    }
}


/*******************************************************************************
* Function Name: Input_Capsense_SsSetAllIOsState
****************************************************************************//**
*
* \brief
*  Sets all electrodes into a default state.
*
* \details
*  Sets all the CSD/CSX IOs into a default state:
*  - HSIOM   - Disconnected, the GPIO mode.
*  - DM      - Strong drive.
*  - State   - Zero.
*
*  Sets all the ADC channels into a default state:
*  - HSIOM   - Disconnected, the GPIO mode.
*  - DM      - HiZ-Analog.
*  - State   - Zero.
*
*  It is not recommended to call this function directly from the application
*  layer.
*
*******************************************************************************/
void Input_Capsense_SsSetAllIOsState(uint32 state)
{
    uint8  interruptState;

    uint32 loopIndex;

    uint32 newPinPcVal;
    uint32 newPinHsiomVal;

    uint32 tmpPcDrRegValue;
    uint32 tmpHsiomRegValue;

    Input_Capsense_FLASH_IO_STRUCT const *snsIoPtr;

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

    /* Loop through all electrodes */
    snsIoPtr = &Input_Capsense_ioList[0u];
    for (loopIndex = 0u; loopIndex < Input_Capsense_TOTAL_ELECTRODES; loopIndex++)
    {
        interruptState = CyEnterCriticalSection();

        tmpHsiomRegValue = CY_GET_REG32 (snsIoPtr->hsiomPtr);
        tmpHsiomRegValue &= ~(snsIoPtr->hsiomMask);
        CY_SET_REG32 (snsIoPtr->hsiomPtr, tmpHsiomRegValue);

        tmpPcDrRegValue = CY_GET_REG32 (snsIoPtr->pcPtr);
        tmpPcDrRegValue &= ~(Input_Capsense_GPIO_PC_MASK << snsIoPtr->shift);
        tmpPcDrRegValue |=  (newPinPcVal << snsIoPtr->shift);
        CY_SET_REG32 (snsIoPtr->pcPtr, tmpPcDrRegValue);

        tmpHsiomRegValue |=  (newPinHsiomVal << snsIoPtr->hsiomShift);
        CY_SET_REG32 (snsIoPtr->hsiomPtr, tmpHsiomRegValue);

        tmpPcDrRegValue = CY_GET_REG32 (snsIoPtr->drPtr);
        tmpPcDrRegValue &= ~(snsIoPtr->mask);
        CY_SET_REG32 (snsIoPtr->drPtr, tmpPcDrRegValue);

        CyExitCriticalSection(interruptState);

        /* Get next electrode */
        snsIoPtr++;
    }

    #if ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) &&\
         (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) &&\
         (0u != Input_Capsense_CSD_TOTAL_SHIELD_COUNT))
        Input_Capsense_SsCSDSetShieldElectrodesState(state);
    #endif

    #if(Input_Capsense_ENABLE == Input_Capsense_ADC_EN)
        Input_Capsense_ClearAdcChannels();
    #endif

}

#if (Input_Capsense_ENABLE == Input_Capsense_ADC_EN)
/*******************************************************************************
* Function Name: Input_Capsense_SsReleaseResources()
****************************************************************************//**
*
* \brief
*  This function sets the resources that do not belong to the sensing HW block to
*  default state.
*
* \details
*  The function performs following tasks:
*  1. Checks if CSD block busy and returns error if it is busy
*  2. Disconnects integration capacitors (CintA, CintB for CSX mode and
*     Cmod for CSD mode)
*  3. Disconnect electroded if they have been connected.
*
* \return
*  Returns the status of the operation:
*  - Zero        - Resources released successfully.
*  - Non-zero    - One or more errors occurred in releasing process.
*
*******************************************************************************/
cystatus Input_Capsense_SsReleaseResources(void)
{
    cystatus busyStatus = CYRET_SUCCESS;

    if (Input_Capsense_SW_STS_BUSY == (Input_Capsense_dsRam.status & Input_Capsense_SW_STS_BUSY))
    {
        /* Previous widget is being scanned. Return error. */
        busyStatus = CYRET_INVALID_STATE;
    }
    else
    {
        #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
            Input_Capsense_SsDisableCSXMode();
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSX_EN) */

        #if (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
            Input_Capsense_SsDisableISXMode();
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_ISX_EN) */

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
            Input_Capsense_SsCSDDisableMode();
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) */

        #if (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN)
            Input_Capsense_BistDisableMode();
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN) */

        Input_Capsense_SsSetAllIOsState((uint32)Input_Capsense_SNS_CONNECTION_GROUND);

        /*
         * Reset of the currentSenseMethod variable to make sure that the next
         * call of SetupWidget() API setups the correct widget mode
         */
        Input_Capsense_currentSenseMethod = Input_Capsense_UNDEFINED_E;
    }

    return busyStatus;
}
#endif /* (Input_Capsense_ENABLE == Input_Capsense_ADC_EN) */


/*******************************************************************************
* Function Name: Input_Capsense_SsPostAllWidgetsScan
****************************************************************************//**
*
* \brief
*  The ISR function for multiple widget scanning implementation.
*
* \details
*  This is the function used by the Input_Capsense ISR to implement multiple widget
*  scanning.
*  Should not be used by the application layer.
*
*******************************************************************************/
void Input_Capsense_SsPostAllWidgetsScan(void)
{
    /*
    *  1. Increment widget index
    *  2. Check if all the widgets are scanned
    *  3. If all the widgets are not scanned, set up and scan next widget
    */
    #if (1u != Input_Capsense_TOTAL_WIDGETS)
        cystatus postScanStatus;

        do
        {
            Input_Capsense_widgetIndex++;

            postScanStatus = Input_Capsense_SetupWidget((uint32)Input_Capsense_widgetIndex);

            if (CYRET_SUCCESS == postScanStatus)
            {
                if((Input_Capsense_TOTAL_WIDGETS - 1u) == Input_Capsense_widgetIndex)
                {
                    /* The last widget will be scanned. Reset flag to skip configuring the next widget setup in ISR. */
                    Input_Capsense_requestScanAllWidget = Input_Capsense_DISABLE;
                }
                (void)Input_Capsense_Scan();
            }
            else if((Input_Capsense_TOTAL_WIDGETS - 1u) == Input_Capsense_widgetIndex)
            {
                #if ((Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN) && \
                     (Input_Capsense_ENABLE == Input_Capsense_CSD_EN))
                    if (Input_Capsense_SENSE_METHOD_CSD_E ==
                        Input_Capsense_GET_SENSE_METHOD(&Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex]))
                    {
                        /* Disable the CSD block */
                        CY_SET_REG32(Input_Capsense_CONFIG_PTR, Input_Capsense_configCsd);
                    }
                #endif /* ((Input_Capsense_ENABLE == Input_Capsense_BLOCK_OFF_AFTER_SCAN_EN) && \
                           (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)) */

                /* Update scan Counter */
                Input_Capsense_dsRam.scanCounter++;
                /* All widgets are totally processed. Reset BUSY flag */
                Input_Capsense_dsRam.status &= ~Input_Capsense_SW_STS_BUSY;

                /* Update status with with the failure */
                Input_Capsense_dsRam.status &= ~Input_Capsense_STATUS_ERR_MASK;
                Input_Capsense_dsRam.status |= ((postScanStatus & Input_Capsense_STATUS_ERR_SIZE) << Input_Capsense_STATUS_ERR_SHIFT);

                /* Set postScanStatus to exit the while loop */
                postScanStatus = CYRET_SUCCESS;
            }
            else
            {
                /* Update status with with the failure. Configure the next widget in while() loop */
                Input_Capsense_dsRam.status &= ~Input_Capsense_STATUS_ERR_MASK;
                Input_Capsense_dsRam.status |= ((postScanStatus & Input_Capsense_STATUS_ERR_SIZE) << Input_Capsense_STATUS_ERR_SHIFT);
            }
        } while (CYRET_SUCCESS != postScanStatus);
    #endif /* (1u != Input_Capsense_TOTAL_WIDGETS) */
}


/*******************************************************************************
* Function Name: Input_Capsense_SsIsrInitialize
****************************************************************************//**
*
* \brief
*  Enables and initializes for the function pointer for a callback for the ISR.
*
* \details
*  The "address" is a special type cyisraddress defined by Cylib. This function
*  is used by Component APIs and should not be used by an application program for
*  proper working of the Component.
*
* \param address
*  The address of the function to be called when interrupt is fired.
*
*******************************************************************************/
void Input_Capsense_SsIsrInitialize(cyisraddress address)
{
    Input_Capsense_ISR_StartEx(address);
}


/*******************************************************************************
* Function Name: Input_Capsense_SsSetModClkClockDivider
****************************************************************************//**
*
* \brief
*  Sets the divider values for the modulator clock and then starts
*  the modulator clock.
*
* \details
*  It is not recommended to call this function directly by the application layer.
*  It is used by initialization, widget APIs or wakeup functions to
*  enable the clocks.
*
* \param modClk
*  The divider value for the modulator clock.
*
*******************************************************************************/
void Input_Capsense_SsSetModClkClockDivider(uint32 modClk)
{
#if (Input_Capsense_ENABLE == Input_Capsense_IS_M0S8PERI_BLOCK)
    /* Stop modulator clock */
    CY_SET_REG32(Input_Capsense_MODCLK_CMD_PTR,
                 ((uint32)Input_Capsense_ModClk__DIV_ID <<
                 Input_Capsense_MODCLK_CMD_DIV_SHIFT)|
                 ((uint32)Input_Capsense_MODCLK_CMD_DISABLE_MASK));

    /*
     * Set divider value for sense modClk.
     * 1u is subtracted from modClk because Divider register value 0 corresponds
     * to dividing by 1.
     */
    CY_SET_REG32(Input_Capsense_MODCLK_DIV_PTR, ((modClk - 1u) << 8u));

    /* Check whether previous modulator clock start command has finished. */
    while(0u != (CY_GET_REG32(Input_Capsense_MODCLK_CMD_PTR) & Input_Capsense_MODCLK_CMD_ENABLE_MASK))
    {
        /* Wait until previous modulator clock start command has finished */
    }

    /* Start modulator clock, aligned to HFCLK */
    CY_SET_REG32(Input_Capsense_MODCLK_CMD_PTR,
                 (uint32)(((uint32)Input_Capsense_ModClk__DIV_ID << Input_Capsense_MODCLK_CMD_DIV_SHIFT) |
                  ((uint32)Input_Capsense_ModClk__PA_DIV_ID << Input_Capsense_MODCLK_CMD_PA_DIV_SHIFT) |
                  Input_Capsense_MODCLK_CMD_ENABLE_MASK));
#else
    uint32 newRegValue;

    /* Clear bit to disable ModClk clock. */
    CY_SET_REG32(Input_Capsense_MODCLK_CMD_PTR,
                 CY_GET_REG32(Input_Capsense_MODCLK_CMD_PTR) &
                 (uint32)(~Input_Capsense_ModClk__ENABLE_MASK));

    /*
     * Update ModClk clock divider.
     * 1u is subtracted from modClk because Divider register value has range (0-65535).
     */
    newRegValue = CY_GET_REG32(Input_Capsense_MODCLK_DIV_PTR) & (uint32)(~(uint32)Input_Capsense_ModClk__DIVIDER_MASK);
    newRegValue |= (modClk - 1u);
    CY_SET_REG32(Input_Capsense_MODCLK_DIV_PTR, newRegValue);

    /* Set bit to enable ModClk clock. */
    CY_SET_REG32(Input_Capsense_MODCLK_CMD_PTR,
                 CY_GET_REG32(Input_Capsense_MODCLK_CMD_PTR) |
                Input_Capsense_ModClk__ENABLE_MASK);
#endif /* (Input_Capsense_ENABLE == Input_Capsense_IS_M0S8PERI_BLOCK) */
}


/*******************************************************************************
* Function Name: Input_Capsense_SsSetSnsClockDivider
****************************************************************************//**
*
* \brief
*  Sets the divider values for the sense clock and then starts
*  the sense clock.
*
* \details
*  It is not recommended to call this function directly by the application layer.
*  It is used by initialization, widget APIs or wakeup functions to
*  enable the clocks.
*
* \param
*  snsClk The divider value for the sense clock.
*
*******************************************************************************/
void Input_Capsense_SsSetSnsClockDivider(uint32 snsClk)
{
#if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
    uint32 newRegValue;

    /*
     * Set divider value for sense clock.
     * 1u is subtracted from snsClk because SENSE_DIV value 0 corresponds
     * to dividing by 1.
     */
    newRegValue = CY_GET_REG32(Input_Capsense_SENSE_PERIOD_PTR);
    newRegValue &= (uint32)(~Input_Capsense_SENSE_PERIOD_SENSE_DIV_MASK);
    newRegValue |= snsClk - 1u;
    CY_SET_REG32(Input_Capsense_SENSE_PERIOD_PTR, newRegValue);
#else
    #if (Input_Capsense_ENABLE == Input_Capsense_IS_M0S8PERI_BLOCK)
        /* Stop sense clock clock   */
        CY_SET_REG32(Input_Capsense_SNSCLK_CMD_PTR,
                     ((uint32)Input_Capsense_SnsClk__DIV_ID <<
                     Input_Capsense_SNSCLK_CMD_DIV_SHIFT)|
                     ((uint32)Input_Capsense_SNSCLK_CMD_DISABLE_MASK));

        /*
         * Set divider value for sense clock.
         * 1u is subtracted from snsClk because Divider register value 0 corresponds
         * to dividing by 1.
         */
        CY_SET_REG32(Input_Capsense_SNSCLK_DIV_PTR, ((snsClk - 1u) << 8u));

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
        uint32 newRegValue;

        /* Clear bit to disable SnsClk clock. */
        CY_SET_REG32(Input_Capsense_SNSCLK_CMD_PTR,
                     CY_GET_REG32(Input_Capsense_SNSCLK_CMD_PTR) &
                     (uint32)(~(uint32)Input_Capsense_SnsClk__ENABLE_MASK));

        /*
         * Update snsClk clock divider.
         * 1u is subtracted from snsClk because Divider register value has range (0-65535).
         */
        newRegValue = CY_GET_REG32(Input_Capsense_SNSCLK_DIV_PTR) & (uint32)(~(uint32)Input_Capsense_SnsClk__DIVIDER_MASK);
        newRegValue |= (snsClk - 1u);
        CY_SET_REG32(Input_Capsense_SNSCLK_DIV_PTR, newRegValue);

        /* Set bit to enable SnsClk clock. */
        CY_SET_REG32(Input_Capsense_SNSCLK_CMD_PTR,
                     CY_GET_REG32(Input_Capsense_SNSCLK_CMD_PTR) |
                    Input_Capsense_SnsClk__ENABLE_MASK);
    #endif /* (Input_Capsense_ENABLE == Input_Capsense_IS_M0S8PERI_BLOCK) */
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
}


/*******************************************************************************
* Function Name: Input_Capsense_SsSetClockDividers
****************************************************************************//**
*
* \brief
*  Sets the divider values for sense and modulator clocks and then starts
*  a modulator clock-phase aligned to HFCLK and sense clock-phase aligned to
*  the modulator clock.
*
* \details
*  It is not recommended to call this function directly by the application layer.
*  It is used by initialization, widget APIs or wakeup functions to
*  enable the clocks.
*
* \param
*  snsClk The divider value for the sense clock.
*  modClk The divider value for the modulator clock.
*
*******************************************************************************/
void Input_Capsense_SsSetClockDividers(uint32 snsClk, uint32 modClk)
{
    /* Configure Mod clock */
    Input_Capsense_SsSetModClkClockDivider(modClk);

    /* Configure Sns clock */
    Input_Capsense_SsSetSnsClockDivider(snsClk);
}


#if (Input_Capsense_ANYMODE_AUTOCAL)
    /*******************************************************************************
    * Function Name: Input_Capsense_CalibrateWidget
    ****************************************************************************//**
    *
    * \brief
    *  Calibrates the IDACs for all the sensors in the specified widget to the default
    *  target, this function detects the sensing method used by the
    *  widget prior to calibration.
    *
    * \details
    *  This function performs exactly the same tasks as
    *  Input_Capsense_CalibrateAllWidgets, but only for a specified widget.
    *  This function detects the sensing method used by the widgets and uses
    *  the Enable compensation IDAC parameter.
    *  \if SECTION_I_REP
    *  For ISX mode, the frequency is also calibrated.
    *  \endif
    *
    *  \if SECTION_C_LOW_LEVEL
    *  This function is available when the CSD and/or CSX Enable IDAC
    *  auto-calibration parameter is enabled.
    *  \endif
    *  \if SECTION_I_REP
    *  This function is available when the ISX Enable auto-calibration parameter
    *  is enabled.
    *  \endif
    *
    * \param widgetId
    *  Specifies the ID number of the widget to calibrate its raw count.
    *  A macro for the widget ID can be found in the
    *  Input_Capsense Configuration header file defined as
    *  Input_Capsense_<WidgetName>_WDGT_ID.
    *
    * \return
    *  Returns the status of the specified widget calibration:
    *  - CYRET_SUCCESS - The operation is successfully completed.
    *  - CYRET_BAD_PARAM - The input parameter is invalid.
    *  - CYRET_BAD_DATA - The calibration failed and the Component may not
    *    operate as expected.
    *
    *******************************************************************************/
    cystatus Input_Capsense_CalibrateWidget(uint32 widgetId)
    {
        cystatus calibrateStatus = CYRET_SUCCESS;

        do
        {
            if (Input_Capsense_TOTAL_WIDGETS <= widgetId)
            {
                calibrateStatus = CYRET_BAD_PARAM;
            }

            /*
             *  Check if widget id is valid, specified widget did not
             *  detect any faults conditions if BIST is enabled.
             */
            #if (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN)
                if (0u != Input_Capsense_GET_WIDGET_EN_STATUS(widgetId))
                {
                    calibrateStatus = CYRET_SUCCESS;
                }
                else
                {
                    calibrateStatus = CYRET_INVALID_STATE;
                }
            #endif  /* (Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN) */

            if (CYRET_SUCCESS != calibrateStatus)
            {
                /* Exit from the loop because of a fail */
                break;
            }

            /* If both CSD and CSX are enabled, calibrate widget using sensing method */
            #if (Input_Capsense_ENABLE == Input_Capsense_MANY_WIDGET_METHODS_EN)
                /* Check widget sensing method and call appropriate APIs */
                #if (Input_Capsense_ENABLE == Input_Capsense_ISX_IDAC_AUTOCAL_EN)
                    if (Input_Capsense_SENSE_METHOD_ISX_E ==
                        Input_Capsense_GET_SENSE_METHOD(&Input_Capsense_dsFlash.wdgtArray[widgetId]))
                    {
                        /* Calibrate CSX widget */
                       Input_Capsense_ISXCalibrateWidget(widgetId, Input_Capsense_ISX_RAWCOUNT_CAL_LEVEL);
                    }
                #endif  /* (Input_Capsense_ENABLE == Input_Capsense_ISX_IDAC_AUTOCAL_EN) */

                /* Check widget sensing method and call appropriate APIs */
                #if (Input_Capsense_ENABLE == Input_Capsense_CSX_IDAC_AUTOCAL_EN)
                    if (Input_Capsense_SENSE_METHOD_CSX_E ==
                        Input_Capsense_GET_SENSE_METHOD(&Input_Capsense_dsFlash.wdgtArray[widgetId]))
                    {
                        /* Calibrate CSX widget */
                       calibrateStatus = Input_Capsense_CSXCalibrateWidget(widgetId, Input_Capsense_CSX_RAWCOUNT_CAL_LEVEL);
                    }
                #endif  /* (Input_Capsense_ENABLE == Input_Capsense_CSX_IDAC_AUTOCAL_EN) */

                #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTOCAL_EN)
                    if (Input_Capsense_SENSE_METHOD_CSD_E ==
                        Input_Capsense_GET_SENSE_METHOD(&Input_Capsense_dsFlash.wdgtArray[widgetId]))
                    {
                        /* Calibrate CSD widget */
                        calibrateStatus = Input_Capsense_CSDCalibrateWidget(widgetId, Input_Capsense_CSD_RAWCOUNT_CAL_LEVEL);
                    }
                #endif  /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_AUTOCAL_EN) */

            /* If only CSD is enabled, calibrate CSD sensor */
            #elif (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
                calibrateStatus = Input_Capsense_CSDCalibrateWidget(widgetId, Input_Capsense_CSD_RAWCOUNT_CAL_LEVEL);

            /* If only CSX is enabled, call CSX scan */
            #elif (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
                calibrateStatus = Input_Capsense_CSXCalibrateWidget(widgetId, Input_Capsense_CSX_RAWCOUNT_CAL_LEVEL);

            /* If only ISX is enabled, call ISX scan */
            #elif (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
                Input_Capsense_ISXCalibrateWidget(widgetId, Input_Capsense_ISX_RAWCOUNT_CAL_LEVEL);

            #else
                calibrateStatus = CYRET_UNKNOWN;
            #endif
        } while (0u);

        return calibrateStatus;
    }


    /*******************************************************************************
    * Function Name: Input_Capsense_CalibrateAllWidgets
    ****************************************************************************//**
    *
    * \brief
    *  Calibrates the IDACs for all the widgets in the Component to the default
    *  target, this function detects the sensing method used by the widgets
    *  prior to calibration.
    *
    * \details
    *  Calibrates the IDACs for all the widgets in the Component to the default
    *  target value. This function detects the sensing method used by the widgets
    *  and regards the Enable compensation IDAC parameter.
    *  \if SECTION_I_REP
    *  For ISX mode, the frequency is also calibrated.
    *  \endif
    *
    *  \cond SECTION_C_LOW_LEVEL
    *  This function is available when the CSD and/or CSX Enable IDAC
    *  auto-calibration parameter is enabled.
    *  \endcond
    *  \if SECTION_I_REP
    *  This function is available when the ISX Enable Auto-calibration parameter
    *  is enabled.
    *  \endif
    *
    * \return
    *  Returns the status of the calibration process:
    *  - CYRET_SUCCESS - The operation is successfully completed.
    *  - CYRET_BAD_DATA - The calibration failed and the Component may not
    *    operate as expected.
    *
    *******************************************************************************/
    cystatus Input_Capsense_CalibrateAllWidgets(void)
    {
        cystatus calibrateStatus = CYRET_SUCCESS;
        uint32 wdgtIndex;

        for (wdgtIndex = 0u; wdgtIndex < Input_Capsense_TOTAL_WIDGETS; wdgtIndex++)
        {
            calibrateStatus |= Input_Capsense_CalibrateWidget(wdgtIndex);
        }

        return calibrateStatus;
    }
#endif /* (Input_Capsense_ANYMODE_AUTOCAL) */


#if (Input_Capsense_CSD_SS_DIS != Input_Capsense_CSD_AUTOTUNE)
    /*******************************************************************************
    * Function Name: Input_Capsense_SsAutoTuneWidget
    ****************************************************************************//**
    *
    * \brief
    *  This API performs the parameters auto-tuning for the optimal Input_Capsense
    *  operation for a desired widget.
    *
    * \details
    *  This API performs the following:
    *  - Calibrates Modulator and Compensation IDACs.
    *  - Tunes the Sense Clock optimal value to get a Sense Clock period greater than
    *    2*5*R*Cp.
    *  - Calculates the resolution for the optimal finger capacitance.
    *
    * \param widgetId
    *  Specifies the ID number of a desired widget.
    *  A macro for the widget ID can be found in the
    *  Input_Capsense Configuration header file defined as
    *  Input_Capsense_<WidgetName>_WDGT_ID.
    *
    * \return
    *  Returns the status of the operation:
    *  - Zero     - All the widgets are auto-tuned successfully.
    *  - Non-zero - Auto-tuning failed for any widget.
    *
    *******************************************************************************/
    cystatus Input_Capsense_SsAutoTuneWidget(uint32 widgetId)
    {
        cystatus autoTuneStatus = CYRET_SUCCESS;

        uint32 snsIndex;
        uint32 inputSnsClk;
        uint32 minSnsClkDiv;
        uint32 minSnsClkDivTmp;

        AUTO_TUNE_CONFIG_TYPE autoTuneConfig;

        uint32 maxRaw = 0u;
        uint32 maxCp = 0u;
        uint32 maxIdacComp = 0u;

        #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
            uint32 maxCpSnsId = 0u;
            uint32 maxCpRowSnsId = 0u;
        #endif

        Input_Capsense_FLASH_WD_STRUCT const *ptrFlashWidget = &Input_Capsense_dsFlash.wdgtArray[widgetId];
        Input_Capsense_RAM_WD_BASE_STRUCT *ptrRamWidget = (Input_Capsense_RAM_WD_BASE_STRUCT *)ptrFlashWidget->ptr2WdgtRam;
        Input_Capsense_RAM_SNS_STRUCT *ptrRamSensor = ptrFlashWidget->ptr2SnsRam;

        /* Find input of sensor clock frequency */
        #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
            /* Dividers are chained (Fourth-generation HW block). Flip flop is not available */
            inputSnsClk = ((uint32)CYDEV_BCLK__HFCLK__KHZ / (uint32)Input_Capsense_dsRam.modCsdClk);

            /* Minimum value of SnaClk divider that is allowed for all Fourth-generation
             * CSD HW block based devices.
            */
            minSnsClkDiv = Input_Capsense_MIN_SNS_CLK_DIVIDER;
        #elif (Input_Capsense_ENABLE == Input_Capsense_IS_M0S8PERI_BLOCK)
            /* Dividers are not chained */
            inputSnsClk = CYDEV_BCLK__HFCLK__KHZ >> Input_Capsense_FLIP_FLOP_DIV;

            /* Minimum value of SnaClk divider that is allowed for PSoC 4100 and PSoC 4200
               device families.
            */
            minSnsClkDiv = Input_Capsense_dsRam.modCsdClk;
        #else
            /* Dividers are chained (PSoC 4100, PSoC 4200) */
            inputSnsClk = (CYDEV_BCLK__HFCLK__KHZ / Input_Capsense_dsRam.modCsdClk) >> Input_Capsense_FLIP_FLOP_DIV;

            /* Minimum value of SnaClk divider that is allowed for all Fourth-generation
             * CSD HW block based device except PSoC 4100 and PSoC 4200 device families.
            */
            minSnsClkDiv = Input_Capsense_MIN_SNS_CLK_DIVIDER;
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */

        /* Minimum value of SnsClk divider required to ensure the CSD HW block
         * operation in allowed frequency range.
        */
        minSnsClkDivTmp = inputSnsClk * Input_Capsense_AUTOTUNE_CAL_UNITS;
        minSnsClkDivTmp /= Input_Capsense_CSD_SNS_FREQ_KHZ_MAX;

        if (minSnsClkDiv < minSnsClkDivTmp)
        {
            minSnsClkDiv = minSnsClkDivTmp;
        }

        minSnsClkDiv = (minSnsClkDiv + (Input_Capsense_AUTOTUNE_CAL_UNITS - 1u)) / Input_Capsense_AUTOTUNE_CAL_UNITS;

        /* Make divider even */
        if (0u != (minSnsClkDiv & 0x01u))
        {
            minSnsClkDiv++;
        }

        /* Initialize auto-tuning configuration structure */
        autoTuneConfig.snsClkInputClock = (uint16)inputSnsClk;
        autoTuneConfig.snsClkConstantR = Input_Capsense_CSD_SNSCLK_R_CONST;
        autoTuneConfig.vRef = Input_Capsense_CSD_VREF_MV;
        autoTuneConfig.fingerCap = ptrRamWidget->fingerCap;
        autoTuneConfig.sigPFC = &ptrRamWidget->sigPFC;

        /*
        * Autotune phase #1:
        * - performing the first calibration at fixed settings
        * - getting maximum sensor Cp
        * - getting sense clock frequency based on Cp
        */

        ptrRamWidget->resolution = Input_Capsense_AUTOTUNE_CALIBRATION_RESOLUTION;

        ptrRamWidget->snsClk = (uint16)(inputSnsClk / Input_Capsense_AUTOTUNE_CALIBRATION_FREQ_KHZ);
        ptrRamWidget->snsClkSource = (uint8)Input_Capsense_CLK_SOURCE_DIRECT;

        #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
            ptrRamWidget->rowSnsClk = (uint16)(inputSnsClk / Input_Capsense_AUTOTUNE_CALIBRATION_FREQ_KHZ);
            ptrRamWidget->rowSnsClkSource = (uint8)Input_Capsense_CLK_SOURCE_DIRECT;
        #endif

        /* Calibrate CSD widget to the default calibration target */
        (void)Input_Capsense_CSDCalibrateWidget(widgetId, Input_Capsense_AUTOTUNE_CAL_LEVEL);

        /* Find raw count and IDAC of a sensor with maximum Cp */
        for (snsIndex = 0u; snsIndex < ptrFlashWidget->numCols; snsIndex++)
        {
            #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
                if (maxIdacComp < ptrRamSensor->idacComp[0u])
                {
                    #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
                        maxCpSnsId = snsIndex;
                    #endif
                    maxIdacComp = ptrRamSensor->idacComp[0u];
                    maxRaw = ptrRamSensor->raw[0u];
                }
            #else
                if (maxRaw < ptrRamSensor->raw[0u])
                {
                    #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
                        maxCpSnsId = snsIndex;
                    #endif
                    maxRaw = ptrRamSensor->raw[0u];
                }
            #endif
            ptrRamSensor++;
        }

        /* Update auto-tuning configuration structure */
        autoTuneConfig.iDacMod = ptrRamWidget->idacMod[0u];
        autoTuneConfig.iDacComp = (uint8)maxIdacComp;
        autoTuneConfig.iDacGain = Input_Capsense_idacGainTable[ptrRamWidget->idacGainIndex].gainValue;
        autoTuneConfig.ptrSenseClk = &ptrRamWidget->snsClk;
        autoTuneConfig.calTarget = (uint16)((maxRaw * Input_Capsense_AUTOTUNE_CAL_UNITS) /
                ((uint32)(0x01uL << Input_Capsense_AUTOTUNE_CALIBRATION_RESOLUTION) - 1u));

        /* Find sensor Cp and optimum sense clock value */
        maxCp = SmartSense_TunePrescalers(&autoTuneConfig);
        autoTuneConfig.sensorCap = maxCp;

        /* Increase sensor clock divider to valid value */
        while(ptrRamWidget->snsClk < minSnsClkDiv)
        {
            ptrRamWidget->snsClk <<= 1u;
        }

        /* Do the same for row for touchpad or matrix buttons widgets */
        #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
            if ((Input_Capsense_WD_TOUCHPAD_E == Input_Capsense_GET_WIDGET_TYPE(ptrFlashWidget)) ||
                (Input_Capsense_WD_MATRIX_BUTTON_E == Input_Capsense_GET_WIDGET_TYPE(ptrFlashWidget)))
            {
                /* Find a sensor with maximum Cp */
                maxRaw = 0u;
                maxIdacComp = 0u;
                for (snsIndex = ptrFlashWidget->numCols; snsIndex < ptrFlashWidget->totalNumSns; snsIndex++)
                {
                    #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
                        if (maxIdacComp < ptrRamSensor->idacComp[0u])
                        {
                            maxCpRowSnsId = snsIndex;
                            maxIdacComp = ptrRamSensor->idacComp[0u];
                            maxRaw = ptrRamSensor->raw[0u];
                        }
                    #else
                        if (maxRaw < ptrRamSensor->raw[0u])
                        {
                            maxCpRowSnsId = snsIndex;
                            maxRaw = ptrRamSensor->raw[0u];
                        }
                    #endif
                    ptrRamSensor++;
                }

                /* Configure auto-tuning configuration structure */
                autoTuneConfig.iDacMod = ptrRamWidget->rowIdacMod[0u];
                autoTuneConfig.iDacComp = (uint8)maxIdacComp;
                autoTuneConfig.ptrSenseClk = &ptrRamWidget->rowSnsClk;
                autoTuneConfig.calTarget = (uint16)((maxRaw * Input_Capsense_AUTOTUNE_CAL_UNITS) /
                        ((uint32)(0x01uL << Input_Capsense_AUTOTUNE_CALIBRATION_RESOLUTION) - 1u));

                /* Find correct sense clock value */
                maxCp = SmartSense_TunePrescalers(&autoTuneConfig);

                /* Save maximum sensor Cp and corresponding sensor Id */
                if (autoTuneConfig.sensorCap < maxCp)
                {
                    autoTuneConfig.sensorCap = maxCp;
                    maxCpSnsId = maxCpRowSnsId;
                }

                /* Increase sensor clock divider to valid value */
                while(ptrRamWidget->rowSnsClk < minSnsClkDiv)
                {
                    ptrRamWidget->rowSnsClk <<= 1u;
                }
            }
        #endif /* (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN) */

        /* Check tuning results */
        if (Input_Capsense_AUTOTUNE_CP_MAX < maxCp)
        {
            autoTuneStatus = CYRET_BAD_DATA;
        }

        /*
        * Autotune phase #2:
        * - repeating calibration with new sense clock frequency
        * - getting resolution
        */

        /* Calibrate CSD widget to the default calibration target with newly defined sense frequency */
        (void)Input_Capsense_CSDCalibrateWidget(widgetId, Input_Capsense_AUTOTUNE_CAL_LEVEL);

        autoTuneConfig.iDacGain = Input_Capsense_idacGainTable[ptrRamWidget->idacGainIndex].gainValue;
        autoTuneConfig.iDacMod = ptrRamWidget->idacMod[0u];
        autoTuneConfig.ptrSenseClk = &ptrRamWidget->snsClk;

        #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
            if ((Input_Capsense_WD_TOUCHPAD_E == Input_Capsense_GET_WIDGET_TYPE(ptrFlashWidget)) ||
                (Input_Capsense_WD_MATRIX_BUTTON_E == Input_Capsense_GET_WIDGET_TYPE(ptrFlashWidget)))
            {
                if (maxCpSnsId >= ptrFlashWidget->numCols)
                {
                    autoTuneConfig.iDacMod = ptrRamWidget->rowIdacMod[0u];
                    autoTuneConfig.ptrSenseClk = &ptrRamWidget->rowSnsClk;
                }
            }
        #endif

        /* Find resolution */
        ptrRamWidget->resolution = SmartSense_TuneSensitivity(&autoTuneConfig);

        /*
        * Autotune phase #3:
        * - selecting a widget clock source if AUTO
        * - repeating calibration with found clock frequency, resolution and clock source
        * - updating sensitivity
        */

        /* Tune widget sensitivity */
        Input_Capsense_SsSetWidgetSenseClkSrc(widgetId, ptrRamWidget);

        /* Calibrate CSD widget to the default calibration target with newly defined resolution */
        autoTuneStatus |= Input_Capsense_CSDCalibrateWidget(widgetId, Input_Capsense_AUTOTUNE_CAL_LEVEL);

        #if (Input_Capsense_ENABLE == Input_Capsense_TST_WDGT_CRC_EN)
            Input_Capsense_DsUpdateWidgetCrc(widgetId);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_TST_WDGT_CRC_EN) */

        return autoTuneStatus;
    }


    /*******************************************************************************
    * Function Name: Input_Capsense_SsAutoTune
    ****************************************************************************//**
    *
    * \brief
    *  This API performs the parameters auto-tuning for the optimal Input_Capsense
    *  operation.
    *
    * \details
    *  This API performs the following:
    *  - Calibrates Modulator and Compensation IDACs.
    *  - Tunes the Sense Clock optimal value to get a Sense Clock period greater than
    *    2*5*R*Cp.
    *  - Calculates the resolution for the optimal finger capacitance.
    *
    * \return
    *  Returns the status of the operation:
    *  - Zero     - All the widgets are auto-tuned successfully.
    *  - Non-zero - Auto-tuning failed for any widget.
    *
    *******************************************************************************/
    cystatus Input_Capsense_SsAutoTune(void)
    {
        cystatus autoTuneStatus = CYRET_SUCCESS;
        uint32 wdgtIndex;

        /* Tune each CSD widget */
        for (wdgtIndex = 0u; wdgtIndex < Input_Capsense_TOTAL_WIDGETS; wdgtIndex++)
        {
            if (Input_Capsense_SENSE_METHOD_CSD_E ==
                Input_Capsense_GET_SENSE_METHOD(&Input_Capsense_dsFlash.wdgtArray[wdgtIndex]))
            {
                autoTuneStatus |= Input_Capsense_SsAutoTuneWidget(wdgtIndex);
            }
        }
        return autoTuneStatus;
    }
#endif /* (Input_Capsense_CSD_SS_DIS != Input_Capsense_CSD_AUTOTUNE)) */


#if (Input_Capsense_DISABLE == Input_Capsense_CSDV2)
    #if ( ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) \
        || (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)) ||\
         (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG))
        /*******************************************************************************
        * Function Name: Input_Capsense_SsTrimIdacsSinking
        ****************************************************************************//**
        *
        * \brief
        *  This function loads trim values from SFLASH rows to calibrate
        *  IDAC1 and IDAC2 for Sinking CSD Mode
        *
        * \details
        *  Function reads trim value from SFLASH and loads it into IDAC trim register.
        *  If Compensation IDAC is disabled the function loads trim values for IDAC1 only.
        *
        *******************************************************************************/
        static void Input_Capsense_SsTrimIdacsSinking(void)
        {
            uint32 trimValue;

            /* Mod iDAC Sinking Mode */
            trimValue = CY_GET_REG32(Input_Capsense_TRIM2_PTR) & ~Input_Capsense_IDAC_TRIM2_MOD_SNK_MASK;
            trimValue |= ((uint32)CY_GET_REG8(Input_Capsense_SFLASH_TRIM2_PTR) &
                                                      Input_Capsense_SFLASH_TRIM_IDAC_MOD_MASK) ;

            #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
                /* Comp iDAC Sinking Mode */
                trimValue &= ~Input_Capsense_IDAC_TRIM2_COMP_SNK_MASK;
                trimValue |= ((uint32)CY_GET_REG8(Input_Capsense_SFLASH_TRIM2_PTR) &
                                                          Input_Capsense_SFLASH_TRIM_IDAC_COMP_MASK);
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) */

            /* Update IDAC trim bits for gain control in current sink mode */
            CY_SET_REG32(Input_Capsense_TRIM2_PTR, trimValue);
        }
    #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || \
               (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG)) */


    #if ( ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) \
        || (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)) || \
         (Input_Capsense_IDAC_SOURCING == Input_Capsense_CSD_IDAC_CONFIG))
        /*******************************************************************************
        * Function Name: Input_Capsense_SsTrimIdacsSourcing
        ****************************************************************************//**
        *
        * \brief
        *  This function loads trim values from SFLASH rows to calibrate
        *  IDAC1 and IDAC2 for Sourcing CSD Mode
        *
        * \details
        *  Function reads trim value from SFLASH and loads it into IDAC trim register.
        *  If Compensation IDAC is disabled the function loads trim values for IDAC1 only.
        *
        *******************************************************************************/
        static void Input_Capsense_SsTrimIdacsSourcing(void)
        {
            uint32 trimValue;

            /* Mod iDAC Sourcing Mode */
            trimValue = CY_GET_REG32(Input_Capsense_TRIM1_PTR) & ~Input_Capsense_IDAC_TRIM1_MOD_SRC_MASK;
            trimValue |= ((uint32)CY_GET_REG8(Input_Capsense_SFLASH_TRIM1_PTR) &
                                                      Input_Capsense_SFLASH_TRIM_IDAC_MOD_MASK);

            #if (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN)
                 /* Comp iDAC Sourcing Mode */
                trimValue &= ~Input_Capsense_IDAC_TRIM1_COMP_SRC_MASK;
                trimValue |= ((uint32)CY_GET_REG8(Input_Capsense_SFLASH_TRIM1_PTR) &
                                                          Input_Capsense_SFLASH_TRIM_IDAC_COMP_MASK);
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_IDAC_COMP_EN) */

            /* Update IDAC trim bits for gain control in current source mode */
            CY_SET_REG32(Input_Capsense_TRIM1_PTR, trimValue);
        }
    #endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || \
               (Input_Capsense_IDAC_SOURCING == Input_Capsense_CSD_IDAC_CONFIG)) */


    /*******************************************************************************
    * Function Name: Input_Capsense_SsTrimIdacs
    ****************************************************************************//**
    *
    * \brief
    *  This function loads trim values from SFLASH rows to calibrate
    *  IDAC1 and IDAC2 for CSD Mode
    *
    * \details
    *  If CSX mode is enabled the function loads trim values for both sink and source
    *  mode. If CSX mode is disabled the function loads trim values for sink or
    *  source mode based on sink/source mode configuration.
    *  If Compensation IDAC is disabled the function loads trim values for IDAC1 only.
    *
    *******************************************************************************/
    static void Input_Capsense_SsTrimIdacs(void)
    {
        #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)
            Input_Capsense_SsTrimIdacsSinking();
            Input_Capsense_SsTrimIdacsSourcing();
        #elif (Input_Capsense_IDAC_SINKING == Input_Capsense_CSD_IDAC_CONFIG)
            Input_Capsense_SsTrimIdacsSinking();
        #elif (Input_Capsense_IDAC_SOURCING == Input_Capsense_CSD_IDAC_CONFIG)
            Input_Capsense_SsTrimIdacsSourcing();
        #else
            #error "Not supported Mode, Component cannot work in this mode"
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || (Input_Capsense_ENABLE == Input_Capsense_ISX_EN) */
    }
#endif  /* (Input_Capsense_DISABLE == Input_Capsense_CSDV2) */


#if (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN)
    /*******************************************************************************
    * Function Name: Input_Capsense_SsChangeImoFreq
    ****************************************************************************//**
    *
    * \brief
    *  This function changes the IMO frequency.
    *
    * \details
    *  The IMO frequency can have three offsets: 0%, -5% and +5%. The frequency
    *  trims are contained in the Input_Capsense_immunity[value] array for each
    *  frequency channel.
    *
    * \param value The frequency channel ID.
    *
    *******************************************************************************/
    void Input_Capsense_SsChangeImoFreq(uint32 value)
    {
        CY_SET_REG32(CY_SYS_CLK_IMO_TRIM1_PTR, Input_Capsense_immunity[value]);
    }

    /*******************************************************************************
    * Function Name: Input_Capsense_SsChangeClkFreq
    ****************************************************************************//**
    *
    * \brief
    *  This function changes the sensor clock frequency by configuring
    *  the corresponding divider.
    *
    * \details
    *  This function changes the sensor clock frequency by configuring
    *  the corresponding divider.
    *
    * \param chId
    *  The frequency channel ID.
    *
    *******************************************************************************/
    void Input_Capsense_SsChangeClkFreq(uint32 chId)
    {
        uint32 snsClkDivider;
        uint32 freqOffset1 = 0u;
        uint32 freqOffset2 = 0u;

        #if (0u != Input_Capsense_TOTAL_CSD_WIDGETS)
            #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
                uint32 conversionsNum;
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */

            #if((Input_Capsense_CLK_SOURCE_PRS8  == Input_Capsense_CSD_SNS_CLK_SOURCE) ||\
                (Input_Capsense_CLK_SOURCE_PRS12 == Input_Capsense_CSD_SNS_CLK_SOURCE) ||\
                (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE))
                uint32 snsClkSrc;
            #endif
        #endif

        #if ((0u != Input_Capsense_TOTAL_CSD_WIDGETS) || \
             ((Input_Capsense_DISABLE == Input_Capsense_CSX_COMMON_TX_CLK_EN) && (0u != Input_Capsense_TOTAL_CSX_WIDGETS)))
            Input_Capsense_FLASH_WD_STRUCT const *ptrFlashWdgt = &Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex];
            Input_Capsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (Input_Capsense_RAM_WD_BASE_STRUCT *)ptrFlashWdgt->ptr2WdgtRam;
        #endif

        switch(Input_Capsense_GET_SENSE_METHOD(&Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex]))
        {
        #if (0u != Input_Capsense_TOTAL_CSD_WIDGETS)
            case Input_Capsense_SENSE_METHOD_CSD_E:
                /* Get sensor clock divider value */
                #if (Input_Capsense_ENABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN)
                    snsClkDivider = Input_Capsense_dsRam.snsCsdClk;
                #else /* (Input_Capsense_ENABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN) */
                    #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
                        /* Get SnsClck divider for rows or columns */
                        if (Input_Capsense_dsFlash.wdgtArray[Input_Capsense_widgetIndex].numCols <= Input_Capsense_sensorIndex)
                        {
                            snsClkDivider = ptrWdgt->rowSnsClk;
                        }
                        else
                        {
                            snsClkDivider = ptrWdgt->snsClk;
                        }
                    #else
                        snsClkDivider = ptrWdgt->snsClk;
                    #endif /* (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN) */
                #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN) */

                freqOffset1 = Input_Capsense_CSD_MFS_DIVIDER_OFFSET_F1;
                freqOffset2 = Input_Capsense_CSD_MFS_DIVIDER_OFFSET_F2;

                #if((Input_Capsense_CLK_SOURCE_PRS8  == Input_Capsense_CSD_SNS_CLK_SOURCE) ||\
                    (Input_Capsense_CLK_SOURCE_PRS12 == Input_Capsense_CSD_SNS_CLK_SOURCE) ||\
                    (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE))
                    /* Get sense clk source */
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

                    switch (snsClkSrc)
                    {
                    case Input_Capsense_CLK_SOURCE_PRS8:
                    case Input_Capsense_CLK_SOURCE_PRS12:
                        /* Multiply by 2 for PRS8/PRS12 mode */
                        freqOffset1 <<= 1u;
                        freqOffset2 <<= 1u;
                        break;

                    default:
                        break;
                    }
                #endif

                /* Change the divider based on the chId */
                switch (chId)
                {
                    case Input_Capsense_FREQ_CHANNEL_1:
                    {
                        snsClkDivider += freqOffset1;
                        break;
                    }
                    case Input_Capsense_FREQ_CHANNEL_2:
                    {
                        snsClkDivider += freqOffset2;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }

                #if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
                    /* Set Number Of Conversions based on scanning resolution */
                    conversionsNum = Input_Capsense_SsCSDGetNumberOfConversions(snsClkDivider, (uint32)ptrWdgt->resolution, (uint32)ptrWdgt->snsClkSource);
                    CY_SET_REG32(Input_Capsense_SEQ_NORM_CNT_PTR, (conversionsNum & Input_Capsense_SEQ_NORM_CNT_CONV_CNT_MASK));
                #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */

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
                #endif

                /* Configure the new divider */
                Input_Capsense_SsSetSnsClockDivider(snsClkDivider);

                break;
        #endif /* #if (0u != Input_Capsense_TOTAL_CSD_WIDGETS) */

        #if (0u != Input_Capsense_TOTAL_CSX_WIDGETS)
            case Input_Capsense_SENSE_METHOD_CSX_E:
                #if (Input_Capsense_ENABLE == Input_Capsense_CSX_COMMON_TX_CLK_EN)
                    snsClkDivider = Input_Capsense_dsRam.snsCsxClk;
                #else /* (Input_Capsense_ENABLE == Input_Capsense_CSX_COMMON_TX_CLK_EN) */
                    snsClkDivider = ptrWdgt->snsClk;
                #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSX_COMMON_TX_CLK_EN) */
                freqOffset1 = Input_Capsense_CSX_MFS_DIVIDER_OFFSET_F1;
                freqOffset2 = Input_Capsense_CSX_MFS_DIVIDER_OFFSET_F2;

                /* Change the divider based on the chId */
                switch (chId)
                {
                    case Input_Capsense_FREQ_CHANNEL_1:
                    {
                        snsClkDivider += freqOffset1;
                        break;
                    }
                    case Input_Capsense_FREQ_CHANNEL_2:
                    {
                        snsClkDivider += freqOffset2;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }

                /* Configure the new divider */
                Input_Capsense_SsSetSnsClockDivider(snsClkDivider);

                break;
        #endif /* #if (0u != Input_Capsense_TOTAL_CSX_WIDGETS) */

        default:
            CYASSERT(0);
            break;
        }
    }
#endif  /* (Input_Capsense_ENABLE == Input_Capsense_MULTI_FREQ_SCAN_EN) */


#if((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) || \
    ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && \
     (Input_Capsense_ENABLE == Input_Capsense_CSDV2)))
/*******************************************************************************
* Function Name: Input_Capsense_SsInitializeSourceSenseClk
****************************************************************************//**
*
* \brief
*  Sets a source for Sense Clk for all CSD widgets.
*
* \details
*  Updates snsClkSource and rowSnsClkSource with a source for the sense Clk.
*  for all CSD widgets.
*
*******************************************************************************/
void Input_Capsense_SsInitializeSourceSenseClk(void)
{
    uint32 wdgtIndex;
    Input_Capsense_RAM_WD_BASE_STRUCT *ptrWdgt;

    for (wdgtIndex = 0u; wdgtIndex < Input_Capsense_TOTAL_WIDGETS; wdgtIndex++)
    {
        ptrWdgt = (Input_Capsense_RAM_WD_BASE_STRUCT *)Input_Capsense_dsFlash.wdgtArray[wdgtIndex].ptr2WdgtRam;

        switch (Input_Capsense_GET_SENSE_METHOD(&Input_Capsense_dsFlash.wdgtArray[wdgtIndex]))
        {
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
            case Input_Capsense_SENSE_METHOD_CSD_E:
                Input_Capsense_SsSetWidgetSenseClkSrc(wdgtIndex, ptrWdgt);
                break;
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) */
        #if ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && (Input_Capsense_ENABLE == Input_Capsense_CSDV2))
            case Input_Capsense_SENSE_METHOD_CSX_E:
                Input_Capsense_SsSetWidgetTxClkSrc(wdgtIndex, ptrWdgt);
                break;
        #endif /* (((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)) && (Input_Capsense_ENABLE == Input_Capsense_CSDV2)) */
        default:
            break;
        }
        #if (Input_Capsense_ENABLE == Input_Capsense_TST_WDGT_CRC_EN)
            Input_Capsense_DsUpdateWidgetCrc(wdgtIndex);
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_TST_WDGT_CRC_EN) */
    }
}
#endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) || \
           (((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) || \
           (Input_Capsense_ENABLE == Input_Capsense_ISX_EN)) && \
           (Input_Capsense_ENABLE == Input_Capsense_CSDV2))) */


#if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
    /*******************************************************************************
    * Function Name: Input_Capsense_SsSetWidgetSenseClkSrc
    ****************************************************************************//**
    *
    * \brief
    *  Sets a source for the sense clock for a widget.
    *
    * \param wdgtIndex
    *  Specifies the ID of the widget.
    * \param ptrWdgt
    *  The pointer to the RAM_WD_BASE_STRUCT structure.
    *
    * \details
    *  Updates snsClkSource and rowSnsClkSource with a source for the sense Clk for a
    *  widget.
    *
    *******************************************************************************/
    static void Input_Capsense_SsSetWidgetSenseClkSrc(uint32 wdgtIndex, Input_Capsense_RAM_WD_BASE_STRUCT * ptrWdgt)
    {
        uint8 lfsrSize;
        uint8 lfsrScale;

        #if(Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE)
            #if(Input_Capsense_ENABLE == Input_Capsense_CSDV2)
                uint32 conversionsNum;
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
            uint32 snsClkDivider;
        #endif /* (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE) */

        #if(Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE)
            snsClkDivider = Input_Capsense_SsCSDGetColSnsClkDivider(wdgtIndex);

            #if(Input_Capsense_ENABLE == Input_Capsense_CSDV2)
                conversionsNum = Input_Capsense_SsCSDGetNumberOfConversions(snsClkDivider, (uint32)ptrWdgt->resolution,
                                                                                             Input_Capsense_CLK_SOURCE_DIRECT);
                lfsrSize = Input_Capsense_SsCalcLfsrSize(snsClkDivider, conversionsNum);
                if (Input_Capsense_CLK_SOURCE_DIRECT == lfsrSize)
                {
                    /*
                    * Multiplying of the snsClkDivider by 2 is needed to pass the
                    * average PRS frequency through the argument.
                    */
                    lfsrSize = Input_Capsense_SsCSDCalcPrsSize(snsClkDivider << 1uL, (uint32)ptrWdgt->resolution);
                }
                lfsrScale = Input_Capsense_SsCalcLfsrScale(snsClkDivider, lfsrSize);
            #else
                /*
                * Multiplying of the snsClkDivider by 2 is needed to pass the
                * average PRS frequency through the argument.
                */
                lfsrSize = Input_Capsense_SsCSDCalcPrsSize(snsClkDivider << 1uL, (uint32)ptrWdgt->resolution);
                lfsrScale = 0u;
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
        #else
            lfsrSize = (uint8)Input_Capsense_DEFAULT_MODULATION_MODE;
            lfsrScale = 0u;
            (void)wdgtIndex; /* This parameter is unused in such configurations */
        #endif /* (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE) */

        ptrWdgt->snsClkSource = lfsrSize | (uint8)(lfsrScale << Input_Capsense_CLK_SOURCE_LFSR_SCALE_OFFSET);

        #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
            if ((Input_Capsense_WD_TOUCHPAD_E == (Input_Capsense_WD_TYPE_ENUM)Input_Capsense_dsFlash.wdgtArray[wdgtIndex].wdgtType) ||
                (Input_Capsense_WD_MATRIX_BUTTON_E == (Input_Capsense_WD_TYPE_ENUM)Input_Capsense_dsFlash.wdgtArray[wdgtIndex].wdgtType))
            {
                #if(Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE)
                    snsClkDivider = Input_Capsense_SsCSDGetRowSnsClkDivider(wdgtIndex);

                    #if(Input_Capsense_ENABLE == Input_Capsense_CSDV2)
                        lfsrSize = Input_Capsense_SsCalcLfsrSize(snsClkDivider, conversionsNum);
                        if (Input_Capsense_CLK_SOURCE_DIRECT == lfsrSize)
                        {
                            /*
                            * Multiplying of the snsClkDivider by 2 is needed to pass the
                            * average PRS frequency through the argument.
                            */
                            lfsrSize = Input_Capsense_SsCSDCalcPrsSize(snsClkDivider << 1uL, (uint32)ptrWdgt->resolution);
                        }
                        lfsrScale = Input_Capsense_SsCalcLfsrScale(snsClkDivider, lfsrSize);
                    #else
                        /*
                        * Multiplying of the snsClkDivider by 2 is needed to pass the
                        * average PRS frequency through the argument.
                        */
                        lfsrSize = Input_Capsense_SsCSDCalcPrsSize(snsClkDivider << 1uL, (uint32)ptrWdgt->resolution);
                        lfsrScale = 0u;
                    #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */
                #else
                    lfsrSize = (uint8)Input_Capsense_DEFAULT_MODULATION_MODE;
                    lfsrScale = 0u;
                #endif /* (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE) */
                ptrWdgt->rowSnsClkSource = lfsrSize | (uint8)(lfsrScale << Input_Capsense_CLK_SOURCE_LFSR_SCALE_OFFSET);
            }
        #endif /* (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN) */
    }
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) */


#if ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && (Input_Capsense_ENABLE == Input_Capsense_CSDV2))
    /*******************************************************************************
    * Function Name: Input_Capsense_SsSetWidgetTxClkSrc
    ****************************************************************************//**
    *
    * \brief
    *  Sets a source for the Tx clock for a widget.
    *
    * \param wdgtIndex
    *  Specifies the ID of the widget.
    * \param ptrWdgt
    *  The pointer to the RAM_WD_BASE_STRUCT structure.
    *
    * \details
    *  Updates snsClkSource with a source for Tx Clk for a widget.
    *
    *******************************************************************************/
    static void Input_Capsense_SsSetWidgetTxClkSrc(uint32 wdgtIndex, Input_Capsense_RAM_WD_BASE_STRUCT * ptrWdgt)
    {
        uint8 lfsrSize;
        uint8 lfsrScale;

        #if ((Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSX_TX_CLK_SOURCE) && \
             (Input_Capsense_DISABLE == Input_Capsense_CSX_SKIP_OVSMPL_SPECIFIC_NODES))
            uint32 conversionsNum;
            uint32 snsClkDivider;
        #endif

        #if(Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSX_TX_CLK_SOURCE)
            #if (Input_Capsense_DISABLE == Input_Capsense_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
                conversionsNum = (uint32)ptrWdgt->resolution;
                snsClkDivider = Input_Capsense_SsCSXGetTxClkDivider(wdgtIndex);
                lfsrSize = Input_Capsense_SsCalcLfsrSize(snsClkDivider, conversionsNum);
                lfsrScale = Input_Capsense_SsCalcLfsrScale(snsClkDivider, lfsrSize);
            #else
                lfsrSize = (uint8)Input_Capsense_CLK_SOURCE_DIRECT;
                lfsrScale = 0u;
                /* Unused function argument */
                (void)wdgtIndex;
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */
        #else
            lfsrSize = (uint8)Input_Capsense_CSX_TX_CLK_SOURCE;
            lfsrScale = 0u;
            /* Unused function argument */
            (void)wdgtIndex;
        #endif /* (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSX_TX_CLK_SOURCE) */

        ptrWdgt->snsClkSource = lfsrSize | (uint8)(lfsrScale << Input_Capsense_CLK_SOURCE_LFSR_SCALE_OFFSET);
    }
#endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && (Input_Capsense_ENABLE == Input_Capsense_CSDV2)) */


#if(((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && \
     (Input_Capsense_DISABLE == Input_Capsense_CSX_SKIP_OVSMPL_SPECIFIC_NODES) && \
     (Input_Capsense_ENABLE == Input_Capsense_CSDV2) && \
     (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSX_TX_CLK_SOURCE)) ||\
    ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) && \
     (Input_Capsense_ENABLE == Input_Capsense_CSDV2) && \
     (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE)))
/*******************************************************************************
* Function Name: Input_Capsense_SsCalcLfsrSize
****************************************************************************//**
*
* \brief
*  This is an internal function that finds a SSC polynomial size in the Auto mode.
*
* \details
*  The SSC polynomial size in the auto mode is found based on the following
*  requirements:
*  - an LFSR value should be selected so that the max clock dither is limited with +/-10%.
*  - at least one full spread spectrum polynomial should pass during the scan time.
*  - the value of the number of conversions should be an integer multiple of the
*    repeat period of the programmed LFSR_SIZE.
*
* \param
*  snsClkDivider The divider value for the sense clock.
*  resolution The widget resolution.
*
* \return lfsrSize The LFSRSIZE value for the SENSE_PERIOD register.
*
*******************************************************************************/
static uint8 Input_Capsense_SsCalcLfsrSize(uint32 snsClkDivider, uint32 conversionsNum)
{
    uint8 lfsrSize = 0u;

    /* Find LFSR value */
    if((Input_Capsense_SNSCLK_SSC4_THRESHOLD <= snsClkDivider) &&
       (Input_Capsense_SNSCLK_SSC4_PERIOD <= conversionsNum) &&
       (0uL == (conversionsNum % Input_Capsense_SNSCLK_SSC4_PERIOD)))
    {
        lfsrSize = Input_Capsense_CLK_SOURCE_SSC4;
    }
    else if((Input_Capsense_SNSCLK_SSC3_THRESHOLD <= snsClkDivider) &&
            (Input_Capsense_SNSCLK_SSC3_PERIOD <= conversionsNum) &&
            (0uL == (conversionsNum % Input_Capsense_SNSCLK_SSC3_PERIOD)))
    {
        lfsrSize = Input_Capsense_CLK_SOURCE_SSC3;
    }
    else if((Input_Capsense_SNSCLK_SSC2_THRESHOLD <= snsClkDivider) &&
            (Input_Capsense_SNSCLK_SSC2_PERIOD <= conversionsNum) &&
            (0uL == (conversionsNum % Input_Capsense_SNSCLK_SSC2_PERIOD)))
    {
        lfsrSize = Input_Capsense_CLK_SOURCE_SSC2;
    }
    else if((Input_Capsense_SNSCLK_SSC1_THRESHOLD <= snsClkDivider) &&
            (Input_Capsense_SNSCLK_SSC1_PERIOD <= conversionsNum) &&
            (0uL == (conversionsNum % Input_Capsense_SNSCLK_SSC1_PERIOD)))
    {
        lfsrSize = Input_Capsense_CLK_SOURCE_SSC1;
    }
    else
    {
        lfsrSize = (uint8)Input_Capsense_CLK_SOURCE_DIRECT;
    }

    return (lfsrSize);
}


/*******************************************************************************
* Function Name: Input_Capsense_SsCalcLfsrScale
****************************************************************************//**
*
* \brief
*  This is an internal function that calculates the LFSR scale value.
*
* \details
*  The LFSR scale value is used to increase the clock dither if the desired dither
*  is wider than can be achieved with the current Sense Clock Divider and current LFSR
*  period.
*
*  This returns the LFSR scale value needed to keep the clock dither in
*  range +/-10%.
*
* \param
*  snsClkDivider The divider value for the sense clock.
*  lfsrSize The period of the LFSR sequence.
*          For devices with Input_Capsense_CSDV2_REF9P6UA_EN = TRUE, the
*          mode parameters can take the following values:
*          Input_Capsense_CLK_SOURCE_DIRECT The spreadspectrum is not used.
*          Input_Capsense_CLK_SOURCE_SSC1   The length of LFSR sequence is 63 cycles.
*          Input_Capsense_CLK_SOURCE_SSC2   The length of LFSR sequence is 127 cycles.
*          Input_Capsense_CLK_SOURCE_SSC3   The length of LFSR sequence is 255 cycles.
*          Input_Capsense_CLK_SOURCE_SSC4   The length of LFSR sequence is 511 cycles.
*
*          For devices with Input_Capsense_CSDV2_REF9P6UA_EN = TRUE, the
*          mode parameters can take the following values:
*          Input_Capsense_CLK_SOURCE_DIRECT The spreadspectrum is not used.
*          Input_Capsense_CLK_SOURCE_SSC1   The length of LFSR sequence is 3 cycles.
*          Input_Capsense_CLK_SOURCE_SSC2   The length of LFSR sequence is 7 cycles.
*          Input_Capsense_CLK_SOURCE_SSC3   The length of LFSR sequence is 15 cycles.
*          Input_Capsense_CLK_SOURCE_SSC4   The length of LFSR sequence is 31 cycles.
*
* \return
*  Returns the LFSR scale value needed to keep the clock dither in range +/-10%.
*
*******************************************************************************/
static uint8 Input_Capsense_SsCalcLfsrScale(uint32 snsClkDivider, uint8 lfsrSize)
{
    uint32 lfsrScale;
    uint32 lfsrRange;
    uint32 lfsrDither;

    /* Initialize the lfsrSize variable with the LFSR Range for given Lfsr Size. */
    switch(lfsrSize)
    {
        case Input_Capsense_CLK_SOURCE_SSC1:
        {
            lfsrRange = Input_Capsense_SNSCLK_SSC1_RANGE;
            break;
        }
        case Input_Capsense_CLK_SOURCE_SSC2:
        {
            lfsrRange = Input_Capsense_SNSCLK_SSC2_RANGE;
            break;
        }
        case Input_Capsense_CLK_SOURCE_SSC3:
        {
            lfsrRange = Input_Capsense_SNSCLK_SSC3_RANGE;
            break;
        }
        case Input_Capsense_CLK_SOURCE_SSC4:
        {
            lfsrRange = Input_Capsense_SNSCLK_SSC4_RANGE;
            break;
        }
        default:
        {
            lfsrRange = 0u;
            break;
        }
    }

    /* Calculate the LFSR Scale value that is required to keep the Clock dither
     * as close as possible to the +/-10% limit of the used frequency.
     */
    if((lfsrSize != Input_Capsense_CLK_SOURCE_DIRECT) && (0u != lfsrRange))
    {
        /* Calculate the LFSR Dither in percents. */
        lfsrDither  = ((lfsrRange * 100uL) / snsClkDivider);
        lfsrScale = 0uL;

        while(lfsrDither < Input_Capsense_LFSR_DITHER_PERCENTAGE)
        {
            lfsrScale++;
            lfsrDither <<=1uL;
        }

        if(lfsrDither > Input_Capsense_LFSR_DITHER_PERCENTAGE)
        {
            lfsrScale--;
        }
    }
    else
    {
        lfsrScale = 0uL;
    }

    return ((uint8)lfsrScale);
}

#endif /* (((Input_Capsense_ENABLE == Input_Capsense_CSX_EN) && \
           (Input_Capsense_DISABLE == Input_Capsense_CSX_SKIP_OVSMPL_SPECIFIC_NODES) && \
           (Input_Capsense_ENABLE == Input_Capsense_CSDV2) && \
           (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSX_TX_CLK_SOURCE)) ||\
          ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) && \
           (Input_Capsense_ENABLE == Input_Capsense_CSDV2) && \
           (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE))) */


#if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)


    /*******************************************************************************
    * Function Name: Input_Capsense_SsCSDGetColSnsClkDivider
    ****************************************************************************//**
    *
    * \brief
    *  This function gets the Sense Clock Divider value for one-dimension widgets
    *  and Column Sense Clock divider value for two-dimension widgets.
    *
    * \details
    *  This function gets the Sense Clock Divider value based on the Component
    *  configuration. The function is applicable for one-dimension widgets and for
    *  two-dimension widgets.
    *
    * \param widgetId
    *  Specifies the ID of the widget.
    *
    * \return
    *  Returns the Sense Clock Divider value for one-dimension widgets
    *  and the Column Sense Clock divider value for two-dimension widgets.
    *
    *******************************************************************************/
    uint32 Input_Capsense_SsCSDGetColSnsClkDivider(uint32 widgetId)
    {
        uint32 retVal;

        /* Get sense divider based on configuration */
        #if (Input_Capsense_ENABLE != Input_Capsense_CSD_COMMON_SNS_CLK_EN)
            Input_Capsense_RAM_WD_BASE_STRUCT *ptrWdgt;

            ptrWdgt = (Input_Capsense_RAM_WD_BASE_STRUCT *)
            Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

            retVal = (uint32)(ptrWdgt->snsClk);
        #else
            retVal = (uint32)Input_Capsense_dsRam.snsCsdClk;

            (void)widgetId; /* This parameter is unused in such configurations */
        #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN) */

        return (retVal);
    }


    #if (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN)
        /*******************************************************************************
        * Function Name: Input_Capsense_SsCSDGetRowSnsClkDivider
        ****************************************************************************//**
        *
        * \brief
        *  This function gets the Sense Clock Divider value for one-dimension widgets
        *  and the Column Sense Clock divider value for two-dimension widgets.
        *
        * \details
        *  This function gets the Sense Clock Divider value based on the Component
        *  configuration. The function is applicable for one-dimension widgets and for
        *  two-dimension widgets.
        *
        * \param
        *  widgetId Specifies the ID of the widget.
        *
        * \return
        *  Returns the sense clock divider value for one-dimension widgets
        *  and column sense clock divider value for two-dimension widgets.
        *
        *******************************************************************************/
        uint32 Input_Capsense_SsCSDGetRowSnsClkDivider(uint32 widgetId)
        {
            uint32 retVal;

            /* Get sense divider based on configuration */
            #if (Input_Capsense_ENABLE != Input_Capsense_CSD_COMMON_SNS_CLK_EN)
                Input_Capsense_RAM_WD_BASE_STRUCT *ptrWdgt;

                ptrWdgt = (Input_Capsense_RAM_WD_BASE_STRUCT *)
                Input_Capsense_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

                retVal = ptrWdgt->rowSnsClk;
            #else
                retVal = (uint32)Input_Capsense_dsRam.snsCsdClk;

                (void)widgetId; /* This parameter is unused in such configurations */
            #endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_COMMON_SNS_CLK_EN) */

            return (retVal);
        }

    #endif /* (Input_Capsense_CSD_MATRIX_WIDGET_EN || Input_Capsense_CSD_TOUCHPAD_WIDGET_EN) */


    #if (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE)
        /*******************************************************************************
        * Function Name: Input_Capsense_SsCSDCalcPrsSize
        ****************************************************************************//**
        *
        * \brief
        *  The function finds PRS polynomial size in the Auto mode.
        *
        * \details
        *  The PRS polynomial size in the Auto mode is found based on the following
        *  requirements:
        *  - at least one full spread spectrum polynomial should pass during scan time.
        *
        * \param
        *  snsClkDivider The divider value for the sense clock.
        *  resolution The widget resolution.
        *
        * \return prsSize PRS value for SENSE_PERIOD register.
        *
        *******************************************************************************/
        uint8 Input_Capsense_SsCSDCalcPrsSize(uint32 snsClkDivider, uint32 resolution)
        {
            uint32 prsSize;
            uint32 modClkDivider = 1u;

            #if (Input_Capsense_ENABLE != Input_Capsense_CSDV2)
                #if(Input_Capsense_ENABLE == Input_Capsense_IS_M0S8PERI_BLOCK)
                    modClkDivider = (uint32)Input_Capsense_dsRam.modCsdClk;
                #endif

                /*
                * This operation is needed for Third-generation HW Block
                * based devices to take into account DIV-2 flip-flop.
                */
                snsClkDivider <<= 1uL;
            #endif

            if ((snsClkDivider * Input_Capsense_PRS_LENGTH_12_BITS) <= (modClkDivider * ((0x00000001Lu << resolution) - 1u)))
            {
                /* Set PRS12 mode */
                prsSize = Input_Capsense_PRS_12_CONFIG;
            }
            else if ((snsClkDivider * Input_Capsense_PRS_LENGTH_8_BITS) <= (modClkDivider * ((0x00000001Lu << resolution) - 1u)))
            {
                /* Set PRS8 mode */
                prsSize = Input_Capsense_PRS_8_CONFIG;
            }
            else
            {
                /* Set Direct clock mode */
                prsSize = Input_Capsense_CLK_SOURCE_DIRECT;
            }

            return (uint8)prsSize;
        }
    #endif /* (Input_Capsense_CLK_SOURCE_PRSAUTO == Input_Capsense_CSD_SNS_CLK_SOURCE) */
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) */


#if (Input_Capsense_ENABLE == Input_Capsense_CSDV2)
    /*******************************************************************************
    * Function Name: Input_Capsense_DischargeExtCapacitors
    ****************************************************************************//**
    *
    * \brief
    *  The internal function discharge available external capacitors.
    *
    * \details
    *  The function discharge available external capacitors by connection them
    *  to GND using STRONG GPIO drive mode. Additionaly, the function disconnects
    *  the capacitors from analog mux buses if connected.
    *  Note: the function does not restore the connection to analog mux busses
    *  and supposes that all the capacitors belong to a single device port.
    *
    * \param
    *  dischargeTime The discharge time in us.
    *
    *******************************************************************************/
    void Input_Capsense_DischargeExtCapacitors(uint32 dischargeTime)
    {
        uint32 hsiomReg;
        uint32 drReg;
        uint32 pcReg;
        uint32 newRegValue;
        uint8  interruptState;

        /* Store register state */
        hsiomReg = CY_GET_REG32(Input_Capsense_EXT_CAP_HSIOM_PTR) & Input_Capsense_EXT_CAP_HSIOM_MASK;
        drReg = CY_GET_REG32(Input_Capsense_EXT_CAP_DR_PTR) & Input_Capsense_EXT_CAP_DR_MASK;
        pcReg = CY_GET_REG32(Input_Capsense_EXT_CAP_PC_PTR) & Input_Capsense_EXT_CAP_PC_MASK;

        /* Disconnect Ext Cap from AMUXBUS-A using HSIOM registers */
        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(Input_Capsense_EXT_CAP_HSIOM_PTR);
        newRegValue &= (uint32)(~(uint32)Input_Capsense_EXT_CAP_HSIOM_MASK);
        CY_SET_REG32(Input_Capsense_EXT_CAP_HSIOM_PTR, newRegValue);
        CyExitCriticalSection(interruptState);

        /* Set output port register to 0 to connect to GND */
        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(Input_Capsense_EXT_CAP_DR_PTR);
        newRegValue &= (uint32)(~(uint32)Input_Capsense_EXT_CAP_DR_MASK);
        CY_SET_REG32(Input_Capsense_EXT_CAP_DR_PTR, newRegValue);
        CyExitCriticalSection(interruptState);

        /* Set port configuration register (drive mode) in STRONG mode */
        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(Input_Capsense_EXT_CAP_PC_PTR);
        newRegValue &= (uint32)(~((uint32)Input_Capsense_EXT_CAP_PC_MASK));
        newRegValue |= (Input_Capsense_EXT_CAP_PC_STRONG_CFG);
        CY_SET_REG32(Input_Capsense_EXT_CAP_PC_PTR, newRegValue);
        CyExitCriticalSection(interruptState);

        /* Delay to discharge external capacitors */
        CyDelayUs((uint16)dischargeTime);

        /* Restore previous register values */
        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(Input_Capsense_EXT_CAP_PC_PTR);
        newRegValue &= (uint32)(~((uint32)Input_Capsense_EXT_CAP_PC_MASK));
        newRegValue |= pcReg;
        CY_SET_REG32(Input_Capsense_EXT_CAP_PC_PTR, newRegValue);
        CyExitCriticalSection(interruptState);

        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(Input_Capsense_EXT_CAP_DR_PTR);
        newRegValue &= (uint32)(~(uint32)Input_Capsense_EXT_CAP_DR_MASK);
        newRegValue |= drReg;
        CY_SET_REG32(Input_Capsense_EXT_CAP_DR_PTR, newRegValue);
        CyExitCriticalSection(interruptState);

        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(Input_Capsense_EXT_CAP_HSIOM_PTR);
        newRegValue &= (uint32)(~(uint32)Input_Capsense_EXT_CAP_HSIOM_MASK);
        newRegValue |= hsiomReg;
        CY_SET_REG32(Input_Capsense_EXT_CAP_HSIOM_PTR, newRegValue);
        CyExitCriticalSection(interruptState);
    }

#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV2) */


#if (Input_Capsense_ENABLE == Input_Capsense_CSDV1)
    /*******************************************************************************
    * Function Name: Input_Capsense_DischargeExtCapacitors
    ****************************************************************************//**
    *
    * \brief
    *  The internal function discharge available external capacitors.
    *
    * \details
    *  The function discharge available external capacitors by connection them
    *  to GND using STRONG GPIO drive mode. Additionaly, the function disconnects
    *  the capacitors from analog mux buses if connected.
    *  Note: the function does not restore the connection to analog mux busses
    *  and supposes that all the capacitors belong to a single device port.
    *
    * \param
    *  dischargeTime The discharge time in us.
    *
    *******************************************************************************/
    void Input_Capsense_DischargeExtCapacitors(uint32 dischargeTime)
    {
        /* Store the pin configuration, the CMOD capacitor is connected to. */
        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
            uint32 cmodHsiom = CY_GET_REG32(Input_Capsense_CMOD_HSIOM_PTR) & Input_Capsense_EXT_CAP_HSIOM_MASK_CMOD;
            uint32 cmodDr = CY_GET_REG32(Input_Capsense_CMOD_DR_PTR) & Input_Capsense_EXT_CAP_DR_MASK_CMOD;
            uint32 cmodPc = CY_GET_REG32(Input_Capsense_CMOD_PC_PTR) & Input_Capsense_EXT_CAP_PC_MASK_CMOD;

            /* Store the pin configuration, the CSH capacitor is connected to. */
            #if((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) &&\
                (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN))
                uint32 cshHsiom = CY_GET_REG32(Input_Capsense_CSH_HSIOM_PTR) & Input_Capsense_EXT_CAP_HSIOM_MASK_CSH;
                uint32 cshDr = CY_GET_REG32(Input_Capsense_CSH_DR_PTR) & Input_Capsense_EXT_CAP_DR_MASK_CSH;
                uint32 cshPc = CY_GET_REG32(Input_Capsense_CSH_PC_PTR) & Input_Capsense_EXT_CAP_PC_MASK_CSH;
            #endif
        #endif

        #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
            /* Store the pin configuration, the CintA capacitor is connected to. */
            uint32 cintAHsiom = CY_GET_REG32(Input_Capsense_CintA_HSIOM_PTR) & Input_Capsense_EXT_CAP_HSIOM_MASK_CINTA;
            uint32 cintADr = CY_GET_REG32(Input_Capsense_CintA_DR_PTR) & Input_Capsense_EXT_CAP_DR_MASK_CINTA;
            uint32 cintAPc = CY_GET_REG32(Input_Capsense_CintA_PC_PTR) & Input_Capsense_EXT_CAP_PC_MASK_CINTA;

            /* Store the pin configuration, the CintB capacitor is connected to. */
            uint32 cintBHsiom = CY_GET_REG32(Input_Capsense_CintB_HSIOM_PTR) & Input_Capsense_EXT_CAP_HSIOM_MASK_CINTB;
            uint32 cintBDr = CY_GET_REG32(Input_Capsense_CintB_DR_PTR) & Input_Capsense_EXT_CAP_DR_MASK_CINTB;
            uint32 cintBPc = CY_GET_REG32(Input_Capsense_CintB_PC_PTR) & Input_Capsense_EXT_CAP_PC_MASK_CINTB;
        #endif

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
            /* Disconnect the CMOD capacitor from the AMUXBUS and connect it to GND. */
            Input_Capsense_WriteBitsSafe(Input_Capsense_CMOD_HSIOM_PTR, Input_Capsense_EXT_CAP_HSIOM_MASK_CMOD,
                                           Input_Capsense_HSIOM_SEL_GPIO);
            Input_Capsense_WriteBitsSafe(Input_Capsense_CMOD_DR_PTR, Input_Capsense_EXT_CAP_DR_MASK_CMOD, 0u);
            Input_Capsense_WriteBitsSafe(Input_Capsense_CMOD_PC_PTR, Input_Capsense_EXT_CAP_PC_MASK_CMOD,
                                           Input_Capsense_EXT_CAP_PC_STRONG_CFG_CMOD);

            #if((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) &&\
                (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN))
                /* Disconnect the CSH capacitor from the AMUXBUS and connect it to GND. */
                Input_Capsense_WriteBitsSafe(Input_Capsense_CSH_HSIOM_PTR, Input_Capsense_EXT_CAP_HSIOM_MASK_CSH,
                                               Input_Capsense_HSIOM_SEL_GPIO);
                Input_Capsense_WriteBitsSafe(Input_Capsense_CSH_DR_PTR, Input_Capsense_EXT_CAP_DR_MASK_CSH, 0u);
                Input_Capsense_WriteBitsSafe(Input_Capsense_CSH_PC_PTR, Input_Capsense_EXT_CAP_PC_MASK_CSH,
                                               Input_Capsense_EXT_CAP_PC_STRONG_CFG_CSH);
            #endif
        #endif

        #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
            /* Disconnect the CintA capacitor from the AMUXBUS and connect it to GND. */
            Input_Capsense_WriteBitsSafe(Input_Capsense_CintA_HSIOM_PTR, Input_Capsense_EXT_CAP_HSIOM_MASK_CINTA,
                                           Input_Capsense_HSIOM_SEL_GPIO);
            Input_Capsense_WriteBitsSafe(Input_Capsense_CintA_DR_PTR, Input_Capsense_EXT_CAP_DR_MASK_CINTA, 0u);
            Input_Capsense_WriteBitsSafe(Input_Capsense_CintA_PC_PTR, Input_Capsense_EXT_CAP_PC_MASK_CINTA,
                                           Input_Capsense_EXT_CAP_PC_STRONG_CFG_CINTA);

            /* Disconnect the CintB capacitor from the AMUXBUS and connect it to GND. */
            Input_Capsense_WriteBitsSafe(Input_Capsense_CintB_HSIOM_PTR, Input_Capsense_EXT_CAP_HSIOM_MASK_CINTB,
                                           Input_Capsense_HSIOM_SEL_GPIO);
            Input_Capsense_WriteBitsSafe(Input_Capsense_CintB_DR_PTR, Input_Capsense_EXT_CAP_DR_MASK_CINTB, 0u);
            Input_Capsense_WriteBitsSafe(Input_Capsense_CintB_PC_PTR, Input_Capsense_EXT_CAP_PC_MASK_CINTB,
                                           Input_Capsense_EXT_CAP_PC_STRONG_CFG_CINTB);
        #endif

        /* Delay to discharge external capacitors */
        CyDelayUs((uint16)dischargeTime);

        #if (Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
            /* Restore the pin configuration, the CMOD capacitor is connected to. */
            Input_Capsense_WriteBitsSafe(Input_Capsense_CMOD_PC_PTR,
                                           Input_Capsense_EXT_CAP_PC_MASK_CMOD, cmodPc);
            Input_Capsense_WriteBitsSafe(Input_Capsense_CMOD_DR_PTR,
                                           Input_Capsense_EXT_CAP_DR_MASK_CMOD, cmodDr);
            Input_Capsense_WriteBitsSafe(Input_Capsense_CMOD_HSIOM_PTR,
                                           Input_Capsense_EXT_CAP_HSIOM_MASK_CMOD, cmodHsiom);

            #if((Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN) &&\
                (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_TANK_EN))
                /* Restore the pin configuration, the CSH capacitor is connected to. */
                Input_Capsense_WriteBitsSafe(Input_Capsense_CSH_PC_PTR,
                                               Input_Capsense_EXT_CAP_PC_MASK_CSH, cshPc);
                Input_Capsense_WriteBitsSafe(Input_Capsense_CSH_DR_PTR,
                                               Input_Capsense_EXT_CAP_DR_MASK_CSH, cshDr);
                Input_Capsense_WriteBitsSafe(Input_Capsense_CSH_HSIOM_PTR,
                                               Input_Capsense_EXT_CAP_HSIOM_MASK_CSH, cshHsiom);
            #endif
        #endif

        #if (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
            /* Restore the pin configuration, the CintA capacitor is connected to. */
            Input_Capsense_WriteBitsSafe(Input_Capsense_CintA_PC_PTR,
                                           Input_Capsense_EXT_CAP_PC_MASK_CINTA, cintAPc);
            Input_Capsense_WriteBitsSafe(Input_Capsense_CintA_DR_PTR,
                                           Input_Capsense_EXT_CAP_DR_MASK_CINTA, cintADr);
            Input_Capsense_WriteBitsSafe(Input_Capsense_CintA_HSIOM_PTR,
                                           Input_Capsense_EXT_CAP_HSIOM_MASK_CINTA, cintAHsiom);

            /* Restore the pin configuration, the CintB capacitor is connected to. */
            Input_Capsense_WriteBitsSafe(Input_Capsense_CintB_PC_PTR,
                                           Input_Capsense_EXT_CAP_PC_MASK_CINTB, cintBPc);
            Input_Capsense_WriteBitsSafe(Input_Capsense_CintB_DR_PTR,
                                           Input_Capsense_EXT_CAP_DR_MASK_CINTB, cintBDr);
            Input_Capsense_WriteBitsSafe(Input_Capsense_CintB_HSIOM_PTR,
                                           Input_Capsense_EXT_CAP_HSIOM_MASK_CINTB, cintBHsiom);
        #endif
    }
#endif /* (Input_Capsense_ENABLE == Input_Capsense_CSDV1) */


#if((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) ||\
    (Input_Capsense_ENABLE == Input_Capsense_CSX_EN))
    /*******************************************************************************
    * Function Name: Input_Capsense_SetInactiveElectrodeState
    ****************************************************************************//**
    *
    * \brief
    *  The function updates the RAM data structure with the desired state of inactive
    *  electrodes for the specified operation mode. The state of pins is not changed
    *  in scope of this routine.
    *
    * \details
    *  The function updates the following registers of RAM data structure:
    *   - Input_Capsense_SCAN_CSD_ISC_VALUE - Connection of inactive CSD and CSX
    *     electrodes during the regular CSD scan. By default, this register is initialized
    *     with the value of Inactive Sensor Connection combobox on the CSD Settings tab.
    *     The Input_Capsense_SCAN_CSD_E value should be used as the Mode parameter
    *     to update this register.
    *
    *   - Input_Capsense_SCAN_CSX_ISC_VALUE - Connection of inactive CSD, CSX and
    *     the dedicated Shield electrodes during the regular CSX scan. By default, this
    *     register is initialized with the value of Inactive Sensor Connection combobox
    *     on the CSX Settings tab.
    *     The Input_Capsense_SCAN_CSX_E value should be used as the Mode parameter
    *     to update this register.
    *
    *   - Input_Capsense_BIST_CSD_SNS_CAP_ISC_VALUE - Connection of inactive CSD and CSX
    *     electrodes during measurement of CSD electrodes capacitance.
    *     This register is initialized with the Input_Capsense_SNS_CONNECTION_GROUND value
    *     by default.
    *     The Input_Capsense_BIST_CSD_SNS_CAP_E value should be used as the Mode parameter
    *     to update this register.
    *
    *   - Input_Capsense_BIST_CSX_SNS_CAP_ISC_VALUE - Connection of inactive CSD, CSX and
    *     the dedicated Shield electrodes during measurement of CSX electrodes (Tx and Rx)
    *     capacitance. This register is initialized with the Input_Capsense_SNS_CONNECTION_GROUND
    *     value by default.
    *     The Input_Capsense_BIST_CSX_SNS_CAP_E value should be used as the Mode parameter
    *     to update this register.
    *
    *   - Input_Capsense_BIST_CSD_SH_CAP_ISC_VALUE - Connection of inactive CSD and CSX electrodes
    *     measurement of dedicated Shield  electrodes capacitance. This register is initialized with
    *     the Input_Capsense_SNS_CONNECTION_GROUND value by default.
    *     The Input_Capsense_BIST_CSD_SH_CAP_E value should be used as the Mode parameter
    *     to update this register.
    *
    * \param
    *  mode Operation mode, the state of inactive sensors should be configured for.
    *       This parameter can take the following values:
    *        - Input_Capsense_SCAN_CSD_E - Regular CSD scan.
    *        - Input_Capsense_SCAN_CSX_E - Regular CSX scan.
    *        - Input_Capsense_BIST_CSD_SNS_CAP_E - Measurement of the CSD sensor capacitance.
    *        - Input_Capsense_BIST_CSX_SNS_CAP_E - Measurement of the CSX electrode capacitance.
    *        - Input_Capsense_BIST_CSD_SH_CAP_E - Measurement of the dedicated CSD Shield
    *          electrode capacitance.
    *
    * \param
    *  state The desired state of inactive sensors.
    *        This parameter can take the following values:
    *         - Input_Capsense_SNS_CONNECTION_GROUND - Inactive sensors are connected to the ground.
    *         - Input_Capsense_SNS_CONNECTION_HIGHZ - Inactive sensors are floating (not
    *           connected to GND or Shield).
    *         - Input_Capsense_SNS_CONNECTION_SHIELD - Inactive sensors are connected to the shield.
    *           This option is available only if the Enable shield electrode check box is set.
    *           At least one dedicated shield electrode is required to use the
    *           Input_Capsense_SNS_CONNECTION_SHIELD option for the Input_Capsense_BIST_CSD_SH_CAP_E
    *           operation mode.
    *
    * \return
    *  Returns the status of the operation:
    *  - CYRET_SUCCESS - The operation was successfully completed.
    *  - CYRET_BAD_PARAM - The input parameter is invalid.
    *
    *******************************************************************************/
    uint32_t Input_Capsense_SetInactiveElectrodeState(Input_Capsense_OPERATION_MODE_ENUM mode, uint32_t state)
    {
        uint32_t retVal = CYRET_SUCCESS;

        switch(mode)
        {
        #if(Input_Capsense_ENABLE == Input_Capsense_CSD_EN)
            case Input_Capsense_SCAN_CSD_E:
                Input_Capsense_dsRam.scanCsdISC = (uint8)state;
                break;
        #endif

        #if(Input_Capsense_ENABLE == Input_Capsense_CSX_EN)
            case Input_Capsense_SCAN_CSX_E:
                Input_Capsense_dsRam.scanCsxISC = (uint8)state;
                break;
        #endif

        #if((Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN) &&\
            (Input_Capsense_ENABLE == Input_Capsense_TST_SNS_CAP_EN) &&\
            (Input_Capsense_ENABLE == Input_Capsense_CSD_EN))
            case Input_Capsense_BIST_CSD_SNS_CAP_E:
                Input_Capsense_dsRam.selfTestConfig.bistCsdSnsCapISC = (uint8)state;
                break;
        #endif

        #if((Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN) &&\
            (Input_Capsense_ENABLE == Input_Capsense_TST_SNS_CAP_EN) &&\
            (Input_Capsense_ENABLE == Input_Capsense_CSX_EN))
            case Input_Capsense_BIST_CSX_SNS_CAP_E:
                Input_Capsense_dsRam.selfTestConfig.bistCsxSnsCapISC = (uint8)state;
                break;
        #endif

        #if((Input_Capsense_ENABLE == Input_Capsense_SELF_TEST_EN) &&\
            (Input_Capsense_ENABLE == Input_Capsense_TST_SH_CAP_EN) &&\
            (Input_Capsense_ENABLE == Input_Capsense_CSD_EN) &&\
            (Input_Capsense_ENABLE == Input_Capsense_CSD_SHIELD_EN))
            case Input_Capsense_BIST_CSD_SH_CAP_E:
                if((Input_Capsense_CSD_TOTAL_SHIELD_COUNT == 0u) &&
                   (Input_Capsense_SNS_CONNECTION_SHIELD != state))
                {
                    retVal = CYRET_BAD_PARAM;
                }
                else
                {
                    Input_Capsense_dsRam.selfTestConfig.bistCsdShCapISC = (uint8)state;
                }
                break;
        #endif

        default:
            CYASSERT(0u);
            retVal = CYRET_BAD_PARAM;
            break;
        }

        return(retVal);
    }
#endif /* ((Input_Capsense_ENABLE == Input_Capsense_CSD_EN) ||\
           (Input_Capsense_ENABLE == Input_Capsense_CSX_EN)) */


/*******************************************************************************
* Function Name: Input_Capsense_WriteBitsSafe
****************************************************************************//**
*
* \brief
*  Writes a field in port-pin register, specified by the mask parameter
*  with the specified value in critical section.
*
* \details
*  Writes a field in port-pin register, specified by the mask parameter
*  with the specified value in critical section.
*
* \param regPtr
*  Specifies a pointer to port-pin register.
*
* \param mask
*  Specifies bits to be modified.
*
* \param value
*  Specifies a value to be written to the register.
*
*******************************************************************************/
void Input_Capsense_WriteBitsSafe(reg32 * regPtr, uint32 mask, uint32 value)
{
    uint8 interruptState = CyEnterCriticalSection();
    (* regPtr) = ((* regPtr) & ((uint32)~mask)) | (value & mask);
    CyExitCriticalSection(interruptState);
}


/* [] END OF FILE */
