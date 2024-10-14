/***************************************************************************/ /**
 * @file Test_cpu_ns.c
 * @brief Watchdog test cases
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
#include "Test_System.h"
#include "iec60730.h"
#include "iec60730_oem_timer.h"
#include "iec60730_cpu_registers.h"

__no_init imcParams_t imcTest __CLASSB_RAM;
__no_init vmcParams_t vmcTest __CLASSB_RAM;

uint16_t iec60730_programmeCounterCheck = IEC60730_ALL_COMPLETE_BITS;

// Dump functions
__WEAK void iec60730_programmeCounterTest(void)
{
  if (iec60730_programmeCounterCheck) {
    iec60730_programmeCounterCheck = 0;
  }
}

__WEAK iec60730_TestResult_t iec60730_VmcBist(vmcParams_t *params)
{
  (void) params;
  return iec60730_TestPassed;
}

__WEAK iec60730_TestResult_t iec60730_ImcBist(imcParams_t *params)
{
  (void) params;
  return iec60730_TestPassed;
}

__WEAK iec60730_TestResult_t iec60730_VmcPost(vmcParams_t *params)
{
  (void) params;
  return iec60730_TestPassed;
}

__WEAK iec60730_TestResult_t iec60730_ImcPost(imcParams_t *params)
{
  (void) params;
  return iec60730_TestPassed;
}

#ifndef TEST_WDOG_EN
__WEAK SI_SEGMENT_POINTER(iec60730_wdogInstance, WDOG_TypeDef, SI_SEG_DATA);

__WEAK void iec60730_RestartWatchdogs(void) {}
#endif

void test_main_ns(void)
{
  Test_Init();

  /* For clock test */
  /* iec60730_clockTicksReset();
  iec60730_clockTestTolerance = 1;
  iec60730_systemClockToTestClockFrequency = 10;
  iec60730_timerTestControl = iec60730_TimerTestEnable;
  TestTimer_Enable(); */

  iec60730_CpuRegistersPost();

  while (1) {
    iec60730_Bist();
  }
  Test_DeInit();
}
