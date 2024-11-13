/***************************************************************************/ /**
 * @file  integration_test_common.c
 * @brief integration_test_common
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

/* Use CMSE intrinsics */
#if defined(TEST_NONSECURE_ENABLE)
#include <arm_cmse.h>
#include "partition_ARMCM33.h"
#endif
#include "integration_test_common.h"

/* TZ_START_NS: Start address of non-secure application */
#ifndef TZ_START_NS
#define TZ_START_NS (FLASH_MEM_BASE + 0x00028000U)
#endif

/* typedef for non-secure callback functions */
#if defined(TEST_NONSECURE_ENABLE)
typedef void (*funcptr_void)(void) __attribute__((cmse_nonsecure_call));
#endif

// Watchdog config
const WDOG_Init_TypeDef integration_test_wdog0_init  = WDOG_INIT_DEFAULT;
const WDOG_Init_TypeDef integration_test_wdog1_init = WDOG_INIT_DEFAULT;
// Timer config
const TIMER_Init_TypeDef integration_test_timer_10ms_config    = TIMER_INIT_TEST_10MS;
const LETIMER_Init_TypeDef integration_test_timer_100ms_config = TIMER_INIT_TEST_100MS;

void system_init_ns(void)
{
#if defined(TEST_NONSECURE_ENABLE)
#if defined(__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
  SCB_NS->VTOR = (uint32_t) TZ_START_NS;
#endif

#if defined(UNALIGNED_SUPPORT_DISABLE)
  SCB_NS->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
#endif

#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB_NS->CPACR |= ((3U << 10U * 2U)     /* set CP10 Full Access */
                    | (3U << 11U * 2U)); /* set CP11 Full Access */
#endif
#endif
}

void nvic_init(void)
{
  // One Group Priority
  NVIC_SetPriorityGrouping(7);
 /* Timer 0 */
  NVIC_SetPriority(TIMER0_IRQn, 1);
  NVIC_EnableIRQ(TIMER0_IRQn);
  /* LETIMER 0 */
  NVIC_SetPriority(LETIMER0_IRQn, 1);
  NVIC_EnableIRQ(LETIMER0_IRQn);
}

/* SMU configuration */
void smu_config(void)
{
#if defined(SMU_PRESENT) && defined(_SILICON_LABS_32B_SERIES_2)
  /* WDOG0, WDOG1 non-secure */
  SMU_S->PPUSATD0_CLR =
      (SMU_PPUSATD0_CMU | SMU_PPUSATD0_HFRCO0 | SMU_PPUSATD0_FSRCO
       | SMU_PPUSATD0_DPLL0 | SMU_PPUSATD0_LFXO | SMU_PPUSATD0_LFRCO
       | SMU_PPUSATD0_GPIO | SMU_PPUSATD0_TIMER0 | SMU_PPUSATD0_BURAM
       | SMU_PPUSATD0_GPCRC | SMU_PPUSATD0_EMU)
      & _SMU_PPUSATD0_MASK;
  /* WDOG0, WDOG1 non-secure */
  SMU_S->PPUSATD1_CLR =
      (SMU_PPUSATD1_LETIMER0 | SMU_PPUSATD1_WDOG0) & _SMU_PPUSATD1_MASK;
#if (WDOG_COUNT > 1)
  SMU_S->PPUSATD1_CLR |= SMU_PPUSATD1_WDOG1;
#endif
  /* Flash Secure region */
  SMU_S->ESAUMRB01 = 0x00020000 & _SMU_ESAUMRB01_MASK;
  /* Flash Secure - Non secure callable region */
  SMU_S->ESAUMRB12 = 0x00028000 & _SMU_ESAUMRB12_MASK;
  /* RAM Secure region */
  SMU_S->ESAUMRB45 = 0x2000A000 & _SMU_ESAUMRB45_MASK;
  /* RAM Secure - Non secure callable region */
  SMU_S->ESAUMRB56 = 0x2000C000 & _SMU_ESAUMRB56_MASK;
#endif
}

/* Function Definition */
void integration_test_init(void)
{
  integration_test_clock_config();
  nvic_init();
#if defined(_RMU_CTRL_PINRMODE_MASK)
  RMU_ResetControl(rmuResetWdog, rmuResetModeExtended);
#endif // defined(_RMU_CTRL_PINRMODE_MASK)
#if (defined(WDOG0) && (SL_IEC60730_WDOG0_ENABLE == 1))
  WDOGn_Init(SL_IEC60730_WDOG_INST(0), &integration_test_wdog0_init);
#endif
#if (defined(WDOG1) && (SL_IEC60730_WDOG1_ENABLE == 1))
  WDOGn_Init( SL_IEC60730_WDOG_INST(1), &integration_test_wdog1_init);
#endif
  CORE_ATOMIC_IRQ_ENABLE();
}

