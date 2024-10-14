/***************************************************************************/ /**
 * @file
 * @brief Power On Self Test
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

extern __no_init imcParams_t imcTest __CLASSB_RAM;
extern __no_init vmcParams_t vmcTest __CLASSB_RAM;

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_POST
 * @{
 *****************************************************************************/

const iec60730_LibraryVersion_t iec60730_LibraryVersion =
    IE60730_LIBRARY_VERSION;

void iec60730_Post(void)
{
  iec60730_TestResult_t result = iec60730_TestFailed;

  // Watchdog check
  result = iec60730_WatchdogPost();
  if (result == iec60730_TestFailed) {
    iec60730_SafeState(iec60730_WatchdogPostFail);
  }

  // Invariable memory check
  result = iec60730_ImcPost(&imcTest);
  if (result == iec60730_TestFailed) {
    iec60730_SafeState(iec60730_IMCFail);
  }
  LABEL_DEF(IEC60730_IMC_POST_END_BKPT);

  // Variable memory check
  result = iec60730_VmcPost(&vmcTest);
  if (result == iec60730_TestFailed) {
    iec60730_SafeState(iec60730_VMCFail);
  }

  // CPU registers check
  result = iec60730_CpuRegistersPost();
  if (result == iec60730_TestFailed) {
    iec60730_SafeState(iec60730_CpuRegistersFail);
  }

  // Initialize timers for BIST testing
  iec60730_TimersInit();
  LABEL_DEF(IEC60730_SYSTEM_CLOCK_FREQ_ADJUSTMENT_BKPT);
  iec60730_timerTestControl = iec60730_TimerTestEnable;

  iec60730_RestartWatchdogs();

  return;
}

/** @} (end addtogroup IEC60730_POST) */
/** @} (end addtogroup efr32_iec60730) */
