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

#include "sl_iec60730_internal.h"

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_BIST
 * @{
 *****************************************************************************/

extern __no_init imcParams_t imcTest __CLASSB_RAM;
extern __no_init vmcParams_t vmcTest __CLASSB_RAM;

SI_SEGMENT_VARIABLE(iec60730_SafetyCheck,
                    iec60730_TestFailure_t,
                    SI_SEG_DATA) = iec60730_NoFailure;

void iec60730_Bist(void)
{
  iec60730_TestResult_t
      result; ///< Temporary storage of the result of each test

  result = iec60730_ImcBist(&imcTest);
  if (result == iec60730_TestFailed) {
    iec60730_SafeState(iec60730_IMCFail);
  }
  LABEL_DEF(IEC60730_IMC_BIST_END_BKPT);

  result = iec60730_VmcBist(&vmcTest);
  if (iec60730_TestFailed == result) {
    iec60730_SafeState(iec60730_VMCFail);
  }

  // CPU Register Check
  result = iec60730_CpuRegistersBist();
  if (result == iec60730_TestFailed) {
    iec60730_SafeState(iec60730_CpuRegistersFail);
  }

  LABEL_DEF(IEC60730_RESTART_WATCHDOG_BKPT);

  if (iec60730_SafetyCheck == iec60730_NoFailure) {
    // Pet the watchdog
    iec60730_RestartWatchdogs();
  } else {
    // Enter Safe State and secure the system
    iec60730_SafeState(iec60730_SafetyCheck);
  }
  return;
}

/** @} (end addtogroup IEC60730_BIST) */
/** @} (end addtogroup efr32_iec60730) */