void integration_test_deinit(void)
{
  /* Disable watchdog timer */
#if (defined(WDOG0) && (SL_IEC60730_WDOG0_ENABLE == 1))
  WDOGn_Enable(SL_IEC60730_WDOG_INST(0), false);
#endif
#if (defined(WDOG1) && (SL_IEC60730_WDOG1_ENABLE == 1))
  WDOGn_Enable( SL_IEC60730_WDOG_INST(1), false);
#endif
}

/* Clock configuration */
void integration_test_clock_config(void)
{
#if (_SILICON_LABS_32B_SERIES_2_CONFIG >= 1)
  /* System clock is default FSRCO - 20Mhz */
  /* Watchdog and LETIMER clock is default LFRCO - 32Khz */
  /* FSRCO clocks for timers at fixed 20Mhz */
  CMU_ClockSelectSet(cmuClock_TIMER0, cmuSelect_FSRCO);

  CMU_ClockSelectSet(cmuClock_LETIMER0, cmuSelect_LFRCO);

#if (_SILICON_LABS_32B_SERIES_2_CONFIG > 1)
  CMU_ClockEnable(cmuClock_TIMER0, true);
  CMU_ClockEnable(cmuClock_LETIMER0, true);
  CMU_ClockEnable(cmuClock_WDOG0, true);
#if (WDOG_COUNT > 1)
  CMU_ClockEnable(cmuClock_WDOG1, true);
#endif
  CMU_ClockEnable(cmuClock_GPCRC, true);
  CMU_ClockEnable(cmuClock_BURAM, true);
  CMU_ClockEnable(cmuClock_FSRCO, true);
  CMU_ClockEnable(cmuClock_LFRCO, true);
#endif
#else
  /* System clock is default HFRCO - 19Mhz */
  /* Watchdog clock is default LFRCO - 32Khz */
  /* FSRCO clocks for timers at 19Mhz */
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_TIMER0, true);
/* Enable Low energy Peripherals clock */
#if defined(CMU_HFCORECLKEN0_LE)
  CMU_ClockEnable(cmuClock_HFLE, true);
#else
  CMU->HFBUSCLKEN0 |= (CMU_HFBUSCLKEN0_LE & _CMU_HFBUSCLKEN0_MASK);
#endif

  /* LFACLK clock is selected as LFRCO */
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);
  /* Enable clock for LETIMER0 as LFRCO - 32.768 kHz*/
  CMU_ClockEnable(cmuClock_LETIMER0, true);
  /* Enable clock of CRC */
  CMU_ClockEnable(cmuClock_GPCRC, true);
#endif
}

/* Init timer test */
void integration_test_timers_init(void) {
  /* Initialize 10ms timer */
  TIMER_Init(TIMER_10MS, &integration_test_timer_10ms_config);
  /* Initialize 10ms timer */
  LETIMER_Init(TIMER_100MS, &integration_test_timer_100ms_config);

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

/* Enable timer to test interupt */
void integration_test_timers_enable(void)
{
  // Start timer
  TIMER_Enable(TIMER_10MS, true);
  LETIMER_Enable(TIMER_100MS, true);
}

/* Disable timer to test interupt */
void integration_test_timers_disable(void)
{
  // Start timer
  TIMER_Enable(TIMER_10MS, false);
  LETIMER_Enable(TIMER_100MS, false);
}

// Dump functions
__WEAK sl_iec60730_test_result_t sl_iec60730_vmc_bist()
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t sl_iec60730_imc_bist()
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t sl_iec60730_cpu_registers_bist(void)
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t sl_iec60730_vmc_post()
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t sl_iec60730_imc_post()
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t sl_iec60730_watchdog_post(void)
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t sl_ec60730_cpu_registers_post(void)
{
  return IEC60730_TEST_PASSED;
}

/* IEC60730 safe state */
void sl_iec60730_safe_state(sl_iec60730_test_failure_t failure)
{
  printf("Fail-Test. Error status: %d\n",failure);
  LABEL_DEF(IEC60730_SAFE_STATE_BKPT);
  SL_IEC60730_RSTCAUSES_CLEAR();
  while (1) {
    sl_iec60730_restart_watchdogs();
  }
}