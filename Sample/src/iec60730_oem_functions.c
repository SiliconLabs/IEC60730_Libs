/**************************************************************************//**
 * Copyright (c) 2017 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/

#include "iec60730.h"
#include "iec60730_watchdog.h"
#include "iec60730_oem_timer.h"
#include "iec60730_oem_comm.h"

iec60730_TestFailure_t currFailure = iec60730_NoFailure;
const uint8_t err_log[] = "Fail-Test";

void iec60730_SafeState(iec60730_TestFailure_t failure) {
  iec60730_Timers_Disable();
  currFailure = failure; // Use for debug purpose
  iec60730_commLog(err_log);
  IEC60730_RSTCAUSES_CLEAR();
  while (1) {
    iec60730_RestartWatchdogs();
  }
}
