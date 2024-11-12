/***************************************************************************/ /**
 * @file Test_irq.c
 * @brief Irq test cases
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
#include "sl_iec60730.h"
#include "oem_iec60730_timer.h"

#define IEC60730_IRQ_SIZE 8

uint16_t iec60730_programmeCounterCheck;

__no_init imcParams_t imcTest __CLASSB_RAM;
__no_init vmcParams_t vmcTest __CLASSB_RAM;

SI_SEGMENT_CONST(iec60730_IRQFreqBoundsSize, uint8_t, SI_SEG_CODE) = 8;
SI_SEGMENT_VARIABLE(iec60730_IRQExecCount[IEC60730_IRQ_SIZE],
                    uint8_t,
                    SI_SEG_DATA);
SI_SEGMENT_CONST(iec60730_IRQFreqBounds[IEC60730_IRQ_SIZE],
                 iec60730_IRQExecutionBounds_t,
                 SI_SEG_CODE) = {{.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11}};

void Test_irq(void)
{
  for (uint8_t i = 0; i < iec60730_IRQFreqBoundsSize; i++) {
    iec60730_IRQExecCount[i]++;
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

__WEAK iec60730_TestResult_t iec60730_CpuRegistersBist(void)
{
  return iec60730_TestPassed;
}

#ifndef TEST_WDOG_EN
__WEAK SI_SEGMENT_POINTER(iec60730_wdogInstance, WDOG_TypeDef, SI_SEG_DATA);

__WEAK void iec60730_RestartWatchdogs(void) {}
#endif

void integration_test_run(void)
{
  integration_test_init();
  TestTimer_Enable();
  while (1) {
    //iec60730_RestartWatchdogs();
  }
  integration_test_deinit();
}
