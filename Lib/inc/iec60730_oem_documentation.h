/***************************************************************************//**
 * @file
 * @brief OEM documentation
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

// This file is a centralized location for documentation on OEM functions.
// It contains no source.

/**************************************************************************//**
 * @addtogroup efr32_iec60730
 * @{ 
 * @addtogroup IEC60730_GPIO_PLAUSIBILTY_Test
 * @{
 * @details
 * A GPIO plausibility test example is not possible with the EFR32 STK. Details
 * on functional safety with GPIOs will be included in the EFR32 IEC60730
 * application note.
 *****************************************************************************/
 
/**************************************************************************//**
 * @fn void iec60730_GpioInit()
 * @brief public IEC60730 GPIO Initialization
 * @returns None. 
 * 
 * This function configures the GPIO pins for the IEC60730 demo. 
 * @warning This function must be replaced by the OEM's own 
 * GPIO configuration routine.
 *****************************************************************************/

/**************************************************************************//**
 * @fn void iec60730_GpioCheck()
 * @brief public IEC60730 GPIO Plausibility check
 * @returns None. 
 * 
 * This function checks the state of the GPIO pins. If the pins are not
 * in the correct state, this function calls iec60730_SafeState() with 
 * #iec60730_GpioFail. This function must set #IEC60730_GPIO_COMPLETE in 
 * #iec60730_programmeCounterCheck before #iec60730_programmeCounterCheck is checked in 
 * iec60730_BistFreqTest(). 
 * @warning This function must be written by the OEM.
 *****************************************************************************/

/** @} (end addtogroup IEC60730_GPIO_PLAUSIBILTY_Test) */

/**************************************************************************//**
 * @addtogroup IEC60730_ADC_PLAUSIBILTY_Test
 * @{
 * @details
 * A ADC/ADCMUX plausibility test example is not possible with the EFR32 STK. 
 * Details on functional safety with ADC will be included in the EFR32 
 * IEC60730 application note.
 *****************************************************************************/

/**************************************************************************//**
 * @fn void iec60730_AnalogCheck()
 * @brief public IEC60730 Analog Plausibility check
 * @details This function checks the state of the Analog pins. If the pins are not
 * in the correct state, this function calls iec60730_SafeState() with 
 * #iec60730_AnalogFail. This function must set #IEC60730_ANALOG_COMPLETE in 
 * #iec60730_programmeCounterCheck before #iec60730_programmeCounterCheck is checked in 
 * iec60730_BistFreqTest(). 
 * @warning This function must be rewritten by the OEM.
 * @return None
*****************************************************************************/

/** @} (end addtogroup IEC60730_ADC_PLAUSIBILTY_Test) */

/**************************************************************************//**
 * @addtogroup IEC60730_SYSTEM_CLOCK_Test
 * @{
 *****************************************************************************/
#ifdef DOXYGEN
#define TESTCLK             ///< Test clock frequency
#define SYSCLK              ///< System clock frequency
#define IEC_TEST_TIMER_OVERFLOW_FREQUENCY       ///< Test timer overflow frequency
#define IEC_SYSTEM_TIMER_OVERFLOW_FREQUENCY     ///< System timer overflow frequency
#define IEC_TEST_TIMER_OVERFLOW                 ///< Test timer overflow count
#define IEC_SYSTEM_TIMER_OVERFLOW               ///< System timer overflow count
#else
  // Actual definitions for macros are in device-specific demo files.
#endif

/** @} (end addtogroup IEC60730_SYSTEM_CLOCK_Test) */
/** @} (end addtogroup efr32_iec60730) */

