/***************************************************************************/ /**
 * @file
 * @brief Watchdog check
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

#include "iec60730_internal.h"

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_WDOG_Test
 * @{
 *****************************************************************************/
/**************************************************************************/ /**
 * static IEC60730 Watchdog Restart
 *
 * @returns None.
 *
 * This function abstracts the differences between the EFR32 family watchdog
 * timers.
 *****************************************************************************/
static void iec60730_RestartWatchdog(WDOG_TypeDef *wdog);

// Global variable to store Watchdog states
volatile SI_SEGMENT_VARIABLE(iec60730_WatchdogState,
                             iec60730_TestWatchdog_t,
                             SI_SEG_DATA_RETAINED_NO_CLEAR);
// Local variable to store Watchdog instance under testing
static SI_SEGMENT_VARIABLE(iec60730_WatchdogCount,
                           uint8_t,
                           SI_SEG_DATA_NO_CLEAR);

// Define Watchdog configuration
WDG_INST_DEF();

void iec60730_RestartWatchdog(WDOG_TypeDef *wdog)
{
  if (NULL == wdog) {
    return;
  }
#if (_SILICON_LABS_32B_SERIES < 2)
  // WDOG should not be fed while it is disabled.
  if (!(wdog->CTRL & WDOG_CTRL_EN)) {
    return;
  }

  // If a previous clearing is synchronized to the LF domain, there
  // is no point in waiting for it to complete before clearing over again.
  // This avoids stalling the core in the typical use case where some idle loop
  // keeps clearing WDOG.
  if (wdog->SYNCBUSY & WDOG_SYNCBUSY_CMD) {
    return;
  }
  // Before writing to the WDOG_CMD register, make sure that
  // any previous write to the WDOG_CTRL is complete.
  while ((wdog->SYNCBUSY & WDOG_SYNCBUSY_CTRL) != 0U) {}

  wdog->CMD = WDOG_CMD_CLEAR;

#else // Series 2 devices

  IEC60370_DECLARE_IRQ_STATE

  // WDOG should not be fed while it is disabled.
  if ((wdog->EN & WDOG_EN_EN) == 0U) {
    return;
  }

  // We need an atomic section around the check for sync and the clear command
  // because sending a clear command while a previous command is being synchronized
  // will cause a BusFault.
  IEC60370_ENTER_ATOMIC();
  if ((wdog->SYNCBUSY & WDOG_SYNCBUSY_CMD) == 0U) {
    wdog->CMD = WDOG_CMD_CLEAR;
  }
  IEC60370_EXIT_ATOMIC();

#endif
}

void iec60730_RestartWatchdogs(void)
{
#ifdef IEC60730_ENABLE_WDOG0
  iec60730_RestartWatchdog(IEC60730_WDOG_INST(0));
#endif
#ifdef IEC60730_ENABLE_WDOG1
  iec60730_RestartWatchdog(IEC60730_WDOG_INST(1));
#endif
}

iec60730_TestResult_t iec60730_WatchdogPost(void)
{
  iec60730_TestResult_t result = iec60730_TestFailed;
  volatile uint32_t timeOut;

  // Check for the power on reset and watchdog reset condition
  if (IEC60730_RST_POR && !IEC60730_RST_WDOGS) {
    LABEL_DEF(IEC60730_WATCHDOG_POST_POR_RESET_BKPT);
    iec60730_WatchdogCount = 0;
    // Set watchdog state to TESTING
    iec60730_WatchdogState = iec60730_WatchdogTesting;
  } else { // It's not power on reset context
    LABEL_DEF(IEC60730_WATCHDOG_POST_WORKING_BKPT);
#if defined(IEC60730_SAVE_STAGE_ENABLE) && (_SILICON_LABS_32B_SERIES == 2)
    if (IEC60730_RST_EM4) {
      iec60730_WatchdogState =
          (iec60730_TestWatchdog_t) IEC60730_BURAM_READ(IEC60730_BURAM,
                                                        IEC60730_BURAM_IDX);
    }
#endif
    if (iec60730_WatchdogState == iec60730_WatchdogTesting) {
      LABEL_DEF(IEC60730_WATCHDOG_POST_TESTING_BKPT);
      // Prevent unexpected changed value when reset or
      // return from power saving mode
      if (iec60730_WatchdogCount >= IEC60730_WDOGINST_NUMB) {
        iec60730_SafeState(iec60730_WatchdogPostFail);
      }
      // Check for the validity of the Watchdog reset reason
      if (IEC60730_RST_WDOG_CHECK(iec60730_WatchdogCount)) {
        // Next Watchdog to test
        iec60730_WatchdogCount++;

        // If all Watchdogs are tested then finish
        if (iec60730_WatchdogCount >= IEC60730_WDOGINST_NUMB) {
          iec60730_WatchdogState = iec60730_WatchdogValid;

#if defined(IEC60730_SAVE_STAGE_ENABLE) && (_SILICON_LABS_32B_SERIES == 2)
          // Write to backup ram
          IEC60730_BURAM_WRITE(IEC60730_BURAM,
                               IEC60730_BURAM_IDX,
                               iec60730_WatchdogState);
#endif

          result = iec60730_TestPassed;

// Clear reset flags of the reset causes register
#ifdef IEC60730_RSTCAUSES_CLEAR_ENABLE
          IEC60730_RSTCAUSES_CLEAR();
#endif
        }
      } else { // Watchdog reset checking failed
        iec60730_SafeState(iec60730_WatchdogPostFail);
      }
    } else { // Watchdog is not in the testing state
      // If reset causes are not POR and not Watchdog reset then no action
      if (!IEC60730_RST_POR && !IEC60730_RST_WDOGS) {
        result = iec60730_TestPassed;
      } else { // Otherwise system has failed
        iec60730_SafeState(iec60730_WatchdogPostFail);
      }
    }
  }

  if (iec60730_WatchdogState == iec60730_WatchdogTesting) {
    LABEL_DEF(IEC60730_WATCHDOG_POST_TIMEOUT_BKPT);
    // Set timeout to minimum
    IEC60730_SETWATCHDOGTIMEOUTMIN(iec60730_WatchdogCount);

    // Wait for watchdog reset
    timeOut = IEC60730_WDOG_WAIT_TIMEOUT;
    while (timeOut > 0) {
      timeOut--;
    }
    // Timeout, watchdog failed
    iec60730_SafeState(iec60730_WatchdogPostFail);
  }

  LABEL_DEF(IEC60730_WATCHDOG_POST_END_BKPT);
  return (result);
}

/** @} (end addtogroup IEC60730_WDOG_Test) */
/** @} (end addtogroup efr32_iec60730) */
