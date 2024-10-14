/***************************************************************************/ /**
 * @file
 * @brief Build In Self Test
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
 * @addtogroup IEC60730_BIST
 * @{
 *****************************************************************************/

extern __no_init imcParams_t imcTest __CLASSB_RAM;
extern __no_init vmcParams_t vmcTest __CLASSB_RAM;

static sl_iec60730_safety_check_t iec60730_safety_check = {IEC60730_NO_FAILURE,0};

void sl_iec60730_safety_check_reset_error(void)
{
  iec60730_safety_check.error = IEC60730_NO_FAILURE;
  iec60730_safety_check.number_error = 0;
}

void sl_iec60730_safety_check_error_occur(sl_iec60730_test_failure_t failure)
{
  iec60730_safety_check.error |= (1<<failure);
  iec60730_safety_check.number_error++;
}

sl_iec60730_safety_check_t* sl_iec60730_safety_check_get_error(void)
{
  sl_iec60730_safety_check_t* result = NULL;

  result = &iec60730_safety_check;

  return result;
}

void iec60730_Bist(void)
{
  sl_iec60730_test_result_t
      result; ///< Temporary storage of the result of each test

  result = iec60730_ImcBist(&imcTest);
  if (result == IEC60730_TEST_FAILED) {
    sl_iec60730_safety_check_error_occur(IEC60730_IMC_FAIL);
    iec60730_SafeState(IEC60730_IMC_FAIL);
  }
  LABEL_DEF(IEC60730_IMC_BIST_END_BKPT);

  result = iec60730_VmcBist(&vmcTest);
  if (IEC60730_TEST_FAILED == result) {
    sl_iec60730_safety_check_error_occur(IEC60730_VMC_FAIL);
    iec60730_SafeState(IEC60730_VMC_FAIL);
  }

  // CPU Register Check
  result = iec60730_CpuRegistersBist();
  if (result == IEC60730_TEST_FAILED) {
    sl_iec60730_safety_check_error_occur(IEC60730_CPU_REGISTERS_FAIL);
    iec60730_SafeState(IEC60730_CPU_REGISTERS_FAIL);
  }

  LABEL_DEF(IEC60730_RESTART_WATCHDOG_BKPT);

  if (iec60730_safety_check.number_error == IEC60730_NO_FAILURE) {
    // Pet the watchdog
    iec60730_RestartWatchdogs();
  } else {
    // Enter Safe State and secure the system
    iec60730_SafeState(IEC60730_SAFETY_CHECK_FAIL);
  }
  return;
}

/** @} (end addtogroup IEC60730_BIST) */
/** @} (end addtogroup efr32_iec60730) */
