/***************************************************************************/ /**
 * @file
 * @brief Clock check
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

#include "sl_iec60730_internal.h"

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_SYSTEM_CLOCK_Test
 * @{
 *****************************************************************************/

SI_SEGMENT_VARIABLE(iec60730_systemClockToTestClockFrequency,
                    uint16_t,
                    SI_SEG_DATA)                                       = 0;
SI_SEGMENT_VARIABLE(iec60730_clockTestTolerance, uint8_t, SI_SEG_DATA) = 0;
SI_SEGMENT_VARIABLE(iec60730_systemClockCounter, uint8_t, SI_SEG_DATA) = 0;
SI_SEGMENT_VARIABLE(iec60730_timerTestControl,
                    uint8_t,
                    SI_SEG_DATA) = iec60730_TimerTestDisable;
SI_SEGMENT_VARIABLE(iec60730_timerTick, uint16_t, SI_SEG_DATA) = 0;

void iec60730_SystemClockTick(void)
{
  LABEL_DEF(IEC60730_SYSTEM_CLOCK_TICK_BKPT);
  // Increment counter, to be compared with iec60730_systemClockToTestClockFrequency
  iec60730_systemClockCounter++;
}

void iec60730_TestClockTick(void)
{
  static uint8_t test_clock_multiplier_counter = 0;
  LABEL_DEF(IEC60730_TEST_CLOCK_TICK_BKPT);
  // Only run test if OEM has enabled ISR-based IEC tests
  if (iec60730_timerTestControl == iec60730_TimerTestEnable) {
    // System clock ticks must equal OEM-configured ratio plus or minus tolerance
    if ((iec60730_systemClockCounter > (iec60730_systemClockToTestClockFrequency
                                        + iec60730_clockTestTolerance))
        || (iec60730_systemClockCounter
            < (iec60730_systemClockToTestClockFrequency
               - iec60730_clockTestTolerance))) {
      iec60730_SafetyCheck = iec60730_ClockFail;
    }
    iec60730_programmeCounterCheck |= IEC60730_CPU_CLOCKS_COMPLETE;

    iec60730_IRQCheck();

    // Increment multiplier, which runs bist frequency test at terminal value
    test_clock_multiplier_counter++;
    if (test_clock_multiplier_counter > TEST_CLOCK_MULTIPLIER) {
      iec60730_programmeCounterTest();
      test_clock_multiplier_counter = 0;
    }
  }
  iec60730_systemClockCounter = 0;
  // Increment timer tick, used for OEM testing
  iec60730_timerTick++;
}

void iec60730_clockTicksReset(void)
{
  iec60730_systemClockCounter = 0;
}

/** @} (end addtogroup IEC60730_SYSTEM_CLOCK_Test) */
/** @} (end addtogroup efr32_iec60730) */
