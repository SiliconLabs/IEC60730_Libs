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

#include "integration_test_common.h"

__WEAK void sl_iec60730_irq_check(void)
{
}

/* 10ms timer interrupt handler */
void TIMER0_IRQHandler(void)
{
  TIMER_IntClear(TIMER_10MS, TIMER_IF_OF);
  // Increase clock tick counter
  sl_iec60730_sys_clock_count_tick();
}

/* 100ms timer interrupt handler */
void LETIMER0_IRQHandler(void)
{
  LETIMER_IntClear(TIMER_100MS, LETIMER_IF_UF);
  sl_iec60730_test_clock_tick();
}

void integration_test_run_init(void)
{
  integration_test_init();
  integration_test_timers_init();
  integration_test_timers_enable();
  // Reset clock tick counter
  sl_iec60730_sys_clock_count_reset();
  sl_iec60730_post();
}

void integration_test_run_process_action(void)
{
  sl_iec60730_program_counter_check = IEC60730_ALL_COMPLETE_BITS;
  sl_iec60730_bist();
}
