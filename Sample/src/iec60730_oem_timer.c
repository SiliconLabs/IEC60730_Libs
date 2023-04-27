/***************************************************************************//**
 * @file iec60730_oem_timer.c
 * @brief Oem timer used for test
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

#include "iec60730.h"
#include "em_timer.h"
#include "em_letimer.h"
#include "iec60730_oem_timer.h"
#ifdef IEC60730_OS_PRESENT
#include "os.h"
#endif

//TestClock_source_t TestClock_Status = Clk_Sys;

const TIMER_Init_TypeDef Timer_10ms_cfg = TIMER_INIT_TEST_10MS;
const LETIMER_Init_TypeDef Timer_100ms_cfg = TIMER_INIT_TEST_100MS;

// Change the test clock source
//void TestClock_Switch(TestClock_source_t test_clk);
// Increase IRQ counter
void IrqTick(void);

void iec60730_Timers_Init(void) {
  /* Initialze 10ms timer */
  TIMER_Init(TIMER_10MS, &Timer_10ms_cfg);
  /* Initialze 10ms timer */
  LETIMER_Init(TIMER_100MS, &Timer_100ms_cfg);

  /* Reset counter */
  TIMER_CounterSet(TIMER_10MS, TEST_TIMER_RESET_VAL);
  LETIMER_CounterSet(TIMER_100MS, TEST_TIMER_PRESET_VAL);

  /* Set reload value */
  TIMER_TopSet(TIMER_10MS, TEST_TIMER_10MS_VAL);
  LETIMER_TopSet(TIMER_100MS, TEST_TIMER_100MS_VAL);

  /* Clear pending interrupt */
  TIMER_IntClear(TIMER_10MS, TIMER_IF_OF);
  LETIMER_IntClear(TIMER_100MS, LETIMER_IF_UF);

  /* Enable overflow interrupt */
  TIMER_IntEnable(TIMER_10MS, TIMER_IF_OF);
  LETIMER_IntEnable(TIMER_100MS, LETIMER_IEN_UF);
}

/* 10ms timer interrupt handler */
void TIMER0_IRQHandler(void) {
#ifdef IEC60730_OS_PRESENT
  OSIntEnter();
#endif
  TIMER_IntClear(TIMER_10MS, TIMER_IF_OF);

  // Signal the Bist execution
#ifndef IEC60730_OS_PRESENT
  BistCheck_Flag = true;
#endif

  // Increase clock tick counter
  iec60730_SystemClockTick();

  // Increase IRQ counter
  IrqTick();

#ifdef IEC60730_OS_PRESENT
  OSIntExit();
#endif
}

/* 100ms timer interrupt handler */
void LETIMER0_IRQHandler(void) {
#ifdef IEC60730_OS_PRESENT
  OSIntEnter();
#endif
  LETIMER_IntClear(TIMER_100MS, LETIMER_IF_UF);

#ifndef IEC60730_OS_PRESENT
  usart_Flag = true;
#endif

  // Execute clock checking
  iec60730_TestClockTick();

#ifdef IEC60730_OS_PRESENT
  OSIntExit();
#endif
}

void iec60730_Timers_Enable(void) {
  // Start timer
  TIMER_Enable(TIMER_10MS, true);
  LETIMER_Enable(TIMER_100MS, true);
}

void iec60730_Timers_Disable(void) {
  // Start timer
  TIMER_Enable(TIMER_10MS, false);
  LETIMER_Enable(TIMER_100MS, false);
}

void iec60730_TimersInit(void) {
  iec60730_Timers_Enable();
}

// Increase IRQ counter
void IrqTick(void)
{
  iec60730_IRQExecCount[0]++;
}
