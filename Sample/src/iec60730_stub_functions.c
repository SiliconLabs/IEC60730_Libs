/**************************************************************************//**
 * Copyright (c) 2021 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/
#include "iec60730.h"

// TODO
// This file will be removed when components are completed

#ifdef EFR32MG12P_DEVICE
__WEAK iec60730_TestResult_t iec60730_CpuRegistersPost(void) {
  return iec60730_TestPassed;
}

__WEAK iec60730_TestResult_t iec60730_CpuRegistersBist(void) {
  return iec60730_TestPassed;
}
#endif /* EFR32MG12P_DEVICE */
