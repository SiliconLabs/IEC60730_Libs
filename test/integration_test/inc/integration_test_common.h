/***************************************************************************/ /**
 * @file  integration_test_common.h
 * @brief Integration test init header
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
#ifndef INTEGRATION_TEST_COMMON_H
#define INTEGRATION_TEST_COMMON_H

#include "stdio.h"
#include "em_core.h"
#include "em_wdog.h"
#include "em_cmu.h"
#include "em_rmu.h"
#include "sl_iec60730_internal.h"

#define TEST_ENABLE  1
#define TEST_DISABLE 0

#if defined(TEST_NONSECURE_ENABLE)
#if defined(__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1)
#define TEST_WDOG_INST_NS WDOG0_NS
#define TEST_WDOG_INST0   WDOG0_NS
#define TEST_WDOG_INST1   WDOG1_NS
#endif
#define T_NVIC_SetPriorityGrouping TZ_NVIC_SetPriorityGrouping_NS
#define T_NVIC_SetPriority         TZ_NVIC_SetPriority_NS
#define T_NVIC_EnableIRQ           TZ_NVIC_EnableIRQ_NS
#else
#define TEST_WDOG_INST0            WDOG0
#define TEST_WDOG_INST1            WDOG1
#define T_NVIC_SetPriorityGrouping NVIC_SetPriorityGrouping
#define T_NVIC_SetPriority         NVIC_SetPriority
#define T_NVIC_EnableIRQ           NVIC_EnableIRQ
#endif

#define WDOG_INIT_TEST                                                         \
  {                                                                            \
      true,            /* Start watchdog when initialization is done. */       \
      false,           /* WDOG is not counting during debug halt. */           \
      false,           /* WDOG is not counting when in EM2. */                 \
      false,           /* WDOG is not counting when in EM3. */                 \
      false,           /* EM4 can be entered. */                               \
      false,           /* Do not lock WDOG configuration. */                   \
      wdogPeriod_256k, /* Set longest possible timeout period. */              \
      wdogWarnDisable, /* Disable warning interrupt. */                        \
      wdogIllegalWindowDisable, /* Disable illegal window interrupt. */        \
      false                     /* Do not disable reset. */                    \
  }

/* Function Prototype */
/* SMU configuration */
void smu_config(void);
/* NVIC configuration */
void nvic_init(void);
/* SCB non-secure configuration */
void system_init_ns(void);
/* Integration test config support */
void integration_test_clock_config(void);
void integration_test_run(void);
void integration_test_run_ns(void);
void integration_test_init(void);
void integration_test_deinit(void);

#endif // INTEGRATION_TEST_COMMON_H
