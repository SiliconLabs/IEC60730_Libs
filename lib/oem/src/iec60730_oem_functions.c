/***************************************************************************/ /**
 * @file iec60730_oem_functions.c
 * @brief Oem function iec60730_SafeState
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include <stdio.h>
#include "sl_udelay.h"
#include "iec60730.h"
#include "iec60730_watchdog.h"
#include "iec60730_oem_timer.h"
#include "iec60730_oem_comm.h"

sl_iec60730_test_failure_t currFailure = IEC60730_NO_FAILURE;
uint8_t err_log[60];

void iec60730_print_error(void)
{
  uint8_t number_of_failure;
  sl_iec60730_safety_check_t* iec60730_safety_check_result;

  iec60730_safety_check_result = sl_iec60730_safety_check_get_error();
  currFailure = iec60730_safety_check_result->error;
  number_of_failure = iec60730_safety_check_result->number_error;
  sprintf((char *) err_log, "Fail-Test by IEC60730_SAFETY_CHECK_FAIL. Number error: %d\n", number_of_failure);
  iec60730_commLog(err_log);
  sl_udelay_wait(5000);
  sprintf((char *) err_log, "Fail-Test by IEC60730_SAFETY_CHECK_FAIL. Error status: %d\n", currFailure);
  iec60730_commLog(err_log);
  sl_udelay_wait(5000);
}

void iec60730_SafeState(sl_iec60730_test_failure_t failure)
{
  (void) failure;
  iec60730_Timers_Disable();
  iec60730_print_error();
  IEC60730_RSTCAUSES_CLEAR();
  while (1) {
    iec60730_RestartWatchdogs();
  }
}
