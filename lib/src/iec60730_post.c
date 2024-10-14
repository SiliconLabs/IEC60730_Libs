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

#include "iec60730_internal.h"

extern __no_init imcParams_t imcTest __CLASSB_RAM;
extern __no_init vmcParams_t vmcTest __CLASSB_RAM;

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_POST
 * @{
 *****************************************************************************/

const sl_iec60730_library_version_t iec60730_library_version =
    IE60730_LIBRARY_VERSION;

void iec60730_Post(void)
{
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;

  // Watchdog check
  result = iec60730_WatchdogPost();
  if (result == IEC60730_TEST_FAILED) {
    sl_iec60730_safety_check_error_occur(IEC60730_WATCHDOG_POST_FAIL);
    iec60730_SafeState(IEC60730_WATCHDOG_POST_FAIL);
  }

  // Invariable memory check
  result = iec60730_ImcPost(&imcTest);
  if (result == IEC60730_TEST_FAILED) {
    sl_iec60730_safety_check_error_occur(IEC60730_IMC_FAIL);
    iec60730_SafeState(IEC60730_IMC_FAIL);
  }
  LABEL_DEF(IEC60730_IMC_POST_END_BKPT);

  // Variable memory check
  result = iec60730_VmcPost(&vmcTest);
  if (result == IEC60730_TEST_FAILED) {
    sl_iec60730_safety_check_error_occur(IEC60730_VMC_FAIL);
    iec60730_SafeState(IEC60730_VMC_FAIL);
  }

  // CPU registers check
  result = iec60730_CpuRegistersPost();
  if (result == IEC60730_TEST_FAILED) {
    sl_iec60730_safety_check_error_occur(IEC60730_CPU_REGISTERS_FAIL);
    iec60730_SafeState(IEC60730_CPU_REGISTERS_FAIL);
  }

  LABEL_DEF(IEC60730_SYSTEM_CLOCK_FREQ_ADJUSTMENT_BKPT);
  sl_iec60730_sys_clock_test_enable();

  iec60730_RestartWatchdogs();

  return;
}

/** @} (end addtogroup IEC60730_POST) */
/** @} (end addtogroup efr32_iec60730) */
