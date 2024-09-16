/***************************************************************************/ /**
 * @file Test_watchdog.c
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
#include "sl_iec60730_internal.h"

const WDOG_Init_TypeDef wdog1_init = WDOG_INIT_DEFAULT;
uint8_t wdog_restart_en            = 1;
volatile uint32_t wdog_por_wait    = 0;

void test_main_ns(void)
{
  // Program is waiting for debugger take control after power on reset
  // Debugger must set this flag to true
  LABEL_DEF(IEC60730_TEST_WDOG_POR_BKPT);
  while (wdog_por_wait == 0)
    ;

  Test_Init();

  iec60730_TestResult_t result = iec60730_WatchdogPost();

  LABEL_DEF(IEC60730_TEST_RESTART_WDOG_BKPT);
  while (1) {
    if (wdog_restart_en) {
      iec60730_RestartWatchdogs();
    }
  }
  Test_DeInit();
}
